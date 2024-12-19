#include "ToolLayer.h"

USING_NS_CC;

// ��ʼ������ʵ��
ToolLayer* ToolLayer::instance = nullptr;

ToolLayer* ToolLayer::getInstance() {
    if (!instance) {
        instance = new ToolLayer();
        if (instance && instance->init()) {
            // ��ʼ��������ʱ��Ҫ���빤��ͼƬ�б�
        }
        else {
            CC_SAFE_DELETE(instance);
            instance = nullptr;
        }
    }
    return instance;
}

ToolLayer::ToolLayer() {
    // ˽�й��캯��
}

ToolLayer::~ToolLayer() {
    // ˽����������
}

bool ToolLayer::init() {
    // ���ø���� init ����
    if (!Layer::init()) {
        return false;
    }

    // ������ʾ��ǰ���������ı�ǩ
    currentToolLabel = Label::createWithSystemFont("Current Tool: 1", "Arial", 24);
    currentToolLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 155));
    this->addChild(currentToolLabel);

    // ���������¼�
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(ToolLayer::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void ToolLayer::initToolBar(const std::vector<std::string>& toolImages) {
    // ��������������
    auto toolLayout = ui::Layout::create();
    toolLayout->setContentSize(Size(Director::getInstance()->getVisibleSize().width, 100));
    toolLayout->setPosition(Vec2(0, 0));

    // ��ӱ���ͼ
    auto backgroundSprite = Sprite::create("ToolLayer.png"); // ����ͼ
    backgroundSprite->setPosition(Vec2(toolLayout->getContentSize().width / 2, toolLayout->getContentSize().height / 2+25));
    toolLayout->addChild(backgroundSprite, -1); // ������ͼ��ӵ���������������ײ�

    //// ���ñ�����ɫ����ѡ��
    //toolLayout->setBackGroundColor(Color3B::GRAY);
    //toolLayout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);

    this->addChild(toolLayout);

    // ���ݹ���������̬�������߲�
    int toolCount = toolImages.size();
    for (int i = 0; i < toolCount; ++i) {
        auto toolSlot = ui::Button::create(); // ���߲۱���ͼƬ
        toolSlot->setContentSize(Size(40, 40));
        toolSlot->setPosition(Vec2(262+ i * 75, 30)); // ���߲�λ��
        toolLayout->addChild(toolSlot);

        // ��ӹ���ͼƬ
        auto toolSprite = Sprite::create(toolImages[i]);
        toolSprite->setPosition(Vec2(40, 40)); // ����ͼƬ�ڲ��е�λ��
        toolSlot->addChild(toolSprite);

        // ���湤�߲�
        toolSlots.push_back(toolSlot);

        // �󶨹��߲۵���¼�
        toolSlot->addClickEventListener([this, i](Ref* sender) {
            this->switchTool(i);
            });

        // �󶨹��߲���ק�¼�
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(ToolLayer::onToolSlotDragStart, this); // ʹ�� CC_CALLBACK_2
        touchListener->onTouchMoved = CC_CALLBACK_2(ToolLayer::onToolSlotDragMove, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(ToolLayer::onToolSlotDragEnd, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, toolSlot);
    }

    // Ĭ��ѡ�е�һ������
    if (toolCount > 0) {
        switchTool(0);
    }
}

void ToolLayer::switchTool(int index) {
    if (index < 0 || index >= toolSlots.size()) {
        return;
    }

    // ���µ�ǰѡ�еĹ�������
    currentToolIndex = index;

    // ����UI��ʾ�����������ǰѡ�еĹ��߲ۣ�
    for (int i = 0; i < toolSlots.size(); ++i) {
        if (i == currentToolIndex) {
            toolSlots[i]->setColor(Color3B::YELLOW); // ����ѡ�й��߲�
        }
        else {
            toolSlots[i]->setColor(Color3B::WHITE); // �ָ��������߲���ɫ
        }
    }

    // ���±�ǩ��ʾ��ǰѡ�еĹ�������
    currentToolLabel->setString("Current Tool: " + std::to_string(currentToolIndex + 1));


    // ��ӡ��ǰѡ�еĹ���
    CCLOG("Selected tool: %d", currentToolIndex + 1);
}

void ToolLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    // �жϰ��µ����ּ�
    if (keyCode >= EventKeyboard::KeyCode::KEY_1 && keyCode <= EventKeyboard::KeyCode::KEY_9) {
        int index = static_cast<int>(keyCode) - 49; // ���㹤������
        if (index < toolSlots.size()) {
            switchTool(index);
        }
    }
}

void ToolLayer::onToolSlotClicked(Ref* sender) {
    auto button = static_cast<ui::Button*>(sender);
    for (int i = 0; i < toolSlots.size(); ++i) {
        if (toolSlots[i] == button) {
            switchTool(i);
            break;
        }
    }
}

bool ToolLayer::onToolSlotDragStart(Touch* touch, Event* event) {
    auto target = static_cast<ui::Button*>(event->getCurrentTarget());
    auto touchPoint = touch->getLocation();

    // ��鴥�����Ƿ��ڹ��߲���
    if (target->getBoundingBox().containsPoint(touchPoint)) {
        target->setColor(Color3B::GREEN); // ��ק��ʼʱ�������߲�
        return true; // ���� true ��ʾ���������������ק�¼�
    }

    return false; // ���� false ��ʾ�������������ק�¼�
}

void ToolLayer::onToolSlotDragMove(Touch* touch, Event* event) {
    auto target = static_cast<ui::Button*>(event->getCurrentTarget());
    auto touchPoint = touch->getLocation();
    target->setPosition(target->getPosition() + touch->getDelta());
}

void ToolLayer::onToolSlotDragEnd(Touch* touch, Event* event) {
    auto target = static_cast<ui::Button*>(event->getCurrentTarget());
    auto touchPoint = touch->getLocation();
    target->setColor(Color3B::WHITE); // ��ק����ʱ�ָ����߲���ɫ

    // ����Ƿ���ק���������߲�
    for (int i = 0; i < toolSlots.size(); ++i) {
        if (toolSlots[i] != target && toolSlots[i]->getBoundingBox().containsPoint(touchPoint)) {
            // �������߲۵�λ��
            auto tempPos = target->getPosition();
            target->setPosition(toolSlots[i]->getPosition());
            toolSlots[i]->setPosition(tempPos);

            // �������߲۵�����
            std::swap(toolSlots[currentToolIndex], toolSlots[i]);
            break;
        }
    }
}

// ���±�������λ��
void ToolLayer::updatePosition(cocos2d::Vec2 position) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto backpackSize = this->getContentSize(); // ���豳��������getContentSize()����
    position = position - Vec2(backpackSize.width / 2, backpackSize.height / 2);
    this->setPosition(position);
};