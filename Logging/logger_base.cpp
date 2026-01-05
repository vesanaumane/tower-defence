#include "logger_base.hpp"

#include <ctime>
#include <chrono>
#include <iomanip>

using namespace Logging;



Logging::LoggerBase::LoggerBase()
{
    // Set max log level to verbose.
    m_max_level = LogLevel::Verbose;
}

Logging::LoggerBase::LoggerBase( LogLevel maximum_log_level )
{
    m_max_level = maximum_log_level;
}

LoggerBase::~LoggerBase()
{
    // Nothing to do here.
}

std::string LoggerBase::getCurrentTimestamp()
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
    std::stringstream time_str;
    time_str << std::put_time( utc_tm, "%Y-%m-%d %H:%M:%S" );
    if( time_str.fail() )
    {
        throw std::runtime_error( "Failed to format time string" );
    }

    return time_str.str();
}

void LoggerBase::prefixMessage( LogLevel level, std::string& message )
{
    // Add timestamp to the prefix.
    std::stringstream message_prefix;
    message_prefix << "["
        << getCurrentTimestamp()
        << "]";

    // Add the message level part to the prefix.
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

    // Add a dash to separate the prefix and the actual message.
    message_prefix << " - ";

    // Add the prefix to the message.
    message = message_prefix.str().append( message );
}

bool LoggerBase::shouldLog( LogLevel log_level )
{
    return log_level <= m_max_level;
}
