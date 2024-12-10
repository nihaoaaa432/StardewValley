#pragma once

#include "cocos2d.h"
#define SIZE_X 100
#define SIZE_Y 100
#define FROM_HOME_TO_TOWN SIZE_Y*0.8*16+16*7
class TownScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TownScene);

private:
    cocos2d::TMXTiledMap* map;       // ��ͼ
    cocos2d::Sprite* player;         // ��ɫ����
    cocos2d::Vec2 moveDirection;     // �ƶ�����
    float speed = 100.0f;            // �ƶ��ٶ�

    void update(float deltaTime);    // ÿ֡���º���
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateCameraPosition();
    bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
};
