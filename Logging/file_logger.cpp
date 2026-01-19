#include "file_logger.hpp"

#include <string>
#include <stdexcept>
#include <fstream>
#include <filesystem>

using namespace Logging;

FileLogger::FileLogger( LogLevel maximum_log_level, bool enabled, const std::string& file_path )
    : LoggerBase( maximum_log_level, enabled ), m_file_path( file_path ), m_initialized( false )
{
    if( isEnabled() )
        initialize();
}

void FileLogger::logError( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Error, message, add_prefix );
}

void FileLogger::logWarning( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Warning, message, add_prefix );
}

void FileLogger::logInfo( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Info, message, add_prefix );
}

void FileLogger::logDebug( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Debug, message, add_prefix );
}

void FileLogger::logVerbose( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( LogLevel::Verbose, message, add_prefix );
}

FileLogger::~FileLogger()
{
    // The file stream closes itself.
}

void Logging::FileLogger::initialize()
{
    // No need to initialize twice.
    if( m_initialized )
        return;

    // Create the directories for the file if those do not exist yet.
    std::filesystem::path path( m_file_path );
    if( path.has_parent_path() )
    {
        try
        {
            std::filesystem::create_directories( path.parent_path() );
        }
        catch( const std::filesystem::filesystem_error& e )
        {
            throw std::runtime_error(
                "Failed to create log directory: " + path.parent_path().string()
            );
        }
    }

    // Open the file in append mode, this will create the file if it does not exist.
    m_file.open( m_file_path, std::ios::app );
    if( !m_file.is_open() )
    {
        throw std::runtime_error(
            "Failed to open log file: " + m_file_path
        );
    }

    // Log a header to the file to mark the starting time.
    m_file << "****************************************\n"
        << "*                Start\n"
        << "*         " << getCurrentTimestamp() << "\n"
        << "****************************************\n";

    m_initialized = true;
}

void FileLogger::logMessage( LogLevel level, std::string message, bool add_prefix )
{
    // Check if the message should be logged at all based on the log level settings.
    if( !shouldLog( level ) )
        return;

    // Initialize the log file if not yet done.
    if( !m_initialized )
        initialize();

    // Add prefix if wanted.
    if( add_prefix )
        prefixMessage( level, message );

    // Write the log.
    m_file << message << '\n';

    // Flush on error messages for error messages to appear in log files faster.
    if( level == LogLevel::Error )
        m_file.flush();
}
