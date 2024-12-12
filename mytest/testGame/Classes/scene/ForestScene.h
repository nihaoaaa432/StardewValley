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

    void goToNextScene();
    bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    void checkMapSwitch(const cocos2d::Vec2& position);
};
