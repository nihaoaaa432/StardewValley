#ifndef __STOPPING_LAYER_H__
#define __STOPPING_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class StoppingLayer : public cocos2d::Layer {
public:
    static StoppingLayer* createLayer();

    virtual bool init();


    void onSettingButton(cocos2d::Ref* sender);
    void onQuitButton(cocos2d::Ref* sender);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    CREATE_FUNC(StoppingLayer);

private:
    cocos2d::Node* menuNode;    // 菜单节点
    cocos2d::ui::Button* settingButton;
    cocos2d::ui::Button* quitButton;
    int currentPage;            // 当前页面索引
};

#endif // __STOPPING_LAYER_H__