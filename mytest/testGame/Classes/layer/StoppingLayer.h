#ifndef __STOPPING_LAYER_H__
#define __STOPPING_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class StoppingLayer : public cocos2d::Layer {
public:
    // ��ȡ��������
    static StoppingLayer* getInstance();

    // ��ʼ����������
    virtual bool init();

    void onSettingButton(cocos2d::Ref* sender);
    void onQuitButton(cocos2d::Ref* sender);

    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    void updatePosition(cocos2d::Vec2 position);

    CREATE_FUNC(StoppingLayer);

private:

    // ���ٵ�������
    static void destroyInstance();

    static StoppingLayer* _instance; // ��������ָ��

    int currentPage;            // ��ǰҳ������
};

#endif // __STOPPING_LAYER_H__