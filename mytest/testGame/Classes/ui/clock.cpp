// UILayer.cpp
#include "clock.h"

USING_NS_CC;

UILayer::UILayer() : clockLabel(nullptr), timeInSeconds(0) {}

UILayer::~UILayer() {}

UILayer* UILayer::createLayer()
{
    UILayer* layer = new UILayer();
    if (layer && layer->init())
    {
        layer->autorelease();
        return layer;
    }
    else
    {
        delete layer;
        return nullptr;
    }
}

bool UILayer::init()
{
    if (!Layer::init())
    {
        return false;
    }

    // 初始化时钟UI
    clockLabel = Label::createWithSystemFont("Time: 00:00", "Arial", 24);
    clockLabel->setPosition(Director::getInstance()->getVisibleSize().width - 100,
        Director::getInstance()->getVisibleSize().height - 50);
    this->addChild(clockLabel, 100000);  // 设置很高的z-order，确保时钟UI在最上层

    // 每帧更新时间
    this->schedule([=](float deltaTime) {
        updateClock(deltaTime);  // 更新时钟
        }, 1.0f, "update_clock_key");  // 每秒更新一次时钟

    return true;
}

void UILayer::updateClock(float deltaTime)
{
    timeInSeconds += deltaTime;

    // 获取小时、分钟、秒数
    int hours = static_cast<int>(timeInSeconds / 3600);
    int minutes = static_cast<int>((timeInSeconds - hours * 3600) / 60);
    int seconds = static_cast<int>(timeInSeconds - hours * 3600 - minutes * 60);

    // 格式化时间
    char timeStr[9];
    snprintf(timeStr, sizeof(timeStr), "Time: %02d:%02d:%02d", hours, minutes, seconds);

    // 设置时钟显示
    setClockLabel(timeStr);
}

void UILayer::setClockLabel(const std::string& timeStr)
{
    if (clockLabel)
    {
        clockLabel->setString(timeStr);  // 更新时钟文字
    }
}
