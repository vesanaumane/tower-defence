#include "configuration.hpp"

#include <mutex>
#include <cassert>

namespace Configuration
{
    /// @brief Anonymous namespace to hide global variables.
    namespace
    {
        /// @brief Global config instance.
        std::unique_ptr<IConfig> g_config;

        /// @brief Mutex to protect the global config modifications.
        std::mutex g_mutex;
    }

    void init( std::unique_ptr<IConfig> config )
    {
        // Protect the global config instance during initialization.
        std::lock_guard<std::mutex> lock( g_mutex );

        // Init can be called only once.
        assert( !g_config && "Configuration::init() called twice" );

        // Set the global config instance.
        g_config = std::move( config );
    }

    void shutdown()
    {
        // Guard the config.
        std::lock_guard<std::mutex> lock( g_mutex );

        // Delete the logger.
        g_config.reset();
    }

    IConfig& getRoot()
    {
        // Init must be called before getting the config.
        assert( g_config && "Configuration::getRoot() called before init()" );

        // Return a reference to the config.
        return *g_config;
    }

    IConfigNode& get( const std::string& key )
    {
        // Init must be called before getting the config.
        assert( g_config && "Configuration::get( std::string ) called before init()" );

        return g_config->getChildNode( key );
    }


}