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

    // ���������ð�ť
    void onSettingButton(cocos2d::Ref* sender);
    // �������˳���Ϸ��ť
    void onQuitButton(cocos2d::Ref* sender);
    // ���������ְ�ť
    void onMusicButton(cocos2d::Ref* sender);
    // �����˷��ذ�ť
    void onBackButton(cocos2d::Ref* sender);

    void updatePosition(cocos2d::Vec2 position);
    // ����esc����
    void onEscPress();

    CREATE_FUNC(StoppingLayer);

private:

    // ���ٵ�������
    static void destroyInstance();

    static StoppingLayer* _instance; // ��������ָ��

    cocos2d::Layer* settingLayer;

    int currentPage;            // ��ǰҳ������
};

#endif // __STOPPING_LAYER_H__