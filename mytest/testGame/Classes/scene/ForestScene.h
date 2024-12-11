#pragma once
#include "cocos2d.h"
#include "layer/inventoryLayer.h" 
#include"layer/StoppingLayer.h"

#define RATIO 1.25f
#define FROM_FARM_TO_TOWN 16 * 25 * RATIO
#define SIZE_FARM_X 50
#define SIZE_FARM_Y 50
class ForestScene : public cocos2d::Scene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ForestScene);
    // ��ȡ����ʵ��
    static ForestScene* getInstance() {
        if (!_instance) {
            _instance = ForestScene::create();
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
    static ForestScene* _instance; // ��̬����ָ��
    InventoryLayer* inventoryLayer; //���������
    StoppingLayer* stoppingLayer;    // ��ͣ�����

    void onBKeyPressed();

    void update(float deltaTime);    // ÿ֡���º���
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void updateCameraPosition();
    bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
    void setCameraHeight(float height);
    void checkMapSwitch(const cocos2d::Vec2& position);
};