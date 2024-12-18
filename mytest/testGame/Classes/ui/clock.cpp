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

    // ��ʼ��ʱ��UI
    clockLabel = Label::createWithSystemFont("Time: 00:00", "Arial", 24);
    clockLabel->setPosition(Director::getInstance()->getVisibleSize().width - 100,
        Director::getInstance()->getVisibleSize().height - 50);
    this->addChild(clockLabel, 100000);  // ���úܸߵ�z-order��ȷ��ʱ��UI�����ϲ�

    // ÿ֡����ʱ��
    this->schedule([=](float deltaTime) {
        updateClock(deltaTime);  // ����ʱ��
        }, 1.0f, "update_clock_key");  // ÿ�����һ��ʱ��

    return true;
}

void UILayer::updateClock(float deltaTime)
{
    timeInSeconds += deltaTime;

    // ��ȡСʱ�����ӡ�����
    int hours = static_cast<int>(timeInSeconds / 3600);
    int minutes = static_cast<int>((timeInSeconds - hours * 3600) / 60);
    int seconds = static_cast<int>(timeInSeconds - hours * 3600 - minutes * 60);

    // ��ʽ��ʱ��
    char timeStr[9];
    snprintf(timeStr, sizeof(timeStr), "Time: %02d:%02d:%02d", hours, minutes, seconds);

    // ����ʱ����ʾ
    setClockLabel(timeStr);
}

void UILayer::setClockLabel(const std::string& timeStr)
{
    if (clockLabel)
    {
        clockLabel->setString(timeStr);  // ����ʱ������
    }
}
