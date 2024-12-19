#include "MapScene.h"
#include "TownScene.h"
#include "helper/MouseCoordinateLayer.h"
// 调整镜头高度的函数
void MapScene::setCameraHeight(float height) {
    auto camera = cocos2d::Director::getInstance()->getRunningScene()->getDefaultCamera();
    if (camera) {
        // 获取当前摄像机的位置
        cocos2d::Vec3 cameraPos = camera->getPosition3D();

        // 设置新的高度
        cameraPos.z = height;
        camera->setPosition3D(cameraPos);
    }
}
cocos2d::Scene* MapScene::createScene() {
    return MapScene::create();
}

bool MapScene::init() {
    if (!Scene::init()) {
        return false;
    }



    // 加载地图
    map = cocos2d::TMXTiledMap::create("farm/farm.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));  // 将锚点设置为中心
    map->setPosition(cocos2d::Vec2(0, 0));  // 设置地图的位置    // 设置地图锚点，确保地图从左下角开始渲染
    this->addChild(map);
    // ���þ�ͷ��ʼ�߶�
    setCameraHeight(100.0f);  // ������Ҫ�������ֵ

    // 创建角色精灵
    player = cocos2d::Sprite::create("sand.png");
    player->setPosition(cocos2d::Vec2(0, 0));  // 初始位置
    this->addChild(player);

    // 获取 ToolLayer 单例实例并添加到场景中
    auto toolLayer = ToolLayer::getInstance();
    this->addChild(toolLayer,2);

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
    this->addChild(inventoryLayer,2);  // 将背包界面添加到场景中

    // 创建暂停层
    auto stoppingLayer = StoppingLayer::getInstance();
    stoppingLayer->setVisible(false);  // 默认隐藏暂停界面
    this->addChild(stoppingLayer,2);  // 将暂停界面添加到场景中

    // 设置镜头初始高度
    setCameraHeight(100.0f);  // 根据需要调整这个值

    // 键盘事件监听器
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    auto mouseGet = MouseCoordinateLayer::create();
    this->addChild(mouseGet);
    //mouseGet->setPosition(cocos2d::Vec2(0,0));

    // 每帧更新
    this->schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    return true;
}

void MapScene::update(float deltaTime) {
    if (moveDirection != cocos2d::Vec2::ZERO) {
        cocos2d::Vec2 newPosition = player->getPosition() + moveDirection * speed * deltaTime;
        if (canMoveToPosition(newPosition)) {
            player->setPosition(newPosition);  // 只有可以移动时才更新位置
        }
    }
    //checkMapSwitch(player->getPosition());

    // 更新镜头位置，确保镜头跟随角色
    updateCameraPosition();

    //背包处于打开状态时以任务为中心
    auto inventoryLayer = InventoryLayer::getInstance();
    if (inventoryLayer->isVisible()) {
        inventoryLayer->updatePosition(player->getPosition());
    }
    auto stoppingLayer = StoppingLayer::getInstance();
    if (stoppingLayer->isVisible()) {
        stoppingLayer->updatePosition(player->getPosition());
    }
    auto toolLayer = ToolLayer::getInstance();
    toolLayer->updatePosition(player->getPosition());
}

void MapScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    auto inventoryLayer = InventoryLayer::getInstance();
    auto stoppingLayer = StoppingLayer::getInstance();
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
        stoppingLayer->onEscPress();
    }


}

void MapScene::onBKeyPressed() {
    auto stoppingLayer = StoppingLayer::getInstance();
    auto inventoryLayer = InventoryLayer::getInstance();
    // 处理 "B" 键被按下的逻辑
    if(!stoppingLayer->isVisible()) inventoryLayer->setVisible(!inventoryLayer->isVisible());

}

void MapScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        moveDirection = cocos2d::Vec2::ZERO;  // 停止移动
    }
}

bool MapScene::canMoveToPosition(const cocos2d::Vec2& position) {
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
                if (objRect.containsPoint(position)) {
                    return false;
                }
            }
        }
    }

        // 如果不在任何不可行走区域内，则允许移动
        return true;
}
//void MapScene::checkMapSwitch(const cocos2d::Vec2& position) {
//    if (position.x > FROM_FARM_TO_TOWN_X) {
//        auto townScene = TownScene::getInstance();
//        townScene->setPlayerPosition(cocos2d::Vec2(FROM_TOWN_TO_FARM_X + 16, FROM_TOWN_TO_FARM_Y));
//        moveDirection = cocos2d::Vec2::ZERO; // 停止角色移动
//        cocos2d::Director::getInstance()->pushScene(cocos2d::TransitionFade::create(0.3, TownScene::getInstance(), cocos2d::Color3B::WHITE));
//    }
//}


// 镜头跟随角色的函数
void MapScene::updateCameraPosition() {
 // 获取摄像机
    auto director = cocos2d::Director::getInstance();
    auto camera = director->getRunningScene()->getDefaultCamera();
    if (camera) {
         // 设置摄像机的位置，确保角色始终位于屏幕中央
        camera->setPosition(player->getPosition());
    }
}