#include "ParallaxController.h"
#include "AssetManagerSingleton.h"

ParallaxController::ParallaxController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher) 
    : _parent(parent), _eventDispatcher(eventDispatcher) {
    // Note: setup() is called separately, not in the constructor
}

void ParallaxController::setup() {
    auto listener = cocos2d::EventListenerCustom::create("EVENT_SCENE_DRAGGED", [this](cocos2d::EventCustom* event) {
        this->onSceneDragged(event);
        });
    _eventDispatcher.addEventListenerWithSceneGraphPriority(listener, _parent);

    // Initialize Parallax Nodes for each layer
    _parallaxNodes[ParallaxLayer::Background] = cocos2d::ParallaxNode::create();
    _parallaxNodes[ParallaxLayer::Focus] = cocos2d::ParallaxNode::create();
    _parallaxNodes[ParallaxLayer::Foreground] = cocos2d::ParallaxNode::create();

    // Add Parallax Nodes to the parent node
    for (auto& pair : _parallaxNodes) {
        _parent->addChild(pair.second);
    }
}

void ParallaxController::update(float delta) {
    // Implement any update logic for the parallax layers if needed
}

void ParallaxController::addSpriteToLayer(const std::string& filename, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& position, int zOrder) {
    auto sprite = AssetManagerSingleton::getInstance().GetSprite(filename);
    if (sprite) {
        sprite->setName(filename);
        _parallaxNodes[layer]->addChild(sprite, zOrder, ratio, position);
        _highestZOrders[layer] = std::max(_highestZOrders[layer], zOrder);
    }
}

void ParallaxController::addSpriteToLayerWithAutoZOrder(const std::string& filename, ParallaxLayer layer, const cocos2d::Vec2& ratio, const cocos2d::Vec2& position) {
    int nextZOrder = _highestZOrders[layer] + 1;
    addSpriteToLayer(filename, layer, ratio, position, nextZOrder);
}

cocos2d::ParallaxNode* ParallaxController::getParallaxNode(ParallaxLayer layer) {
    return _parallaxNodes[layer];
}

void ParallaxController::onSceneDragged(cocos2d::EventCustom* event) {
    auto diff = static_cast<cocos2d::Vec2*>(event->getUserData());
    if (diff) {
        // Define movement limits
        float limit = 1000; // Adjust as needed

        // Iterate over each parallax layer and update its position
        for (auto& pair : _parallaxNodes) {
            if (pair.first == ParallaxLayer::Focus) // the focus layer should be static so the front and back moves around it
            {
                continue;
            }
            auto node = pair.second;
            auto newPos = node->getPosition() + cocos2d::Vec2(diff->x, 0); // Modify y-coordinate as needed

            // Apply limits to the movement
            newPos.x = std::max(newPos.x, -limit);
            newPos.x = std::min(newPos.x, limit);

            node->setPosition(newPos);
        }
    }
}