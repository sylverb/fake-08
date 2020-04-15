#pragma once

#include <string>

#include "graphics.h"


class Cart {
    std::string fullCartText;


    public:
    Cart (std::string filename);

    std::string Filename;
    std::string LuaString;
    std::string SpriteSheetString;
    std::string SpriteFlagsString;
    std::string MapString;

    //SpriteSheet CartSpriteSheet;
    //uint8_t map_data[128 * 128];

};
