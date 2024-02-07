#ifndef CHARACTERSELECTIONVIEW_H
#define CHARACTERSELECTIONVIEW_H

#include "Controllers/CharacterSelectionController.h"
#include "AssetManager/AssetManagerSingleton.h"
#include "UI/CustomUIButton.h"
#include <cocos2d.h>

class CharacterSelectionView {
public:
    CharacterSelectionView(cocos2d::Node* parent, CharacterSelectionController* controller);
    virtual ~CharacterSelectionView() = default; // all allocation is handled by the cocos2d::Ref

    CharacterSelectionView(const CharacterSelectionView&) = delete;
    CharacterSelectionView& operator=(const CharacterSelectionView&) = delete;

    CharacterSelectionView(CharacterSelectionView&&) = delete;
    CharacterSelectionView& operator=(CharacterSelectionView&&) = delete;

    void setup();
    void show();
    void hide();

    void updateLayout();

private:
    AssetManagerSingleton& _aManager;
    cocos2d::Node* _parent;
    CharacterSelectionController* _controller; // perhaps we may want to use a different controller or reassign, so that's why raw *

    cocos2d::LayerColor* _blockingLayer; // could be a sprite too, but wanted to distinct it since SRP principle
    cocos2d::Sprite* _menuBackground;
    cocos2d::Sprite* _characterDisplayBackground;
    cocos2d::Sprite* _characterDisplayBackgroundHeader;

    cocos2d::Sprite* _currentCharacterSprite;
    CustomUIButton* _nextButton;
    CustomUIButton* _prevButton;
    CustomUIButton* _submitButton;
    CustomUIButton* _closeButton;

    void createBlockingLayer();
    void createMenuBackground();

    void createCharacterDisplay();
    void updateCharacterDisplay();

    void createButtons();
    void setupButtonListeners();
    
    void onArrowButtonClicked(int direction);
    void onSelectButtonClicked();
    void onCloseButtonClicked();
};

#endif // CHARACTERSELECTIONVIEW_H
