#pragma once
#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"

#define RATIO 1.25f
#define FROM_FARM_TO_TOWN 16 * 25 * RATIO
#define SIZE_FARM_X 50
#define SIZE_FARM_Y 50
class MapScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MapScene);
    // 获取单例实例
    static MapScene* getInstance() {
        if (!_instance) {
            _instance = MapScene::create();
        }
        return _instance;
    }

    // 销毁单例实例
    static void destroyInstance() {
        if (_instance) {
            _instance->release();
            _instance = nullptr;
        }
    }

private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Sprite* player;         // 角色精灵
    cocos2d::Vec2 moveDirection;     // 移动方向
    float speed = 100.0f;            // 移动速度
    static MapScene* _instance; // 静态单例指针

    InventoryLayer* inventoryLayer; //背包界面层
    StoppingLayer* stoppingLayer;    // 暂停界面层

   // void MapScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void MapScene::onBKeyPressed();

    void update(float deltaTime);    // 每帧更新函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateCameraPosition();
    bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    void setCameraHeight(float height);
    void checkMapSwitch(const cocos2d::Vec2& position);
};
