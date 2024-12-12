#pragma once
#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
#include "ParentScene.h"
#define RATIO 1.25f
#define FROM_FARM_TO_TOWN 16 * 25 * RATIO
#define SIZE_FARM_X 50
#define SIZE_FARM_Y 50
class ForestScene : public ParentScene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ForestScene);
    // ��ȡ����ʵ��
    static ForestScene* getInstance();
    // ���ٵ���ʵ��
    static void destroyInstance();

private:
    cocos2d::TMXTiledMap* map;       // ��ͼ
    cocos2d::Vec2 moveDirection;     // �ƶ�����
    float speed = 100.0f;            // �ƶ��ٶ�
    static ForestScene* _instance; // ��̬����ָ��
    InventoryLayer* inventoryLayer; //���������
    StoppingLayer* stoppingLayer;    // ��ͣ�����

    void goToNextScene();
    bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
    void checkMapSwitch(const cocos2d::Vec2& position);
};
