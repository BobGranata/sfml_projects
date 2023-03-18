#pragma once
#include "cEntity.h"

class enemy : public Entity
{
public:
    bool thrust;
    int m_jumpStrength;

    int distance;

    enemy() : m_jumpStrength(15)
    {
        m_state = state::stay;
        name = "enemy";
    }

    void update()
    {
        //if (distance != 0)
        //{
        //    this->x += dx;
        //    this->y += dy;
        //    distance--;
        //}
        //else
        //{
        //    distance = rand() % 100 + 15;
        //    dx = -1;
        //    int ssPp = rand() % 2;
        //    if (ssPp == 1)
        //    {
        //        dx = +1;
        //    }

        //    dy = -1;
        //    ssPp = rand() % 2;
        //    if (ssPp == 1)
        //    {
        //        dy = +1;
        //    }


        //    int dir = rand() % 6;
        //}
        //this->m_state = state::walk;
    }

};
