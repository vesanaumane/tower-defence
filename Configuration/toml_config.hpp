#pragma once

#include <string>
#include <memory>

#include "iconfig.hpp"
#include "libs/toml.hpp"
#include "toml_config_node.hpp"

namespace Configuration
{
    class TomlConfig : public IConfig
    {
        public:

        explicit TomlConfig( std::string config_file_path );

        // Interface overrides.
        ConfigNodeType type() const override;
        bool hasKey( const std::string& key ) const override;
        bool getBoolean( const std::string& key ) const override;
        float getFloat( const std::string& key ) const override;
        int getInt( const std::string& key ) const override;
        std::string getString( const std::string& key ) const override;
        bool asBoolean() const override;
        float asFloat() const override;
        int asInt() const override;
        std::string asString() const override;
        virtual std::unique_ptr<IConfigNode> getChildNode( const std::string& key ) const override;
        virtual size_t size() const override;
        virtual std::unique_ptr<IConfigNode> at( size_t index ) const override;

        ~TomlConfig() override;

        private:

        std::string m_config_file_path;
        toml::table m_config;
        std::unique_ptr<TomlConfigNode> m_root_node;

        void parseFile( const std::string& config_file_path );
    };
}