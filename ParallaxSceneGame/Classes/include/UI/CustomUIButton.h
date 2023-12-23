/*
    since the UI is most affected by the resolution and scale
    I've created this CustomUIButton that will be affected and 
    resized depending on the aspect ratio or size of the screen
    so it's always constant - not sure if that's a valid approach
    from UX or game design choice, but imo it's viable.
    Here we implement a small factory design by hiding the constructor.

*/
#ifndef UIBUTTON_H
#define UIBUTTON_H

#include "Interfaces/IResizableUI.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class CustomUIButton : public cocos2d::ui::Button, public IResizableUI {
public:
    virtual ~CustomUIButton() {}
    //let the creation be only through a texture provided, constructor private like a factory
    static CustomUIButton* create(const std::string& texture);

    void adjustForResolution(const cocos2d::Size& size) override;
};

#endif // UIBUTTON_H
