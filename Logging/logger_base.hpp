#include "ilogger.hpp"

#include <string>

namespace Logging
{
    class LoggerBase : public ILogger
    {
        public:

        virtual void LogInfo( std::string message ) = 0;
        virtual void LogWarning( std::string message ) = 0;
        virtual void LogError( std::string message ) = 0;
        virtual void LogDebug( std::string message ) = 0;
        virtual void LogVerbose( std::string message ) = 0;

        virtual ~LoggerBase();

        protected:

        /// @brief Prefix log message with timestamp and log level information.
        /// @param level Logging level.
        /// @param message Message to which the prefix is added to.
        void PrefixMessage( LogLevel level, std::string& message );
    };
} // namespace Logging
