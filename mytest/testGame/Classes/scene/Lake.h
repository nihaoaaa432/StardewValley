#pragma once
#include "cocos2d.h"
#include "layer/InventoryLayer.h" 
#include "layer/StoppingLayer.h"
#include "layer/ToolLayer.h"
#include "ParentScene.h"
#include "TownScene.h"
#include "string"
#define SIZE_LAKE_X 50
#define SIZE_LAKE_Y 50
#define FROM_LAKE_TO_TOWN_X SIZE_LAKE_X*0.25*16
#define FROM_LAKE_TO_TOWN_Y 16
class LakeScene : public ParentScene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(LakeScene);
    // ��ȡ����ʵ��
    static LakeScene* getInstance();
    // ���ٵ���ʵ��
    static void destroyInstance();

private:
    cocos2d::TMXTiledMap* map;       // ��ͼ
    cocos2d::Vec2 moveDirection;     // �ƶ�����
    float speed = 100.0f;            // �ƶ��ٶ�
    static LakeScene* _instance; // ��̬����ָ��

    void goToNextScene(const std::string& nextScene);
    bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
    void checkMapSwitch(const cocos2d::Vec2& position);
};
