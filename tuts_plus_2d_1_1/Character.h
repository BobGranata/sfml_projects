#pragma once

#include "MovingObject.h"
#include "Animator.h"

namespace Constants
{
    const float cWalkSpeed = 160.0f;
    const float cJumpSpeed = 410.0f;
    const float cMinJumpSpeed = 200.0f;
    const float cHalfSizeY = 20.0f;
    const float cHalfSizeX = 6.0f;
}

enum KeyInput
{
    GoLeft = 0,
    GoRight,
    GoDown,
    Jump,
    Count
};

class Character : public MovingObject
{
public:
    enum CharacterState
    {
        Stand,
        Walk,
        Jump,
        GrabLedge,
    };
protected:
    std::vector<bool> mInputs;
    std::vector<bool> mPrevInputs;

    bool Released(KeyInput key)
    {
        return (!mInputs[(int)key] && mPrevInputs[(int)key]);
    }
    bool KeyState(KeyInput key)
    {
        return (mInputs[(int)key]);
    }
    bool Pressed(KeyInput key)
    {
        return (mInputs[(int)key] && !mPrevInputs[(int)key]);
    }

public:

    CharacterState mCurrentState;
    float mJumpSpeed;
    float mWalkSpeed;

    Animator mAnimator;

    Character(RenderWindow& renderWindowApp) : mAnimator(renderWindowApp, this), mCurrentState(CharacterState::Stand)
    {

    }

    void CharacterUpdate()
    {
        switch (mCurrentState)
        {
        case CharacterState::Stand:
            //mWalkSfxTimer = cWalkSfxTime;
            mAnimator.Play("Stand");
            mSpeed = sf::Vector2<int>(0, 0);
            if (!mOnGround)
            {
                //mCurrentState = CharacterState::Jump;
                //break;
            }
            //if left or right key is pressed, but not both 
            if (KeyState(KeyInput::GoRight) != KeyState(KeyInput::GoLeft))
            {
                mCurrentState = CharacterState::Walk;
                break;
            }
            else if (KeyState(KeyInput::Jump))
            {
                mSpeed.y = mJumpSpeed;
                //mAudioSource.PlayOneShot(mJumpSfx);
                mCurrentState = CharacterState::Jump;
                break;
            }
            break;
        case CharacterState::Walk:
            mAnimator.Play("Walk");
            /*
            mWalkSfxTimer += Time.deltaTime;
            if (mWalkSfxTimer > cWalkSfxTime)
            {
                mWalkSfxTimer = 0.0f;
                mAudioSource.PlayOneShot(mWalkSfx);
            }*/
            //if both or neither left nor right keys are pressed then stop walking and stand 
            if (KeyState(KeyInput::GoRight) == KeyState(KeyInput::GoLeft))
            {
                mCurrentState = CharacterState::Stand;
                mSpeed = sf::Vector2 <int>(0, 0);
                break;
            }
            else if (KeyState(KeyInput::GoRight))
            {
                if (mPushesRightWall)
                    mSpeed.x = 0.0f;
                else
                    mSpeed.x = mWalkSpeed;
                //mScale.x = -Mathf.Abs(mScale.x);
            }
            else if (KeyState(KeyInput::GoLeft))
            {
                if (mPushesLeftWall)
                    mSpeed.x = 0.0f;
                else
                    mSpeed.x = -mWalkSpeed;
                //mScale.x = Mathf.Abs(mScale.x);
            }
            //if there's no tile to walk on, fall 
            if (KeyState(KeyInput::Jump))
            {
                mSpeed.y = mJumpSpeed;
                //mAudioSource.PlayOneShot(mJumpSfx, 1.0f);
                mCurrentState = CharacterState::Jump;
                break;
            }
            else if (!mOnGround)
            {
                mCurrentState = CharacterState::Jump;
                break;
            }
            break;
        case CharacterState::Jump:
            //mWalkSfxTimer = cWalkSfxTime;
            mAnimator.Play("Jump");
            /*
            mSpeed.y += Constants.cGravity * Time.deltaTime;
            mSpeed.y = Mathf.Max(mSpeed.y, Constants.cMaxFallingSpeed);
            */
            mSpeed.y += 3;
            if (!KeyState(KeyInput::Jump) && mSpeed.y > 0.0f)
            {
                //mSpeed.y = Mathf.Min(mSpeed.y, 200.0f);
            }
            if (KeyState(KeyInput::GoRight) == KeyState(KeyInput::GoLeft))
            {
                mSpeed.x = 0.0f;
            }
            else if (KeyState(KeyInput::GoRight))
            {
                if (mPushesRightWall)
                    mSpeed.x = 0.0f;
                else
                    mSpeed.x = mWalkSpeed;
                //mScale.x = -Mathf.Abs(mScale.x);
            }
            else if (KeyState(KeyInput::GoLeft))
            {
                if (mPushesLeftWall)
                    mSpeed.x = 0.0f;
                else
                    mSpeed.x = -mWalkSpeed;
                //mScale.x = Mathf.Abs(mScale.x);
            }
            //if we hit the ground 
            if (mOnGround)
            {
                //if there's no movement change state to standing 
                if (mInputs[(int)KeyInput::GoRight] == mInputs[(int)KeyInput::GoLeft])
                {
                    mCurrentState = CharacterState::Stand;
                    mSpeed = sf::Vector2 <int>(0, 0);
                    //mAudioSource.PlayOneShot(mHitWallSfx, 0.5f);
                }
                else    //either go right or go left are pressed so we change the state to walk 
                {
                    mCurrentState = CharacterState::Walk;
                    mSpeed.y = 0.0f;
                    // mAudioSource.PlayOneShot(mHitWallSfx, 0.5f);
                }
            }
            break;
        case CharacterState::GrabLedge:
            break;
        }
        UpdatePhysics();
        if ((!mWasOnGround && mOnGround)
            || (!mWasAtCeiling && mAtCeiling)
            || (!mPushedLeftWall && mPushesLeftWall)
            || (!mPushedRightWall && mPushesRightWall))
        {
            //mAudioSource.PlayOneShot(mHitWallSfx, 0.5f);
        }
        UpdatePrevInputs();
    }

    void UpdatePrevInputs()
    {
        int count = KeyInput::Count;
        for (int i = 0; i < count; ++i)
        {
            mPrevInputs[i] = mInputs[i];
        }
    }

    void CharacterInit(std::vector<bool> inputs, std::vector<bool> prevInputs)
    {
        //mPosition = transform.position;
        mAABB = new AABB;
        mAABB->halfSize = new sf::Vector2<int>(Constants::cHalfSizeX, Constants::cHalfSizeY);
        mAABBOffset.y = mAABB->halfSize->y;

        mInputs = inputs;
        mPrevInputs = prevInputs;

        mJumpSpeed = Constants::cJumpSpeed;
        mWalkSpeed = Constants::cWalkSpeed;

        //mScale = Vector2.one;
    }
};