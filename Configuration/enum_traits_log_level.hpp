#pragma once

#include "enum_traits.hpp"
#include "../Logging/log_level.hpp"

namespace Configuration
{
    template<>
    struct EnumTraits<Logging::LogLevel>
    {
        static constexpr const char* name = "LogLevel";

        static const std::unordered_map<std::string, Logging::LogLevel>& map()
        {
            static const std::unordered_map<std::string, Logging::LogLevel> mapping{
                { "Error",   Logging::LogLevel::Error },
                { "Warning", Logging::LogLevel::Warning },
                { "Info",    Logging::LogLevel::Info },
                { "Debug",   Logging::LogLevel::Debug },
                { "Verbose", Logging::LogLevel::Verbose }
            };
            return mapping;
        }
    };
}