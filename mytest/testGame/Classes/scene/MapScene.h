#pragma once
#include "cocos2d.h"
#include "ParentScene.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
#include "ForestScene.h"
#include "string"
#define RATIO 1.25f
#define FROM_FARM_TO_TOWN_X 16 * 25 * RATIO
#define FROM_FARM_TO_TOWN_Y 16*3.5
#define FROM_FARM_TO_FOREST_X 0
#define FROM_FARM_TO_FOREST_Y -16*25*RATIO
#define SIZE_FARM_X 50
#define SIZE_FARM_Y 50
class MapScene : public ParentScene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MapScene);
    // 获取单例实例
    static MapScene* getInstance();

    // 销毁单例实例
    static void destroyInstance();

private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Vec2 moveDirection;     // 移动方向
    static MapScene* _instance; // 静态单例指针

    InventoryLayer* inventoryLayer; //背包界面层
    StoppingLayer* stoppingLayer;    // 暂停界面层

    void goToNextScene(const std::string& nextScene);
    bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    void checkMapSwitch(const cocos2d::Vec2& position);
};
