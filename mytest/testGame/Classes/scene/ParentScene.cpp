#include "ParentScene.h"
#include "MapScene.h"
#include "character/Player.h"
#include "character/Npc/John.h"
#include "ui/Clock.h"
#include "character/Npc/Npc.h"
bool ParentScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // 获取单例的Clock
    Clock* clock = Clock::getInstance();
    if (clock && clock->getParent() == nullptr) {
        // 确保时钟没有父节点，才添加到场景
        this->addChild(clock, 1000);
    }

    // 每帧更新
    this->schedule([=](float deltaTime) {
        CCLOG("Updating clock...");
        update(deltaTime);  // 更新其他内容

        if (clock) {
            clock->update(deltaTime);  // 更新时间
            clock->updateClockPosition(); // 更新时钟位置
        }
        }, 0.02f, "update_key");
    
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

    return true;
}

void ParentScene::mouthEvent() {
    // 键盘事件监听器
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(ParentScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(ParentScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

bool ParentScene::canMoveToPosition(const cocos2d::Vec2& position) {
    return true;  // 检测是否可以移动到目标位置
}

void ParentScene::checkMapSwitch(const cocos2d::Vec2& position) {}

void ParentScene::goToNextScene() {}

void ParentScene::update(float deltaTime) {
    if (moveDirection != cocos2d::Vec2::ZERO) {
        cocos2d::Vec2 newPosition = Player::getInstance()->getPosition() + moveDirection * Player::getInstance()->getSpeed() * deltaTime;
        if (canMoveToPosition(newPosition)) {
            Player::getInstance()->setPosition(newPosition);  // 只有可以移动时才更新位置
        }
    }
    checkMapSwitch(Player::getInstance()->getPosition());

    // 更新镜头位置，确保镜头跟随角色
    updateCameraPosition();

    //背包处于打开状态时以任务为中心
    auto inventoryLayer = InventoryLayer::getInstance();
    if (inventoryLayer->isVisible()) {
        inventoryLayer->updatePosition(Player::getInstance()->getPosition());
    }
    auto stoppingLayer = StoppingLayer::getInstance();
    if (stoppingLayer->isVisible()) {
        stoppingLayer->updatePosition(Player::getInstance()->getPosition());
    }
    auto toolLayer = ToolLayer::getInstance();
    toolLayer->updatePosition(Player::getInstance()->getPosition());

    // 更新所有 NPC 的状态（此处更新 John）
    for (auto& child : this->getChildren()) {
        if (auto npc = dynamic_cast<NPC*>(child)) {
            npc->update(deltaTime);  // 更新 NPC 的状态
        }
    }
}

void ParentScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    auto stoppingLayer = StoppingLayer::getInstance();
    if (!stoppingLayer->isVisible()) {
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


    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_B) {
        onBKeyPressed();
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE) {
        stoppingLayer->setVisible(!stoppingLayer->isVisible());
    }
}

void ParentScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        moveDirection = cocos2d::Vec2::ZERO;  // 停止移动
    }
}

void ParentScene::onBKeyPressed() {
    // 处理 "B" 键被按下的逻辑
    auto inventoryLayer = InventoryLayer::getInstance();
    inventoryLayer->setVisible(!inventoryLayer->isVisible());
}

// 镜头跟随角色的函数
void ParentScene::updateCameraPosition() {
    // 获取摄像机
    auto director = cocos2d::Director::getInstance();
    auto camera = director->getRunningScene()->getDefaultCamera();
    if (camera) {
        // 设置摄像机的位置，确保角色始终位于屏幕中央
        camera->setPosition(Player::getInstance()->getPosition());
    }
}

void ParentScene::setCameraHeight(float height) {
    auto camera = cocos2d::Director::getInstance()->getRunningScene()->getDefaultCamera();
    if (camera) {
        // 获取当前摄像机的位置
        cocos2d::Vec3 cameraPos = camera->getPosition3D();

        // 设置新的高度
        cameraPos.z = height;
        camera->setPosition3D(cameraPos);
    }
}
