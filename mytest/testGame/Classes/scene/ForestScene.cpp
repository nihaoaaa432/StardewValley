#include "ForestScene.h"
#include "TownScene.h"
// ������ͷ�߶ȵĺ���
void ForestScene::setCameraHeight(float height) {
    auto camera = cocos2d::Director::getInstance()->getRunningScene()->getDefaultCamera();
    if (camera) {
        // ��ȡ��ǰ�������λ��
        cocos2d::Vec3 cameraPos = camera->getPosition3D();

        // �����µĸ߶�
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

    // ���ص�ͼ
    map = cocos2d::TMXTiledMap::create("farm/farm.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));  // ��ê������Ϊ����
    map->setPosition(cocos2d::Vec2(0, 0));  // ���õ�ͼ��λ��    // ���õ�ͼê�㣬ȷ����ͼ�����½ǿ�ʼ��Ⱦ
    this->addChild(map);
    setCameraHeight(100.0f);

    // ����������
    inventoryLayer = InventoryLayer::createLayer();
    inventoryLayer->setVisible(false);  // Ĭ�����ر�������
    this->addChild(inventoryLayer);  // ������������ӵ�������

    // ������ͣ��
    stoppingLayer = StoppingLayer::createLayer();
    stoppingLayer->setVisible(false);  // Ĭ��������ͣ����
    this->addChild(stoppingLayer);  // ����ͣ������ӵ�������


    // ���þ�ͷ��ʼ�߶�
    setCameraHeight(100.0f);  // ������Ҫ�������ֵ

    // ������ɫ����
    player = cocos2d::Sprite::create("sand.png");
    player->setPosition(cocos2d::Vec2(0, 0));  // ��ʼλ��
    this->addChild(player);

    // �����¼�������
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(ForestScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(ForestScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // ÿ֡����
    this->schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    return true;
}

void ForestScene::update(float deltaTime) {
    if (moveDirection != cocos2d::Vec2::ZERO) {
        cocos2d::Vec2 newPosition = player->getPosition() + moveDirection * speed * deltaTime;
        if (canMoveToPosition(newPosition)) {
            player->setPosition(newPosition);  // ֻ�п����ƶ�ʱ�Ÿ���λ��
        }
    }
    checkMapSwitch(player->getPosition());

    // ���¾�ͷλ�ã�ȷ����ͷ�����ɫ
    updateCameraPosition();
}

void ForestScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
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

void ForestScene::onBKeyPressed() {
    // ���� "B" �������µ��߼�
    inventoryLayer->setVisible(!inventoryLayer->isVisible());

}

void ForestScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        moveDirection = cocos2d::Vec2::ZERO;  // ֹͣ�ƶ�
    }
}

bool ForestScene::canMoveToPosition(const cocos2d::Vec2& position) {
    // ��ȡ��Ϊ "walk" �Ķ����
    auto objectLayer = map->getObjectGroup("walk");  // ���������
    if (!objectLayer) {
        return true;  // ���û����Ϊ "walk" �Ķ���㣬Ĭ�������ƶ�
    }

    // ��ȡ���ж���
    auto objects = objectLayer->getObjects();

    for (const auto& obj : objects) {
        auto objMap = obj.asValueMap();

        // ��ȡ "walkable" ���ԣ���������ֵ�Ƿ�Ϊ false
        bool walkable = objMap["walkable"].asBool();
        if (!walkable) {
            // ������󲻿����ߣ�������Ƿ񸲸�Ŀ��λ��
            // ���½���������ڵ�ͼ���ĵ�����
            // ��֪Ϊ��Ҫ��RATIO
            float x = objMap["x"].asFloat() - SIZE_FARM_X / 2 * 16 * RATIO;
            float y = objMap["y"].asFloat() - SIZE_FARM_Y / 2 * 16 * RATIO;
            float width = objMap["width"].asFloat();
            float height = objMap["height"].asFloat();

            // ��������ı߽��
            cocos2d::Rect objRect(x, y, width, height);

            // ���Ŀ��λ���ڲ������ߵ������ڣ��򷵻� false
            if (!walkable && objRect.containsPoint(position)) {
                return false;
            }
        }
    }

    // ��������κβ������������ڣ��������ƶ�
    return true;
}
// �������Ƿ񵽴ﴥ����ͼ�л�������
void ForestScene::checkMapSwitch(const cocos2d::Vec2& position) {

    if (position.x > FROM_FARM_TO_TOWN) {
        // ��ҵ����˴��������л����µĵ�ͼ
        cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.3, TownScene::createScene(), cocos2d::Color3B::WHITE));
    }
}


// ��ͷ�����ɫ�ĺ���
void ForestScene::updateCameraPosition() {
    // ��ȡ�����
    auto director = cocos2d::Director::getInstance();
    auto camera = director->getRunningScene()->getDefaultCamera();
    if (camera) {
        // �����������λ�ã�ȷ����ɫʼ��λ����Ļ����
        camera->setPosition(player->getPosition());
    }
}