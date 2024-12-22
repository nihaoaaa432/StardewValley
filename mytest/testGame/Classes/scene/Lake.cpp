#include "Lake.h"
#include "character/Player.h"
LakeScene* LakeScene::_instance = nullptr;

// ��ȡ����ʵ��
LakeScene* LakeScene::getInstance() {
    if (!_instance) {
        LakeScene* pRet = new(std::nothrow) LakeScene();
        if (pRet && pRet->init())
        {
            return pRet;
        }
        else
        {
            delete pRet;
            pRet = nullptr;
            return nullptr;
        }
    }
    return _instance;
}
// ���ٵ���ʵ��
void LakeScene::destroyInstance() {
    if (_instance) {
        _instance->release();
        _instance = nullptr;
    }
}

cocos2d::Scene* LakeScene::createScene() {
    return LakeScene::create();
}

bool LakeScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // ���ص�ͼ
    map = cocos2d::TMXTiledMap::create("lake/lake.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0, 0));  // ��ê������Ϊ���½�
    map->setPosition(cocos2d::Vec2(0, 0));  // ���õ�ͼ��λ��    // ���õ�ͼê�㣬ȷ����ͼ�����½ǿ�ʼ��Ⱦ
    this->addChild(map);

    // ����������
    auto inventoryLayer = InventoryLayer::getInstance();
    inventoryLayer->setVisible(false);  // Ĭ�����ر�������
    this->addChild(inventoryLayer);  // ������������ӵ�������

    // ������ͣ��
    auto stoppingLayer = StoppingLayer::getInstance();
    stoppingLayer->setVisible(false);  // Ĭ��������ͣ����
    this->addChild(stoppingLayer);  // ����ͣ������ӵ�������

    mouthEvent();
    // ÿ֡����
    this->schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    return true;
}

bool LakeScene::canMoveToPosition(const cocos2d::Vec2& position) {
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
            // ��֪Ϊ��Ҫ��1.25
            float x = objMap["x"].asFloat();
            float y = objMap["y"].asFloat();
            float width = objMap["width"].asFloat();
            float height = objMap["height"].asFloat();

            // ��������ı߽��
            cocos2d::Rect objRect(x, y, width, height);

            // ���Ŀ��λ���ڲ������ߵ������ڣ��򷵻� false
            if (objRect.containsPoint(position)) {
                return false;
            }
        }
    }

    // ��������κβ������������ڣ��������ƶ�
    return true;
}


void LakeScene::goToNextScene(const std::string& nextScene) {
    // 1. ��ȡ��ǰ����
    auto currentScene = cocos2d::Director::getInstance()->getRunningScene();
    auto player = Player::getInstance();

    // 2. �ӵ�ǰ�����Ƴ���ɫ
    if (currentScene && player->getParent() == currentScene) {
        player->removeFromParent();
    }

    // 3. �����³���
    Scene* newScene;

    // 4. ��ʼ����ɫ���³����е�״̬
    if (nextScene == "Town") {
        newScene = TownScene::getInstance();
        player->setPosition(cocos2d::Vec2(FROM_TOWN_TO_LAKE_X, FROM_TOWN_TO_LAKE_Y)); // ���ý�ɫλ��
        player->setScale(1.0f); // ���ý�ɫ���ű���
    }
    // 5. ����ɫ��ӵ��³���
    newScene->addChild(player);

    // 6. �л����³���
    cocos2d::Director::getInstance()->replaceScene(newScene);
}


// �������Ƿ񵽴ﴥ����ͼ�л�������
void LakeScene::checkMapSwitch(const cocos2d::Vec2& position) {
    if (position.y<FROM_LAKE_TO_TOWN_Y) {
        goToNextScene("Town");
    }
}