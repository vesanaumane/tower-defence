#pragma once

#include <memory>

#include "iconfig.hpp"

namespace Configuration
{
    /// @brief Initialize a global config.
    /// @param config Config.
    void init( std::unique_ptr<IConfig> config );

    /// @brief Shutdown the global config.
    /// Note: NEVER call this from global constructors or destructors. Can cause hard to debug issues and crashes due to initialization order.
    void shutdown();

    /// @brief Get the global config.
    /// @return Global config.
    IConfig& get();
}