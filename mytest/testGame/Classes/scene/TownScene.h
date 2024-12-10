#pragma once

#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
#define SIZE_TOWN_X 100
#define SIZE_TOWN_Y 100
// 从town到farm的纵坐标
#define FROM_TOWN_TO_FARM_Y 16* SIZE_TOWN_Y *0.8+18*16 
#define FROM_TOWN_TO_FARM_X 0
class TownScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TownScene);
    void setPlayerPosition(cocos2d::Vec2& position);

    // 获取单例实例
    static TownScene* getInstance() {
        if (!_instance) {
            _instance = TownScene::create();
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
    static TownScene* _instance; // 静态单例指针
    InventoryLayer* inventoryLayer; //背包界面层
    StoppingLayer* stoppingLayer;    // 暂停界面层

    // void MapScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onBKeyPressed();

    void update(float deltaTime);    // 每帧更新函数
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateCameraPosition();
    bool canMoveToPosition(const cocos2d::Vec2& position);  // 检测是否可以移动到目标位置
    void setCameraHeight(float height);
    void checkMapSwitch(const cocos2d::Vec2& position);

};
