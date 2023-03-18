#pragma once
#include "Animation.h"

class Entity
{
public:
    float x, y, dx, dy, R;
    bool life;
    std::string name;
    Animation anim;

    enum class direction
    {
        right,
        left
    } m_direction;

    enum class state
    {
        stay,
        walk,
        run,
        jump,
        kick
    } m_state;

    Entity()
    {
        life = 1;
    }

    void settings(Animation& a, int X, int Y, int radius = 1)
    {
        anim = a;
        x = X; y = Y;
        R = radius;
    }

    virtual void update() {};

    void draw(RenderWindow& app)
    {
        anim.sprite.setPosition(x, y);
        app.draw(anim.sprite);

        sf::RectangleShape rect(Vector2f(108, 140));
        rect.setFillColor(Color(255, 255, 0, 255));
        rect.setPosition(x, y);
        //app.draw(rect);
    }

    virtual ~Entity() {};
};


