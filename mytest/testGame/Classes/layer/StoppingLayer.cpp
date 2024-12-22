#include "StoppingLayer.h"
#include "cocos2d.h"
USING_NS_CC;

// 单例对象指针初始化为nullptr
StoppingLayer* StoppingLayer::_instance = nullptr;


// 获取单例对象
StoppingLayer* StoppingLayer::getInstance() {
    if (_instance == nullptr) {
        _instance = new StoppingLayer;
        if (!_instance->init()) {
            delete _instance;
            _instance = nullptr;
            CCLOG("StoppingLayer initialization failed!");
        }
    }
    return _instance;
}


// 初始化单例对象
bool StoppingLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    currentPage = 0; // 默认不显示暂停层

    // 获取屏幕尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 暂停层背景
    auto background = Sprite::create("Stopping.png");
    background->setScale(0.7);
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background, 1);

    // 创建设置界面
    settingLayer = Layer::create();
    this->addChild(settingLayer,3);
    auto settingBackground = Sprite::create("Stopping.png");
    settingBackground->setScale(0.7);
    settingLayer->setVisible(false);
    settingBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    settingLayer->addChild(settingBackground);

    // 音乐按钮
    auto musicButton = ui::Button::create("MusicButtonOff.png", "MusicButtonOff.png"); // 初始为关闭状态
    musicButton->setScale(1.4f);
    musicButton->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y - 100));
    settingLayer->addChild(musicButton);
    musicButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onMusicButton, this));
    // 返回暂停界面按钮
    auto backButton = ui::Button::create("BackButton.png", "BackButton.png");
    backButton->setScale(1.4f);
    backButton ->setPosition(Vec2(visibleSize.width / 2 + origin.x - 180, visibleSize.height / 2 + origin.y - 100));
    settingLayer->addChild(backButton);
    backButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onBackButton, this));


    // 设置按钮
    auto settingButton = ui::Button::create("SettingButton.png", "SettingButton.png");
    settingButton->setScale(1.2f);
    settingButton->setPosition(Vec2(visibleSize.width / 2 + origin.x - 180, visibleSize.height / 2 + origin.y - 100));
    settingButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onSettingButton, this));
    this->addChild(settingButton, 2);

    // 退出按钮
    auto quitButton = ui::Button::create("Quit.png", "Quit.png");
    quitButton->setScale(0.4f);
    quitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x +200, visibleSize.height / 2 + origin.y - 100));
    quitButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onQuitButton, this));
    this->addChild(quitButton, 2);

    return true;
}

// 更新暂停界面位置
void StoppingLayer::updatePosition(cocos2d::Vec2 position) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto backpackSize = this->getContentSize(); 
    position = position - Vec2(backpackSize.width / 2, backpackSize.height / 2);
    this->setPosition(position);
};

// 响应设置按钮点击事件
void StoppingLayer::onSettingButton(cocos2d::Ref* sender) {
    // 切换到设置场景
    if(!settingLayer->isVisible()) settingLayer->setVisible(true);
}

// 响应退出按钮点击事件
void StoppingLayer::onQuitButton(cocos2d::Ref* sender) {
    // 退出游戏
    if(!settingLayer->isVisible())   Director::getInstance()->end();
}

// 响应设置按钮点击事件
void StoppingLayer::onMusicButton(cocos2d::Ref* sender) {
    // 切换按钮的图片
    auto button = dynamic_cast<ui::Button*>(sender);
    if (button->getNormalFile().file == "MusicButtonOff.png") {
        button->loadTextures("MusicButtonOn.png", "MusicButtonOn.png"); // 切换到开启状态
    }
    else {
        button->loadTextures("MusicButtonOff.png", "MusicButtonOff.png"); // 切换到关闭状态
    }
    
}

// 响应设置按钮点击事件
void StoppingLayer::onBackButton(cocos2d::Ref* sender) {
    // 关闭设置界面
    if (settingLayer->isVisible()) settingLayer->setVisible(false);
}

// 处理esc按键
void StoppingLayer::onEscPress() {
    if (settingLayer->isVisible())  settingLayer->setVisible(false);
    else  this->setVisible(!this->isVisible());
}