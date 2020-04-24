// Created by Ruiming
#include "PrizeManager.h"
#include <android/log.h>
#include "cocos2d.h"
#include "tinyxml2.h"
#include "PrizeObject.h"
USING_NS_CC;

PRIZE PrizeManager::rollPrize()
{
    PrizeManager* instance = privGetInstance();

    // Calculate sum of chances
    int chanceSum = 0;
    for(auto i : instance->chanceAttributes)
    {
        chanceSum += i.second.chance;
    }

    // generate a seed sample within 100
    float seed = random(0.0f, 100.0f);

    // Test against each prize's chance in 100 scale
    float percentageSum = 0.0f;
    PRIZE ret = PRIZE::NON_INITIALIZED;
    for(auto i : instance->chanceAttributes)
    {
        // Scale the chance
        float percentage = i.second.chance * 100 / (float)chanceSum;

        // this is the prize
        if (seed < percentageSum + percentage)
        {
            ret = (PRIZE)i.first;
            break;
        }

        percentageSum += percentage;
    }

    assert(ret != PRIZE::NON_INITIALIZED);
    return ret;
}

// Test occurance of 8 prizes in 1000 test spins
void PrizeManager::unitTest()
{
    int sample = 1000;
    int occuranceTable[8] = {0,0,0,0,0,0,0,0};
    for(int i=0;i<sample;i++)
    {
        PRIZE prize = rollPrize();
        int index = (int)prize;
        occuranceTable[index]++;
    }

    __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "Spin Wheel Test, 1000 Spins: \n");

    int occurance = occuranceTable[(int)PRIZE::Brush_1x];
    float chance = 100.0f * occurance / (float)sample;
    __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "Brush_1x: %i, percentage: %f %c\n", occurance, chance, '%');

    occurance = occuranceTable[(int)PRIZE::Brush_3X];
    chance = 100.0f * occurance / (float)sample;
    __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "Brush_3X: %i, percentage: %f %c\n", occurance, chance, '%');

    occurance = occuranceTable[(int)PRIZE::Coins_750];
    chance = 100.0f * occurance / (float)sample;
    __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "Coins_750: %i, percentage: %f %c\n", occurance, chance, '%');

    occurance = occuranceTable[(int)PRIZE::Gems_35];
    chance = 100.0f * occurance / (float)sample;
    __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "Gems_35: %i, percentage: %f %c\n", occurance, chance, '%');

    occurance = occuranceTable[(int)PRIZE::Gems_75];
    chance = 100.0f * occurance / (float)sample;
    __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "Gems_75: %i, percentage: %f %c\n", occurance, chance, '%');

    occurance =  occuranceTable[(int)PRIZE::Hammer_1X];
    chance = 100.0f * occurance / (float)sample;
    __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "Hammer_1X: %i, percentage: %f %c\n", occurance, chance, '%');

    occurance = occuranceTable[(int)PRIZE::Hammer_3X];
    chance = 100.0f * occurance / (float)sample;
    __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "Hammer_3X: %i, percentage: %f %c\n", occurance, chance, '%');

    occurance = occuranceTable[(int)PRIZE::Life_30_min];
    chance = 100.0f * occurance / (float)sample;
    __android_log_print(ANDROID_LOG_DEBUG, "TRACKERS", "Life_30_min: %i, percentage: %f %c\n", occurance, chance, '%');
}

int PrizeManager::getNumPrize() {
    PrizeManager* instance = privGetInstance();
    return instance->chanceAttributes.size();
}

PrizeObject* PrizeManager::getAttribute(PRIZE prize)
{
    PrizeManager* instance = privGetInstance();
    return &(instance->chanceAttributes[(int)prize]);
}

void PrizeManager::initialize()
{

}

void PrizeManager::addPrize(PrizeObject* obj)
{
    PrizeManager* instance = privGetInstance();
    instance->chanceAttributes.insert({(int)obj->prize, *obj});
}

void PrizeManager::addPrize(PRIZE prize, int chance, const char *image_path, const char *text_path)
{
    PrizeManager* instance = privGetInstance();
    PrizeObject obj(prize, chance, image_path, text_path);
    instance->chanceAttributes.insert({(int)prize, obj});
}



