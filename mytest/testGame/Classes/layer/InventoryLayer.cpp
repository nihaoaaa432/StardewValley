#include "InventoryLayer.h"

USING_NS_CC;

CinventoryLayer* CinventoryLayer::createLayer() {
    CinventoryLayer* ret = new CinventoryLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool CinventoryLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // ��ȡ��Ļ�ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // ��������
    auto background = Sprite::create("Inventory.png");
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background, 1);

    // ������߰�ť��
    auto buttonBar = Node::create(); // ��ť���ڵ㣬ָ���ʾ����
    buttonBar->setPosition(Vec2(953, 567));
    this->addChild(buttonBar, 2);

    // ��Ӱ�ť����Ʒ���罻��
    auto itemButton = ui::Button::create("Invnt_backpack.png"); // ��Ʒ��ť
    itemButton->setContentSize(Size(60, 60));
    itemButton->setPosition(Vec2(0, -80));
    buttonBar->addChild(itemButton);

    auto socialButton = ui::Button::create("Invnt_social.png"); // �罻��ť
    socialButton->setContentSize(Size(60, 60));
    socialButton->setPosition(Vec2(0,-180 ));
    buttonBar->addChild(socialButton);

    // ��Ӱ�ť�ص��������л�ҳ�棩
    itemButton->addClickEventListener([this](Ref* sender) {
        this->SwitchToPage(0); // �л�����Ʒҳ��
        });

    socialButton->addClickEventListener([this](Ref* sender) {
        this->SwitchToPage(1); // �л����罻��ϵҳ��
        });

    // ������Ʒҳ��
    itemPage = Node::create();
    this->addChild(itemPage, 2);

    // ʾ����Ʒҳ������
    auto itemLabel = Label::createWithTTF("��Ʒҳ��", "fonts/arial.ttf", 24);
    itemLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    itemPage->addChild(itemLabel);

    // �����罻ҳ��
    socialPage = Node::create();
    this->addChild(socialPage, 2);

    // ʾ���罻ҳ������
    auto socialLabel = Label::createWithTTF("�罻��ϵҳ��", "fonts/arial.ttf", 24);
    socialLabel->setPosition(visibleSize.width / 2, visibleSize.height / 2);
    socialPage->addChild(socialLabel);

    // Ĭ����ʾ��Ʒҳ��
    currentPage = 0;
    SwitchToPage(currentPage);

    // ����������¼�
    auto listener = EventListenerMouse::create();
    listener->onMouseDown = CC_CALLBACK_1(CinventoryLayer::OnMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    // �����رհ�ť
    auto closeButton = ui::Button::create("close.png");  // �رհ�ť
    closeButton->setPosition(Vec2(955, 565)); // �������Ͻ�
    this->addChild(closeButton, 3);

    // �رհ�ť�Ļص�
    closeButton->addClickEventListener(CC_CALLBACK_1(CinventoryLayer::CloseInventoryLayer, this));

    return true;
}

// �л�ҳ��
void CinventoryLayer::SwitchToPage(int pageIndex) {
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
void CinventoryLayer::OnMouseDown(Event* event) {
    auto mouseEvent = (EventMouse*)event;
    auto mousePos = mouseEvent->getLocation();

    // ��ȡ��ť������Ʒ��ť���罻��ť�ľ�������
    auto itemButtonArea = Rect(Director::getInstance()->getVisibleSize().width / 2 - 150, Director::getInstance()->getVisibleSize().height - 70, 100, 50);
    auto socialButtonArea = Rect(Director::getInstance()->getVisibleSize().width / 2 + 50, Director::getInstance()->getVisibleSize().height - 70, 100, 50);

    // �ж������������
    if (itemButtonArea.containsPoint(mousePos)) {
        SwitchToPage(0);  // �л�����Ʒҳ��
    }
    else if (socialButtonArea.containsPoint(mousePos)) {
        SwitchToPage(1);  // �л����罻ҳ��
    }
}

// �رձ�������
void CinventoryLayer::CloseInventoryLayer(Ref* sender) {
    // �رյ�ǰ��
    Director::getInstance()->getRunningScene()->removeChild(this);
    //auto player= Director::getInstance()
}
