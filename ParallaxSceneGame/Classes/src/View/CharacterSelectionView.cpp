#include "View/CharacterSelectionView.h"

#include "Game/GameConstants.h"
#include "Game/GameEventsPriority.h"
#include "Game/GameSettings.h"

CharacterSelectionView::CharacterSelectionView(cocos2d::Node* parent, CharacterSelectionController* controller)
    : _aManager(AssetManagerSingleton::getInstance())
    , _parent(parent)
    , _controller(controller)
    , _blockingLayer(nullptr)
    , _menuBackground(nullptr)
    , _characterDisplayBackground(nullptr)
    , _characterDisplayBackgroundHeader(nullptr)
    , _currentCharacterSprite(nullptr)
    , _nextButton(nullptr)
    , _prevButton(nullptr)
    , _submitButton(nullptr)
    , _closeButton(nullptr) {
}

void CharacterSelectionView::setup() {
    createBlockingLayer();
    createMenuBackground();

    createCharacterDisplay();
    updateCharacterDisplay();

    createButtons();
    setupButtonListeners();

    updateLayout();

    _menuBackground->setVisible(false); // on start we want to hide this
    _blockingLayer->setVisible(false); // used as a click-blocker layer for the background acitvities
}

void CharacterSelectionView::show() {
    _blockingLayer->setVisible(true);
    _menuBackground->setVisible(true);

    // Ensure the menu is initially scaled down
    _menuBackground->setScale(0);

    auto scaleUpAction = cocos2d::ScaleTo::create(.5f, 1.0f); // 0.5 seconds to scale up to full size
    _menuBackground->runAction(scaleUpAction); // run animation

    if (_menuBackground->getParent() == nullptr) {
        _parent->addChild(_menuBackground, GameConstants::UI_MENU_Z_ORDER);
    }
}

void CharacterSelectionView::hide() {
    // Hide the character selection UI and then hide the blocking layer
    auto scaleDownAction = cocos2d::ScaleTo::create(.5f, .0f); // 0.5 seconds to scale up to full zero(almost)
    auto hideAction = cocos2d::CallFunc::create([this]() {
        _menuBackground->setVisible(false);
        _blockingLayer->setVisible(false); // Also hide the blocking layer
    });
    auto sequence = cocos2d::Sequence::create(scaleDownAction, hideAction, nullptr);
    _menuBackground->runAction(sequence);
}

void CharacterSelectionView::updateLayout() {
    // here we can actually adjust all the elements to fit different sizes or layouts, viewports, etc.
    // for now it's just simple scaling if a non-natural aspect ratio or size is used
    GameSettings& gameSettings = GameSettings::getInstance();

    // uniform scale factor based on the current and design aspect ratios
    float uniformScaleFactor = (gameSettings.getCurrentAspectRatio() != gameSettings.getDesignAspectRatio()) ?
        std::min(gameSettings.getScaleFactorWidth(), gameSettings.getScaleFactorHeight()) :
        gameSettings.getScaleFactorWidth();

    // Apply the calculated scale factor to _menuBackground
    if (_menuBackground) {
        _menuBackground->setScale(uniformScaleFactor);
    }

    // readjust in case of scaling
    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    if (_menuBackground) {
        // Recenter the _menuBackground after scaling
        _menuBackground->setPosition(origin.x + visibleSize.width * .5f, origin.y + visibleSize.height * .5f);
    }

    updateCharacterDisplay();
}

void CharacterSelectionView::createBlockingLayer() {
    // Setup _blockingLayer
    _blockingLayer = cocos2d::LayerColor::create(GameConstants::BLOCKING_LAYER_COLOR);
    _blockingLayer->setContentSize(cocos2d::Director::getInstance()->getVisibleSize());
    _blockingLayer->setPosition(cocos2d::Director::getInstance()->getVisibleOrigin());

    // Add the blocking layer directly to the scene (or a high-level parent node)
    _parent->addChild(_blockingLayer, GameConstants::UI_MENU_Z_ORDER); // High z-order to ensure it's on top

     // Touch listener to work as click blocker on margines outside of our view dialogue(menu)
    auto touchListener = cocos2d::EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = [this](cocos2d::Touch* touch, cocos2d::Event* event) -> bool {
        // Only consume the touch event if the blocking layer is visible
        return this->_blockingLayer->isVisible();
    };
    _blockingLayer->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, _blockingLayer);
}

void CharacterSelectionView::createMenuBackground() {
    // Setup _menuBackground
    _menuBackground = cocos2d::Sprite::create(_aManager.getFullPath("menu/menu_background.png"));

    auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

    _menuBackground->setPosition(origin.x + visibleSize.width * .5f, origin.y + visibleSize.height * .5f);
    _parent->addChild(_menuBackground, GameConstants::UI_MENU_Z_ORDER);
}

