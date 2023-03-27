#pragma once

#include <SFML/Graphics.hpp>

struct AABB
{
    sf::Vector2 <float> center;
    sf::Vector2 <float> halfSize;

    AABB()
    {
    }


    AABB(float halfSizeX, float halfSizeY) : halfSize(halfSizeX, halfSizeY)
    {
    }

    bool Overlaps(const AABB& other)
    {
        /*if (std::abs(center->x - other.center->x) > halfSize->x + other.halfSize->x) return false;
        if (std::abs(center->y - other.center->y) > halfSize->y + other.halfSize->y) return false;*/
        if (std::abs(center.x - other.center.x) > halfSize.x + other.halfSize.x) return false;
        if (std::abs(center.y - other.center.y) > halfSize.y + other.halfSize.y) return false;
        return true;
    }
};

class MovingObject
{
public:
    sf::Vector2 <float>  mOldPosition;
    sf::Vector2 <float>  mPosition;

    sf::Vector2 <float>  mOldSpeed;
    sf::Vector2 <float>  mSpeed;

    sf::Vector2 <float>  mScale;

    AABB mAABB;
    sf::Vector2 <float>  mAABBOffset;

    bool mPushedRightWall;
    bool mPushesRightWall;
    bool mPushedLeftWall;
    bool mPushesLeftWall;
    bool mWasOnGround;
    bool mOnGround;
    bool mWasAtCeiling;
    bool mAtCeiling;

    MovingObject() : mPosition(20, 200)
    {
        UpdatePhysics();
    }

    void UpdatePhysics()
    {
        mOldPosition = mPosition;
        mOldSpeed = mSpeed;

        mWasOnGround = mOnGround;
        mPushedRightWall = mPushesRightWall;
        mPushedLeftWall = mPushesLeftWall;
        mWasAtCeiling = mAtCeiling;

        //mPosition += mSpeed * Time.deltaTime;
        mPosition += mSpeed;

        if (mPosition.y >= 200.0f)
        {
            mPosition.y = 200.0f;
            mOnGround = true;
        }
        else
            mOnGround = false;

        mAABB.center = mPosition + mAABBOffset;
    }
};

