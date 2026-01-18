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
        virtual std::unique_ptr<IConfigNode> getChildNode( const std::string& key ) const override;
        virtual size_t size() const override;
        virtual std::unique_ptr<IConfigNode> at( size_t index ) const override;

        private:

        /// @brief Toml node.
        toml::node_view<const toml::node> m_node;

        /// @brief Get the value from a node.
        /// @tparam T Node value type.
        /// @param node Node.
        /// @param key Key to the node.
        /// @return Value of type T.
        template<typename T>
        T getValueFromNode( toml::node_view<const toml::node> node, const std::string& key ) const
        {
            // Get the child node.
            auto child = node.at_path( key );
            if( !child )
                throw ConfigKeyNotFound( key );

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