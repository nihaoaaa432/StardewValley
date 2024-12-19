#include "TownScene.h"
#include "MapScene.h"
#include "character/Player.h"
#include "Lake.h"
#include "ui/Clock.h"

TownScene* TownScene::_instance = nullptr;

// ��ȡ����ʵ��
TownScene* TownScene::getInstance() {
    if (!_instance) {
        TownScene* pRet = new(std::nothrow) TownScene();
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
void TownScene:: destroyInstance() {
    if (_instance) {
        _instance->release();
        _instance = nullptr;
    }
}

cocos2d::Scene* TownScene::createScene() {
    return TownScene::create();
}

bool TownScene::init() {
    if (!Scene::init()) {
        return false;
    }

    // ���ص�ͼ
    map = cocos2d::TMXTiledMap::create("town/town.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0, 0));  // ��ê������Ϊ���½�
    map->setPosition(cocos2d::Vec2(0, 0));  // ���õ�ͼ��λ��    // ���õ�ͼê�㣬ȷ����ͼ�����½ǿ�ʼ��Ⱦ
    this->addChild(map);

    //// ������ɫ����
    //Player::getInstance()->setPosition(cocos2d::Vec2(Player::getInstance()->getPosition().x, Player::getInstance()->getPosition().y));  // ��ʼλ��
    //this->addChild(Player::getInstance());
    // ����������
    inventoryLayer = InventoryLayer::createLayer();
    inventoryLayer->setVisible(false);  // Ĭ�����ر�������
    this->addChild(inventoryLayer);  // ������������ӵ�������

    // ������ͣ��
    stoppingLayer = StoppingLayer::createLayer();
    stoppingLayer->setVisible(false);  // Ĭ��������ͣ����
    this->addChild(stoppingLayer);  // ����ͣ������ӵ�������

    mouthEvent();

    // ÿ֡����
    this->schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");

    return true;
}

bool TownScene::canMoveToPosition(const cocos2d::Vec2& position) {
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
            float x = objMap["x"].asFloat() ;
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


void TownScene::goToNextScene(const std::string& nextScene) {
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
    if (nextScene == "Farm") {
        newScene = MapScene::getInstance();
        player->setPosition(cocos2d::Vec2(FROM_FARM_TO_TOWN_X - 16, FROM_FARM_TO_TOWN_Y)); // ���ý�ɫλ��
        player->setScale(1.0f); // ���ý�ɫ���ű���
        Clock::getInstance()->setPosition(cocos2d::Vec2(300, 300));
    }
    else if (nextScene == "Beach") {
        newScene = SandBeach::getInstance();
        player->setPosition(cocos2d::Vec2(FROM_BEACH_TO_TOWN_X, FROM_BEACH_TO_TOWN_Y)); // ���ý�ɫλ��
        player->setScale(1.0f); // ���ý�ɫ���ű���
    }
    else if (nextScene == "Forest") {
        newScene = ForestScene::getInstance();
        player->setPosition(cocos2d::Vec2(FROM_FOREST_TO_TOWN_X, FROM_FOREST_TO_TOWN_Y)); // ���ý�ɫλ��
        player->setScale(1.0f); // ���ý�ɫ���ű���
    }
    else if (nextScene == "Lake") {
        newScene = LakeScene::getInstance();
        player->setPosition(cocos2d::Vec2(FROM_LAKE_TO_TOWN_X, FROM_LAKE_TO_TOWN_Y)); // ���ý�ɫλ��
        player->setScale(1.0f); // ���ý�ɫ���ű���
    }

    // 5. ����ɫ��ӵ��³���
    newScene->addChild(player);

    // 6. �л����³���
    cocos2d::Director::getInstance()->replaceScene(newScene);
}


// �������Ƿ񵽴ﴥ����ͼ�л�������
void TownScene::checkMapSwitch(const cocos2d::Vec2& position) {
    if (position.x < FROM_TOWN_TO_FARM_X && position.y>FROM_TOWN_TO_FARM_Y_DOWN && position.y < FROM_TOWN_TO_FARM_Y_UP) {
        goToNextScene("Farm");
    }
    else if (position.y < FROM_TOWN_TO_BEACH_Y) {
        goToNextScene("Beach");
    }
    else if (position.x< FROM_TOWN_TO_FOREST_X && position.y>FROM_TOWN_TO_FOREST_Y_DOWN && position.y < FROM_TOWN_TO_FOREST_Y_UP) {
        goToNextScene("Forest");
    }
    else if (position.y > FROM_TOWN_TO_LAKE_Y) {
        goToNextScene("Lake");
    }
}