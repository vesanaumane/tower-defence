#include "multi_logger.hpp"

#include <memory>

using namespace Logging;

MultiLogger::MultiLogger()
    : LoggerBase(), m_loggers()
{
    // Nothing to do here.
}

MultiLogger::~MultiLogger()
{
    // Nothing to do here.
}

void MultiLogger::add( std::unique_ptr<ILogger> log )
{
    m_loggers.push_back( std::move( log ) );
}

void MultiLogger::logError( std::string message, bool add_prefix )
{
    logMessage( LogLevel::Error, message, add_prefix );
}

void MultiLogger::logWarning( std::string message, bool add_prefix )
{
    logMessage( LogLevel::Warning, message, add_prefix );
}

void MultiLogger::logInfo( std::string message, bool add_prefix )
{
    logMessage( LogLevel::Info, message, add_prefix );
}

void MultiLogger::logDebug( std::string message, bool add_prefix )
{
    logMessage( LogLevel::Debug, message, add_prefix );
}

void MultiLogger::logVerbose( std::string message, bool add_prefix )
{
    logMessage( LogLevel::Verbose, message, add_prefix );
}

void MultiLogger::logMessage( LogLevel level, std::string& message, bool add_prefix )
{
    // Add prefix if wanted. We want to create the prefix here
    // so that every log has the same timestamp in the prefix.
    if( add_prefix )
        prefixMessage( level, message );

    // Call all loggers.
    for( const auto& logger : m_loggers )
    {
        // Do not add prefix again to the message.
        switch( level )
        {
            case Error:
                logger->logError( message, false );
                break;
            case Warning:
                logger->logWarning( message, false );
                break;
            case Info:
                logger->logInfo( message, false );
                break;
            case Debug:
                logger->logDebug( message, false );
                break;
            case Verbose:
                logger->logVerbose( message, false );
                break;
            default:
                // By default log as an error message with a note that the level is unknown.
                std::string error_message = "Unknow Logging Level [" + std::to_string( ( int )level ) + "]! " + message;
                logger->logError( error_message, false );
                break;
        }
    }
}
