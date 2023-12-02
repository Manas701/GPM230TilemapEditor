#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <SFML/Graphics.hpp>

class Ball
{
    public:
        float radius;
        float diameter;
        sf::Vector2f velocity;
        float acceleration;
        int bounces = 0;
        sf::CircleShape sprite;
        sf::Vector2f resetPosition;
        bool inPaddle = false;
        void Init();
        void Reset();
        void Serve();
        void Update();
        void CheckServe();
};

#endif