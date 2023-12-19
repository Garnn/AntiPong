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
#include <stdio.h>
#include <string>
#include <variant>
#include <vector>
#include "SFML/Window/Mouse.hpp"
#include <random>
#include "balls.cpp"

#define WIDTH 800
#define HEIGHT 600
#define TELEPORT_COOLDOWN 100

int main()
{
    //Inicjalizacja okna
    auto window = sf::RenderWindow{ { WIDTH, HEIGHT+10 }, "AntiPong" };
    window.setVerticalSyncEnabled(true);
    int gamestate = 0;

    //Ładowanie czcionek
    sf::Font font;
    font.loadFromFile("arial.ttf");

    //Inicjalizacja gracza
    sf::CircleShape player(5.f);
    player.setFillColor(sf::Color::White);
    player.setPosition(WIDTH/2.f,HEIGHT/2.f);

    //Punkciki !
    long long int points = 10;
    sf::Text pointDisplay;
    pointDisplay.setFont(font);
    pointDisplay.setCharacterSize(20);

    //Inicjalizacja paska ładowania
    sf::RectangleShape teleIndicator;
    int teleCooldown = 0;
    teleIndicator.setFillColor(sf::Color::Cyan);
    teleIndicator.setPosition(0,HEIGHT);

    //Inicjalizacja generatora liczb pseudolosowych
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> screenAreaX(0,WIDTH);
    std::uniform_int_distribution<> screenAreaY(0,HEIGHT);
    std::uniform_real_distribution<> randomDegree(0,360);
    std::uniform_real_distribution<> randomSpeed(2,5);
    std::uniform_int_distribution<> ballType(0,2);

    //Deklaracja tablic dynamicznych zawierających wszystkie kulki

    int spawningCooldown=0;
    int spawning;
    int variant;
    sf::Vector2f spawnPosition;
    float spawnDegree;
    float spawnSpeed;
    sf::RectangleShape spawnIndicator(sf::Vector2f(10,10));
    spawnIndicator.setFillColor(sf::Color::Yellow);
    std::vector<Ball> Standard;
    std::vector<CurveBall> Curving;
    std::vector<TrackingBall> Tracking;

    // Ball a = Ball(sf::Vector2f(WIDTH/2.f, HEIGHT/2.f), 30.f, 2.f, 0, (float)WIDTH, 0, (float)HEIGHT);

    // CurveBall b = CurveBall(sf::Vector2f(WIDTH/2.f, HEIGHT/2.f), 30.f, 2.f, 0, (float)WIDTH, 0, (float)HEIGHT);

    // TrackingBall c = TrackingBall(sf::Vector2f(WIDTH/2.f, HEIGHT/2.f-100), 30.f, 2.f, 0, (float)WIDTH, 0, (float)HEIGHT);

    // a.circ.setFillColor(sf::Color::Black);
    // b.circ.setFillColor(sf::Color::Green);
    // c.circ.setFillColor(sf::Color::Red);

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
        
        if(gamestate == 0){
        
        points+=1;
        std::string pointsString = "Punkty:" + std::to_string(points);
        pointDisplay.setString(pointsString);
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !teleCooldown) {
                player.setPosition(sf::Vector2f(mousePosition));
                teleCooldown=TELEPORT_COOLDOWN;
        }

        if(teleCooldown){
            teleCooldown-=1;
        }

        teleIndicator.setSize(sf::Vector2f(((float)teleCooldown/TELEPORT_COOLDOWN)*WIDTH,10));

        //Dodawanie kulek
        if (!spawningCooldown) {
            
            int roll = ballType(generator);
            variant = roll;

            spawnPosition = sf::Vector2f(screenAreaX(generator),screenAreaY(generator));
            spawnDegree = randomDegree(generator);
            spawnSpeed = randomSpeed(generator);

            switch (roll) {
                case 0:
                spawningCooldown = 200;
                break;
                case 1:
                spawningCooldown = 400;
                break;
                case 2:
                spawningCooldown = 800;
                break;
            }

            spawning = 100;
        }
        spawningCooldown--;

        if(spawning>0){
            spawning--;
            spawnIndicator.setPosition(spawnPosition);
        }
        else if (spawning == 0){
            switch (variant) {
                case 0:
                Standard.push_back(Ball(spawnPosition,spawnDegree,spawnSpeed,0,(float)WIDTH,0,(float)HEIGHT,sf::Color::Black));
                break;
                case 1:
                Curving.push_back(CurveBall(spawnPosition,spawnDegree,spawnSpeed,0,(float)WIDTH,0,(float)HEIGHT,sf::Color::Green));
                break;
                case 2:
                Tracking.push_back(TrackingBall(spawnPosition,spawnDegree,spawnSpeed,0,(float)WIDTH,0,(float)HEIGHT,sf::Color::Red));
                break;
            }
            spawning=-1;
        }
        else{
            spawnIndicator.setPosition(sf::Vector2f(-100,-100));
        }

        //Czyszczenie ekranu
        window.clear(sf::Color(100,100,100));

        //Zachowanie kulek
        for(Ball& a : Standard){
            a.move();
            window.draw(a.circ);
            if(a.circ.getGlobalBounds().intersects(player.getGlobalBounds())) gamestate = 1;
        }
        for(CurveBall& b : Curving){
            b.move();
            b.skew();
            window.draw(b.circ);
            if(b.circ.getGlobalBounds().intersects(player.getGlobalBounds())) gamestate = 1;
        }
        for(TrackingBall& c : Tracking){
            c.move();
            c.skew_towards(player.getPosition());
            window.draw(c.circ);
            if(c.circ.getGlobalBounds().intersects(player.getGlobalBounds())) gamestate = 1;
        }
        window.draw(spawnIndicator);
        window.draw(teleIndicator);
        window.draw(player);
        window.draw(pointDisplay);
        window.display();
        }
        if (gamestate==1 && sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            points = 10;
            teleCooldown = 0;
            player.setPosition(WIDTH/2.f,HEIGHT/2.f);
            Standard.clear();
            Curving.clear();
            Tracking.clear();
            spawningCooldown=0;
            gamestate = 0;
        }
        
    }
}