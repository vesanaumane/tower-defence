#include "logging.hpp"

#include <cassert>
#include <mutex>

namespace Logging
{
    /// @brief Anonymous namespace provides private variables (and methods) for this cpp.
    namespace
    {
        /// @brief Global logger object.
        std::unique_ptr<ILogger> g_logger;

        /// @brief Mutex to guard the g_logger. 
        std::mutex g_mutex;
    }

    void init( std::unique_ptr<ILogger> logger )
    {
        // Guard the logger.
        std::lock_guard<std::mutex> lock( g_mutex );

        // Init can be called only once.
        assert( !g_logger && "Logging::init() called twice" );

        // Save the logger.
        g_logger = std::move( logger );
    }

    ILogger& get()
    {
        // Guard the access to the logger.
        std::lock_guard<std::mutex> lock( g_mutex );

        // Init must be called before getting the logger.
        assert( g_logger && "Logging::get() called before init()" );

        // Return a reference to the logger (not a pointer).
        return *g_logger;
    }

    void shutdown()
    {
        // Guard the logger.
        std::lock_guard<std::mutex> lock( g_mutex );

        // Delete the logger.
        g_logger.reset();
    }
}