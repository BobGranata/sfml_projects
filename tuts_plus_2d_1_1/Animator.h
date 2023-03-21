#pragma once

#include <SFML/Graphics.hpp>
#include "MovingObject.h"

using namespace sf;

class Animator
{
private:
    RenderWindow& m_renderWindowApp;
    MovingObject *m_movingObject;
public:

    struct FrameList
    {
        std::string type;
        std::vector<IntRect> frames;
        sf::Sprite sprite;
        float Frame, speed;
    };    

    Texture m_tPlayer;
    std::vector <FrameList*> m_animList;

    Animator(RenderWindow &renderWindowApp, MovingObject *movingObject) : m_renderWindowApp(renderWindowApp), m_movingObject(movingObject)
    {
        Image imm;
        imm.loadFromFile("C:\\Users\\BobGranata\\Desktop\\картинки\\scot\\scott.png");
        m_tPlayer.loadFromImage(imm);

        setAnimator("Stand", 0, 0, 39, 59, 8, 0.1, false);
        setAnimator("Stand_left", 0, 0, 39, 59, 8, 0.1, true);

        setAnimator("Walk", 0, 59, 37, 63, 6, 0.2, false);
        setAnimator("Walk_left", 0, 59, 37, 63, 6, 0.2, true);

        setAnimator("Run", 0, 122, 56, 60, 8, 0.2, false);
        setAnimator("Run_left", 0, 122, 56, 60, 8, 0.2, true);

        setAnimator("Kick_right", 0, 182, 60, 59, 7, 0.2, false);
        setAnimator("Kick_left", 0, 182, 60, 59, 7, 0.2, true);

        setAnimator("Jump_right", 0, 241, 47, 67, 13, 0.1, false);
        setAnimator("Jump_left", 0, 241, 47, 67, 13, 0.1, true);

    }

    void setAnimator(const std::string &type, int x, int y, int w, int h, int count, float Speed, bool left = false)
    {
        FrameList *frameList = new FrameList;

        frameList->Frame = 0;
        frameList->speed = Speed;

        frameList->type = type;

        if (!left)
        {
            for (int i = 0; i < count; i++)
            {
                frameList->frames.push_back(IntRect(x + i * w, y, w, h));
            }
        }
        else
        {
            for (int i = count - 1; i >= 0; i--)
            {
                frameList->frames.push_back(IntRect(x + i * w, y, w, h));
            }
        }

        frameList->sprite.setTexture(m_tPlayer);
        frameList->sprite.setOrigin(w / 2, h / 2);
        frameList->sprite.setTextureRect(frameList->frames[0]);
        frameList->sprite.getTexture();

        m_animList.push_back(frameList);
    }

    void Play(const std::string &type)
    {
        if (type == "Stand")
        {
            FrameList* frameList = NULL;
            for (int i = 0; i < m_animList.size(); i++)
            {
                if (m_animList.at(i)->type == type)
                {
                    frameList = m_animList.at(i);
                }
            }
            
            if (frameList != NULL)
            {
                frameList->Frame += frameList->speed;
                int n = frameList->frames.size();
                if (frameList->Frame >= n)
                {
                    frameList->Frame -= n;
                }

                if (n > 0)
                {
                    frameList->sprite.setTextureRect(frameList->frames[int(frameList->Frame)]);
                }

                int x = m_movingObject->mPosition.x;
                int y = m_movingObject->mPosition.y;
                frameList->sprite.setPosition(x, y);
                //frameList->sprite.setPosition(0, 0);
                m_renderWindowApp.draw(frameList->sprite);

                sf::RectangleShape rect(Vector2f(108, 140));
                rect.setFillColor(Color(255, 255, 0, 255));
                rect.setPosition(x, y);
                //rect.setPosition(0, 0);
            }
        }
    }

    void draw(RenderWindow& app)
    {
        //anim.sprite.setPosition(x, y);
        //app.draw(anim.sprite);

        //sf::RectangleShape rect(Vector2f(108, 140));
        //rect.setFillColor(Color(255, 255, 0, 255));
        //rect.setPosition(x, y);
        ////app.draw(rect);
    }

    void update()
    {
    }

    bool isEnd()
    {
    }

};


