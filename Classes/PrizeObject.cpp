// Created by Ruiming on 4/23/2020.
#include "PrizeObject.h"
#include "cocos2d.h"

PrizeObject::PrizeObject(PRIZE _prize, int _chance, const char *_image, const char *_text)
{
    this->prize = _prize;
    this->chance = _chance;
    memcpy(this->image_path, _image, strlen(_image));
    memcpy(this->text_path, _text, strlen(_text));
    // Terminate string
    this->image_path[strlen(_image)] = '\0';
    this->text_path[strlen(_text)] = '\0';
}

PrizeObject::PrizeObject(const PrizeObject &cpy)
{
    this->chance = cpy.chance;
    memcpy(this->image_path, cpy.image_path, MAX_CHAR_FILEPATH);
    memcpy(this->text_path, cpy.text_path, MAX_CHAR_FILEPATH);
}

PrizeObject &PrizeObject::operator=(const PrizeObject & cpy)
{
    this->chance = cpy.chance;
    memcpy(this->image_path, cpy.image_path, MAX_CHAR_FILEPATH);
    memcpy(this->text_path, cpy.text_path, MAX_CHAR_FILEPATH);
    return *this;
}

void PrizeObject::doThing() {

}

