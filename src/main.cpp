#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include "SFML/Window/Mouse.hpp"
#include "balls.cpp"

#define WIDTH 500
#define HEIGHT 500

int main()
{
    auto window = sf::RenderWindow{ { WIDTH, HEIGHT }, "ReturnPong" };
    window.setVerticalSyncEnabled(true);

    sf::CircleShape player(5.f);
    player.setFillColor(sf::Color::White);
    player.setPosition(window.getSize().x/2.f,window.getSize().y/2.f);

    BlackBall a = BlackBall(sf::Vector2f(WIDTH/2.f, HEIGHT/2.f), 30.f, 5.f, 0, (float)WIDTH, 0, (float)HEIGHT);

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

        //Obsługa ruchu gracza
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

        //Kolizja gracza z oknem gry
        if (player.getPosition().x>WIDTH-10.f) {
            player.setPosition(WIDTH-10.f,player.getPosition().y);
        }
        if (player.getPosition().x<0) {
            player.setPosition(0,player.getPosition().y);
        }
        if (player.getPosition().y>HEIGHT-10.f) {
            player.setPosition(player.getPosition().x,HEIGHT-10.f);
        }
        if (player.getPosition().y<0) {
            player.setPosition(player.getPosition().x,0);
        }

        //Teleportacja
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        // sf::Vertex testLine[] = {
        //     sf::Vertex(sf::Vector2f(player.getPosition().x+5.f,player.getPosition().y+5.f)),
        //     sf::Vertex(sf::Vector2f(mousePosition))
        // };

        // window.draw(testLine,2,sf::Lines);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                player.setPosition(sf::Vector2f(mousePosition));
        }

        //Zachowanie kulek
        a.move();


        //Czyszczenie ekranu
        window.clear(sf::Color(100,100,100));

        

        //float a = (mousePosition.x-player.getPosition().x)/(mousePosition.y-player.getPosition().y);
        
        window.draw(a.circ);
        window.draw(player);
        window.display();
    }
}