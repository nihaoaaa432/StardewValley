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
    // ��ȡ����ʵ��
    static TestScene* getInstance();

    // ���ٵ���ʵ��
    static void destroyInstance();

    //npc���ƶ�
    void JohnMove();
private:
    cocos2d::TMXTiledMap* map;       // ��ͼ
    cocos2d::Vec2 moveDirection;     // �ƶ�����
    static TestScene* _instance; // ��̬����ָ��

    InventoryLayer* inventoryLayer; //���������
    StoppingLayer* stoppingLayer;    // ��ͣ�����

};
