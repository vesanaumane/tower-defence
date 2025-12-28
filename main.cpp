#include "Logging/console_logger.hpp"

#include <SFML/Graphics.hpp>

int main()
{

    // Create a new logger.
    Logging::ILogger* logger = new Logging::ConsoleLogger( Logging::LogLevel::Info );

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