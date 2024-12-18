// UILayer.h
#ifndef __UILAYER_H__
#define __UILAYER_H__

#include "cocos2d.h"

class UILayer : public cocos2d::Layer
{
public:
    UILayer();
    ~UILayer();

    // 初始化方法
    virtual bool init();

    // 创建UI层
    static UILayer* createLayer();

    // 更新时间
    void updateClock(float deltaTime);

    // 设置时钟显示
    void setClockLabel(const std::string& timeStr);

private:
    cocos2d::Label* clockLabel;
    float timeInSeconds;
};

#endif // __UILAYER_H__
