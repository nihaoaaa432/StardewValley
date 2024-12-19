#pragma once
#include "cocos2d.h"
#include "ParentScene.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
#include "character/Player.h"
#include "cocos2d.h"
class TestScene : public ParentScene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TestScene);
    // 获取单例实例
    static TestScene* getInstance();

    // 销毁单例实例
    static void destroyInstance();

    //npc的移动
    void JohnMove();
private:
    cocos2d::TMXTiledMap* map;       // 地图
    cocos2d::Vec2 moveDirection;     // 移动方向
    static TestScene* _instance; // 静态单例指针

    InventoryLayer* inventoryLayer; //背包界面层
    StoppingLayer* stoppingLayer;    // 暂停界面层

};
