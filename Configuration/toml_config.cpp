#include <sstream>

#include "toml_config.hpp"
#include "config_error.hpp"
#include "config_key_not_found_error.hpp"
#include "config_type_mismatch_error.hpp"
#include "type_name.hpp"

using namespace Configuration;

TomlConfig::TomlConfig( std::string config_file_path )
    : m_config_file_path( std::move( config_file_path ) )
{
    // Parse the toml-file.
    parseFile( m_config_file_path );

    // Set the root node.
    m_root_node = std::make_unique<TomlConfigNode>( toml::node_view<const toml::node>( m_config ) );
}

ConfigNodeType Configuration::TomlConfig::type() const
{
    return m_root_node->type();
}

bool TomlConfig::hasKey( const std::string& key ) const
{
    return m_root_node->hasKey( key );
}

bool TomlConfig::getBoolean( const std::string& key ) const
{
    return m_root_node->getBoolean( key );
}

float TomlConfig::getFloat( const std::string& key ) const
{
    return m_root_node->getFloat( key );
}

int TomlConfig::getInt( const std::string& key ) const
{
    return m_root_node->getInt( key );
}

std::string TomlConfig::getString( const std::string& key ) const
{
    return m_root_node->getString( key );
}

bool TomlConfig::asBoolean() const
{
    return m_root_node->asBoolean();
}

float TomlConfig::asFloat() const
{
    return m_root_node->asFloat();
}

int Configuration::TomlConfig::asInt() const
{
    return m_root_node->asInt();
}

std::string Configuration::TomlConfig::asString() const
{
    return m_root_node->asString();
}

IConfigNode& TomlConfig::getChildNode( const std::string& key ) const
{
    return m_root_node->getChildNode( key );
}

size_t TomlConfig::size() const
{
    return m_root_node->size();
}

IConfigNode& TomlConfig::at( size_t index ) const
{
    return m_root_node->at( index );
}

TomlConfig::~TomlConfig() = default;

void TomlConfig::parseFile( const std::string& config_file_path )
{
    try
    {
        m_config = toml::parse_file( config_file_path );
    }
    catch( const toml::parse_error& err )
    {
        // Wrap error to ConfigError.
        std::string error_message = "Parsing config file \'" + config_file_path + "\' failed:\n" + err.what();
        throw ConfigError( error_message );
    }
}
