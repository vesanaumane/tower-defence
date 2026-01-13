#pragma once

#include <string>

#include "config_error.hpp"

namespace Configuration
{
    class ConfigTypeMismatch : public ConfigError
    {
        public:

        /// @brief Configuration key not found exception.
        /// @param key Key that was not found.
        explicit ConfigTypeMismatch( const std::string& key, const std::string& expected_type, const std::string& actual_type )
            : ConfigError( "Config key \'" + key + "\' expected type \'"
                + expected_type + "\' but got \'" + actual_type + "\'" ),
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

        // Key  that caused the error.
        std::string m_key;
    };
}