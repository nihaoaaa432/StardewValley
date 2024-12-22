#include "test.h"
#include "TownScene.h"
#include "ForestScene.h"
#include "character/Player.h"
#include "character/Npc/John.h"
#include "ui/clock.h"
#include "character/Npc/DialogSystem.h"
TestScene* TestScene::_instance = nullptr;
using namespace cocos2d;

void TestScene::JohnMove() {
    // �ڳ����д���һ�� John NPC
    auto john = John::create("npc/john.png");  // "john.png" ����� John NPC ��ͼƬ�ļ�
    john->setPosition(Vec2(30 * 16 * RATIO, 30 * 16 * RATIO));  // ���� John �ĳ�ʼλ��
    john->setSpeed(50.0f);  // ���� John ���ƶ��ٶ�
    john->setPath({ Vec2(100, 100), Vec2(200, 200), Vec2(300, 300) });  // ���� John ���ƶ�·��
    this->addChild(john);  // �� John ��ӵ�������

    // ÿ10�����¿�ʼ��·����һ��
    this->schedule([=](float dt) {
        john->resetDailyMovement();  // ����ÿ�յ��ƶ�
        }, 10, "reset_daily_movement");
}
// ��ȡ����ʵ��
TestScene* TestScene::getInstance() {
    if (!_instance) {
        TestScene* pRet = new(std::nothrow) TestScene();
        if (pRet && pRet->init())
        {
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    return _instance;
}
// ���ٵ���ʵ��
void TestScene::destroyInstance() {
    if (_instance) {
        _instance->release();
        _instance = nullptr;
    }
}
cocos2d::Scene* TestScene::createScene() {
    return TestScene::create();
}

bool TestScene::init() {
    if (!ParentScene::init()) {
        return false;
    }

    // ���ص�ͼ
    map = cocos2d::TMXTiledMap::create("test.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0, 0));  // ��ê������Ϊ����
    map->setPosition(cocos2d::Vec2(0, 0));  // ���õ�ͼ��λ��
    this->addChild(map);

    // ����������
    inventoryLayer = InventoryLayer::createLayer();
    inventoryLayer->setVisible(false);  // Ĭ�����ر�������
    this->addChild(inventoryLayer);  // ������������ӵ�������

    // ������ͣ��
    stoppingLayer = StoppingLayer::createLayer();
    stoppingLayer->setVisible(false);  // Ĭ��������ͣ����
    this->addChild(stoppingLayer);  // ����ͣ������ӵ�������

    // ���þ�ͷ��ʼ�߶�
    setCameraHeight(50.0f);  // ������Ҫ�������ֵ
    //�����¼�
    mouthEvent();
    JohnMove();

    //// ���������UI��
    //UILayer* uiLayer = UILayer::createLayer();
    //this->addChild(uiLayer, 100000);  // ȷ���������ϲ�
    // ÿ֡����
    this->schedule([=](float deltaTime) {
        update(deltaTime);

        }, 0.02f, "update_key");
    this->addChild(DialogSystem::getInstance());


    return true;
}




