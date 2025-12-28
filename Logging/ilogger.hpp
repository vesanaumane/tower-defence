#include <string>

namespace Logging
{

    // Logging levels.
    enum LogLevel
    {
        Info,
        Debug,
        Verbose,
        Warning,
        Error
    };

    // Interface for loggers.
    class ILogger
    {
        public:

        virtual void LogInfo( std::string message ) = 0;
        virtual void LogWarning( std::string message ) = 0;
        virtual void LogError( std::string message ) = 0;
        virtual void LogDebug( std::string message ) = 0;
        virtual void LogVerbose( std::string message ) = 0;

        virtual ~ILogger() {};
    };
} // namespace Logging