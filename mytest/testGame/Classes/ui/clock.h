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
    // ��������ʼ��ʱ�Ӳ�
    static Clock* createLayer();
    static Clock* getInstance();
    void destroyInstance();
    // ��ʼ��
    virtual bool init() override;

    // ����ʱ����ʾ
    void updateClock(float deltaTime);

    // ����ʱ�ӵ�λ��
    void updateClockPosition();
    float getTime();

    Season getCurrentSeason()const;//��ȡ��ǰ����

    int getCurrentDays()const;//��ȡ��ǰ���ӣ�����Ϸ�ڼ���
private:
    // ��ʾʱ�ӵı�ǩ
    cocos2d::Label* _clockLabel = nullptr;

    // ��¼������ʱ�䣨�룩
    float _elapsedTime = 0.0f;
    static Clock* instance;

    int currentDays;//��ǰ���ڣ���1��1�տ�ʼ��Ϊ��1��
    Season currentSeason;//��ǰ���ڣ��涨1-3��Ϊ���죬4-6��Ϊ���죬7-9��Ϊ���죬10-12��Ϊ����,��������

};

#endif // __CLOCK_H__
