#pragma once

#include <string>

namespace Configuration
{
    class IConfig
    {
        public:

        /// @brief Does the configuration have the key?
        /// @param key Value key, e.g. "window.height".
        /// @return True if has.
        virtual bool hasKey( const std::string& key ) const = 0;

        /// @brief Get boolean value from the config.
        /// @param key Value key, e.g. "window.height".
        /// @return The value, throws if key not found.
        virtual bool getBoolean( const std::string& key ) const = 0;

        /// @brief Get float value from the config.
        /// @param key Value key, e.g. "window.height".
        /// @return The value, throws if key not found.
        virtual float getFloat( const std::string& key ) const = 0;

        /// @brief Get integer value from the config.
        /// @param key Value key, e.g. "window.height".
        /// @return The value, throws if key not found.
        virtual int getInt( const std::string& key ) const = 0;

        /// @brief Get string value from the config.
        /// @param key Value key, e.g. "window.height".
        /// @return The value, throws if key not found.
        virtual std::string getString( const std::string& key ) const = 0;

        virtual ~IConfig() {};
    };
}