#pragma once

#include <string>

#include "iconfig_node.hpp"

namespace Configuration
{
    /// @brief Config is the parent node of the whole config.
    class IConfig : public IConfigNode
    {
        public:

        virtual ~IConfig() {};
    };
}