#pragma once

#include <string>


#include "iconfig.hpp"
#include "libs/toml.hpp"

namespace Configuration
{
    class TomlConfig : IConfig
    {
        public:

        explicit TomlConfig( std::string config_file_path );

        // Interface overrides.
        bool hasKey( const std::string& key ) const override;
        bool getBoolean( const std::string& key ) const override;
        float getFloat( const std::string& key ) const override;
        int getInt( const std::string& key ) const override;
        std::string getString( const std::string& key ) const override;

        ~TomlConfig() {};

        private:

        std::string m_config_file_path;
        toml::table m_config;

        void parseFile( const std::string& config_file_path );
    };
}