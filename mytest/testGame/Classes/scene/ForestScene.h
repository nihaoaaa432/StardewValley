#pragma once
#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
#include "ParentScene.h"
#include "MapScene.h"
#include "string"
#define FROM_FOREST_TO_FARM_Y SIZE_FOREST_Y*16*RATIO 
#define FROM_FOREST_TO_FARM_X 16*22
#define FROM_FOREST_TO_TOWN_X SIZE_FOREST_X*16*RATIO
#define FROM_FOREST_TO_TOWN_Y SIZE_FOREST_Y*16*0.7+16*2
#define SIZE_FOREST_X 100
#define SIZE_FOREST_Y 100
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

    void goToNextScene(const std::string& nextScene);
    bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
    void checkMapSwitch(const cocos2d::Vec2& position);
};
