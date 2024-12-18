// UILayer.h
#ifndef __UILAYER_H__
#define __UILAYER_H__

#include "cocos2d.h"

class UILayer : public cocos2d::Layer
{
public:
    UILayer();
    ~UILayer();

    // ��ʼ������
    virtual bool init();

    // ����UI��
    static UILayer* createLayer();

    // ����ʱ��
    void updateClock(float deltaTime);

    // ����ʱ����ʾ
    void setClockLabel(const std::string& timeStr);

private:
    cocos2d::Label* clockLabel;
    float timeInSeconds;
};

#endif // __UILAYER_H__
