#ifndef __STOPPING_LAYER_H__
#define __STOPPING_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class StoppingLayer : public cocos2d::Layer
{
public:
    // 场景切换标记
    static const int menuSceneTag = 1;
    static const int settingSceneTag = 2;

    // 场景切换函数
    static cocos2d::Scene* createLayer();

    // 必须实现的初始化函数
    virtual bool init();

    // 创建按钮并添加事件监听器
    void createMenu();

    // 响应按钮点击事件
    void onSettingButton(cocos2d::Ref* sender, cocos2d::ui::Button::TouchEventType type);
    void onQuitButton(cocos2d::Ref* sender, cocos2d::ui::Button::TouchEventType type);

    // 响应键盘事件
    virtual void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) override;

    // 其他成员函数和变量
    // ...

protected:
    // 按钮变量
    cocos2d::ui::Button* settingButton;
    cocos2d::ui::Button* quitButton;
};

#endif // __STOPPING_LAYER_H__
