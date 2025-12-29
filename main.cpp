#include "Logging/console_logger.hpp"
#include "Logging/multi_logger.hpp"
#include "Logging/logger.hpp"

#include <SFML/Graphics.hpp>
#include <memory>

int main()
{
    // Create a new console logger.
    Logging::ILogger* console_logger = new Logging::ConsoleLogger( Logging::LogLevel::Info );

    // Create a new multi logger with the console logger.
    auto multi_logger = std::make_shared<Logging::MultiLogger>();
    multi_logger->add( console_logger );

    // Create the main logger instance.
    Logging::ILogger* logger = new Logging::Logger( multi_logger );

    logger->logInfo( "First message" );

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

    logger->logInfo( "Other message" );

    delete logger;

    return 0;
}