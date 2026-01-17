#pragma once

#include <memory>

#include "iconfig.hpp"

namespace Configuration
{
    void init( std::unique_ptr<IConfig> config );

    void shutdown();

    IConfig& get();
}