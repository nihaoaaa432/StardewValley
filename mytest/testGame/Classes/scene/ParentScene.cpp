#include "ParentScene.h"
#include "MapScene.h"
#include "character/Player.h"
bool ParentScene::canMoveToPosition(const cocos2d::Vec2& position) {
    return true;
}  // ����Ƿ�����ƶ���Ŀ��λ��
void ParentScene::checkMapSwitch(const cocos2d::Vec2& position) {}
void ParentScene::goToNextScene() {}

void ParentScene::update(float deltaTime) {
    if (moveDirection != cocos2d::Vec2::ZERO) {
        cocos2d::Vec2 newPosition = Player::getInstance()->getPosition() + moveDirection * Player::getInstance()->getSpeed() * deltaTime;
        if (canMoveToPosition(newPosition)) {
            Player::getInstance()->setPosition(newPosition);  // ֻ�п����ƶ�ʱ�Ÿ���λ��
        }
    }
    checkMapSwitch(Player::getInstance()->getPosition());

    // ���¾�ͷλ�ã�ȷ����ͷ�����ɫ
    updateCameraPosition();
}

void ParentScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    switch (keyCode) {
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
        moveDirection = cocos2d::Vec2(0, 1);  // ����
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
        moveDirection = cocos2d::Vec2(0, -1); // ����
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        moveDirection = cocos2d::Vec2(-1, 0); // ����
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        moveDirection = cocos2d::Vec2(1, 0);  // ����
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
        moveDirection = cocos2d::Vec2::ZERO;  // ֹͣ�ƶ�
    }
}
void ParentScene::onBKeyPressed() {
    // ���� "B" �������µ��߼�
    inventoryLayer->setVisible(!inventoryLayer->isVisible());

}



// ��ͷ�����ɫ�ĺ���
void ParentScene::updateCameraPosition() {
    // ��ȡ�����
    auto director = cocos2d::Director::getInstance();
    auto camera = director->getRunningScene()->getDefaultCamera();
    if (camera) {
        // �����������λ�ã�ȷ����ɫʼ��λ����Ļ����
        camera->setPosition(Player::getInstance()->getPosition());
    }
}

void ParentScene::setCameraHeight(float height) {
    auto camera = cocos2d::Director::getInstance()->getRunningScene()->getDefaultCamera();
    if (camera) {
        // ��ȡ��ǰ�������λ��
        cocos2d::Vec3 cameraPos = camera->getPosition3D();

        // �����µĸ߶�
        cameraPos.z = height;
        camera->setPosition3D(cameraPos);
    }
}

