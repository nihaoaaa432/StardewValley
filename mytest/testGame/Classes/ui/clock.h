#ifndef __CLOCK_H__
#define __CLOCK_H__

#include "cocos2d.h"

enum class Season {
    SPRING = 0,
    SUMMER,
    AUTUMN,
    WINTER
};
#define DAYS_IN_YEAR 365
#define DAYS_IN_SPRING 90
#define DAYS_IN_SUMMER 91
#define DAYS_IN_AUTUMN 92
#define DAYS_IN_WINTER 92
#define REAL_SECONDS_IN_MINUTE_OF_GAME 1
#define REAL_MINUTES_IN_HOURS_OF_GAME 1
#define REAL_HOURS_IN_DAY_OF_GAME 1

class Clock : public cocos2d::Layer {
public:
    // 创建并初始化时钟层
    static Clock* createLayer();
    static Clock* getInstance();
    void destroyInstance();
    // 初始化
    virtual bool init() override;

    // 更新时钟显示
    void updateClock(float deltaTime);

    // 更新时钟的位置
    void updateClockPosition();
    float getTime();

    Season getCurrentSeason()const;//获取当前季节

    int getCurrentDays()const;//获取当前日子，即游戏第几天
private:
    // 显示时钟的标签
    cocos2d::Label* _clockLabel = nullptr;

    // 记录经过的时间（秒）
    float _elapsedTime = 0.0f;
    static Clock* instance;

    int currentDays;//当前日期，从1月1日开始算为第1天
    Season currentSeason;//当前季节，规定1-3月为春天，4-6月为夏天，7-9月为秋天，10-12月为冬天,且无润年

};

#endif // __CLOCK_H__
