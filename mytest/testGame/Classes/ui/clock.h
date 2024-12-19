#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "cocos2d.h"

class Clock : public cocos2d::Layer {
public:
    // 创建并初始化时钟层
    static Clock* createLayer();
    static Clock* Clock::getInstance();
    void Clock::destroyInstance();
    // 初始化
    virtual bool init() override;

    // 更新时钟显示
    void updateClock(float deltaTime);

    // 更新时钟的位置
    void updateClockPosition();
    float getTime();
private:
    // 显示时钟的标签
    cocos2d::Label* _clockLabel = nullptr;

    // 记录经过的时间（秒）
    float _elapsedTime = 0.0f;
    static Clock* instance;
};

#endif // __CLOCK_H__
