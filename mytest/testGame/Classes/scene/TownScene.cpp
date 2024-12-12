#include "TownScene.h"
#include "MapScene.h"
#include "character/Player.h"
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
void TownScene:: destroyInstance() {
    if (_instance) {
        _instance->release();
        _instance = nullptr;
    }
}

cocos2d::Scene* TownScene::createScene() {
    return TownScene::create();
}

bool TownScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 加载地图
    map = cocos2d::TMXTiledMap::create("town/town.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0, 0));  // 将锚点设置为左下角
    map->setPosition(cocos2d::Vec2(0, 0));  // 设置地图的位置    // 设置地图锚点，确保地图从左下角开始渲染
    this->addChild(map);

    //// 创建角色精灵
    //Player::getInstance()->setPosition(cocos2d::Vec2(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y));  // 初始位置
    //this->addChild(Player::getInstance());
    // 创建背包层
    inventoryLayer = InventoryLayer::createLayer();
    inventoryLayer->setVisible(false);  // 默认隐藏背包界面
    this->addChild(inventoryLayer);  // 将背包界面添加到场景中

    // 创建暂停层
    stoppingLayer = StoppingLayer::createLayer();
    stoppingLayer->setVisible(false);  // 默认隐藏暂停界面
    this->addChild(stoppingLayer);  // 将暂停界面添加到场景中

    // 键盘事件监听器
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(TownScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(TownScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 每帧更新
    this->schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    return true;
}

void TownScene::update(float deltaTime) {
    if (moveDirection != cocos2d::Vec2::ZERO) {
        cocos2d::Vec2 newPosition = Player::getInstance()->getPosition() + moveDirection * Player::getInstance()->getSpeed() * deltaTime;
        if (canMoveToPosition(newPosition)) {
            Player::getInstance()->setPosition(newPosition);  // 只有可以移动时才更新位置
        }
    }
    checkMapSwitch(Player::getInstance()->getPosition());

    // 更新镜头位置，确保镜头跟随角色
    updateCameraPosition();
}

void TownScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
        moveDirection = cocos2d::Vec2(0, 1);  // 向上
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
        moveDirection = cocos2d::Vec2(0, -1); // 向下
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        moveDirection = cocos2d::Vec2(-1, 0); // 向左
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        moveDirection = cocos2d::Vec2(1, 0);  // 向右
        break;

    default:
        break;
    }
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_B) {
        onBKeyPressed();
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE) {
        stoppingLayer->setVisible(!stoppingLayer->isVisible());
    }


}

void TownScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        moveDirection = cocos2d::Vec2::ZERO;  // 停止移动
    }
}
void TownScene::onBKeyPressed() {
    // 处理 "B" 键被按下的逻辑
    inventoryLayer->setVisible(!inventoryLayer->isVisible());

}

bool TownScene::canMoveToPosition(const cocos2d::Vec2& position) {
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
            float x = objMap["x"].asFloat() ;
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


// 镜头跟随角色的函数
void TownScene::updateCameraPosition() {
    // 获取摄像机
    auto director = cocos2d::Director::getInstance();
    auto camera = director->getRunningScene()->getDefaultCamera();
    if (camera) {
        // 设置摄像机的位置，确保角色始终位于屏幕中央
        camera->setPosition(Player::getInstance()->getPosition());
    }
}

void TownScene::goToNextScene() {
    // 1. 获取当前场景
    auto currentScene = cocos2d::Director::getInstance()->getRunningScene();
    auto player = Player::getInstance();

    // 2. 从当前场景移除角色
    if (currentScene && player->getParent() == currentScene) {
        player->removeFromParent();
    }

    // 3. 创建新场景
    auto newScene = MapScene::getInstance();

    // 4. 初始化角色在新场景中的状态
    player->setPosition(cocos2d::Vec2(FROM_FARM_TO_TOWN_X - 16, FROM_FARM_TO_TOWN_Y)); // 设置角色位置
    player->setScale(1.0f); // 设置角色缩放比例

    // 5. 将角色添加到新场景
    newScene->addChild(player);

    // 6. 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(newScene);
}


// 检查玩家是否到达触发地图切换的区域
void TownScene::checkMapSwitch(const cocos2d::Vec2& position) {
    if (position.x < FROM_TOWN_TO_FARM_X&&position.y>FROM_TOWN_TO_FARM_Y_UP -16&&position.y< FROM_TOWN_TO_FARM_Y_UP+16) {
        goToNextScene();
        //auto mapScene = MapScene::getInstance();
        //Player::getInstance()->setPosition(cocos2d::Vec2(FROM_FARM_TO_TOWN_X - 16, FROM_FARM_TO_TOWN_Y));
        //moveDirection = cocos2d::Vec2::ZERO; // 停止角色移动
        //cocos2d::Director::getInstance()->pushScene(cocos2d::TransitionFade::create(0.3, mapScene, cocos2d::Color3B::WHITE));
    }
    
}