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

    // 获取屏幕尺寸
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // 创建一个标签来显示坐标
    coordinateLabel = Label::createWithTTF("Mouse Position: (0, 0)", "fonts/arial.ttf", 24);
    coordinateLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height - 50));
    this->addChild(coordinateLabel);

    // 创建鼠标事件监听器
    auto listener = EventListenerMouse::create();
    listener->onMouseMove = CC_CALLBACK_1(MouseCoordinateLayer::onMouseMove, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void MouseCoordinateLayer::onMouseMove(Event* event) {
    auto mouseEvent = (EventMouse*)event;
    auto mousePos = mouseEvent->getLocation();

    // 更新坐标标签显示
    coordinateLabel->setString(StringUtils::format("Mouse Position: (%.2f, %.2f)", mousePos.x, mousePos.y));
}
