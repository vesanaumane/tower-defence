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

        virtual void LogInfo( std::string message ) = 0;
        virtual void LogWarning( std::string message ) = 0;
        virtual void LogError( std::string message ) = 0;
        virtual void LogDebug( std::string message ) = 0;
        virtual void LogVerbose( std::string message ) = 0;

        virtual ~ILogger() {};
    };
} // namespace Logging