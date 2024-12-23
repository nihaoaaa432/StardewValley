#pragma once
#include "cocos2d.h"
#include "layer/InventoryLayer.h" 
#include "layer/StoppingLayer.h"
#include "layer/ToolLayer.h"
#include "ParentScene.h"
#include "character/Player.h"
#include "ForestScene.h"
#include "string"
#include "character/Crops.h"
#define RATIO 1.25f
#define FROM_FARM_TO_TOWN_X 16 * 50 * RATIO
#define FROM_FARM_TO_TOWN_Y 16*28.5*RATIO
#define FROM_FARM_TO_FOREST_X 0.45*16*SIZE_FARM_X*RATIO
#define FROM_FARM_TO_FOREST_Y 0
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

    //npc的移动
    void JohnMove();
private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Vec2 moveDirection;     // 移动方向
    static MapScene* _instance; // 静态单例指针

    std::vector<Interactable*> interactbales;//可交互物品容器

    void update(float deltaTime);    // 每帧更新函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onBKeyPressed();
    bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    void goToNextScene(const std::string& nextScene);
    void checkMapSwitch(const cocos2d::Vec2& position);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    //鼠标相关
    void mouthEvent();    //总体调用函数
    void onMouseDown(cocos2d::Event* event);
};

