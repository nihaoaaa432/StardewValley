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

    // ��ȡ������Clock
    Clock* clock = Clock::getInstance();
    if (clock && clock->getParent() == nullptr) {
        // ȷ��ʱ��û�и��ڵ㣬����ӵ�����
        this->addChild(clock, 1000);
    }

    // ÿ֡����
    this->schedule([=](float deltaTime) {
        CCLOG("Updating clock...");
        update(deltaTime);  // ������������

        if (clock) {
            clock->update(deltaTime);  // ����ʱ��
            clock->updateClockPosition(); // ����ʱ��λ��
        }
        }, 0.02f, "update_key");

    return true;
}

void ParentScene::mouthEvent() {
    // �����¼�������
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(ParentScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(ParentScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

bool ParentScene::canMoveToPosition(const cocos2d::Vec2& position) {
    return true;  // ����Ƿ�����ƶ���Ŀ��λ��
}

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

    // �������� NPC ��״̬���˴����� John��
    for (auto& child : this->getChildren()) {
        if (auto npc = dynamic_cast<NPC*>(child)) {
            npc->update(deltaTime);  // ���� NPC ��״̬
        }
    }
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
