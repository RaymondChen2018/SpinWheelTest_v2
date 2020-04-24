#ifndef PROJ_ANDROID_PRIZEMANAGER_H
#define PROJ_ANDROID_PRIZEMANAGER_H
#include <unordered_map>
#include "PrizeObject.h"
class PrizeManager {
public:
    static void initialize();
    static void addPrize(PRIZE prize, int chance, const char* image_path, const char* text_path);
    static void addPrize(PrizeObject* obj); // Would be useful if one day we need to refactor this into linked-list
    static PRIZE rollPrize();
    static void unitTest();
    static int getNumPrize();
    static PrizeObject* getAttribute(PRIZE prize);

private:
    static PrizeManager * privGetInstance(void) {
        static PrizeManager przMngr;
        return &przMngr;
    }

    // Better than linked-list in our design case
    std::unordered_map<int, PrizeObject> chanceAttributes;
};
#endif
