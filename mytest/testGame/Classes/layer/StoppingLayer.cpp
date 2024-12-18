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
    background->setScale(0.5);
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background, 1);

    // 设置按钮
    auto settingButton = ui::Button::create("sand.png", "sand.png");
    settingButton->setContentSize(Size(30, 20));
    settingButton->setPosition(Vec2(visibleSize.width / 2 + origin.x - 60, visibleSize.height / 2 + origin.y - 20));
    settingButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onSettingButton, this));
    this->addChild(settingButton, 2);

    // 退出按钮
    auto quitButton = ui::Button::create("Quit.png", "Quit.png");
    quitButton->setScale(0.4f);
    quitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x + 150, visibleSize.height / 2 + origin.y - 80));
    quitButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onQuitButton, this));
    this->addChild(quitButton, 2);

    // 注册键盘事件监听器
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(StoppingLayer::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// 更新暂停界面位置
void StoppingLayer::updatePosition(cocos2d::Vec2 position) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto backpackSize = this->getContentSize(); // 假设背包界面有getContentSize()方法
    position = position - Vec2(backpackSize.width / 2, backpackSize.height / 2);
    this->setPosition(position);
};

// 响应设置按钮点击事件
void StoppingLayer::onSettingButton(cocos2d::Ref* sender) {
    // 切换到设置场景
    auto settingScene = Scene::create();
    Director::getInstance()->replaceScene(settingScene);
}

// 响应退出按钮点击事件
void StoppingLayer::onQuitButton(cocos2d::Ref* sender) {
    // 退出游戏
    Director::getInstance()->end();
}

// 响应键盘事件
void StoppingLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        currentPage = (currentPage == 0) ? 1 : 0; // 切换当前页面索引
        this->setVisible(currentPage == 1); // 根据当前页面索引显示或隐藏
    }
}