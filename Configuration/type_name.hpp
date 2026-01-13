#pragma once

#include <string>

namespace Configuration
{
    template<typename T>
    struct TypeName;

    template<>
    struct TypeName<bool>
    {
        static constexpr const char* value = "boolean";
    };

    template<>
    struct TypeName<int>
    {
        static constexpr const char* value = "integer";
    };

    template<>
    struct TypeName<int64_t>
    {
        static constexpr const char* value = "int64";
    };

    template<>
    struct TypeName<float>
    {
        static constexpr const char* value = "float";
    };

    template<>
    struct TypeName<double>
    {
        static constexpr const char* value = "double";
    };

    template<>
    struct TypeName<std::string>
    {
        static constexpr const char* value = "string";
    };
}