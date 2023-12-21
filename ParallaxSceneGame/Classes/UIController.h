#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include "IController.h"
#include <cocos2d.h>
#include <IResizableUI.h>

class UIController : public IController {
public:
    enum class ScreenType {
        ASPECT_16_9,
        ASPECT_4_3,
        ASPECT_5_4,
        // Add other aspect ratios or resolutions? 
    };

    explicit UIController(cocos2d::Node* parent);

    void setup() override;
    void update(float delta) override;

    void registerUIElement(IResizableUI* element);
    void adjustUIElementsForResolution(const cocos2d::Size& size);

private:
    cocos2d::Node* _parent;
    cocos2d::Size _visibleSize;
    cocos2d::Vec2 _origin;
    std::vector<IResizableUI*> _uiElements;

    ScreenType determineScreenType();

    void setupUIForAspectRatio16_9();
    void setupUIForAspectRatio4_3();
    void setupUIForAspectRatio5_4();
    // Additional methods for other aspect ratios
};

#endif // UICONTROLLER_H