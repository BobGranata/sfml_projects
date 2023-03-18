// ConsoleApplication3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <list>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

using namespace sf;

//const int W = 1200;
//const int H = 800;

const int W = 632;
const int H = 284;

bool isCollide(Entity* a, Entity* b)
{
    a->m_state;
    b->m_state;
    return (b->x - a->x) * (b->x - a->x) +
        (b->y - a->y) * (b->y - a->y) <
        (a->R + b->R) * (a->R + b->R);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(W, H), "SFML works!");
    window.setFramerateLimit(60);


    //Texture tStay_right, tStay_left, tRun_right, tRun_left, t3, t4, t5;
    //Image imm;
    //imm.loadFromFile("C:\\Users\\BobGranata\\Desktop\\картинки\\scot\\sp_stay_green.png");    
    //tStay_right.loadFromImage(imm);
    //imm.flipHorizontally();
    //tStay_left.loadFromImage(imm);

    //imm.loadFromFile("C:\\Users\\BobGranata\\Desktop\\картинки\\scot\\sp_run_green.png");
    //tRun_right.loadFromImage(imm);
    //imm.flipHorizontally();
    //tRun_left.loadFromImage(imm);

    //imm.loadFromFile("C:\\Users\\BobGranata\\Desktop\\картинки\\scot\\sp_walk_green.png");
    //t3.loadFromImage(imm);
    //imm.flipHorizontally();
    //t4.loadFromImage(imm);

    //imm.loadFromFile("C:\\Users\\BobGranata\\Desktop\\картинки\\scot\\sp_jump_right.png");
    //t5.loadFromImage(imm);

    Texture tBack;
    //tBack.loadFromFile("C:\\Users\\BobGranata\\Desktop\\картинки\\scot\\suburb.png");
    tBack.loadFromFile("C:\\Users\\BobGranata\\Desktop\\картинки\\scot\\isometric_paper.png");
    Sprite background(tBack);

    //Animation sPlayerStay(tStay_right, 0, 0, 39, 59, 8, 0.1, false);
    //Animation sPlayerStay_left(tStay_left, 0, 0, 39, 59, 8, 0.1, true);

    //Animation sPlayerRun(tRun_right, 0, 0, 56, 60, 8, 0.2, false);
    //Animation sPlayerRun_left(tRun_left, 0, 0, 56, 60, 8, 0.2, true);

    //Animation sPlayerWalk(t3, 0, 0, 37, 63, 6, 0.2, false);
    //Animation sPlayerWalk_left(t4, 0, 0, 37, 63, 6, 0.2, true);

    //Animation sPlayerJump_right(t5, 0, 0, 47, 67, 13, 0.1, false);    
    //Animation sPlayerJump_left(t5, 0, 0, 47, 67, 13, 0.1, true);

    Texture tPlayer;
    Image imm;
    imm.loadFromFile("C:\\Users\\BobGranata\\Desktop\\картинки\\scot\\scott.png");
    tPlayer.loadFromImage(imm);

    //imm.flipHorizontally();
    //t4.loadFromImage(imm);


    Animation sPlayerStay(tPlayer, 0, 0, 39, 59, 8, 0.1, false);
    Animation sPlayerStay_left(tPlayer, 0, 0, 39, 59, 8, 0.1, true);

    Animation sPlayerWalk(tPlayer, 0, 59, 37, 63, 6, 0.2, false);
    Animation sPlayerWalk_left(tPlayer, 0, 59, 37, 63, 6, 0.2, true);

    Animation sPlayerRun(tPlayer, 0, 122, 56, 60, 8, 0.2, false);
    Animation sPlayerRun_left(tPlayer, 0, 122, 56, 60, 8, 0.2, true);

    Animation sPlayerKick_right(tPlayer, 0, 182, 60, 59, 7, 0.2, false);
    Animation sPlayerKick_left(tPlayer, 0, 182, 60, 59, 7, 0.2, true);

    Animation sPlayerJump_right(tPlayer, 0, 241, 47, 67, 13, 0.1, false);
    Animation sPlayerJump_left(tPlayer, 0, 241, 47, 67, 13, 0.1, true);

    std::list<Entity*> entities;

    player* p = new player();
    p->settings(sPlayerStay, 200, 200, 1);
    entities.push_back(p);

    for (int i = 0; i < 15; i++)
    {
        enemy* en = new enemy();
        //en->settings(sPlayerStay, rand() % W, rand() % H, 1);
        en->settings(sPlayerWalk, rand() % W, rand() % H, 1);
        entities.push_back(en);
    }    

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        player::state currState = p->m_state;
        player::state difState = player::state::stay;
        player::direction currdirection = p->m_direction;

        if (Keyboard::isKeyPressed(Keyboard::Right))
        {
            p->m_direction = player::direction::right;

            difState = player::state::walk;
            int dirMult = 2;
            if (Keyboard::isKeyPressed(Keyboard::LShift))
            {
                difState = player::state::run;
                dirMult *= 2;
            }

            p->x += dirMult;
        }
        else if (Keyboard::isKeyPressed(Keyboard::Left))
        {
            p->m_direction = player::direction::left;

            difState = player::state::walk;
            int dirMult = 2;
            if (Keyboard::isKeyPressed(Keyboard::LShift))
            {
                difState = player::state::run;
                dirMult *= 2;
            }

            p->x -= dirMult;
        }
        if (Keyboard::isKeyPressed(Keyboard::Up))
        {
            difState = player::state::walk;
            int dirMult = 2;
            if (Keyboard::isKeyPressed(Keyboard::LShift))
            {
                difState = player::state::run;
                dirMult *= 2;
            }
            p->y -= dirMult;
        }
        if (Keyboard::isKeyPressed(Keyboard::Down))
        {
            difState = player::state::walk;
            int dirMult = 2;
            if (Keyboard::isKeyPressed(Keyboard::LShift))
            {
                difState = player::state::run;
                dirMult *= 2;
            }
            p->y += dirMult;
        }
        if (Keyboard::isKeyPressed(Keyboard::Space))
        {
            p->m_direction = player::direction::right;
            difState = player::state::jump;
        }
        if (Keyboard::isKeyPressed(Keyboard::X))
        {
            difState = player::state::kick;
        }


        if (currState != difState && currState != player::state::jump)
        {
            p->m_state = difState;
        }

        if (p->m_state == player::state::jump)
        {
            p->y -= p->m_jumpStrength;
            p->m_jumpStrength--;

            if (p->m_jumpStrength < -15)
            {
                p->m_jumpStrength = 15;
                p->m_state = player::state::stay;
            }
        }

        if (p->m_state == player::state::run && (p->m_state != currState || p->m_direction != currdirection))
        {
            if (p->m_direction == player::direction::right)
            {
                p->anim = sPlayerRun;
            }
            else
            {
                p->anim = sPlayerRun_left;
            }
        }
        else if (p->m_state == player::state::walk && (p->m_state != currState || p->m_direction != currdirection))
        {
            if (p->m_direction == player::direction::right)
            {
                p->anim = sPlayerWalk;
            }
            else
            {
                p->anim = sPlayerWalk_left;
            }
        }
        else if (p->m_state == player::state::jump && (p->m_state != currState || p->m_direction != currdirection))
        {
            if (p->m_direction == player::direction::right)
            {
                p->anim = sPlayerJump_right;
            }
            else
            {
                p->anim = sPlayerRun_left;
            }
        }
        else if (p->m_state == player::state::stay && (p->m_state != currState || p->m_direction != currdirection))
        {
            if (p->m_direction == player::direction::right)
            {
                p->anim = sPlayerStay;
            }
            else
            {
                p->anim = sPlayerStay_left;
            }
        }
        else if (p->m_state == player::state::kick && (p->m_state != currState || p->m_direction != currdirection))
        {
            if (p->m_direction == player::direction::right)
            {
                p->anim = sPlayerKick_right;
            }
            else
            {
                p->anim = sPlayerKick_left;
            }
        }

        for (auto a : entities)
        {
            for (auto b : entities)
            {
                if (a->name == "asteroid" && b->name == "bullet")
                    if (isCollide(a, b))
                    {
                    }
            }
        }
  
        window.clear();     


        for (auto i = entities.begin(); i != entities.end();)
        {
            Entity* e = *i;

            e->update();
            e->anim.update();

            if (e->life == false) { i = entities.erase(i); delete e; }
            else i++;
        }

        //window.clear();

        //////draw//////
        window.draw(background);

        for (auto i : entities) i->draw(window);

        window.display();
    }      
}