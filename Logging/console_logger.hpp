#pragma once

#include "logger_base.hpp"

#include <iostream>
#include <string>
#include <map>
#include <mutex>

namespace Logging
{
    class ConsoleLogger : public LoggerBase
    {
        public:

        ConsoleLogger( LogLevel maximum_log_level );

        void logError( std::string message, bool add_prefix ) override;
        void logWarning( std::string message, bool add_prefix ) override;
        void logInfo( std::string message, bool add_prefix ) override;
        void logDebug( std::string message, bool add_prefix ) override;
        void logVerbose( std::string message, bool add_prefix ) override;

        ~ConsoleLogger();

        private:

        /// @brief Console colors.
        enum ConsoleColor
        {
            Default,
            Red,
            Yellow,
            Grey,
            Cyan
        };

        /// @brief Get the string to setup the console color.
        /// @param color Color to set.
        const char* getConsoleTextColorANSIString( ConsoleColor color );

        /// @brief Log a message to the console.
        /// @param stream Stream to write to.
        /// @param text_colour Text color in console.
        /// @param level Logging level.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message, like timestamp.
        void logMessage( std::ostream& stream, ConsoleColor text_colour, LogLevel level, std::string message, bool add_prefix );
    };
} // namespace Logging
