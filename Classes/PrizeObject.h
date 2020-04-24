// Created by Ruiming on 4/23/2020.
#ifndef PROJ_ANDROID_PRIZEOBJECT_H
#define PROJ_ANDROID_PRIZEOBJECT_H
enum class PRIZE : int
{
    NON_INITIALIZED = -1,
    Brush_3X = 0,// 10%
    Life_30_min = 1,// 20%
    Hammer_1X = 2,// 20%
    Gems_75 = 3,// 5%
    Brush_1x = 4,// 20%
    Coins_750 = 5,// 5%
    Hammer_3X = 6,// 10%
    Gems_35 = 7,// 10%
};
#define MAX_CHAR_FILEPATH 64
class PrizeObject {
public:
    PrizeObject() = default;
    PrizeObject(PRIZE _prize, int _chance, const char* _image, const char* _text);
    PrizeObject(const PrizeObject& cpy);
    PrizeObject& operator= ( const PrizeObject & );
    ~PrizeObject() = default; // nothing to deallocate because nothing is on heap.

    int chance;
    PRIZE prize;
    char image_path[MAX_CHAR_FILEPATH];
    char text_path[MAX_CHAR_FILEPATH];

    // Stub method for children class;
    // Since in the limited scope of this test, every prize is identical and have no unique behaviour,
    // so I used a collection of the same objects instead of having inherited objects
    virtual void doThing();
};
#endif
