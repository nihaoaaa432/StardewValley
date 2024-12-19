#include "InventoryLayer.h"
#include "StoppingLayer.h"
#include "../scene/MapScene.h"
#include "cocos2d.h"
USING_NS_CC;

// ��������ָ���ʼ��Ϊnullptr
InventoryLayer* InventoryLayer::_instance = nullptr;

// ��ȡ��������
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

// ��ʼ����������
bool InventoryLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // ��ȡ��Ļ�ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // ��������
    auto background = Sprite::create("Inventory.png");
    background->setPosition(Vec2(visibleSize.width / 2 + origin.x-20, visibleSize.height / 2 + origin.y+40));
    this->addChild(background, 1);

    // ������߰�ť��
    buttonBar = Node::create(); // ��ť���ڵ㣬ָ���ʾ����
    buttonBar->setPosition(Vec2(953, 567));
    this->addChild(buttonBar, 2);

    // ������Ʒҳ��
    itemPage = Layer::create();
    itemPage->setName("ItemPage");  // ���������Ա����
    this->addChild(itemPage, 1);

    // ����Ʒҳ�����������
    auto itemLabel = Label::createWithSystemFont("itemPage", "Arial", 30);
    itemLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    itemPage->addChild(itemLabel);

    // �����罻ҳ��
    socialPage = Layer::create();
    auto socialBackground= Sprite::create("SocialPage.png");
    socialBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x+70, visibleSize.height / 2 + origin.y+35));
    
    // ��ȡ����ͼ��ԭʼ��С
    Size backgroundSize = socialBackground->getContentSize();
    // ���ñ���ͼ�����ű���
    socialBackground->setScale(0.8f);

    socialPage->addChild(socialBackground, 1);
    socialPage->setName("SocialPage");  // ���������Ա����
    this->addChild(socialPage, 1);

    // ���罻ҳ�����������
    auto socialLabel = Label::createWithSystemFont("SocialPage", "Arial", 30);
    socialLabel->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    socialPage->addChild(socialLabel,2);

    // ��Ӱ�ť����Ʒ���罻��
    auto itemButton = ui::Button::create("ItemButton.png"); // ��Ʒ��ť
    itemButton->setContentSize(Size(60, 60));
    itemButton->setPosition(Vec2(33, -33));
    buttonBar->addChild(itemButton);


    auto socialButton = ui::Button::create("SocialButton.png"); // �罻��ť
    socialButton->setContentSize(Size(60, 60));
    socialButton->setPosition(Vec2(33, -123));
    buttonBar->addChild(socialButton);

    // Ĭ����ʾ��Ʒҳ��
    currentPage = 0;
    switchToPage(currentPage);

    // ����������¼�
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(InventoryLayer::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // ��Ӱ�ť�ص��������л�ҳ�棩
    itemButton->addClickEventListener([this](Ref* sender) {
        this->switchToPage(0); // �л�����Ʒҳ��
        });

    socialButton->addClickEventListener([this](Ref* sender) {
        this->switchToPage(1); // �л����罻��ϵҳ��
        });

    return true;
}

// ���±�������λ��
void InventoryLayer::updatePosition(cocos2d::Vec2 position) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto backpackSize = this->getContentSize(); // ���豳��������getContentSize()����
    position = position - Vec2(backpackSize.width / 2, backpackSize.height / 2);
    this->setPosition(position);
};

// �л�ҳ��
void InventoryLayer::switchToPage(int pageIndex) {
    // ����ҳ��Ŀɼ���
    if (pageIndex == 0) {
        
        itemPage->setVisible(true);
        socialPage->setVisible(false);
    }
    else if (pageIndex == 1) {
        itemPage->setVisible(false);
        socialPage->setVisible(true);
    }
    currentPage = pageIndex; // ���µ�ǰҳ������
}

// ������¼�
void InventoryLayer::onMouseDown(cocos2d::Event* event) {
    auto mouseEvent = (EventMouse*)event;
    auto mousePos = mouseEvent->getLocation();

    // ��ȡ��ť������Ʒ��ť���罻��ť�ľ�������
    auto itemButtonArea = Rect(Director::getInstance()->getVisibleSize().width / 2 - 150, Director::getInstance()->getVisibleSize().height - 70, 100, 50);
    auto socialButtonArea = Rect(Director::getInstance()->getVisibleSize().width / 2 + 50, Director::getInstance()->getVisibleSize().height - 70, 100, 50);

    auto stoppingPlayer = StoppingLayer::getInstance();
    if (stoppingPlayer->isVisible())  return;

    // �ж������������
    if (itemButtonArea.containsPoint(mousePos)) {
        switchToPage(0);  // �л�����Ʒҳ��
    }
    else if (socialButtonArea.containsPoint(mousePos)) {
        switchToPage(1);  // �л����罻ҳ��
    }
}

// �رձ�������
void InventoryLayer::closeInventoryLayer(cocos2d::Ref* sender) {
    // �رյ�ǰ��
    Director::getInstance()->getRunningScene()->removeChild(this);
}

// ���ÿɼ���
void InventoryLayer::setVisible(bool visible) {
    Layer::setVisible(visible);
    if (visible) {
        CCLOG("InventoryLayer is now visible.");
    }
    else {
        CCLOG("InventoryLayer is now hidden.");
    }
}