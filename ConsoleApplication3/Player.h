#pragma once
#include "cEntity.h"

class player : public Entity
{
public:
    bool thrust;
    int m_jumpStrength;

    player() : m_jumpStrength(15)
    {
        m_state = state::stay;
        name = "player";
    }

    void update()
    {
        IntRect ddd = this->anim.frames[int(this->anim.Frame)];
        ddd.height;
        ddd.width;

        //if (thrust)
        //{
        //}
        //else
        //{
        //    dx *= 0.99;
        //    dy *= 0.99;
        //}

        //if (x > W) x = 0; if (x < 0) x = W;
        //if (y > H) y = 0; if (y < 0) y = H;
    }

};