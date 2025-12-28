#include <string>

namespace Logging
{

    // Logging levels.
    enum LogLevel
    {
        Error = 0,
        Warning = 1,
        Info = 2,
        Debug = 3,
        Verbose = 4
    };

    // Interface for loggers.
    class ILogger
    {
        public:

        /// @brief Log error level message.
        /// @param message Log message.
        /// @param no_prefix Do not add prefix to the message. Prefix contains for example date and the log level.
        virtual void logError( std::string message, bool no_prefix ) = 0;

        /// @brief Log warning level message.
        /// @param message Log message.
        /// @param no_prefix Do not add prefix to the message. Prefix contains for example date and the log level.
        virtual void logWarning( std::string message, bool no_prefix ) = 0;

        /// @brief Log information level message.
        /// @param message Log message.
        /// @param no_prefix Do not add prefix to the message. Prefix contains for example date and the log level.
        virtual void logInfo( std::string message, bool no_prefix ) = 0;

        /// @brief Log debug level message.
        /// @param message Log message.
        /// @param no_prefix Do not add prefix to the message. Prefix contains for example date and the log level.
        virtual void logDebug( std::string message, bool no_prefix ) = 0;

        /// @brief Log verbose level message.
        /// @param message Log message.
        /// @param no_prefix Do not add prefix to the message. Prefix contains for example date and the log level.
        virtual void logVerbose( std::string message, bool no_prefix ) = 0;

        virtual ~ILogger() {};
    };
} // namespace Logging