#include "Controllers/CharacterSelectionController.h"

#include "Game/GameEvents.h"

CharacterSelectionController::CharacterSelectionController(cocos2d::Node* parent, cocos2d::EventDispatcher& eventDispatcher)
    : _parent(parent), _eventDispatcher(eventDispatcher), _currentCharacterIndex(0) {
}

void CharacterSelectionController::setup() {
    // this could be separated to some kind of model if needed
    // but since it's quite coupled, I'll keep the model-controller together
    // since the model makes no big sense here
    // the data is added through the addCharacterPath
    // if expanded, make sure to load the data from some kind of prefab
    // or data format, to make it more flexible and dynamic
}

void CharacterSelectionController::update(float delta) {
    // Update method called each frame, if needed
}

void CharacterSelectionController::selectCharacter(int step) {
    int characterCount = static_cast<int>(_characterImagePaths.size());

    // Update the current character index with the step and by this we are sure it around correctly, not oob(oor)
    _currentCharacterIndex = (_currentCharacterIndex + step + characterCount) % characterCount;
}

void CharacterSelectionController::updateCharacter() {
    if (_currentCharacterIndex < _characterImagePaths.size()) {
        std::string currentPath = _characterImagePaths[_currentCharacterIndex];
        cocos2d::EventCustom event(GameEvents::EVENT_CHARACTER_AVATAR_CHANGED);

        auto dataPath = new std::string(currentPath);
        event.setUserData(dataPath);
        _eventDispatcher.dispatchEvent(&event);
    }
}

void CharacterSelectionController::addCharacterPath(const std::string& path) {
    _characterImagePaths.push_back(path);
}

std::string CharacterSelectionController::getCurrentCharacterPath() const {
    return _characterImagePaths[_currentCharacterIndex];
}
