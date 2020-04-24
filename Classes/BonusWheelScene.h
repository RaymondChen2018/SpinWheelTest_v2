#ifndef __BONUSWHEEL_SCENE_H
#define __BONUSWHEEL_SCENE_H

#include "cocos2d.h"
enum class PRIZE : int;

USING_NS_CC;
class BonusWheelScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    void pushPrizeIcon(const char* imagePath, const char* textPath, float angleDegree, Node* spinWheel);

    // a selector callback
    void resetWheel(cocos2d::Ref* pSender);
    void menuSpinCallback(cocos2d::Ref* pSender);
    void rollAnimation(PRIZE);
    void prizePresent(PRIZE prize);

    // implement the "static create()" method manually
    CREATE_FUNC(BonusWheelScene);
private:
    const int NUM_TURNS = 10;
    const float SPIN_DURATION = 4.0f;

    const float BACK_ACC_DIST_RATIO = 0.105f;
    const float BACK_ACC_TIME_RATIO = 0.1f;
    const float ROTATION_DIST_RATIO = 0.89f;
    const float ROTATION_TIME_RATIO = 0.8f;
    const float BACK_DEC_DIST_RATIO = 0.005f;
    const float BACK_DEC_TIME_RATIO = 0.1f;

    const float PAUSE_DURATION = 0.3f;
    const float PRIZE_PRESENT_DURATION = 2.0f;

    Node* pSpinWheel;
    Node* pLayerSpinWheel;
    Node* pPlayOnButton;
    Node* pResetButton;
    Node* pPrizeSprite;

    Vec2 center;
    Vec2 buttonPos;
};

#endif //__BONUSWHEEL_SCENE_H
