#include "SFML/Graphics/Transform.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>

int main()
{
    auto window = sf::RenderWindow{ { 200u, 200u }, "ReturnPong" };
    window.setVerticalSyncEnabled(true);

    sf::CircleShape circle(5.f);
    circle.setFillColor(sf::Color::White);
    float rotation = 0;
    circle.setPosition(window.getSize().x/2.f,window.getSize().y/2.f);

    while (window.isOpen())
    {
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            
        }
        rotation+=0.1f;

        circle.setPosition(window.getSize().x/2.f+sin(rotation)*50.f,window.getSize().y/2.f+cos(rotation)*20.f);


        window.clear(sf::Color::Black);

        window.draw(circle);
        window.display();
    }
}