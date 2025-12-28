#include "multi_logger.hpp"

using namespace Logging;

MultiLogger::MultiLogger()
    : LoggerBase()
{
    // Initialize the container for loggers.
    m_loggers = std::vector< ILogger* >();
}

MultiLogger::~MultiLogger()
{
    // Delete all loggers.
    for( ILogger* logger : m_loggers )
    {
        delete logger;
    }
}

void MultiLogger::add( ILogger* log )
{
    m_loggers.push_back( log );
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
    for( ILogger* logger : m_loggers )
    {
        // Do not add prefix again to the message.
        logger->logInfo( message, false );
    }
}
