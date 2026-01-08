#pragma once

#include <stdexcept>
#include <string>

namespace Configuration
{
    class ConfigError : public std::runtime_error
    {
        public:

        /// @brief General configuration error.
        /// @param message Error message.
        explicit ConfigError( const std::string& message )
            : std::runtime_error( message ) {}
    };
}
