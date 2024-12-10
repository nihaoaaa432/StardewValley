#pragma once

#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"
#define SIZE_TOWN_X 100
#define SIZE_TOWN_Y 100
// ��town��farm��������
#define FROM_TOWN_TO_FARM_Y 16* SIZE_TOWN_Y *0.8+18*16 
#define FROM_TOWN_TO_FARM_X 0
class TownScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(TownScene);
    void setPlayerPosition(cocos2d::Vec2& position);

    // ��ȡ����ʵ��
    static TownScene* getInstance() {
        if (!_instance) {
            _instance = TownScene::create();
        }
        return _instance;
    }

    // ���ٵ���ʵ��
    static void destroyInstance() {
        if (_instance) {
            _instance->release();
            _instance = nullptr;
        }
    }
private:
    cocos2d::TMXTiledMap* map;       // ��ͼ
    cocos2d::Sprite* player;         // ��ɫ����
    cocos2d::Vec2 moveDirection;     // �ƶ�����
    float speed = 100.0f;            // �ƶ��ٶ�
    static TownScene* _instance; // ��̬����ָ��
    InventoryLayer* inventoryLayer; //���������
    StoppingLayer* stoppingLayer;    // ��ͣ�����

    // void MapScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onBKeyPressed();

    void update(float deltaTime);    // ÿ֡���º���
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateCameraPosition();
    bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
    void setCameraHeight(float height);
    void checkMapSwitch(const cocos2d::Vec2& position);

};
