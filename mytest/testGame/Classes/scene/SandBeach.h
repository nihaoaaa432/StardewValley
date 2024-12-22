#pragma once

#include "cocos2d.h"
#include "layer/InventoryLayer.h" 
#include "layer/StoppingLayer.h"
#include "layer/ToolLayer.h"
#include <string>
#include "ForestScene.h"
#define SIZE_BEACH_X 50
#define SIZE_BEACH_Y 50
#define FROM_BEACH_TO_TOWN_X 16*23
#define FROM_BEACH_TO_TOWN_Y SIZE_BEACH_Y*16*RATIO
class SandBeach : public ParentScene {
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(SandBeach);

    // ��ȡ����ʵ��
    static SandBeach* getInstance();

    // ���ٵ���ʵ��
    static void destroyInstance();
private:
    cocos2d::TMXTiledMap* map;       // ��ͼ
    cocos2d::Vec2 moveDirection;     // �ƶ�����
    static SandBeach* _instance; // ��̬����ָ��


    bool canMoveToPosition(const cocos2d::Vec2& position);  // ����Ƿ�����ƶ���Ŀ��λ��
    void checkMapSwitch(const cocos2d::Vec2& position);
    void goToNextScene(const std::string& nextScene);

};
