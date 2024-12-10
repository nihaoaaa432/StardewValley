#include "InventoryLayer.h"

USING_NS_CC;

InventoryLayer* InventoryLayer::createLayer() {
    InventoryLayer* ret = new InventoryLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool InventoryLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // 获取屏幕尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 背包背景
    auto background = Sprite::create("Inventory.png");
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background, 1);

    // 创建侧边按钮栏
    auto buttonBar = Node::create(); // 按钮栏节点，指针表示数组
    buttonBar->setPosition(Vec2(953, 567));
    this->addChild(buttonBar, 2);

    // 添加按钮（物品、社交）
    auto itemButton = ui::Button::create("Invnt_backpack.png"); // 物品按钮
    itemButton->setContentSize(Size(60, 60));
    itemButton->setPosition(Vec2(0, -80));
    buttonBar->addChild(itemButton);

    auto socialButton = ui::Button::create("Invnt_social.png"); // 社交按钮
    socialButton->setContentSize(Size(60, 60));
    socialButton->setPosition(Vec2(0, -180));
    buttonBar->addChild(socialButton);

    // 添加按钮回调（用于切换页面）
    itemButton->addClickEventListener([this](Ref* sender) {
        this->SwitchToPage(0); // 切换到物品页面
        });

    socialButton->addClickEventListener([this](Ref* sender) {
        this->SwitchToPage(1); // 切换到社交关系页面
        });

    //// 创建物品页面
    //itemPage = Node::create();
    //this->addChild(itemPage, 2);

    //// 示例物品页面内容
    //auto itemLabel = Label::createWithTTF("物品页面", "fonts/arial.ttf", 24);
    //itemLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    //itemPage->addChild(itemLabel);

    //// 创建社交页面
    //socialPage = Node::create();
    //this->addChild(socialPage, 2);

    //// 示例社交页面内容
    //auto socialLabel = Label::createWithTTF("社交关系页面", "fonts/arial.ttf", 24);
    //socialLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    //socialPage->addChild(socialLabel);

    // 默认显示物品页面
    //currentPage = 0;
   // SwitchToPage(currentPage);

    // 添加鼠标监听事件
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(InventoryLayer::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // 创建关闭按钮
    auto closeButton = ui::Button::create("close.png");  // 关闭按钮
    closeButton->setPosition(Vec2(955, 565)); // 放在右上角
    this->addChild(closeButton, 3);

    // 关闭按钮的回调
    closeButton->addClickEventListener(CC_CALLBACK_1(CinventoryLayer::CloseInventoryLayer, this));

    return true;
}

// 切换页面
void CinventoryLayer::SwitchToPage(int pageIndex) {
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
void CinventoryLayer::OnMouseDown(Event* event) {
    auto mouseEvent = (EventMouse*)event;
    auto mousePos = mouseEvent->getLocation();

    // 获取按钮区域（物品按钮和社交按钮的矩形区域）
    auto itemButtonArea = Rect(Director::getInstance()->getVisibleSize().width / 2 - 150, Director::getInstance()->getVisibleSize().height - 70, 100, 50);
    auto socialButtonArea = Rect(Director::getInstance()->getVisibleSize().width / 2 + 50, Director::getInstance()->getVisibleSize().height - 70, 100, 50);

    // 判断鼠标点击的区域
    if (itemButtonArea.containsPoint(mousePos)) {
        SwitchToPage(0);  // 切换到物品页面
    }
    else if (socialButtonArea.containsPoint(mousePos)) {
        SwitchToPage(1);  // 切换到社交页面
    }
}

// 关闭背包界面
void CinventoryLayer::CloseInventoryLayer(Ref* sender) {
    // 关闭当前层
    Director::getInstance()->getRunningScene()->removeChild(this);
    //auto player= Director::getInstance()

    //���ûص�����֪ͨ�رձ���

}
