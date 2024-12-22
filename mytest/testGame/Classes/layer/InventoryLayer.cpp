#include "InventoryLayer.h"
#include "StoppingLayer.h"
#include "../scene/MapScene.h"
#include "cocos2d.h"
USING_NS_CC;

// 单例对象指针初始化为nullptr
InventoryLayer* InventoryLayer::_instance = nullptr;

// 获取单例对象
InventoryLayer* InventoryLayer::getInstance() {
    if (_instance == nullptr) {
        _instance = new InventoryLayer;
        if (!_instance->init()) {
            delete _instance;
            _instance = nullptr;
            CCLOG("InventoryLayer initialization failed!");
        }
    }
    return _instance;
}

// 初始化单例对象
bool InventoryLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // 获取屏幕尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 背包背景
    auto background = Sprite::create("Inventory.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x-20, visibleSize.height / 2 + origin.y+40));
    this->addChild(background, 1);

    // 创建侧边按钮栏
    buttonBar = Node::create(); // 按钮栏节点，指针表示数组
    buttonBar->setPosition(Vec2(953, 567));
    this->addChild(buttonBar, 2);

    // 创建物品页面
    itemPage = Layer::create();
    itemPage->setName("ItemPage");  // 设置名称以便调试
    this->addChild(itemPage, 1);

    // 在物品页面中添加内容
    auto itemLabel = Label::createWithSystemFont("itemPage", "Arial", 30);
    itemLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    itemPage->addChild(itemLabel);

    // 创建社交页面
    socialPage = Layer::create();
    auto socialBackground= Sprite::create("SocialPage.png");
    socialBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x+70, visibleSize.height / 2 + origin.y+35));
    
    // 获取背景图的原始大小
    Size backgroundSize = socialBackground->getContentSize();
    // 设置背景图的缩放比例
    socialBackground->setScale(0.8f);

    socialPage->addChild(socialBackground, 1);
    socialPage->setName("SocialPage");  // 设置名称以便调试
    this->addChild(socialPage, 1);

    // 在社交页面中添加内容
    auto socialLabel = Label::createWithSystemFont("SocialPage", "Arial", 30);
    socialLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    socialPage->addChild(socialLabel,2);

    // 添加按钮（物品、社交）
    auto itemButton = ui::Button::create("ItemButton.png"); // 物品按钮
    itemButton->setContentSize(Size(60, 60));
    itemButton->setPosition(Vec2(33, -33));
    buttonBar->addChild(itemButton);


    auto socialButton = ui::Button::create("SocialButton.png"); // 社交按钮
    socialButton->setContentSize(Size(60, 60));

    socialButton->setPosition(Vec2(33, -123));
    buttonBar->addChild(socialButton);

    // 默认显示物品页面
    currentPage = 0;
    switchToPage(currentPage);


    // 添加鼠标监听事件
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(InventoryLayer::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 添加按钮回调（用于切换页面）
    itemButton->addClickEventListener([this](Ref* sender) {
        this->switchToPage(0); // 切换到物品页面
        });

    socialButton->addClickEventListener([this](Ref* sender) {
        this->switchToPage(1); // 切换到社交关系页面
        });

    return true;
}


// 更新背包界面位置
void InventoryLayer::updatePosition(cocos2d::Vec2 position) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto backpackSize = this->getContentSize(); // 假设背包界面有getContentSize()方法
    position = position - Vec2(backpackSize.width / 2, backpackSize.height / 2);
    this->setPosition(position);
};

// 切换页面
void InventoryLayer::switchToPage(int pageIndex) {
    // 设置页面的可见性
    if (pageIndex == 0) {
        
        itemPage->setVisible(true);
        socialPage->setVisible(false);
    }
    else if (pageIndex == 1) {
        itemPage->setVisible(false);
        socialPage->setVisible(true);
    }
    currentPage = pageIndex; // 更新当前页面索引
}

// 鼠标点击事件
void InventoryLayer::onMouseDown(cocos2d::Event* event) {
    auto mouseEvent = (EventMouse*)event;
    auto mousePos = mouseEvent->getLocation();

    // 获取按钮区域（物品按钮和社交按钮的矩形区域）
    auto itemButtonArea = Rect(Director::getInstance()->getVisibleSize().width / 2 - 150, Director::getInstance()->getVisibleSize().height - 70, 100, 50);
    auto socialButtonArea = Rect(Director::getInstance()->getVisibleSize().width / 2 + 50, Director::getInstance()->getVisibleSize().height - 70, 100, 50);

    auto stoppingPlayer = StoppingLayer::getInstance();
    if (stoppingPlayer->isVisible())  return;

    // 判断鼠标点击的区域
    if (itemButtonArea.containsPoint(mousePos)) {
        switchToPage(0);  // 切换到物品页面
    }
    else if (socialButtonArea.containsPoint(mousePos)) {
        switchToPage(1);  // 切换到社交页面
    }
}

// 关闭背包界面
void InventoryLayer::closeInventoryLayer(cocos2d::Ref* sender) {
    // 关闭当前层
    Director::getInstance()->getRunningScene()->removeChild(this);
}

// 设置可见性
void InventoryLayer::setVisible(bool visible) {
    Layer::setVisible(visible);
    if (visible) {
        CCLOG("InventoryLayer is now visible.");
    }
    else {
        CCLOG("InventoryLayer is now hidden.");
    }
}