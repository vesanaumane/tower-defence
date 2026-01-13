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
}

bool TomlConfig::hasKey( const std::string& key ) const
{
    // at_path returns a node_view if the value exists or empty node if it does not.
    // Node object has operator bool, so we want to cast it to it. It will be true
    // if it is a non-empty node.
    return static_cast< bool >( m_config.at_path( key ) );
}

bool TomlConfig::getBoolean( const std::string& key ) const
{
    // Get the toml node from the config.
    auto node = getNode( key );

    // Get the value from the node.
    return getValueFromNode<bool>( node, key );
}

float TomlConfig::getFloat( const std::string& key ) const
{
    // Get the toml node from the config.
    auto node = getNode( key );

    // Get the value from the node.
    return getValueFromNode<float>( node, key );
}

int TomlConfig::getInt( const std::string& key ) const
{
    // Get the toml node from the config.
    auto node = getNode( key );

    // Get the value from the node.
    return getValueFromNode<int>( node, key );
}

std::string TomlConfig::getString( const std::string& key ) const
{
    // Get the toml node from the config.
    auto node = getNode( key );

    // Get the value from the node.
    return getValueFromNode<std::string>( node, key );
}

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

toml::node_view<const toml::node> TomlConfig::getNode( const std::string& key ) const
{
    // Get the node by the key.
    auto node = m_config.at_path( key );
    if( !node )
        throw ConfigKeyNotFound( key );

    return node;
}

template<typename T>
T TomlConfig::getValueFromNode( toml::node_view<const toml::node> node, const std::string& key ) const
{
    // Get the value from the node.
    auto value = node.value<T>();

    // Throw error if the value is not of correct type.
    if( !value )
    {
        // Get the type of the node. We need to get it through stream.
        std::ostringstream oss;
        oss << node.type();

        throw ConfigTypeMismatch(
            key,
            TypeName<T>::value,
            oss.str() );
    }
    return *value;
}
