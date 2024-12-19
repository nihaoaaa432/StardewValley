#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "cocos2d.h"

class Clock : public cocos2d::Layer {
public:
    // ��������ʼ��ʱ�Ӳ�
    static Clock* createLayer();
    static Clock* Clock::getInstance();
    void Clock::destroyInstance();
    // ��ʼ��
    virtual bool init() override;

    // ����ʱ����ʾ
    void updateClock(float deltaTime);

    // ����ʱ�ӵ�λ��
    void updateClockPosition();
    float getTime();
private:
    // ��ʾʱ�ӵı�ǩ
    cocos2d::Label* _clockLabel = nullptr;

    // ��¼������ʱ�䣨�룩
    float _elapsedTime = 0.0f;
    static Clock* instance;
};

#endif // __CLOCK_H__
