#pragma once

#include "logger_base.hpp"

#include <string>

namespace Logging
{
    class ConsoleLogger : public LoggerBase
    {
        public:

        ConsoleLogger( LogLevel maximum_log_level );

        void logError( std::string message, bool add_prefix ) override;
        void logWarning( std::string message, bool add_prefix ) override;
        void logInfo( std::string message, bool add_prefix ) override;
        void logDebug( std::string message, bool add_prefix ) override;
        void logVerbose( std::string message, bool add_prefix ) override;

        ~ConsoleLogger();
    };
} // namespace Logging
