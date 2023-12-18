#include "SFML/Graphics/Transform.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

int main()
{
    auto window = sf::RenderWindow{ { 200u, 200u }, "ReturnPong" };
    window.setVerticalSyncEnabled(true);

    sf::CircleShape player(5.f);
    player.setFillColor(sf::Color::White);
    float rotation = 0;
    player.setPosition(window.getSize().x/2.f,window.getSize().y/2.f);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {


            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                player.move(0,-2);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
                player.move(0,2);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                player.move(-2,0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                player.move(2,0);
        }


        window.clear(sf::Color::Black);

        window.draw(player);
        window.display();
    }
}