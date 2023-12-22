#ifndef PARALLAXCONTROLLER_H
#define PARALLAXCONTROLLER_H

#include "IController.h"
#include <map>
#include <string>

class ParallaxController : public IController {
public:
    enum class ParallaxLayer {
        Background,
        Focus,
        Foreground
    };

    explicit ParallaxController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher);

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
    // highest z order per layer - I don't like this approach, but it's important to have it imo @mkrevatin
    std::map<ParallaxLayer, int> _highestZOrders;

    void onSceneDragged(cocos2d::EventCustom* event);
};

#endif // PARALLAXCONTROLLER_H