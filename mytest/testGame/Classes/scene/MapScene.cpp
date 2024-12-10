#include "MapScene.h"
#include"layer/InventoryLayer.h"
#include"layer/StoppingLayer.h"

cocos2d::Scene* MapScene::createScene() {
    return MapScene::create();
}

bool MapScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 加载地图
    map = cocos2d::TMXTiledMap::create("farm.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));  // 将锚点设置为中心
    map->setPosition(cocos2d::Vec2(0, 0));  // 设置地图的位置    // 设置地图锚点，确保地图从左下角开始渲染
    this->addChild(map);

    // 创建背包层
    cinventoryLayer = CinventoryLayer::createLayer();
    cinventoryLayer->setVisible(false);  // 默认隐藏背包界面
    this->addChild(cinventoryLayer);  // 将背包界面添加到场景中

    // 创建暂停层
    auto stoppingLayer = StoppingLayer::createLayer();
    stoppingLayer = static_cast<StoppingLayer*> (stoppingLayer->getChildByTag(StoppingLayer::menuSceneTag));
    stoppingLayer->setVisible(false);  // 默认隐藏暂停界面
    stoppingLayer->setTag(StoppingLayer::menuSceneTag);  // 设置标签
    this->addChild(stoppingLayer);  // 将暂停界面添加到场景中


    // 注册键盘事件监听器
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);


    // 创建角色精灵
    //player=player->Create("Abigail.png", 16, 32, 13, 8, 100.0f);
    //int mapHeight ;
    //float cocosX = 0;
    //float cocosY = mapHeight;
    //player->SetPosition(cocos2d::Vec2(0, 0));  // 初始位置
    //this->addChild(player);

    //// 键盘事件监听器
    //auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    //keyboardListener->onKeyPressed = CC_CALLBACK_2(Cplayer::OnKeyPressed, this);
    //keyboardListener->onKeyReleased = CC_CALLBACK_2(Cplayer::OnKeyReleased, this);
    //_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // 每帧更新
    /*this->schedule([=](float deltaTime) {
        player->update(deltaTime);
        }, "update_key");*/

    return true;
}



void MapScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_B) {
        onBKeyPressed();
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE) {
        // 处理 "ESC" 键被按下的逻辑
        auto stoppingLayer = static_cast<StoppingLayer*>(this->getChildByTag(StoppingLayer::menuSceneTag));
        if (!stoppingLayer->isVisible()) {
            stoppingLayer->setVisible(true);
        }
        else {
            stoppingLayer->setVisible(false);
        }
    }
}

void MapScene::onBKeyPressed() {
    // 处理 "B" 键被按下的逻辑
    if (!cinventoryLayer->isVisible()) {
        cinventoryLayer->setVisible(true);
    }
    else {
        cinventoryLayer->setVisible(false);
    }
}

//void MapScene::update(float deltaTime) {
//    if (moveDirection != cocos2d::Vec2::ZERO) {
//        cocos2d::Vec2 newPosition = player->getPosition() + moveDirection * speed * deltaTime;
//        if (canMoveToPosition(newPosition)) {
//            player->setPosition(newPosition);  // 只有可以移动时才更新位置
//        }
//    }
//
//    // 更新镜头位置，确保镜头跟随角色
//    updateCameraPosition();
//}
//
//void MapScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
//    switch (keyCode) {
//    case cocos2d::EventKeyboard::KeyCode::KEY_W:
//        moveDirection = cocos2d::Vec2(0, 1);  // 向上
//        break;
//    case cocos2d::EventKeyboard::KeyCode::KEY_S:
//        moveDirection = cocos2d::Vec2(0, -1); // 向下
//        break;
//    case cocos2d::EventKeyboard::KeyCode::KEY_A:
//        moveDirection = cocos2d::Vec2(-1, 0); // 向左
//        break;
//    case cocos2d::EventKeyboard::KeyCode::KEY_D:
//        moveDirection = cocos2d::Vec2(1, 0);  // 向右
//        break;
//    default:
//        break;
//    }
//}
//
//void MapScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
//    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
//        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
//        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
//        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
//        moveDirection = cocos2d::Vec2::ZERO;  // 停止移动
//    }
//}

bool MapScene::canMoveToPosition(const cocos2d::Vec2& position) {
    // 获取对象层
    auto objectLayer = map->getObjectGroup("walk");  // 对象层名称
    if (!objectLayer) {
        return true;  // 没有对象层则默认允许移动
    }

    // 获取所有对象
    auto objects = objectLayer->getObjects();

    for (const auto& obj : objects) {
        auto objMap = obj.asValueMap();

        // 检查对象的 walkable 属性
        bool walkable = objMap["walkable"].asBool();
        float x = objMap["x"].asFloat();
        float y = objMap["y"].asFloat();
        float width = objMap["width"].asFloat();
        float height = objMap["height"].asFloat();

        // 创建对象的边界框
        cocos2d::Rect objRect(x, y, width, height);

        // 如果目标位置在不可行走的区域内，则返回 false
        if (!walkable && objRect.containsPoint(position)) {
            return false;
        }
    }

    // 如果不在任何不可行走区域内，则允许移动
    return true;
}

// 镜头跟随角色的函数
void MapScene::updateCameraPosition() {
    // 获取摄像机
    auto director = cocos2d::Director::getInstance();
    auto camera = director->getRunningScene()->getDefaultCamera();
    if (camera) {
        // 设置摄像机的位置，确保角色始终位于屏幕中央
       // camera->setPosition(player->getPosition());
    }
}
