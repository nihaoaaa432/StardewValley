#include "ForestScene.h"
#include "TownScene.h"
#include "character/Player.h"

ForestScene* ForestScene::_instance = nullptr;
ForestScene* ForestScene:: getInstance() {
    if (!_instance) {
        ForestScene* pRet = new(std::nothrow) ForestScene();
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
void ForestScene::destroyInstance() {
    if (_instance) {
        _instance->release();
        _instance = nullptr;
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
    map = cocos2d::TMXTiledMap::create("forest/forest.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0, 0));  // ��ê������Ϊ����
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
void ForestScene::goToNextScene(const std::string& nextScene) {
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
        player->setPosition(cocos2d::Vec2(FROM_FARM_TO_FOREST_X, FROM_FARM_TO_FOREST_Y)); // ���ý�ɫλ��
        player->setScale(1.0f); // ���ý�ɫ���ű���
    }
    else if (nextScene == "Town") {
        newScene = TownScene::getInstance();
        player->setPosition(cocos2d::Vec2(FROM_TOWN_TO_FOREST_X, FROM_TOWN_TO_FOREST_Y_UP-16)); // ���ý�ɫλ��
        player->setScale(1.0f); // ���ý�ɫ���ű���
    }

    // 5. ����ɫ��ӵ��³���
    newScene->addChild(player);

    // 6. �л����³���
    cocos2d::Director::getInstance()->replaceScene(newScene);
}

// �������Ƿ񵽴ﴥ����ͼ�л�������
void ForestScene::checkMapSwitch(const cocos2d::Vec2& position) {

    if (position.y > FROM_FOREST_TO_FARM_Y) {
        // ��ҵ����˴��������л����µĵ�ͼ
        goToNextScene("Farm");
    }
    else if (position.x > FROM_FOREST_TO_TOWN_X) {
        goToNextScene("Town");
    }
}


