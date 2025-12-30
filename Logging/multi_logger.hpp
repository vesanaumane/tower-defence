#pragma once

#include "logger_base.hpp"

#include <vector>
#include <memory>

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
        void add( std::unique_ptr<ILogger> log );

        void logError( std::string message, bool add_prefix ) override;
        void logWarning( std::string message, bool add_prefix ) override;
        void logInfo( std::string message, bool add_prefix ) override;
        void logDebug( std::string message, bool add_prefix ) override;
        void logVerbose( std::string message, bool add_prefix ) override;

        ~MultiLogger();

        private:

        /// @brief Target loggers.
        std::vector<std::unique_ptr<ILogger>> m_loggers;

        /// @brief Log message.
        /// @param level Log level.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message.
        void logMessage( LogLevel level, std::string& message, bool add_prefix = true );

    };
}