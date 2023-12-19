#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <cmath>
#include <iostream>
#include <stdio.h>

class Ball{
    protected:
        sf::Vector2f _position;
        float _direction, _speed;
        float _lowerXLim, _upperXLim, _lowerYLim, _upperYLim;

        //Ograniczanie kątów
        float constrain_angle(float angle){
            angle = fmod(angle,360);
            if(angle<0) angle+=360;
            return angle;
        }

        //Sprawdzenie czy kulka jest na ekranie
        void check_bounds(){
            if (_position.x>_upperXLim) {
                _direction+=90;
                _position.x-=(_position.x-_upperXLim);
            }
            if (_position.x<_lowerXLim) {
                _direction+=90;
                _position.x-=(_position.x-_lowerXLim);
            }
            if (_position.y>_upperYLim) {
                _direction+=90;
                _position.y-=(_position.y-_upperYLim);
            }
            if (_position.y<_lowerYLim) {
                _direction+=90;
                _position.y-=(_position.y-_lowerYLim);
            }
        }
    public:
        sf::CircleShape circ;

        //Konstruktor
        Ball(sf::Vector2f position, float direction, float speed, int lowerXLim, int upperXLim, int lowerYLim, int upperYLim){
            _position = position;
            _direction = direction;
            _speed = speed;
            circ = sf::CircleShape(5.f);
            _lowerXLim = lowerXLim;
            _upperXLim = upperXLim;
            _lowerYLim = lowerYLim;
            _upperYLim = upperYLim;
        };
        
        //Obsługa ruchu
        void move(){
            check_bounds();

            _direction = constrain_angle(_direction);
            _position.x+=cos(_direction*(M_PI/180))*_speed;
            _position.y+=sin(_direction*(M_PI/180))*_speed;
            circ.setPosition(_position);
        }
};

class CurveBall : public Ball{

    using Ball::Ball;
    public:
        //Skręcanie
        void skew(){
            _direction+=0.2f;
        }

};

class TrackingBall : public Ball{

    using Ball::Ball;
    public:
        void skew_towards(sf::Vector2f target){

            float futureX = _position.x+cos(_direction*(M_PI/180))*_speed;
            float futureY = _position.y+sin(_direction*(M_PI/180))*_speed;

            //Iloczyn wektorowy aby określić czy kulka jest po lewej czy prawej stronie, aby wiedzieć jak skręcać
            float crossp = (futureX - _position.x)*(target.y-_position.y)-(futureY-_position.y)*(target.x-_position.x);

            if(crossp>0){
                _direction+=1.f;
            }
            if(crossp<0){
                _direction-=1.f;
            }

        }
};