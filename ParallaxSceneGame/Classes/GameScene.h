#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "UIController.h"
#include "InputController.h"
#include "ParallaxController.h"
#include "CharacterController.h"

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // so I remove boilerplate code @mkrevatin
    CREATE_FUNC(GameScene);

private:
    std::unique_ptr<UIController> _uiController;
    std::unique_ptr<InputController> _inputController;
    std::unique_ptr<ParallaxController> _parallaxController;
    std::unique_ptr<CharacterController> _characterController;
};

#endif // __GAME_SCENE_H__