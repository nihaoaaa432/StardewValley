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
    // 在场景中创建一个 John NPC
    auto john = John::create("npc/john.png");  // "john.png" 是你给 John NPC 的图片文件
    john->setPosition(Vec2(30 * 16 * RATIO, 30 * 16 * RATIO));  // 设置 John 的初始位置
    john->setSpeed(50.0f);  // 设置 John 的移动速度
    john->setPath({ Vec2(100, 100), Vec2(200, 200), Vec2(300, 300) });  // 设置 John 的移动路径
    this->addChild(john);  // 将 John 添加到场景中

    // 每10秒重新开始按路径走一遍
    this->schedule([=](float dt) {
        john->resetDailyMovement();  // 重置每日的移动
        }, 10, "reset_daily_movement");
}
// 获取单例实例
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
// 销毁单例实例
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

    // 加载地图
    map = cocos2d::TMXTiledMap::create("test.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0, 0));  // 将锚点设置为中心
    map->setPosition(cocos2d::Vec2(0, 0));  // 设置地图的位置
    this->addChild(map);

    // 创建背包层
    inventoryLayer = InventoryLayer::createLayer();
    inventoryLayer->setVisible(false);  // 默认隐藏背包界面
    this->addChild(inventoryLayer);  // 将背包界面添加到场景中

    // 创建暂停层
    stoppingLayer = StoppingLayer::createLayer();
    stoppingLayer->setVisible(false);  // 默认隐藏暂停界面
    this->addChild(stoppingLayer);  // 将暂停界面添加到场景中

    // 设置镜头初始高度
    setCameraHeight(50.0f);  // 根据需要调整这个值
    //键盘事件
    mouthEvent();
    JohnMove();

    //// 创建并添加UI层
    //UILayer* uiLayer = UILayer::createLayer();
    //this->addChild(uiLayer, 100000);  // 确保它在最上层
    // 每帧更新
    this->schedule([=](float deltaTime) {
        update(deltaTime);

        }, 0.02f, "update_key");
    this->addChild(DialogSystem::getInstance());


    return true;
}




