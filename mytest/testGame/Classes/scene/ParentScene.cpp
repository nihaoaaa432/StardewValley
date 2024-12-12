#include "ParentScene.h"
#include "MapScene.h"
#include "character/Player.h"
bool ParentScene::canMoveToPosition(const cocos2d::Vec2& position) {
    return true;
}  // 检测是否可以移动到目标位置
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
}

void ParentScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
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

