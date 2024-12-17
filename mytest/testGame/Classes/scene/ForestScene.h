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
    // 获取单例实例
    static ForestScene* getInstance();
    // 销毁单例实例
    static void destroyInstance();

private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Vec2 moveDirection;     // 移动方向
    float speed = 100.0f;            // 移动速度
    static ForestScene* _instance; // 静态单例指针
    InventoryLayer* inventoryLayer; //背包界面层
    StoppingLayer* stoppingLayer;    // 暂停界面层

    void goToNextScene(const std::string& nextScene);
    bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    void checkMapSwitch(const cocos2d::Vec2& position);
};
