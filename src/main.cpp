#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/PrimitiveType.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Transform.hpp"
#include "SFML/Graphics/Vertex.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/Event.hpp"
#include "SFML/Window/Keyboard.hpp"
#include <SFML/Graphics.hpp>
#include <math.h>
#include <vector>
#include "SFML/Window/Mouse.hpp"
#include "balls.cpp"

#define WIDTH 800
#define HEIGHT 600
#define TELEPORT_COOLDOWN 100

int main()
{
    //Inicjalizacja okna
    auto window = sf::RenderWindow{ { WIDTH, HEIGHT+10 }, "ReturnPong" };
    window.setVerticalSyncEnabled(true);

    //Inicjalizacja gracza
    sf::CircleShape player(5.f);
    player.setFillColor(sf::Color::White);
    player.setPosition(window.getSize().x/2.f,window.getSize().y/2.f);

    //Inicjalizacja paska ładowania
    sf::RectangleShape tele_indicator;
    int tele_cooldown = 0;
    tele_indicator.setFillColor(sf::Color::Cyan);
    tele_indicator.setPosition(0,HEIGHT);

    //Inicjalizacja generatora liczb pseudolosowych

    //Deklaracja tablic dynamicznych zawierających wszystkie kulki

    int spawning_cooldown=0;
    std::vector<Ball> Standard;
    std::vector<CurveBall> Curving;
    std::vector<TrackingBall> Tracking;

    Ball a = Ball(sf::Vector2f(WIDTH/2.f, HEIGHT/2.f), 30.f, 2.f, 0, (float)WIDTH, 0, (float)HEIGHT);

    CurveBall b = CurveBall(sf::Vector2f(WIDTH/2.f, HEIGHT/2.f), 30.f, 2.f, 0, (float)WIDTH, 0, (float)HEIGHT);

    TrackingBall c = TrackingBall(sf::Vector2f(WIDTH/2.f, HEIGHT/2.f-100), 30.f, 2.f, 0, (float)WIDTH, 0, (float)HEIGHT);

    a.circ.setFillColor(sf::Color::Black);
    b.circ.setFillColor(sf::Color::Green);
    c.circ.setFillColor(sf::Color::Red);

    while (window.isOpen())
    {
        //Obsługa wydarzeń
        for (auto event = sf::Event{}; window.pollEvent(event);)
        {

            //Wyłączanie programu jeśli użytkownik zamknie okno
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


        // sf::Vertex testLine[] = {
        //     sf::Vertex(sf::Vector2f(player.getPosition().x+5.f,player.getPosition().y+5.f)),
        //     sf::Vertex(sf::Vector2f(mousePosition))
        // };

        // window.draw(testLine,2,sf::Lines);

        //Teleportacja
        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !tele_cooldown) {
                player.setPosition(sf::Vector2f(mousePosition));
                tele_cooldown=TELEPORT_COOLDOWN;
        }

        if(tele_cooldown){
            tele_cooldown-=1;
        }

        tele_indicator.setSize(sf::Vector2f(((float)tele_cooldown/TELEPORT_COOLDOWN)*WIDTH,10));

        //Dodawanie kulek
        if (!spawning_cooldown) {
            
        }

        //Zachowanie kulek
        a.move();
        b.move();
        c.move();
        b.skew();
        c.skew_towards(player.getPosition());

        //Czyszczenie ekranu
        window.clear(sf::Color(100,100,100));

        
        window.draw(c.circ);
        window.draw(b.circ);
        window.draw(a.circ);
        window.draw(tele_indicator);
        window.draw(player);
        window.display();
    }
}