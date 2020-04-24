// Created by Ruiming
#include "BonusWheelScene.h"
#include "SimpleAudioEngine.h"
#include <android/log.h>
#include "PrizeManager.h"
#include "PrizeObject.h"
USING_NS_CC;

Scene* BonusWheelScene::createScene()
{
    return BonusWheelScene::create();
}
// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// Place icon in the spin wheel slot
void parentPrizeItem(float angleDegree, Node* prizeIcon, Node* spinWheel)
{
    float centerX = spinWheel->getBoundingBox().size.width / 2.0f;
    float centerY = spinWheel->getBoundingBox().size.height / 2.0f;
    float offsetCenter = 0.6f * spinWheel->getBoundingBox().size.width / 2.0f;
    prizeIcon->setRotation(90.0f - angleDegree);

    float angleRadian = 3.14f * angleDegree / 180.0f;
    prizeIcon->setPosition(centerX + offsetCenter * cosf(angleRadian), centerY + offsetCenter * sinf(angleRadian));
}

// Create
void BonusWheelScene::pushPrizeIcon(const char* imagePath, const char* textPath, float angle, Node* spinWheel)
{
    auto prizeIcon = Sprite::create(imagePath);
    spinWheel->addChild(prizeIcon, 1);

    auto prizeHint = Sprite::create(textPath);
    prizeIcon->addChild(prizeHint, 1);
    prizeHint->setPosition(prizeIcon->getBoundingBox().size.width * 0.7f, prizeIcon->getBoundingBox().size.height * 0.1f);

    parentPrizeItem(angle, prizeIcon, spinWheel);
}

// on "init" you need to initialize your instance
bool BonusWheelScene::init()
{
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    this->center.x = visibleSize.width/2 + origin.x;
    this->center.y = visibleSize.height/2 + origin.y + 30.0f;

    // You can add more/remove some prizes from this list, it's scalable
    PrizeManager::addPrize(PRIZE::Brush_3X, 10, "tapblaze/brush.png", "tapblaze/x3.png");
    PrizeManager::addPrize(PRIZE::Life_30_min, 20, "tapblaze/heart.png", "tapblaze/30min.png");
    PrizeManager::addPrize(PRIZE::Hammer_1X, 20, "tapblaze/hammer.png", "tapblaze/x1.png");
    PrizeManager::addPrize(PRIZE::Gems_75, 5, "tapblaze/gem.png", "tapblaze/x75.png");
    PrizeManager::addPrize(PRIZE::Brush_1x, 20, "tapblaze/brush.png", "tapblaze/x1.png");
    PrizeManager::addPrize(PRIZE::Coins_750, 5, "tapblaze/coin.png", "tapblaze/x750.png");
    PrizeManager::addPrize(PRIZE::Hammer_3X, 10, "tapblaze/hammer.png", "tapblaze/x3.png");
    PrizeManager::addPrize(PRIZE::Gems_35, 10, "tapblaze/gem.png", "tapblaze/x35.png");

    //////////////////////////////////////// Graphics below
    // Spin wheel
    auto layerSpinWheel = Layer::create();
    layerSpinWheel->setPosition(0.0f, 0.0f);
    this->addChild(layerSpinWheel, 0);
    auto spinWheel = Sprite::create("tapblaze/wheel_sections_8.png");
    layerSpinWheel->addChild(spinWheel, 0);

    auto spinWheelBorder = Sprite::create("tapblaze/wheel_border.png");
    spinWheelBorder->setScale(0.8f, 0.8f);
    spinWheelBorder->setPosition(center);
    layerSpinWheel->addChild(spinWheelBorder, 2);

    auto arrow = Sprite::create("tapblaze/wheel_arrow.png");
    arrow->setPosition(center.x, center.y + 0.9f * spinWheelBorder->getBoundingBox().size.height / 2.0f);
    layerSpinWheel->addChild(arrow, 3);

    // Populate prizes
    int totalPrizes = PrizeManager::getNumPrize();
    float angleIncrement = 360.0f / totalPrizes;
    for(int i = 0; i < totalPrizes; i++)
    {
        float angleAggregate = angleIncrement / 2.0f + angleIncrement * i;
        PrizeObject* attr = PrizeManager::getAttribute((PRIZE)i);
        pushPrizeIcon(attr->image_path, attr->text_path, angleAggregate, spinWheel);
    }
    spinWheel->setPosition(center);
    spinWheel->setScale(0.8f,0.8f);

    // Buttons
    this->buttonPos.x = origin.x + visibleSize.width/2;
    this->buttonPos.y = origin.y + 50;

    auto playOnButton = MenuItemImage::create("tapblaze/spin_button.png","tapblaze/spin_button.png",CC_CALLBACK_1(BonusWheelScene::menuSpinCallback, this));
    playOnButton->setPosition(buttonPos);
    auto playOnMenu = Menu::create(playOnButton, NULL);
    playOnMenu->setPosition(Vec2::ZERO);
    this->addChild(playOnMenu, 1);
    auto playOnLabel = Sprite::create("tapblaze/playOn.png");
    playOnButton->addChild(playOnLabel, 1);
    playOnLabel->setPosition(playOnButton->getBoundingBox().size.width / 2.0f, playOnButton->getBoundingBox().size.height / 2.0f);

    auto resetButton = MenuItemImage::create("tapblaze/spin_button.png","tapblaze/spin_button.png",CC_CALLBACK_1(BonusWheelScene::resetWheel, this));
    resetButton->setPosition(0.0f, -500.0f);
    auto resetMenu = Menu::create(resetButton, NULL);
    resetMenu->setPosition(Vec2::ZERO);
    this->addChild(resetMenu, 1);
    auto resetLabel = Sprite::create("tapblaze/reset.png");
    resetButton->addChild(resetLabel, 1);
    resetLabel->setPosition(resetButton->getBoundingBox().size.width / 2.0f, resetButton->getBoundingBox().size.height / 2.0f);

    // Misc
    this->pSpinWheel = spinWheel;
    this->pLayerSpinWheel = layerSpinWheel;
    this->pPlayOnButton = playOnButton;
    this->pResetButton = resetButton;

    return true;
}

