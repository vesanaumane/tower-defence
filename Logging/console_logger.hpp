#include "logger_base.hpp"

#include <string>

namespace Logging
{
    class ConsoleLogger : public LoggerBase
    {
        public:
        ConsoleLogger();

        void LogInfo( std::string message );
        void LogWarning( std::string message );
        void LogError( std::string message );
        void LogDebug( std::string message );
        void LogVerbose( std::string message );

        ~ConsoleLogger();
    };
} // namespace Logging
