#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

namespace Configuration
{
    /// @brief By leaving undefined forces explicit specialization per enum that want to be used in the config.
    /// @tparam Enum 
    template<typename Enum>
    struct EnumTraits;
}