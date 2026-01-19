#pragma once

#include <string>
#include <memory>
#include "config_error.hpp"

namespace Configuration
{
    enum class ConfigNodeType
    {
        Value,
        Array,
        Object
    };

    /// @brief Method to have ConfigNode type as a string.
    /// @param type Type.
    /// @return Type as a string.
    inline std::string typeToString( ConfigNodeType type )
    {
        switch( type )
        {
            case ConfigNodeType::Array:
                return "Array";
            case ConfigNodeType::Object:
                return "Object";
            case ConfigNodeType::Value:
                return "Value";
            default:
                return "Unknown type";
        }
    };

    class IConfigNode
    {
        public:

        /// @brief Get the type of this node.
        virtual ConfigNodeType type() const = 0;

        /// @brief Does the node have the key?
        /// @param key Value key, e.g. "window.height".
        /// @return True if has.
        virtual bool hasKey( const std::string& key ) const = 0;

        /// @brief Get boolean value from the current node.
        /// @param key Value key, e.g. "window.height".
        /// @return The value, throws if key not found.
        virtual bool getBoolean( const std::string& key ) const = 0;

        /// @brief Get float value from the current node.
        /// @param key Value key, e.g. "window.height".
        /// @return The value, throws if key not found.
        virtual float getFloat( const std::string& key ) const = 0;

        /// @brief Get integer value from the current node.
        /// @param key Value key, e.g. "window.height".
        /// @return The value, throws if key not found.
        virtual int getInt( const std::string& key ) const = 0;

        /// @brief Get string value from the current node.
        /// @param key Value key, e.g. "window.height".
        /// @return The value, throws if key not found.
        virtual std::string getString( const std::string& key ) const = 0;

        /// @brief Get current node as boolean value. Only for nodes of type Value.
        /// @return The value, throws if node is of wrong type or the value type is not correct.
        virtual bool asBoolean() const = 0;

        /// @brief Get current node as float value. Only for nodes of type Value.
        /// @return The value, throws if node is of wrong type or the value type is not correct.
        virtual float asFloat() const = 0;

        /// @brief Get current node as integer value. Only for nodes of type Value.
        /// @return The value, throws if node is of wrong type or the value type is not correct.
        virtual int asInt() const = 0;

        /// @brief Get current node as string value. Only for nodes of type Value.
        /// @return The value, throws if node is of wrong type or the value type is not correct.
        virtual std::string asString() const = 0;

        /// @brief Get a child node.
        /// @param key Node key, e.g. "loggers"
        /// @return Child node.
        virtual IConfigNode& getChildNode( const std::string& key ) const = 0;

        /// @brief If type is Array, the size of the Array.
        /// @return Array length.
        virtual size_t size() const = 0;

        /// @brief If type is Array, access an item.
        /// @param index Item index.
        /// @return ConfigNode in the index.
        virtual IConfigNode& at( size_t index ) const = 0;

        virtual ~IConfigNode() {};

        /// @brief Iterator support for array types.
        class Iterator
        {
            public:
            Iterator( const IConfigNode& node, size_t index ) : m_node( node ), m_index( index ) {}

            IConfigNode& operator*() const { return m_node.at( m_index ); }
            Iterator& operator++()
            {
                ++m_index;
                return *this;
            }

            bool operator!=( const Iterator& other ) const { return m_index != other.m_index; }

            private:
            const IConfigNode& m_node;
            size_t m_index;
        };

        /// @brief Begin iterator.
        /// @return Iterator pointing to the first item of the array.
        Iterator begin() const
        {
            if( type() != ConfigNodeType::Array )
                throw ConfigError( "Cannot use iterators with node of type " + Configuration::typeToString( type() ) );

            return Iterator( *this, 0 );
        }

        /// @brief End iterator.
        /// @return Iterator pointing to the end of the array.
        Iterator end() const
        {
            if( type() != ConfigNodeType::Array )
                throw ConfigError( "Cannot use iterators with node of type " + Configuration::typeToString( type() ) );

            return Iterator( *this, size() );
        }

    };
}