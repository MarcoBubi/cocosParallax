#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();

    virtual bool init() override;

    void makeCharacterJump();

    // so I remove boilerplate code @mkrevatin
    CREATE_FUNC(GameScene);

private:
    //TODO: refactor this for now, I don't think this is the place for it ... or...@mkrevatin
    //cool stuff about cocos2d-x is that the node is now owner of this and on node(scene) deletion
    //the node is deallocated automatically, no need to specify it! 
    cocos2d::ParallaxNode* _parallaxNode;
    cocos2d::ParallaxNode* _parallaxNode2;
    cocos2d::ParallaxNode* _parallaxNode3;
};

#endif // __GAME_SCENE_H__