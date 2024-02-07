#ifndef __GAME_CONSTANTS_H__
#define __GAME_CONSTANTS_H__

#include <cocos2d.h>

class GameConstants {
public:
    // game constants used and predefined for the game
    static const char* TEXTURES_DIR;
    static const int UI_MENU_Z_ORDER;
    static const int UI_LAYER_Z_ORDER;
    static const int SCROLLABLE_UI_LAYER_Z_ORDER;
    static const cocos2d::Size DESIGN_RESOLUTION;
    static const cocos2d::Color4B BLOCKING_LAYER_COLOR;
};

#endif // __GAME_CONSTANTS_H__
