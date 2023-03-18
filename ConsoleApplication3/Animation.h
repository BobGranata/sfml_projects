#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;
class Animation
{
public:
    float Frame, speed;
    Sprite sprite;
    std::vector<IntRect> frames;

    Animation() {}

    Animation(Texture& t, int x, int y, int w, int h, int count, float Speed, bool left = false)
    {
        Frame = 0;
        speed = Speed;

        if (!left)
        {
            for (int i = 0; i < count; i++)
            {
                frames.push_back(IntRect(x + i * w, y, w, h));
            }
        }
        else
        {
            for (int i = count - 1; i >= 0; i--)
            {
                frames.push_back(IntRect(x + i * w, y, w, h));
            }
        }

        //if (left)
        //{
        //    Image imm = t.copyToImage();
        //    imm.flipHorizontally();
        //    //imm.saveToFile("C:\\lol.png");
        //    //t.loadFromFile("C:\\lol.png");
        //    t.loadFromImage(imm);
        //    t.update(imm);
        //}
        sprite.setTexture(t);
        sprite.setOrigin(w / 2, h / 2);
        sprite.setTextureRect(frames[0]);

        sprite.getTexture();
    }


    void update()
    {
        Frame += speed;
        int n = frames.size();
        if (Frame >= n) Frame -= n;

        if (n > 0) sprite.setTextureRect(frames[int(Frame)]);
    }

    bool isEnd()
    {
        return Frame + speed >= frames.size();
    }

};