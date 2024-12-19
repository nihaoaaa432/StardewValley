#ifndef __STOPPING_LAYER_H__
#define __STOPPING_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class StoppingLayer : public cocos2d::Layer {
public:
    // 获取单例对象
    static StoppingLayer* getInstance();

    // 初始化单例对象
    virtual bool init();

    // 按下了设置按钮
    void onSettingButton(cocos2d::Ref* sender);
    // 按下了退出游戏按钮
    void onQuitButton(cocos2d::Ref* sender);
    // 按下了音乐按钮
    void onMusicButton(cocos2d::Ref* sender);
    // 按下了返回按钮
    void onBackButton(cocos2d::Ref* sender);

    void updatePosition(cocos2d::Vec2 position);
    // 处理esc按键
    void onEscPress();

    CREATE_FUNC(StoppingLayer);

private:

    // 销毁单例对象
    static void destroyInstance();

    static StoppingLayer* _instance; // 单例对象指针

    cocos2d::Layer* settingLayer;

    int currentPage;            // 当前页面索引
};

#endif // __STOPPING_LAYER_H__