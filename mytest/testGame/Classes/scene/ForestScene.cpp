#include "ForestScene.h"
#include "TownScene.h"
// 调整镜头高度的函数
void ForestScene::setCameraHeight(float height) {
    auto camera = cocos2d::Director::getInstance()->getRunningScene()->getDefaultCamera();
    if (camera) {
        // 获取当前摄像机的位置
        cocos2d::Vec3 cameraPos = camera->getPosition3D();

        // 设置新的高度
        cameraPos.z = height;
        camera->setPosition3D(cameraPos);
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
    map = cocos2d::TMXTiledMap::create("farm/farm.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));  // 将锚点设置为中心
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

    // 创建角色精灵
    player = cocos2d::Sprite::create("sand.png");
    player->setPosition(cocos2d::Vec2(0, 0));  // 初始位置
    this->addChild(player);

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

void ForestScene::update(float deltaTime) {
    if (moveDirection != cocos2d::Vec2::ZERO) {
        cocos2d::Vec2 newPosition = player->getPosition() + moveDirection * speed * deltaTime;
        if (canMoveToPosition(newPosition)) {
            player->setPosition(newPosition);  // 只有可以移动时才更新位置
        }
    }
    checkMapSwitch(player->getPosition());

    // 更新镜头位置，确保镜头跟随角色
    updateCameraPosition();
}

void ForestScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
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

void ForestScene::onBKeyPressed() {
    // 处理 "B" 键被按下的逻辑
    inventoryLayer->setVisible(!inventoryLayer->isVisible());

}

void ForestScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        moveDirection = cocos2d::Vec2::ZERO;  // 停止移动
    }
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
            // 如果对象不可行走，检查它是否覆盖目标位置
            // 左下角坐标相对于地图中心的坐标
            // 不知为何要乘RATIO
            float x = objMap["x"].asFloat() - SIZE_FARM_X / 2 * 16 * RATIO;
            float y = objMap["y"].asFloat() - SIZE_FARM_Y / 2 * 16 * RATIO;
            float width = objMap["width"].asFloat();
            float height = objMap["height"].asFloat();

            // 创建对象的边界框
            cocos2d::Rect objRect(x, y, width, height);

            // 如果目标位置在不可行走的区域内，则返回 false
            if (!walkable && objRect.containsPoint(position)) {
                return false;
            }
        }
    }

    // 如果不在任何不可行走区域内，则允许移动
    return true;
}
// 检查玩家是否到达触发地图切换的区域
void ForestScene::checkMapSwitch(const cocos2d::Vec2& position) {

    if (position.x > FROM_FARM_TO_TOWN) {
        // 玩家到达了触发区域，切换到新的地图
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.3, TownScene::createScene(), cocos2d::Color3B::WHITE));
    }
}


// 镜头跟随角色的函数
void ForestScene::updateCameraPosition() {
    // 获取摄像机
    auto director = cocos2d::Director::getInstance();
    auto camera = director->getRunningScene()->getDefaultCamera();
    if (camera) {
        // 设置摄像机的位置，确保角色始终位于屏幕中央
        camera->setPosition(player->getPosition());
    }
}