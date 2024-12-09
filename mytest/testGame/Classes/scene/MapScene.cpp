#include "MapScene.h"

cocos2d::Scene* MapScene::createScene() {
    return MapScene::create();
}

bool MapScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // ���ص�ͼ
    map = cocos2d::TMXTiledMap::create("farm.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));  // ��ê������Ϊ����
    map->setPosition(cocos2d::Vec2(0, 0));  // ���õ�ͼ��λ��    // ���õ�ͼê�㣬ȷ����ͼ�����½ǿ�ʼ��Ⱦ
    this->addChild(map);

    // ������ɫ����
    player = cocos2d::Sprite::create("sand.png");
    //int mapHeight ;
    //float cocosX = 0;
    //float cocosY = mapHeight;
    player->setPosition(cocos2d::Vec2(0, 0));  // ��ʼλ��
    this->addChild(player);

    // �����¼�������
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);

    // ÿ֡����
    this->schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    return true;
}

void MapScene::update(float deltaTime) {
    if (moveDirection != cocos2d::Vec2::ZERO) {
        cocos2d::Vec2 newPosition = player->getPosition() + moveDirection * speed * deltaTime;
        if (canMoveToPosition(newPosition)) {
            player->setPosition(newPosition);  // ֻ�п����ƶ�ʱ�Ÿ���λ��
        }
    }

    // ���¾�ͷλ�ã�ȷ����ͷ�����ɫ
    updateCameraPosition();
}

void MapScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
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
}

void MapScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        moveDirection = cocos2d::Vec2::ZERO;  // ֹͣ�ƶ�
    }
}

bool MapScene::canMoveToPosition(const cocos2d::Vec2& position) {
    // ��ȡ�����
    auto objectLayer = map->getObjectGroup("walk");  // ���������
    if (!objectLayer) {
        return true;  // û�ж������Ĭ�������ƶ�
    }

    // ��ȡ���ж���
    auto objects = objectLayer->getObjects();

    for (const auto& obj : objects) {
        auto objMap = obj.asValueMap();

        // ������� walkable ����
        bool walkable = objMap["walkable"].asBool();
        float x = objMap["x"].asFloat();
        float y = objMap["y"].asFloat();
        float width = objMap["width"].asFloat();
        float height = objMap["height"].asFloat();

        // ��������ı߽��
        cocos2d::Rect objRect(x, y, width, height);

        // ���Ŀ��λ���ڲ������ߵ������ڣ��򷵻� false
        if (!walkable && objRect.containsPoint(position)) {
            return false;
        }
    }

    // ��������κβ������������ڣ��������ƶ�
    return true;
}

// ��ͷ�����ɫ�ĺ���
void MapScene::updateCameraPosition() {
    // ��ȡ�����
    auto director = cocos2d::Director::getInstance();
    auto camera = director->getRunningScene()->getDefaultCamera();
    if (camera) {
        // �����������λ�ã�ȷ����ɫʼ��λ����Ļ����
        camera->setPosition(player->getPosition());
    }
}
