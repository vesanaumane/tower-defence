#pragma once

#include <string>
#include <memory>

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
        virtual std::unique_ptr<IConfigNode> getChildNode( const std::string& key ) const = 0;

        /// @brief If type is Array, the size of the Array.
        /// @return Array length.
        virtual size_t size() const = 0;

        /// @brief If type is Array, access an item.
        /// @param index Item index.
        /// @return ConfigNode in the index.
        virtual std::unique_ptr<IConfigNode> at( size_t index ) const = 0;

        virtual ~IConfigNode() {};
    };
}