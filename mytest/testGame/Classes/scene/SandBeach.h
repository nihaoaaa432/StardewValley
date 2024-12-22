#pragma once

#include "cocos2d.h"
#include "layer/InventoryLayer.h" 
#include "layer/StoppingLayer.h"
#include "layer/ToolLayer.h"
#include <string>
#include "ForestScene.h"
#define SIZE_BEACH_X 50
#define SIZE_BEACH_Y 50
#define FROM_BEACH_TO_TOWN_X 16*23
#define FROM_BEACH_TO_TOWN_Y SIZE_BEACH_Y*16*RATIO
class SandBeach : public ParentScene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SandBeach);

    // 获取单例实例
    static SandBeach* getInstance();

    // 销毁单例实例
    static void destroyInstance();
private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Vec2 moveDirection;     // 移动方向
    static SandBeach* _instance; // 静态单例指针


    bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    void checkMapSwitch(const cocos2d::Vec2& position);
    void goToNextScene(const std::string& nextScene);

};
