#include <memory>

#include "toml_config_node.hpp"
#include "config_key_not_found_error.hpp"
#include "config_type_mismatch_error.hpp"

using namespace Configuration;

TomlConfigNode::TomlConfigNode( toml::node_view<const toml::node> node )
    : m_node( node )
{
}

ConfigNodeType TomlConfigNode::type() const
{
    // Map toml types to ConfigNodeType
    if( m_node.is_table() ) return ConfigNodeType::Object;
    if( m_node.is_array() ) return ConfigNodeType::Array;

    // By default node is of Value type.
    return ConfigNodeType::Value;
}

bool TomlConfigNode::hasKey( const std::string& key ) const
{
    // at_path returns a node_view if the value exists or empty node if it does not.
    // Node object has operator bool, so we want to cast it to it. It will be true
    // if it is a non-empty node.
    return static_cast< bool >( m_node.at_path( key ) );
}

bool TomlConfigNode::getBoolean( const std::string& key ) const
{
    // Get the value from the node.
    return getValueFromNode<bool>( m_node, key );
}

float TomlConfigNode::getFloat( const std::string& key ) const
{
    // Get the value from the node.
    return getValueFromNode<float>( m_node, key );
}

int TomlConfigNode::getInt( const std::string& key ) const
{
    // Get the value from the node.
    return getValueFromNode<int>( m_node, key );
}

std::string TomlConfigNode::getString( const std::string& key ) const
{
    // Get the value from the node.
    return getValueFromNode<std::string>( m_node, key );
}

bool Configuration::TomlConfigNode::asBoolean() const
{
    assertNodeTypeForValueConversion( "bool" );
    return getValueFromNode<bool>( m_node, "" );
}

float Configuration::TomlConfigNode::asFloat() const
{
    assertNodeTypeForValueConversion( "float" );
    return getValueFromNode<float>( m_node, "" );
}

int Configuration::TomlConfigNode::asInt() const
{
    assertNodeTypeForValueConversion( "integer" );
    return getValueFromNode<int>( m_node, "" );
}

std::string Configuration::TomlConfigNode::asString() const
{
    assertNodeTypeForValueConversion( "string" );
    return getValueFromNode<std::string>( m_node, "" );
}

std::unique_ptr<IConfigNode> TomlConfigNode::getChildNode( const std::string& key ) const
{
    // Get the node by the key.
    auto node = m_node.at_path( key );
    if( !node )
        throw ConfigKeyNotFound( key );

    // Wrap it to TomlConfig.
    return std::make_unique<TomlConfigNode>( node );
}

size_t TomlConfigNode::size() const
{
    if( m_node.is_array() )
        return m_node.as_array()->size();

    if( m_node.is_table() )
        return m_node.as_table()->size();

    return 0;
}

std::unique_ptr<IConfigNode> TomlConfigNode::at( size_t index ) const
{
    // At can only be called for arrays.
    if( type() != ConfigNodeType::Array )
    {
        throw ConfigError( "Method \'at\' is only valid for arrays. Node type is" + typeToString( type() ) );
    }

    // Cannot index over size.
    if( size() <= index )
    {
        throw ConfigError(
            "Array index cannot be bigger than the array size. Expected <= "
            + std::to_string( size() )
            + " but was "
            + std::to_string( index ) );
    }

    // Get the toml node for the array item.
    auto child = toml::node_view<const toml::node>(
        m_node.as_array()->at( index )
    );

    // Wrap it to TomlConfig.
    return std::make_unique<TomlConfigNode>( child );
}

void Configuration::TomlConfigNode::assertNodeTypeForValueConversion( const std::string& target_value_type ) const
{
    // Only valid node type for value conversions is Value.
    if( type() != ConfigNodeType::Value )
    {
        throw ConfigError( "Cannot convert " + Configuration::typeToString( type() ) + " to " + target_value_type + "." );
    }
}
