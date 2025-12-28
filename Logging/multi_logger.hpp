#pragma once

#include "logger_base.hpp"

#include <vector>

namespace Logging
{
    /// @brief Logger that will log to multiple logs.
    class MultiLogger : public LoggerBase
    {
        public:

        /// @brief Constuctor.
        MultiLogger();

        /// @brief Add a new target log.
        /// @param log A log to log to.
        void add( ILogger* log );

        void logError( std::string message, bool add_prefix = true );
        void logWarning( std::string message, bool add_prefix = true );
        void logInfo( std::string message, bool add_prefix = true );
        void logDebug( std::string message, bool add_prefix = true );
        void logVerbose( std::string message, bool add_prefix = true );

        ~MultiLogger();

        private:

        /// @brief Target loggers.
        std::vector< ILogger* > m_loggers;

        /// @brief Log message.
        /// @param level Log level.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message.
        void logMessage( LogLevel level, std::string& message, bool add_prefix = true );

    };
}