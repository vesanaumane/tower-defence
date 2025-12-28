#pragma once

#include "ilogger.hpp"

#include <string>

namespace Logging
{
    class LoggerBase : public ILogger
    {
        public:

        LoggerBase();
        LoggerBase( LogLevel maximum_log_level );

        virtual void logInfo( std::string message, bool add_prefix = true ) = 0;
        virtual void logWarning( std::string message, bool add_prefix = true ) = 0;
        virtual void logError( std::string message, bool add_prefix = true ) = 0;
        virtual void logDebug( std::string message, bool add_prefix = true ) = 0;
        virtual void logVerbose( std::string message, bool add_prefix = true ) = 0;

        virtual ~LoggerBase();

        protected:

        /// @brief Prefix log message with timestamp and log level information.
        /// @param level Logging level.
        /// @param message Message to which the prefix is added to.
        void prefixMessage( LogLevel level, std::string& message );

        /// @brief Should the message be logged or not based on the log level.
        /// @return true if the message should be logged.
        bool shouldLog( LogLevel log_level );

        private:

        LogLevel m_max_level;
    };
} // namespace Logging
