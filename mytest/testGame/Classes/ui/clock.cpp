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
     //   clockLayer->autorelease();  // ����ʹ�� autorelease �����ڴ�
        return clockLayer;
    }
    CC_SAFE_DELETE(clockLayer);  // ���ٲ��ϸ��ʵ��
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

    // ����ʱ�ӱ�ǩ
    _clockLabel = Label::createWithSystemFont("00:00", "Arial", 24);
    if (_clockLabel) {
        _clockLabel->setPosition(Vec2(50, 50));  // ��ʼλ��
        this->addChild(_clockLabel);
    }

    // ÿ�����һ��
    this->schedule([=](float deltaTime) {
        updateClock(deltaTime);
        updateClockPosition();
        }, 1.0f, "clock_update_key");

    return true;
}

void Clock::updateClock(float deltaTime) {
    // ����ʱ��
    _elapsedTime += deltaTime;
    int minutes = static_cast<int>(_elapsedTime) / 60;
    int seconds = static_cast<int>(_elapsedTime) % 60;

    char buffer[10];
    snprintf(buffer, sizeof(buffer), "%02d:%02d", minutes, seconds);
    _clockLabel->setString(buffer);
}

void Clock::updateClockPosition() {
    // ��ȡ��ҵ�λ��
    Vec2 playerPosition = Player::getInstance()->getPosition();
    
}

float Clock::getTime() {
    return _elapsedTime;
}