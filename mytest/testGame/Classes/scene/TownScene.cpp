#include "TownScene.h"

cocos2d::Scene* TownScene::createScene() {
    return TownScene::create();
}

bool TownScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 加载地图
    map = cocos2d::TMXTiledMap::create("town/town.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0, 0));  // 将锚点设置为中心
    map->setPosition(cocos2d::Vec2(0, 0));  // 设置地图的位置    // 设置地图锚点，确保地图从左下角开始渲染
    this->addChild(map);

    // 创建角色精灵
    player = cocos2d::Sprite::create("sand.png");
    player->setPosition(cocos2d::Vec2(0, FROM_HOME_TO_TOWN));  // 初始位置
    this->addChild(player);

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
        cocos2d::Vec2 newPosition = player->getPosition() + moveDirection * speed * deltaTime;
        if (canMoveToPosition(newPosition)) {
            player->setPosition(newPosition);  // 只有可以移动时才更新位置
        }
    }

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
}

void TownScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        moveDirection = cocos2d::Vec2::ZERO;  // 停止移动
    }
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
            float x = objMap["x"].asFloat() - 25 * 16 * 1.25;
            float y = objMap["y"].asFloat() - 25 * 16 * 1.25;
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
        camera->setPosition(player->getPosition());
    }
}
