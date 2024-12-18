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

    void onSettingButton(cocos2d::Ref* sender);
    void onQuitButton(cocos2d::Ref* sender);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void updatePosition(cocos2d::Vec2 position);

    CREATE_FUNC(StoppingLayer);

private:

    // 销毁单例对象
    static void destroyInstance();

    static StoppingLayer* _instance; // 单例对象指针

    int currentPage;            // 当前页面索引
};

#endif // __STOPPING_LAYER_H__