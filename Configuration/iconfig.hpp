#pragma once

#include <string>
#include <memory>

#include "iconfig_node.hpp"

namespace Configuration
{
    /// @brief Config is the root node of the whole config.
    class IConfig : public IConfigNode
    {
        public:
        virtual ~IConfig() {};
    };
}