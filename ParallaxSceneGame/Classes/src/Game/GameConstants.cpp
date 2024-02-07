#include "Game/GameConstants.h"

const char* GameConstants::TEXTURES_DIR = "textures/";  // Path for the textures
const int GameConstants::UI_MENU_Z_ORDER = 1000;		// this should have priority over all
const int GameConstants::UI_LAYER_Z_ORDER = 100;        // This can be increased if needed
const int GameConstants::SCROLLABLE_UI_LAYER_Z_ORDER = 99;
const cocos2d::Size GameConstants::DESIGN_RESOLUTION = cocos2d::Size(1920, 1080);
const cocos2d::Color4B GameConstants::BLOCKING_LAYER_COLOR = cocos2d::Color4B(0, 0, 0, 128);