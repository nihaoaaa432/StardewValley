#pragma once
#include "cocos2d.h"
#include "Layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"

#define RATIO 1.25f
class MapScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(MapScene);

private:
    cocos2d::TMXTiledMap* map;       // 地图
    //Cplayer* player;         // 角色精灵
    cocos2d::Vec2 moveDirection;     // 移动方向
    float speed = 100.0f;            // 移动速度

    CinventoryLayer* cinventoryLayer; //背包界面层
    StoppingLayer* stoppingLayer;    // 暂停界面层

    void MapScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void MapScene::onBKeyPressed();

    //void update(float deltaTime);    // 每帧更新函数
    //void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    //void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateCameraPosition();
    bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
    void MapScene::checkMapSwitch(const cocos2d::Vec2& position);  //����Ƿ�Ӧ���л�����
    void MapScene::setCameraHeight(float height);
};
