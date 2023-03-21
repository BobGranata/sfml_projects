#pragma once

#include <SFML/Graphics.hpp>

struct AABB
{
    sf::Vector2 <int>* center;
    sf::Vector2 <int>* halfSize;

    AABB() : center(NULL), halfSize(NULL)
    {
    }


    AABB(sf::Vector2 <int>* center, sf::Vector2 <int>* halfSize)
    {
        this->center = center;
        this->halfSize = halfSize;
    }

    bool Overlaps(const AABB& other)
    {
        if (std::abs(center->x - other.center->x) > halfSize->x + other.halfSize->x) return false;
        if (std::abs(center->y - other.center->y) > halfSize->y + other.halfSize->y) return false;
        return true;
    }
};

class MovingObject
{
public:
    sf::Vector2 <int>  mOldPosition;
    sf::Vector2 <int>  mPosition;

    sf::Vector2 <int>  mOldSpeed;
    sf::Vector2 <int>  mSpeed;

    sf::Vector2 <int>  mScale;

    AABB* mAABB;
    sf::Vector2 <int>  mAABBOffset;

    bool mPushedRightWall;
    bool mPushesRightWall;
    bool mPushedLeftWall;
    bool mPushesLeftWall;
    bool mWasOnGround;
    bool mOnGround;
    bool mWasAtCeiling;
    bool mAtCeiling;

    MovingObject()
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

        if (mPosition.y < 0.0f)
        {
            mPosition.y = 0.0f;
            mOnGround = true;
        }
        else
            mOnGround = false;

        //mAABB->center = mPosition + mAABBOffset;
    }
};

