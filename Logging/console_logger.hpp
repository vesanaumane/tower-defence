#include "logger_base.hpp"

#include <string>

namespace Logging
{
    class ConsoleLogger : public LoggerBase
    {
        public:
        ConsoleLogger( LogLevel maximum_log_level );

        void logError( std::string message, bool no_prefix );
        void logWarning( std::string message, bool no_prefix );
        void logInfo( std::string message, bool no_prefix );
        void logDebug( std::string message, bool no_prefix );
        void logVerbose( std::string message, bool no_prefix );

        ~ConsoleLogger();
    };
} // namespace Logging
