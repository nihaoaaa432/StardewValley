#include "TownScene.h"
#include "MapScene.h"
#include "character/Player.h"
#include "Lake.h"
#include "ui/Clock.h"
USING_NS_CC;
TownScene* TownScene::_instance = nullptr;

// 获取单例实例
TownScene* TownScene::getInstance() {
    if (!_instance) {
        TownScene* pRet = new(std::nothrow) TownScene();
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
void TownScene::destroyInstance() {
    if (_instance) {
        _instance->release();
        _instance = nullptr;
    }
}

Scene* TownScene::createScene() {
    return TownScene::create();
}

bool TownScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 加载地图
    map = TMXTiledMap::create("town/town.tmx");
    map->setAnchorPoint(Vec2(0, 0));  // 将锚点设置为左下角
    map->setPosition(Vec2(0, 0));  // 设置地图的位置    // 设置地图锚点，确保地图从左下角开始渲染
    this->addChild(map);

    //// 创建角色精灵
    //Player::getInstance()->setPosition( Vec2(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y));  // 初始位置
    //this->addChild(Player::getInstance());
// 获取 ToolLayer 单例实例并添加到场景中
    auto toolLayer = ToolLayer::getInstance();
    this->addChild(toolLayer, 100);

    // 初始化工具栏，传入工具图片列表
    std::vector<std::string> toolImages = {
        "Tool1.png",
        "Tool2.png",
        "Tool3.png",
        "Tool4.png",
        "Tool5.png",
        // 添加更多工具图片
    };
    toolLayer->initToolBar(toolImages);


    // 创建背包层
    auto inventoryLayer = InventoryLayer::getInstance();
    inventoryLayer->setVisible(false);  // 默认隐藏背包界面
    this->addChild(inventoryLayer, 2);  // 将背包界面添加到场景中

    // 创建暂停层
    auto stoppingLayer = StoppingLayer::getInstance();
    stoppingLayer->setVisible(false);  // 默认隐藏暂停界面
    this->addChild(stoppingLayer, 1000);  // 将暂停界面添加到场景中
    mouthEvent();

    // 每帧更新
    this->schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    return true;
}

bool TownScene::canMoveToPosition(const  Vec2& position) {
    // 获取名为 "walk" 的对象层
    auto objectLayer = map->getObjectGroup("walk");  // 对象层名称
    if (!objectLayer) {
        return true;  // 如果没有名为 "walk" 的对象层，默认允许移动
    }

    // 获取所有对象
    auto objects = objectLayer->getObjects();

    for (const auto& obj : objects) {
        auto objMap = obj.asValueMap();

        // 获取 "walkable" 属性，检查此属性值是否为 false
        bool walkable = objMap["walkable"].asBool();
        if (!walkable) {
            // 如果对象不可行走，检查它是否覆盖目标位置
            // 左下角坐标相对于地图中心的坐标
            // 不知为何要乘1.25
            float x = objMap["x"].asFloat();
            float y = objMap["y"].asFloat();
            float width = objMap["width"].asFloat();
            float height = objMap["height"].asFloat();

            // 创建对象的边界框
            Rect objRect(x, y, width, height);

            // 如果目标位置在不可行走的区域内，则返回 false
            if (objRect.containsPoint(position)) {
                return false;
            }
        }
    }

    // 如果不在任何不可行走区域内，则允许移动
    return true;
}


void TownScene::goToNextScene(const std::string& nextScene) {
    // 1. 获取当前场景
    auto currentScene = Director::getInstance()->getRunningScene();
    auto player = Player::getInstance();

    // 2. 从当前场景移除角色
    if (currentScene && player->getParent() == currentScene) {
        player->removeFromParent();
    }

    // 3. 创建新场景
    Scene* newScene;

    // 4. 初始化角色在新场景中的状态
    if (nextScene == "Farm") {
        newScene = MapScene::getInstance();
        player->setPosition(Vec2(FROM_FARM_TO_TOWN_X - 16, FROM_FARM_TO_TOWN_Y)); // 设置角色位置
        player->setScale(1.0f); // 设置角色缩放比例
        Clock::getInstance()->setPosition(cocos2d::Vec2(300, 300));
    }
    else if (nextScene == "Beach") {
        newScene = SandBeach::getInstance();
        player->setPosition(Vec2(FROM_BEACH_TO_TOWN_X, FROM_BEACH_TO_TOWN_Y)); // 设置角色位置
        player->setScale(1.0f); // 设置角色缩放比例
    }
    else if (nextScene == "Forest") {
        newScene = ForestScene::getInstance();
        player->setPosition(Vec2(FROM_FOREST_TO_TOWN_X, FROM_FOREST_TO_TOWN_Y)); // 设置角色位置
        player->setScale(1.0f); // 设置角色缩放比例
    }
    else if (nextScene == "Lake") {
        newScene = LakeScene::getInstance();
        player->setPosition(Vec2(FROM_LAKE_TO_TOWN_X, FROM_LAKE_TO_TOWN_Y)); // 设置角色位置
        player->setScale(1.0f); // 设置角色缩放比例
    }

    // 5. 将角色添加到新场景
    newScene->addChild(player);

    // 6. 切换到新场景
    Director::getInstance()->replaceScene(newScene);
}


// 检查玩家是否到达触发地图切换的区域
void TownScene::checkMapSwitch(const  Vec2& position) {
    if (position.x < FROM_TOWN_TO_FARM_X && position.y>FROM_TOWN_TO_FARM_Y_DOWN && position.y < FROM_TOWN_TO_FARM_Y_UP) {
        goToNextScene("Farm");
    }
    else if (position.y < FROM_TOWN_TO_BEACH_Y) {
        goToNextScene("Beach");
    }
    else if (position.x< FROM_TOWN_TO_FOREST_X && position.y>FROM_TOWN_TO_FOREST_Y_DOWN && position.y < FROM_TOWN_TO_FOREST_Y_UP) {
        goToNextScene("Forest");
    }
    else if (position.y > FROM_TOWN_TO_LAKE_Y) {
        goToNextScene("Lake");
    }
}