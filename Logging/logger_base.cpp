#include "logger_base.hpp"

#include <ctime>
#include <chrono>
#include <iomanip>

using namespace Logging;



LoggerBase::~LoggerBase()
{
    // Nothing to do here.
}

void LoggerBase::PrefixMessage( LogLevel level, std::string& message )
{
    // Get current time.
    auto now = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t( now );
    std::tm* utc_tm = std::gmtime( &time );
    if( utc_tm == nullptr )
    {
        throw std::runtime_error( "Failed to convert time_point to tm" );
    }

    // Format tm into string using stringstream and put_time.
    std::stringstream message_prefix;
    message_prefix << "["
        << std::put_time( utc_tm, "%Y-%m-%d %H:%M:%S" )
        << "]";
    if( message_prefix.fail() )
    {
        throw std::runtime_error( "Failed to format time string" );
    }

    // Add the message level part.
    switch( level )
    {
        case LogLevel::Info:
            message_prefix << " [INF]";
            break;

        case LogLevel::Debug:
            message_prefix << " [DBG]";
            break;

        case LogLevel::Verbose:
            message_prefix << " [VRB]";
            break;

        case LogLevel::Warning:
            message_prefix << " [WRN]";
            break;

        case LogLevel::Error:
            message_prefix << " [ERR]";
            break;

        default:
            message_prefix << " [NUL]";
            break;
    }

    // Add dash to separate the prefix and the actual message.
    message_prefix << " - ";

    // Add the prefix to the message.
    message = message_prefix.str().append( message );
}