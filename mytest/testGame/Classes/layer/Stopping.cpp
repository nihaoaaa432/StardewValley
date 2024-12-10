#include "StoppingLayer.h"
#include"cocos2d.h"
USING_NS_CC;
// 场景创建函数
cocos2d::Scene* StoppingLayer::createLayer()
{
    // 创建场景对象
    auto scene = cocos2d::Scene::create();

    // 创建层对象
    auto layer = StoppingLayer::create();

    // 将层对象添加到场景中
    scene->addChild(layer);

    return scene;
}

// 初始化函数
bool StoppingLayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 获取屏幕尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 背包背景
    auto background = Sprite::create("Stopping.png");
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background, 1);

    // 调用创建菜单函数
    createMenu();

    // 设置键盘监听
    auto listener = cocos2d::EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(StoppingLayer::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// 创建按钮并添加事件监听器
void StoppingLayer::createMenu()
{
    // 设置按钮
    settingButton = cocos2d::ui::Button::create("Stopping.png", "Stopping.png");
    settingButton->setPosition(cocos2d::Vec2(200, 200));
    settingButton->addTouchEventListener(CC_CALLBACK_2(StoppingLayer::onSettingButton, this));
    this->addChild(settingButton);

    // 退出按钮
    quitButton = cocos2d::ui::Button::create("Quit.png", "Quit.png");
    quitButton->setPosition(cocos2d::Vec2(200, 100));
    quitButton->addTouchEventListener(CC_CALLBACK_2(StoppingLayer::onQuitButton, this));
    this->addChild(quitButton);
}

// 响应设置按钮点击事件
void StoppingLayer::onSettingButton(cocos2d::Ref* sender, cocos2d::ui::Button::TouchEventType type)
{
    if (type == cocos2d::ui::Button::TouchEventType::ENDED)
    {
        // 切换到设置场景
        auto settingScene = cocos2d::Scene::create();
        // 这里你需要创建你的设置界面，并将其添加到场景中
        // auto settingLayer = SettingLayer::create();
        // settingScene->addChild(settingLayer);
        cocos2d::Director::getInstance()->replaceScene(settingScene);
    }
}

// 响应退出按钮点击事件
void StoppingLayer::onQuitButton(cocos2d::Ref* sender, cocos2d::ui::Button::TouchEventType type)
{
    if (type == cocos2d::ui::Button::TouchEventType::ENDED)
    {
        // 退出游戏
        cocos2d::Director::getInstance()->end();
    }
}

// 响应键盘事件
void StoppingLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE)
    {
        // 隐藏暂停界面
        this->setVisible(false);
    }
}