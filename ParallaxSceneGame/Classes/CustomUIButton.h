#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "IResizableUI.h"

class CustomUIButton : public cocos2d::ui::Button, public IResizableUI {
public:
    // Destructor
    virtual ~CustomUIButton();

    // Implement the adjustForResolution method from IResizableUI
    void adjustForResolution(const cocos2d::Size& size) override;

    // Additional methods and members as needed
};

#endif // UIBUTTON_H
