#pragma once

#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
#include <string>
#include "ForestScene.h"
#include "SandBeach.h"
#define SIZE_TOWN_X 100
#define SIZE_TOWN_Y 100
// ��town��farm��������
#define FROM_TOWN_TO_FARM_Y_UP 16* SIZE_TOWN_Y *0.8+18*16 
#define FROM_TOWN_TO_FARM_Y_DOWN FROM_TOWN_TO_FARM_Y_UP-16
#define FROM_TOWN_TO_FARM_X 0
#define FROM_TOWN_TO_BEACH_X 16*68
#define FROM_TOWN_TO_BEACH_Y 0
class TownScene : public ParentScene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TownScene);

    // ��ȡ����ʵ��
    static TownScene* getInstance();

    // ���ٵ���ʵ��
static void destroyInstance();
private:
    cocos2d::TMXTiledMap* map;       // ��ͼ
    cocos2d::Vec2 moveDirection;     // �ƶ�����
    static TownScene* _instance; // ��̬����ָ��
    InventoryLayer* inventoryLayer; //���������
    StoppingLayer* stoppingLayer;    // ��ͣ�����


    bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
    void checkMapSwitch(const cocos2d::Vec2& position);
    void goToNextScene(const std::string& nextScene);

};