void BonusWheelScene::menuSpinCallback(Ref* pSender)
{
    // Hide play button
    this->pPlayOnButton->setPosition(0.0f, -500.0f);

    // Roll chance
    PRIZE prize = PrizeManager::rollPrize();
    printf("item: %i", prize);

    // Roll Animation
    rollAnimation(prize);

    // Prize animation
    prizePresent(prize);
}

// Ease backin
void BonusWheelScene::rollAnimation(PRIZE prize)
{
    // Math
    int totalPrizes = PrizeManager::getNumPrize();
    float angleIncrement = 360.0f / totalPrizes;
    float totalDegree = (int)prize * angleIncrement + 360.0f * NUM_TURNS + angleIncrement / 2.0f - 90.0f;
    float easeInDegree = totalDegree * BACK_ACC_DIST_RATIO;
    float midDegree = totalDegree * ROTATION_DIST_RATIO;
    float easeOutDegree = totalDegree * BACK_DEC_DIST_RATIO;
    float easeInDuration = SPIN_DURATION * BACK_ACC_TIME_RATIO;
    float midDuration = SPIN_DURATION * ROTATION_TIME_RATIO;
    float easeOutDuration = SPIN_DURATION * BACK_DEC_TIME_RATIO;

    // Turn back then forth
    auto startRotate = RotateBy::create(easeInDuration, Vec3(0,0,easeInDegree));
    EaseBackIn * startRotateEaseBackIn = EaseBackIn::create(startRotate);

    // Slow down gradually
    auto rotate = RotateBy::create(midDuration, Vec3(0,0,midDegree));
    EaseOut* slowDownRotate = EaseOut::create(rotate, 5.0f);

    // Pass destination a bit then turn back
    auto endRotate = RotateBy::create(easeOutDuration, Vec3(0,0,easeOutDegree));
    EaseBackOut* backRotate = EaseBackOut::create(endRotate);

    // Compose sequence
    auto sequence = Sequence::create(startRotateEaseBackIn, slowDownRotate, backRotate, NULL);
    this->pSpinWheel->runAction(sequence);
}

void BonusWheelScene::resetWheel(cocos2d::Ref* pSender)
{
    this->pSpinWheel->setRotation(0.0f);
    this->pLayerSpinWheel->setPosition(0.0f, 0.0f);
    this->pPlayOnButton->setPosition(this->buttonPos);
    this->pResetButton->setPosition(0.0f, -500.0f);

    if(this->pPrizeSprite != nullptr)
    {
        this->removeChild(this->pPrizeSprite, true);
        this->pPrizeSprite = nullptr;
    }
}

void BonusWheelScene::prizePresent(PRIZE prize)
{
    // Create prize icon, text & glow after 4 seconds
    const char* prizeIconPath = PrizeManager::getAttribute(prize)->image_path;
    const char* prizeTextPath = PrizeManager::getAttribute(prize)->text_path;
    auto prizeIcon = Sprite::create(prizeIconPath);
    this->addChild(prizeIcon, 1);
    prizeIcon->setPosition(0.0f, -500.0f);
    auto prizeHint = Sprite::create(prizeTextPath);
    prizeIcon->addChild(prizeHint, 1);
    prizeHint->setPosition(prizeIcon->getBoundingBox().size.width * 0.7f, prizeIcon->getBoundingBox().size.height * 0.1f);
    auto prizeGlow = Sprite::create("tapblaze/glow.png");
    prizeIcon->addChild(prizeGlow, -1);
    prizeGlow->setPosition(prizeIcon->getBoundingBox().size.width / 2.0f, prizeIcon->getBoundingBox().size.height / 2.0f);
    prizeGlow->runAction(RotateBy::create(SPIN_DURATION + PAUSE_DURATION + PRIZE_PRESENT_DURATION, Vec3(0, 0, 1300.0f)));
    prizeGlow->runAction(EaseBackIn::create(ScaleTo::create(SPIN_DURATION + PAUSE_DURATION + PRIZE_PRESENT_DURATION, 0.01f)));

    // Move the prize after 4.3 second
    auto snapToPrizePosition = MoveTo::create(0.0f, Vec2(this->center.x, this->center.y + pSpinWheel->getBoundingBox().size.height * 0.6f/2.0f));
    auto movement = MoveTo::create(2.0f, this->center);
    auto scale = ScaleTo::create(2.0f, 2.0f, 2.0f);
    auto move_scale = Spawn::create(movement, scale, NULL);
    auto sequence = Sequence::create(DelayTime::create(SPIN_DURATION + PAUSE_DURATION), snapToPrizePosition, move_scale, NULL);
    prizeIcon->runAction(sequence);

    // Hide wheel after 4.3 second
    auto hideWheel = MoveTo::create(0.0f, Vec2(0.0f, -500.0f));
    auto sequence2 = Sequence::create(DelayTime::create(SPIN_DURATION + PAUSE_DURATION), hideWheel, NULL);
    pLayerSpinWheel->runAction(sequence2);

    // Show reset button after 6.3 seconds
    auto showReset = MoveTo::create(0.0f, buttonPos);
    auto sequence3 = Sequence::create(DelayTime::create(SPIN_DURATION + PAUSE_DURATION + PRIZE_PRESENT_DURATION), showReset, NULL);
    pResetButton->runAction(sequence3);

    // Misc
    pPrizeSprite = prizeIcon;
}
