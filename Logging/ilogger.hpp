#pragma once

#include <string>

#include "log_level.hpp"

namespace Logging
{
    // Interface for loggers.
    class ILogger
    {
        public:

        /// @brief Log error level message.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message. Prefix contains for example date and the log level.
        virtual void logError( std::string message, bool add_prefix = true ) = 0;

        /// @brief Log warning level message.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message. Prefix contains for example date and the log level.
        virtual void logWarning( std::string message, bool add_prefix = true ) = 0;

        /// @brief Log information level message.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message. Prefix contains for example date and the log level.
        virtual void logInfo( std::string message, bool add_prefix = true ) = 0;

        /// @brief Log debug level message.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message. Prefix contains for example date and the log level.
        virtual void logDebug( std::string message, bool add_prefix = true ) = 0;

        /// @brief Log verbose level message.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message. Prefix contains for example date and the log level.
        virtual void logVerbose( std::string message, bool add_prefix = true ) = 0;

        virtual ~ILogger() {};
    };
} // namespace Logging