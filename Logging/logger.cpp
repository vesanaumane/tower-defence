#include "logger.hpp"

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>

using namespace Logging;


// Explanation of the move:
// Move ownership from the local "logger" to "m_target_logger", as we do not need the local "logger"
// anymore. This saves us a couple of atomic operations as shared pointer does not need to first increase
// and then decrease references.
// Extra note: 
// if caller does this:
// auto console_logger = std::make_shared<ConsoleLogger>();
// Logger log( console_logger );
// Then the shared pointer still has two owners, console_logger and m_target_logger.
Logger::Logger( std::unique_ptr<ILogger> logger )
    : m_target_logger( std::move( logger ) )
{
    // Create a thread that runs the processing method.
    // "Call this->processBuffer() in a new thread."
    // Note: 
    // m_buffer_processor = std::thread( processBuffer );
    // Would work, if processBuffer is static method, but then we do not have access to
    // object members.
    m_buffer_processor = std::thread( &Logger::processBuffer, this );
}

Logger::~Logger()
{
    // Stop running.
    m_running.store( false );
    m_buffer_signal.notify_all();

    // Wait until all logs are written.
    m_buffer_processor.join();
}

void Logger::logError( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Error, message, add_prefix );
}

void Logger::logWarning( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Warning, message, add_prefix );
}

void Logger::logInfo( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Info, message, add_prefix );
}

void Logger::logDebug( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Debug, message, add_prefix );
}

void Logger::logVerbose( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Verbose, message, add_prefix );
}


void Logger::processBuffer()
{
    // The logger is now running.
    m_running.store( true );

    // Run the processor until it is stopped and the queue is empty.
    while( true )
    {
        // Take the next logging task from the buffer.
        std::function<void()> task;
        {
            // Use unique_lock, instead of more simple lock_guard, since
            // condition_variable::wait() needs it. Wait needs it since
            // internally it needs to unlock and lock the mutex, which
            // lock_guard does not allow. 
            std::unique_lock<std::mutex> lock( m_buffer_mutex );

            // Sleep until there are items to process.
            // The thread exits the wait when notify_*() is called AND the predicative is true.
            // Note: the thread does not go to sleep if predicative is true.
            // I.e. State is checked BEFORE waiting and state is checked AFTER waking.
            m_buffer_signal.wait( lock, [ this ]
                {
                    // Wake up when buffer has items, or shutdown is requested.
                    return !m_buffer.empty() || !m_running.load();
                } );

            // Shutdown condition.
            if( !m_running.load() && m_buffer.empty() )
                return;

            // Get the first task from the buffer.
            task = std::move( m_buffer.front() );

            // Remove the task from the buffer. 
            m_buffer.pop();
        }

        // Run the task after releasing the lock.
        task();

    }
}

void Logger::logMessage( LogLevel level, std::string message, bool add_prefix )
{
    // Add the message logging function to the buffer.
    addMessageToBuffer(
        [ this, level, msg = std::move( message ), add_prefix ] ()
        {
            switch( level )
            {
                case Error:
                    m_target_logger->logError( msg, add_prefix );
                    break;
                case Warning:
                    m_target_logger->logWarning( msg, add_prefix );
                    break;
                case Info:
                    m_target_logger->logInfo( msg, add_prefix );
                    break;
                case Debug:
                    m_target_logger->logDebug( msg, add_prefix );
                    break;
                case Verbose:
                    m_target_logger->logVerbose( msg, add_prefix );
                    break;
                default:
                    // By default log as an error message with a note that the level is unknown.
                    std::string error_message = "Unknow Logging Level [" + std::to_string( ( int )level ) + "]! " + msg;
                    m_target_logger->logError( error_message, add_prefix );
                    break;
            }
        }
    );
}

void Logger::addMessageToBuffer( std::function<void()> log_method )
{
    // Protect buffer with mutex when adding a new log to it.
    // Mutex is released when out of scope.
    {
        std::lock_guard<std::mutex> lock( m_buffer_mutex );
        m_buffer.push( std::move( log_method ) );
    }

    // Signal logging processor that there is a new log message in the buffer.
    m_buffer_signal.notify_one();
}
