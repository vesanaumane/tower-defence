#include "console_logger.hpp"
#include <iostream>

using namespace Logging;

ConsoleLogger::ConsoleLogger( LogLevel maximum_log_level )
    : LoggerBase( maximum_log_level )
{
    // Nothing to do here.
}

void ConsoleLogger::logError( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( std::cerr, ConsoleColor::Red, LogLevel::Error, message, add_prefix );
}

void ConsoleLogger::logWarning( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( std::cout, ConsoleColor::Yellow, LogLevel::Warning, message, add_prefix );
}

void ConsoleLogger::logInfo( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( std::cout, ConsoleColor::Default, LogLevel::Info, message, add_prefix );
}

void ConsoleLogger::logDebug( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( std::cout, ConsoleColor::Cyan, LogLevel::Debug, message, add_prefix );
}

void ConsoleLogger::logVerbose( std::string message, bool add_prefix )
{
    // Delegate.
    logMessage( std::cout, ConsoleColor::Grey, LogLevel::Verbose, message, add_prefix );
}

ConsoleLogger::~ConsoleLogger()
{
    // Nothing to delete.
}

const char* ConsoleLogger::getConsoleTextColorANSIString( ConsoleColor color )
{
    switch( color )
    {
        case ConsoleColor::Red:    return "\033[31m";
        case ConsoleColor::Cyan:   return "\033[36m";
        case ConsoleColor::Yellow: return "\033[33m";
        case ConsoleColor::Grey:   return "\033[90m";
        default:                   return "\033[0m";
    }
}

void ConsoleLogger::logMessage( std::ostream& stream, ConsoleColor text_color, LogLevel level, std::string message, bool add_prefix )
{
    // Check if the message should be logged at all based on the log level settings.
    if( !shouldLog( level ) )
        return;

    // Add prefix if needed.
    if( add_prefix )
        prefixMessage( level, message );

    // Log the message.
    stream
        << getConsoleTextColorANSIString( text_color )
        << message
        << getConsoleTextColorANSIString( ConsoleColor::Default ) // Reset to default.
        << '\n'; // Not using std::endl as that is slower due to flushing.
}
