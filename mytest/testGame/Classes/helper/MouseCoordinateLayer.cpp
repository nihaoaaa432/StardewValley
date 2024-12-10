#include "MouseCoordinateLayer.h"

USING_NS_CC;

MouseCoordinateLayer* MouseCoordinateLayer::createLayer() {
    MouseCoordinateLayer* ret = new MouseCoordinateLayer();
    if (ret && ret->init()) {
        ret->autorelease();
        return ret;
    }
    else {
        delete ret;
        return nullptr;
    }
}

bool MouseCoordinateLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    // ��ȡ��Ļ�ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // ����һ����ǩ����ʾ����
    coordinateLabel = Label::createWithTTF("Mouse Position: (0, 0)", "fonts/arial.ttf", 24);
    coordinateLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    this->addChild(coordinateLabel);

    // ��������¼�������
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(MouseCoordinateLayer::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void MouseCoordinateLayer::onMouseMove(Event* event) {
    auto mouseEvent = (EventMouse*)event;
    auto mousePos = mouseEvent->getLocation();

    // ���������ǩ��ʾ
    coordinateLabel->setString(StringUtils::format("Mouse Position: (%.2f, %.2f)", mousePos.x, mousePos.y));
}
