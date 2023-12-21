#ifndef ICONTROLLER_H
#define ICONTROLLER_H

#include <cocos2d.h>

class IController {
public:
    virtual ~IController() = default;

    // basic controller setup
    virtual void setup() = 0;

    // this is usually the best practice, not sure if I'll use it, but let the controller decide
    virtual void update(float delta) = 0;

};

#endif // ICONTROLLER_H