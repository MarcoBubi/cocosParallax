#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "Controllers/UIController.h"
#include "Controllers/InputController.h"
#include "Controllers/ParallaxController.h"
#include "Controllers/CharacterController.h"
#include "AssetManager/AssetManagerSingleton.h"
#include "cocos2d.h"
#include <memory>

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);

private:
    std::unique_ptr<UIController> _uiController;
    std::unique_ptr<InputController> _inputController;
    std::unique_ptr<ParallaxController> _parallaxController;
    std::unique_ptr<CharacterController> _characterController;
};

#endif // __GAME_SCENE_H__
