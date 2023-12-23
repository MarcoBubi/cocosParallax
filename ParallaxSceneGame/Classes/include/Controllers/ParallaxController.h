#ifndef PARALLAXCONTROLLER_H
#define PARALLAXCONTROLLER_H

#include "Interfaces/IController.h"
#include <map>
#include <string>
#include <cocos2d.h>

class ParallaxController : public IController {
public:
    enum class ParallaxLayer {
        Background,
        Focus,
        Foreground
    };

    ParallaxController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher);
    virtual ~ParallaxController();

    ParallaxController(const ParallaxController&) = delete;
    ParallaxController& operator=(const ParallaxController&) = delete;
    ParallaxController(ParallaxController&&) = delete;
    ParallaxController& operator=(ParallaxController&&) = delete;

    void setup() override;
    void update(float delta) override;

    void addSpriteToLayer(const std::string& filename, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& position, int zOrder);
    void addSpriteToLayerWithAutoZOrder(const std::string& filename, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& position);

    cocos2d::ParallaxNode* getParallaxNode(ParallaxLayer layer);

    void scaleSpriteForCurrentResolution(cocos2d::Sprite& sprite);

private:
    cocos2d::Node* _parent;
    cocos2d::EventDispatcher& _eventDispatcher;
    std::map<ParallaxLayer, cocos2d::ParallaxNode*> _parallaxNodes;
    std::map<ParallaxLayer, int> _highestZOrders;

    void onSceneDragged(cocos2d::EventCustom* event);
};

#endif // PARALLAXCONTROLLER_H
