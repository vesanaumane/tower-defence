#pragma once

#include <memory>

#include "iconfig_node.hpp"
#include "libs/toml.hpp"
#include "config_key_not_found_error.hpp"
#include "config_type_mismatch_error.hpp"
#include "type_name.hpp"

namespace Configuration
{
    class TomlConfigNode : public IConfigNode
    {
        public:

        explicit TomlConfigNode( toml::node_view<const toml::node> node );

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

        private:

        /// @brief Toml node.
        toml::node_view<const toml::node> m_node;


        /// @brief Throw error if node type is not suitable for value conversions.
        /// @param target_value_type String representation for the target type of the value conversion.
        void assertNodeTypeForValueConversion( const std::string& target_value_type ) const;

        /// @brief Get the value from a node.
        /// @tparam T Node value type.
        /// @param node Node.
        /// @param key Key to the node, use empty string to get value from current node.
        /// @return Value of type T.
        template<typename T>
        T getValueFromNode( toml::node_view<const toml::node> node, const std::string& key ) const
        {
            // Get either child node or, if key is empty, use the node itself.
            toml::node_view<const toml::node> child = node;
            if( key != "" )
            {
                // Get the child node.
                child = node.at_path( key );
                if( !child )
                    throw ConfigKeyNotFound( key );
            }

            // Get the value from the node.
            auto value = child.value<T>();

            // Throw error if the value is not of correct type.
            if( !value )
            {
                // Get the type of the node. We need to get it through stream.
                std::ostringstream oss;
                oss << child.type();

                throw ConfigTypeMismatch(
                    key,
                    TypeName<T>::value,
                    oss.str() );
            }
            return *value;
        }
    };
}