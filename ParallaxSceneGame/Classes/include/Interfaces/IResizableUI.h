#ifndef IRESIZABLEUI_H
#define IRESIZABLEUI_H

#include "cocos2d.h"

class IResizableUI {
public:
    virtual ~IResizableUI() = default;

    virtual void adjustForResolution(const cocos2d::Size& size) = 0;
};

#endif // IRESIZABLEUI_H