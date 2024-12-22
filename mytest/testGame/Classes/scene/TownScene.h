#pragma once

#include "cocos2d.h"
#include "layer/InventoryLayer.h" 
#include "layer/StoppingLayer.h"
#include "layer/ToolLayer.h"
#include <string>
#include "ForestScene.h"
#include "SandBeach.h"
#define SIZE_TOWN_X 100
#define SIZE_TOWN_Y 100
// 从town到farm的纵坐标
#define FROM_TOWN_TO_FARM_Y_UP 16* SIZE_TOWN_Y *0.8+21*16 
#define FROM_TOWN_TO_FARM_Y_DOWN FROM_TOWN_TO_FARM_Y_UP-16*4
#define FROM_TOWN_TO_FARM_X 0
#define FROM_TOWN_TO_BEACH_X 16*68
#define FROM_TOWN_TO_BEACH_Y 0
#define FROM_TOWN_TO_FOREST_X 0
#define FROM_TOWN_TO_FOREST_Y_UP 16*32
#define FROM_TOWN_TO_FOREST_Y_DOWN FROM_TOWN_TO_FOREST_Y_UP-16*4
#define FROM_TOWN_TO_LAKE_X SIZE_TOWN_X*16*0.68
#define FROM_TOWN_TO_LAKE_Y SIZE_TOWN_Y*16*RATIO-16
class TownScene : public ParentScene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TownScene);

    // 获取单例实例
    static TownScene* getInstance();

    // 销毁单例实例
static void destroyInstance();
private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Vec2 moveDirection;     // 移动方向
    static TownScene* _instance; // 静态单例指针


    bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    void checkMapSwitch(const cocos2d::Vec2& position);
    void goToNextScene(const std::string& nextScene);

};