void CharacterSelectionView::createCharacterDisplay() {
    // Setup _characterDisplayBackground
    _characterDisplayBackground = cocos2d::Sprite::create(_aManager.getFullPath("menu/menu_display.png"));
    _characterDisplayBackground->setPosition(_menuBackground->getContentSize() * .5f);
    _menuBackground->addChild(_characterDisplayBackground);

    // Setup _characterDisplayBackgroundHeader
    _characterDisplayBackgroundHeader = cocos2d::Sprite::create(_aManager.getFullPath("menu/menu_header.png"));
    _characterDisplayBackgroundHeader->setPosition(cocos2d::Vec2(_characterDisplayBackground->getContentSize().width * .5f, _characterDisplayBackground->getContentSize().height));
    _characterDisplayBackground->addChild(_characterDisplayBackgroundHeader);
}

void CharacterSelectionView::updateCharacterDisplay() {
    // Get the path of the current character's image
    std::string characterImagePath = _controller->getCurrentCharacterPath();

    if (!_currentCharacterSprite) {
        // Create the sprite if it doesn't exist
        _currentCharacterSprite = cocos2d::Sprite::create(_aManager.getFullPath(characterImagePath));
        _characterDisplayBackground->addChild(_currentCharacterSprite);
    } else {
        // Update the texture if the sprite already exists
        _currentCharacterSprite->setTexture(_aManager.getFullPath(characterImagePath));
    }

    _currentCharacterSprite->setPosition(_characterDisplayBackground->getContentSize() * .5f);

    // just to fit properly in the background we scale it a bit, to make it more elegant and nice to the eye
    const float maxCharacterHeight = _characterDisplayBackground->getContentSize().height * .8f; // Use 80% of background height
    float spriteHeight = _currentCharacterSprite->getContentSize().height;
    if (spriteHeight > maxCharacterHeight) {
        float scaleRatio = maxCharacterHeight / spriteHeight;
        _currentCharacterSprite->setScale(scaleRatio);
    }
}

void CharacterSelectionView::createButtons() {
// container for the buttons
    auto buttonContainer = cocos2d::Node::create();
    float containerWidth = _menuBackground->getContentSize().width * .5f; // Define the width of the container
    float containerHeight = _menuBackground->getContentSize().height * .25f; // Define the height of the container
    buttonContainer->setContentSize(cocos2d::Size(containerWidth, containerHeight));
    
    // adding button container to the _menuBackground
    buttonContainer->setAnchorPoint(cocos2d::Vec2(.5f, .125f));
    buttonContainer->setPosition(cocos2d::Vec2(containerWidth, containerHeight * .5f));
    _menuBackground->addChild(buttonContainer);

    // Setup for buttons in the button container
    _prevButton = CustomUIButton::create(_aManager.getFullPath("menu/menu_arrow.png"));
    // the submit button doesn't have the label, but it has the text written on it. I know that isn't the common usage and because of
    // the localization it's better to give it a key and a localization manager, but didn't want to complicate stuff for this
    // small example
    _submitButton = CustomUIButton::create(_aManager.getFullPath("menu/menu_submit.png")); 
    _nextButton = CustomUIButton::create(_aManager.getFullPath("menu/menu_arrow.png"));
    _nextButton->setRotation(180); // Rotate the next button by 180 degrees, so we reuse the art

    // setup of positions
    _prevButton->setPosition(cocos2d::Vec2(0, containerHeight * .5f)); // left middle
    _submitButton->setPosition(cocos2d::Vec2(containerWidth * .5f, containerHeight * .5f)); // middle middle
    _nextButton->setPosition(cocos2d::Vec2(containerWidth, containerHeight * .5f)); // right middle

    buttonContainer->addChild(_prevButton);
    buttonContainer->addChild(_submitButton);
    buttonContainer->addChild(_nextButton);

    // Setup _closeButton, doesn't go to the button container
    _closeButton = CustomUIButton::create(_aManager.getFullPath("menu/menu_close.png"));
    // upper right corner of the _menuBackground
    _closeButton->setPosition(cocos2d::Vec2(_menuBackground->getContentSize().width - (_closeButton->getContentSize().width * 1.6f), _menuBackground->getContentSize().height - _closeButton->getContentSize().height));
    _closeButton->addClickEventListener(CC_CALLBACK_0(CharacterSelectionView::onCloseButtonClicked, this));
    _menuBackground->addChild(_closeButton);
}

void CharacterSelectionView::setupButtonListeners() {
    // setting up the events and functions for the buttons
    _prevButton->addClickEventListener([this](cocos2d::Ref* sender) {
        this->onArrowButtonClicked(-1);
    });

    _nextButton->addClickEventListener([this](cocos2d::Ref* sender) {
        this->onArrowButtonClicked(1);
    });

    _submitButton->addClickEventListener([this](cocos2d::Ref* sender) {
        this->onSelectButtonClicked();
    });

    _closeButton->addClickEventListener([this](cocos2d::Ref* sender) {
        this->onCloseButtonClicked();
    });
}

void CharacterSelectionView::onArrowButtonClicked(int direction) {
    _controller->selectCharacter(direction);
    updateCharacterDisplay();
}

void CharacterSelectionView::onSelectButtonClicked() {
    _controller->updateCharacter();
    hide();
}

void CharacterSelectionView::onCloseButtonClicked() {
    hide();
}