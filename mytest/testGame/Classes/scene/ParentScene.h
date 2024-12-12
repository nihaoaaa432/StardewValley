#pragma once
#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
#define SIZE_TOWN_X 100
#define SIZE_TOWN_Y 100
// ��town��farm��������
#define FROM_TOWN_TO_FARM_Y_UP 16* SIZE_TOWN_Y *0.8+18*16 
#define FROM_TOWN_TO_FARM_Y_DOWN FROM_TOWN_TO_FARM_Y_UP-16
#define FROM_TOWN_TO_FARM_X 0
class ParentScene : public cocos2d::Scene {
public:
    void onBKeyPressed();

    void update(float deltaTime);    // ÿ֡���º���
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateCameraPosition();
    void setCameraHeight(float height);

    virtual bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
    virtual void checkMapSwitch(const cocos2d::Vec2& position);
    virtual void goToNextScene();

private:
    cocos2d::TMXTiledMap* map;       // ��ͼ
    cocos2d::Vec2 moveDirection;     // �ƶ�����
    InventoryLayer* inventoryLayer; //���������
    StoppingLayer* stoppingLayer;    // ��ͣ�����


};
