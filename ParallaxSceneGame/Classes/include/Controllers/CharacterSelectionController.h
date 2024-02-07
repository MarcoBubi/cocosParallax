#ifndef CHARACTERSELECTIONCONTROLLER_H
#define CHARACTERSELECTIONCONTROLLER_H

#include "Interfaces/IController.h"
#include <cocos2d.h>
#include <vector>

class CharacterSelectionController : public IController {
public:
    CharacterSelectionController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher);
    virtual ~CharacterSelectionController() = default;

    CharacterSelectionController(const CharacterSelectionController&) = delete;
    CharacterSelectionController& operator=(const CharacterSelectionController&) = delete;
    CharacterSelectionController(CharacterSelectionController&&) = delete;
    CharacterSelectionController& operator=(CharacterSelectionController&&) = delete;

    void setup() override;
    void update(float delta) override;

    void selectCharacter(int step);
    void updateCharacter();

    void addCharacterPath(const std::string& path);
    std::string getCurrentCharacterPath() const;

private:
    cocos2d::Node* _parent;
    cocos2d::EventDispatcher& _eventDispatcher;
    std::vector<std::string> _characterImagePaths;
    size_t _currentCharacterIndex;

};

#endif // CHARACTERSELECTIONCONTROLLER_H
