#include "Clock.h"
#include "character/Player.h"
#include "cocos2d.h"

USING_NS_CC;
Clock* Clock::instance = nullptr;
Clock* Clock::getInstance() {
    if (instance == nullptr) {
        instance = createLayer();
    }
    return instance;
}

Clock* Clock::createLayer() {
    Clock* clockLayer = new Clock();
    if (clockLayer && clockLayer->init()) {
     //   clockLayer->autorelease();  // 正常使用 autorelease 管理内存
        return clockLayer;
    }
    CC_SAFE_DELETE(clockLayer);  // 销毁不合格的实例
    return nullptr;
}

void Clock::destroyInstance()
{
    if (instance != nullptr)
    {
        //instance->release();
        instance = nullptr;
    }
}


bool Clock::init() {
    if (!Layer::init()) {
        return false;
    }

    // 创建时钟标签
    _clockLabel = Label::createWithSystemFont("00:00", "Arial", 24);
    if (_clockLabel) {
        _clockLabel->setPosition(Vec2(50, 50));  // 初始位置
        this->addChild(_clockLabel);
    }

    // 每秒更新一次
    this->schedule([=](float deltaTime) {
        updateClock(deltaTime);
        updateClockPosition();
        }, 1.0f, "clock_update_key");

    return true;
}

void Clock::updateClock(float deltaTime) {
    // 更新时钟
    _elapsedTime += deltaTime;
    int minutes = static_cast<int>(_elapsedTime) / 60;
    int seconds = static_cast<int>(_elapsedTime) % 60;

    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, seconds);
    _clockLabel->setString(buffer);
}

void Clock::updateClockPosition() {
    // 获取玩家的位置
    Vec2 playerPosition = Player::getInstance()->getPosition();
    
}

float Clock::getTime() {
    return _elapsedTime;
}