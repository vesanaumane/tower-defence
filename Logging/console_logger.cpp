#include "console_logger.hpp"
#include <iostream>

using namespace Logging;

ConsoleLogger::ConsoleLogger( LogLevel maximum_log_level )
    : LoggerBase( maximum_log_level )
{
    // Nothing to do here.
}

void ConsoleLogger::logError( std::string message, bool no_prefix )
{
    // Add prefix to the message.
    if( no_prefix == false )
        prefixMessage( LogLevel::Error, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

void ConsoleLogger::logWarning( std::string message, bool no_prefix )
{
    // Add prefix to the message.
    if( no_prefix == false )
        prefixMessage( LogLevel::Warning, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

void ConsoleLogger::logInfo( std::string message, bool no_prefix )
{
    // Add prefix to the message.
    if( no_prefix == false )
        prefixMessage( LogLevel::Info, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

void ConsoleLogger::logDebug( std::string message, bool no_prefix )
{
    // Add prefix to the message.
    if( no_prefix == false )
        prefixMessage( LogLevel::Debug, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

void ConsoleLogger::logVerbose( std::string message, bool no_prefix )
{
    // Add prefix to the message.
    if( no_prefix == false )
        prefixMessage( LogLevel::Verbose, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

ConsoleLogger::~ConsoleLogger()
{
    // Nothing to delete.
}
