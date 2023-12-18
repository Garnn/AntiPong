#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/System/Vector2.hpp"
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
        //Obsługa wydarzeń
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {

            //Wyłączanie programu jeśli użytkownik go zamknie
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
            
        }

        //Obsługa ruchu
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
        //Czyszczenie ekranu
        window.clear(sf::Color::Black);

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        sf::Vertex testLine[] = {
            sf::Vertex(sf::Vector2f(player.getPosition().x+5.f,player.getPosition().y+5.f)),
            sf::Vertex(sf::Vector2f(mousePosition))
        };
        //float a = (mousePosition.x-player.getPosition().x)/(mousePosition.y-player.getPosition().y);
        

        window.draw(testLine,2,sf::Lines);
        window.draw(player);
        window.display();
    }
}