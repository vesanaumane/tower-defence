#pragma once

#include "ilogger.hpp"

#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <functional>
#include <memory>
#include <atomic>

namespace Logging
{
    /// @brief High performance Logger with concurrent logging and log message buffer support.
    class Logger : public ILogger
    {
        public:

        /// @brief Construct the logger with another logger. Disallow implicit conversions.
        /// @param logger Logger that actually logs the messages to its target location.
        explicit Logger( std::unique_ptr<ILogger> logger );

        /// @brief Destructor. Flushes the buffer and stops the processor thread.
        virtual ~Logger();

        void logError( std::string message, bool add_prefix ) override;
        void logWarning( std::string message, bool add_prefix ) override;
        void logInfo( std::string message, bool add_prefix ) override;
        void logDebug( std::string message, bool add_prefix ) override;
        void logVerbose( std::string message, bool add_prefix ) override;

        // Prevent copying and moving. Otherwise threading, mutexes and such might get mixed.
        Logger( const Logger& ) = delete;
        Logger& operator=( const Logger& ) = delete;
        Logger( Logger&& ) = delete;
        Logger& operator=( Logger&& ) = delete;

        private:

        /// @brief Should the logger still be running.
        std::atomic<bool> m_running{ false };

        /// @brief Buffer for the messages.
        std::queue<std::function<void()>> m_buffer;

        /// @brief Mutex for modifying the buffer.
        std::mutex m_buffer_mutex;

        /// @brief Condition variable used to signal processor thread that there are items in the queue.
        std::condition_variable m_buffer_signal;

        /// @brief Thread that processes the buffer, i.e. logs the messages.
        std::thread m_buffer_processor;

        /// @brief Logger that logs the messages.
        std::unique_ptr<ILogger> m_target_logger;

        /// @brief Method for the m_buffer_processor.
        void processBuffer();

        /// @brief Log message.
        /// @param level Log level.
        /// @param message Log message.
        /// @param add_prefix Add prefix to the message.
        void logMessage( LogLevel level, std::string message, bool add_prefix );

        /// @brief Add message to the buffer.
        /// @param log_method Method to log the message. 
        void addMessageToBuffer( std::function<void()> log_method );
    };
}