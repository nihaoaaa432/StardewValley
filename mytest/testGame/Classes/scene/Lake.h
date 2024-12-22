#pragma once
#include "cocos2d.h"
#include "layer/InventoryLayer.h" 
#include "layer/StoppingLayer.h"
#include "layer/ToolLayer.h"
#include "ParentScene.h"
#include "TownScene.h"
#include "string"
#define SIZE_LAKE_X 50
#define SIZE_LAKE_Y 50
#define FROM_LAKE_TO_TOWN_X SIZE_LAKE_X*0.25*16
#define FROM_LAKE_TO_TOWN_Y 16
class LakeScene : public ParentScene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LakeScene);
    // 获取单例实例
    static LakeScene* getInstance();
    // 销毁单例实例
    static void destroyInstance();

private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Vec2 moveDirection;     // 移动方向
    float speed = 100.0f;            // 移动速度
    static LakeScene* _instance; // 静态单例指针

    void goToNextScene(const std::string& nextScene);
    bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    void checkMapSwitch(const cocos2d::Vec2& position);
};
