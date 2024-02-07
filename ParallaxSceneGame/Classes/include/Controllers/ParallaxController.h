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
        Foreground,
        Scrollable_UI
    };

    ParallaxController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher);
    virtual ~ParallaxController() = default;

    ParallaxController(const ParallaxController&) = delete;
    ParallaxController& operator=(const ParallaxController&) = delete;
    ParallaxController(ParallaxController&&) = delete;
    ParallaxController& operator=(ParallaxController&&) = delete;

    void setup() override;
    void update(float delta) override;

    void addSpriteToLayer(const std::string& filename, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& position, int zOrder);
    void addSpriteToLayerWithAutoZOrder(const std::string& filename, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& position);

    // New method for adding any cocos2d::Node to a parallax layer
    void addNodeToLayer(cocos2d::Node* node, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& position, int zOrder);
    void addNodeToLayerWithAutoZOrder(cocos2d::Node* node, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& originalPosition);

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
