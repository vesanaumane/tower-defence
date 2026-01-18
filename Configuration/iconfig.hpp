#pragma once

#include <string>
#include <memory>

#include "iconfig_node.hpp"

namespace Configuration
{
    /// @brief Config is the parent node of the whole config.
    class IConfig : public IConfigNode
    {
        public:

        /// @brief Get a child node by the key.
        /// @param key Key.
        /// @return Child node.
        //virtual const IConfigNode& operator[]( const std::string& key ) const = 0;

        virtual ~IConfig() {};
    };
}