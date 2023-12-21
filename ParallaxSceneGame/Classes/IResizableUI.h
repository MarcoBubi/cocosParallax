#ifndef IRESIZABLEUI_H
#define IRESIZABLEUI_H

#include "cocos2d.h"

class IResizableUI {
public:
    virtual void adjustForResolution(const cocos2d::Size& size) = 0;

    virtual ~IResizableUI() {}
};

#endif // IRESIZABLEUI_H