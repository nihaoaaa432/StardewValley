#include "ForestScene.h"
#include "TownScene.h"
#include "character/Player.h"

ForestScene* ForestScene::_instance = nullptr;
ForestScene* ForestScene:: getInstance() {
    if (!_instance) {
        ForestScene* pRet = new(std::nothrow) ForestScene();
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
void ForestScene::destroyInstance() {
    if (_instance) {
        _instance->release();
        _instance = nullptr;
    }

}

cocos2d::Scene* ForestScene::createScene() {
    return ForestScene::create();
}

bool ForestScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 加载地图
    map = cocos2d::TMXTiledMap::create("forest/forest.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0, 0));  // 将锚点设置为中心
    map->setPosition(cocos2d::Vec2(0, 0));  // 设置地图的位置    // 设置地图锚点，确保地图从左下角开始渲染
    this->addChild(map);
    setCameraHeight(100.0f);

    // 创建背包层
    inventoryLayer = InventoryLayer::createLayer();
    inventoryLayer->setVisible(false);  // 默认隐藏背包界面
    this->addChild(inventoryLayer);  // 将背包界面添加到场景中

    // 创建暂停层
    stoppingLayer = StoppingLayer::createLayer();
    stoppingLayer->setVisible(false);  // 默认隐藏暂停界面
    this->addChild(stoppingLayer);  // 将暂停界面添加到场景中


    // 设置镜头初始高度
    setCameraHeight(100.0f);  // 根据需要调整这个值

    // 键盘事件监听器
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(ForestScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(ForestScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 每帧更新
    this->schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    return true;
}
bool ForestScene::canMoveToPosition(const cocos2d::Vec2& position) {
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
            float x = objMap["x"].asFloat();
            float y = objMap["y"].asFloat();
            float width = objMap["width"].asFloat();
            float height = objMap["height"].asFloat();

            // 创建对象的边界框
            cocos2d::Rect objRect(x, y, width, height);

            // 如果目标位置在不可行走的区域内，则返回 false
            if (objRect.containsPoint(position)) {
                return false;
            }
        }
    }

    // 如果不在任何不可行走区域内，则允许移动
    return true;
} 
void ForestScene::goToNextScene(const std::string& nextScene) {
    // 1. 获取当前场景
    auto currentScene = cocos2d::Director::getInstance()->getRunningScene();
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
        player->setPosition(cocos2d::Vec2(FROM_FARM_TO_FOREST_X, FROM_FARM_TO_FOREST_Y)); // 设置角色位置
        player->setScale(1.0f); // 设置角色缩放比例
    }
    else if (nextScene == "Town") {
        newScene = TownScene::getInstance();
        player->setPosition(cocos2d::Vec2(FROM_TOWN_TO_FOREST_X, FROM_TOWN_TO_FOREST_Y_UP-16)); // 设置角色位置
        player->setScale(1.0f); // 设置角色缩放比例
    }

    // 5. 将角色添加到新场景
    newScene->addChild(player);

    // 6. 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(newScene);
}

// 检查玩家是否到达触发地图切换的区域
void ForestScene::checkMapSwitch(const cocos2d::Vec2& position) {

    if (position.y > FROM_FOREST_TO_FARM_Y) {
        // 玩家到达了触发区域，切换到新的地图
        goToNextScene("Farm");
    }
    else if (position.x > FROM_FOREST_TO_TOWN_X) {
        goToNextScene("Town");
    }
}


