#pragma once

#include "logger_base.hpp"

#include <string>
#include <fstream>

namespace Logging
{
    /// @brief Logs to a file. Note: This logger is not thread safe.
    class FileLogger : public LoggerBase
    {
        public:

        FileLogger( LogLevel maximum_log_level, bool enabled, const std::string& file_path );

        void logError( std::string message, bool add_prefix ) override;
        void logWarning( std::string message, bool add_prefix ) override;
        void logInfo( std::string message, bool add_prefix ) override;
        void logDebug( std::string message, bool add_prefix ) override;
        void logVerbose( std::string message, bool add_prefix ) override;

        ~FileLogger();

        private:

        /// @brief Log file path.
        const std::string m_file_path;

        /// @brief Log file stream.
        std::ofstream m_file;

        /// @brief Has the file been initialized.
        bool m_initialized;

        /// @brief Initialize the log file.
        void initialize();

        /// @brief Log a message to a file.
        /// @param level Logging level.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message, like timestamp.
        void logMessage( LogLevel level, std::string message, bool add_prefix );
    };
} // namespace Logging
