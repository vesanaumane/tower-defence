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

        virtual ~LoggerBase();

        protected:

        /// @brief Get the current time's time stamp.
        /// @return Time now in format 
        std::string getCurrentTimestamp();

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
