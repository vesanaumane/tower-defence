#pragma once

#include <string>

namespace Configuration
{
    enum class ConfigNodeType
    {
        Value,
        Array,
        Object
    };

    /// @brief Method to have ConfigNode type as a string.
    /// @param type Type.
    /// @return Type as a string.
    inline std::string typeToString( ConfigNodeType type )
    {
        switch( type )
        {
            case ConfigNodeType::Array:
                return "Array";
            case ConfigNodeType::Object:
                return "Object";
            case ConfigNodeType::Value:
                return "Value";
            default:
                return "Unknown type";
        }
    };
}