#ifndef UICONTROLLER_H
#define UICONTROLLER_H

#include "Interfaces/IController.h"
#include "Interfaces/IResizableUI.h"
#include <vector>
#include <cocos2d.h>

class UIController : public IController {
public:
    explicit UIController(cocos2d::Node* parent);
    virtual ~UIController();

    UIController(const UIController&) = delete;
    UIController& operator=(const UIController&) = delete;
    UIController(UIController&&) = delete;
    UIController& operator=(UIController&&) = delete;

    void setup() override;
    void update(float delta) override;

    void registerUIElement(IResizableUI* element);

private:
    cocos2d::Node* _parent;
    cocos2d::Size _visibleSize;
    float _scaleFactorWidth;
    float _scaleFactorHeight;
    std::vector<IResizableUI*> _uiElements;

    void calculateScaleFactors();
};

#endif // UICONTROLLER_H
