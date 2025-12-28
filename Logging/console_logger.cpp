#include "console_logger.hpp"
#include <iostream>

using namespace Logging;

ConsoleLogger::ConsoleLogger()
{
    // Nothing to do here.
}

void ConsoleLogger::LogInfo( std::string message )
{
    // Add prefix to the message.
    PrefixMessage( LogLevel::Info, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

void ConsoleLogger::LogWarning( std::string message )
{
    // Add prefix to the message.
    PrefixMessage( LogLevel::Warning, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

void ConsoleLogger::LogError( std::string message )
{
    // Add prefix to the message.
    PrefixMessage( LogLevel::Error, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

void ConsoleLogger::LogDebug( std::string message )
{
    // Add prefix to the message.
    PrefixMessage( LogLevel::Debug, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

void ConsoleLogger::LogVerbose( std::string message )
{
    // Add prefix to the message.
    PrefixMessage( LogLevel::Verbose, message );

    // Print to standard stream.
    std::cout << message << std::endl;
}

ConsoleLogger::~ConsoleLogger()
{
    // Nothing to delete.
}
