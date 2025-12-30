#include "Logging/console_logger.hpp"
#include "Logging/multi_logger.hpp"
#include "Logging/logger.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

int main()
{
    // Create a new console logger.
    auto console_logger = std::make_unique<Logging::ConsoleLogger>( Logging::LogLevel::Info );

    // Create a new multi logger with the console logger.
    auto multi_logger = std::make_unique<Logging::MultiLogger>();
    multi_logger->add( std::move( console_logger ) );

    // Create the main logger instance.
    auto logger = std::make_unique<Logging::Logger>( std::move( multi_logger ) );
    logger->logInfo( "First message", true );

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

    logger->logInfo( "Other message", true );
    return 0;
}