#include "MapScene.h"
#include "TownScene.h"
#include "ForestScene.h"
#include "character/Player.h"
#include "character/Npc/John.h"
#include "ui/clock.h"
#include "character/Npc/DialogSystem.h"
#include "character/Crops.h"

USING_NS_CC;

MapScene* MapScene::_instance = nullptr;


// 获取单例实例
MapScene* MapScene::getInstance() {
    if (!_instance) {
        MapScene* pRet = new(std::nothrow) MapScene();
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
// 销毁单例实例
void MapScene::destroyInstance() {
    if (_instance) {
        _instance->release();
        _instance = nullptr;
    }
}
Scene* MapScene::createScene() {
    return MapScene::create();
}

bool MapScene::init() {
    if (!ParentScene::init()) {
        return false;
    }

    // 加载地图
    map = TMXTiledMap::create("farm/farm.tmx");
    map->setAnchorPoint(Vec2(0.5f, 0.5f));  // 将锚点设置为中心
    map->setPosition(Vec2(0, 0));  // 设置地图的位置
    this->addChild(map);

    // 创建背包层
    inventoryLayer = InventoryLayer::createLayer();
    inventoryLayer->setVisible(false);  // 默认隐藏背包界面
    this->addChild(inventoryLayer);  // 将背包界面添加到场景中

    // 创建暂停层
    stoppingLayer = StoppingLayer::createLayer();
    stoppingLayer->setVisible(false);  // 默认隐藏暂停界面
    this->addChild(stoppingLayer);  // 将暂停界面添加到场景中

    // 设置镜头初始高度
    setCameraHeight(50.0f);  // 根据需要调整这个值

    mouthEvent();

    auto wm = Crops::create(Watermelon);
    this->addChild(wm);
    wm->setPosition(Vec2(-100, -100));

    // 在场景中创建一个 John NPC
    auto john = John::create("npc/john.png");  // "john.png" 是你给 John NPC 的图片文件
    john->setPosition(Vec2(100, 100));  // 设置 John 的初始位置
    john->setSpeed(50.0f);  // 设置 John 的移动速度
    john->setPath({ Vec2(100, 100), Vec2(200, 200), Vec2(300, 300) });  // 设置 John 的移动路径
    this->addChild(john);  // 将 John 添加到场景中
    // 创建并添加UI层
    UILayer* uiLayer = UILayer::createLayer();
    this->addChild(uiLayer, 100000);  // 确保它在最上层
    // 每帧更新
    this->schedule([=](float deltaTime) {
        update(deltaTime);

        }, 0.02f, "update_key");

    DialogSystem::getInstance()->setPosition(-150, -150); // 可根据需要设置位置
    this->addChild(DialogSystem::getInstance());
    return true;
}


bool MapScene::canMoveToPosition(const  Vec2& position) {
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
            Rect objRect(x, y, width, height);

            // 如果目标位置在不可行走的区域内，则返回 false
            if (!walkable && objRect.containsPoint(position)) {
                return false;
            }
        }
    }

    // 如果不在任何不可行走区域内，则允许移动
    return true;
}

void MapScene::goToNextScene(const std::string& nextScene) {
    // 1. 获取当前场景
    auto currentScene = Director::getInstance()->getRunningScene();
    auto player = Player::getInstance();

    // 2. 从当前场景移除角色
    if (currentScene && player->getParent() == currentScene) {
        player->removeFromParent();
    }
    Scene* newScene;
    // 3. 创建新场景
    if (nextScene == "Town") {
        newScene = TownScene::getInstance();
        // 4. 初始化角色在新场景中的状态
        player->setPosition(Vec2(FROM_TOWN_TO_FARM_X + 16, FROM_TOWN_TO_FARM_Y_UP - 16)); // 设置角色位置
        player->setScale(1.0f); // 设置角色缩放比例
    }
    else if (nextScene == "Forest") {
        newScene = ForestScene::getInstance();
        // 4. 初始化角色在新场景中的状态
        player->setPosition(Vec2(FROM_FOREST_TO_FARM_X, FROM_FOREST_TO_FARM_Y)); // 设置角色位置
        player->setScale(1.0f); // 设置角色缩放比例
    }
    // 5. 将角色添加到新场景
    newScene->addChild(player);

    // 6. 切换到新场景
    Director::getInstance()->replaceScene(newScene);
}

void MapScene::checkMapSwitch(const  Vec2& position) {
    if (position.x > FROM_FARM_TO_TOWN_X) {
        goToNextScene("Town");
    }
    else if (position.y < FROM_FARM_TO_FOREST_Y) {
        goToNextScene("Forest");
    }
}

