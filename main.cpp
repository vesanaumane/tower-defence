#include "Logging/console_logger.hpp"
#include "Logging/multi_logger.hpp"

#include <SFML/Graphics.hpp>

int main()
{
    // Create a new console logger.
    Logging::ILogger* console_logger = new Logging::ConsoleLogger( Logging::LogLevel::Info );

    // Create a new multi logger with the console logger.
    Logging::MultiLogger* multi_logger = new Logging::MultiLogger();
    multi_logger->add( console_logger );

    multi_logger->logInfo( "First message" );

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

    multi_logger->logInfo( "Other message" );

    delete multi_logger;

    return 0;
}