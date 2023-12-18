#include "SFML/Graphics/CircleShape.hpp"
#include "SFML/Graphics/Color.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include <cmath>
#include <iostream>
class BlackBall{
    private:
        sf::Vector2f _position;
        float _direction, _speed;
        float _lowerXLim, _upperXLim, _lowerYLim, _upperYLim;

        void constrain_direction(){
            _direction = fmod(_direction,360);
            if(_direction<0) _direction+=360;
        }

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

        BlackBall(sf::Vector2f position, float direction, float speed, int lowerXLim, int upperXLim, int lowerYLim, int upperYLim){
            _position = position;
            _direction = direction;
            _speed = speed;
            circ = sf::CircleShape(5.f);
            circ.setFillColor(sf::Color::Black);
            _lowerXLim = lowerXLim;
            _upperXLim = upperXLim;
            _lowerYLim = lowerYLim;
            _upperYLim = upperYLim;
        }
        
        void move(){
            check_bounds();

            constrain_direction();
            _position.x+=cos(_direction*(M_PI/180))*_speed;
            _position.y+=sin(_direction*(M_PI/180))*_speed;
            circ.setPosition(_position);
        }
};