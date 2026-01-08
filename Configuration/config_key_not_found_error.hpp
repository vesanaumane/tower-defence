#pragma once

#include <string>

#include "config_error.hpp"

namespace Configuration
{
    class ConfigKeyNotFound : public ConfigError
    {
        public:

        /// @brief Configuration key not found exception.
        /// @param key Key that was not found.
        explicit ConfigKeyNotFound( const std::string& key )
            : ConfigError( "Config key not found: " + key ),
            m_key( key )
        {
        }

        /// @brief Get the key that caused the error.
        /// @return The key.
        const std::string& key() const noexcept
        {
            return m_key;
        }

        private:

        // Key that was not found.
        std::string m_key;
    };
}