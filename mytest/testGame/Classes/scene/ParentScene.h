#pragma once
#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
class ParentScene : public cocos2d::Scene {
public:
    void onBKeyPressed();
    void mouthEvent();
    void update(float deltaTime);    // 每帧更新函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateCameraPosition();
    void setCameraHeight(float height);
    bool init();
    virtual bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    virtual void checkMapSwitch(const cocos2d::Vec2& position);
    virtual void goToNextScene();

private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Vec2 moveDirection;     // 移动方向
    InventoryLayer* inventoryLayer; //背包界面层
    StoppingLayer* stoppingLayer;    // 暂停界面层
};
