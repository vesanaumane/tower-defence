#include "Logging/console_logger.hpp"
#include "Logging/file_logger.hpp"
#include "Logging/multi_logger.hpp"
#include "Logging/logger.hpp"
#include "Logging/logging.hpp"
#include "Logging/log_macros.hpp"
#include "Configuration/configuration.hpp"
#include "Configuration/toml_config.hpp"
#include "Configuration/config_error.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

void initializeConfiguration();
void initializeLogging();

int main()
{
    // Setup configuration.
    initializeConfiguration();

    // Setup the logging.
    initializeLogging();

    LOG_INFO( "Application starting..." );
    LOG_DEBUG( "Testing debug!" );
    LOG_WARNING( "Testing warning!" );
    LOG_VERBOSE( "Testing vebose!" );
    LOG_ERROR( "Testing error!" );

    LOG_INFO( Configuration::get( "test.string" ).asString() );

    /*
    // Run the game.
    try
    {
        sf::RenderWindow window( sf::VideoMode( { 200, 200 } ), "SFML works!" );
        sf::CircleShape shape( 100.f );
        shape.setFillColor( sf::Color::Green );

        while( window.isOpen() )
        {
            sf::Event event;

            while( window.pollEvent( event ) )
            {
                if( event.type == sf::Event::Closed )
                    window.close();
            }
            window.clear();
            window.draw( shape );
            window.display();
        }
    }
    catch( const std::exception& e )
    {
        LOG_ERROR( e.what() );
    }
    */
    LOG_INFO( "Application end." );

    // Shutdown the logging service.
    Logging::shutdown();

    // Shutdown config service.
    Configuration::shutdown();

    return 0;
}

void initializeConfiguration()
{
    // Create new toml config reader.
    auto toml_config = std::make_unique<Configuration::TomlConfig>( "config.toml" );

    // Set it as a global config.
    Configuration::init( std::move( toml_config ) );
}

void initializeLogging()
{
    // Get the logging settings.
    auto& loggers = Configuration::get( "logging.loggers" );

    // Create a multi logger.
    auto multi_logger = std::make_unique<Logging::MultiLogger>();

    // Configure all loggers in the config to the multi-logger.
    for( const auto& logger : loggers )
    {
        // Get the logger type from the config.
        std::string logger_type = logger.getString( "type" );

        // Get the logging level.
        Logging::LogLevel level = logger.getEnum<Logging::LogLevel>( "max_logging_level" );

        // Get if the logger should be enabled.
        bool enabled = logger.getBoolean( "enabled" );

        // Create a correct logger.
        if( logger_type == "File" )
        {
            // Get the file path.
            std::string file_path = logger.getString( "file_path" );

            // Create a new file logger to the multi logger.
            multi_logger->add( std::make_unique<Logging::FileLogger>( level, enabled, file_path ) );
        }
        else if( logger_type == "Console" )
        {
            // Create new console logger to the multi logger.
            multi_logger->add( std::make_unique<Logging::ConsoleLogger>( level, enabled ) );
        }
        else
            throw Configuration::ConfigError( "Unknown logger type: " + logger_type );
    }

    // Create the main logger instance.
    auto logger = std::make_unique<Logging::Logger>( std::move( multi_logger ) );

    // Set logger enabled state.
    logger->setEnabled( Configuration::get( "logging.enabled" ).asBoolean() );

    // Initialize the service.
    Logging::init( std::move( logger ) );

    LOG_INFO( "test Loggers setup" );
}