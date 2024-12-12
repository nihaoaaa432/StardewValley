#pragma once
#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
#define SIZE_TOWN_X 100
#define SIZE_TOWN_Y 100
// 从town到farm的纵坐标
#define FROM_TOWN_TO_FARM_Y_UP 16* SIZE_TOWN_Y *0.8+18*16 
#define FROM_TOWN_TO_FARM_Y_DOWN FROM_TOWN_TO_FARM_Y_UP-16
#define FROM_TOWN_TO_FARM_X 0
class ParentScene : public cocos2d::Scene {
public:
    void onBKeyPressed();

    void update(float deltaTime);    // 每帧更新函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateCameraPosition();
    void setCameraHeight(float height);

    virtual bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    virtual void checkMapSwitch(const cocos2d::Vec2& position);
    virtual void goToNextScene();

private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Vec2 moveDirection;     // 移动方向
    InventoryLayer* inventoryLayer; //背包界面层
    StoppingLayer* stoppingLayer;    // 暂停界面层


};
