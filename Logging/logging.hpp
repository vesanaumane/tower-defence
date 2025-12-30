#pragma once

#include "ilogger.hpp"
#include <memory>

/// @brief Public logging API.
namespace Logging
{
    /// @brief Initialize the global logger.
    /// Must be called once at application startup.
    /// @param logger Logger to use.
    void init( std::unique_ptr<ILogger> logger );

    /// @brief Shutdown the global logger.
    ///  Note: NEVER call this from global constructors or destructors. Can cause hard to debug issues and crashes due to initialization order.
    void shutdown();

    /// @brief Access the global logger.
    /// Must not be called before init().
    /// @return The logger.
    ILogger& get();
}