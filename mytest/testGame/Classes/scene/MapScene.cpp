#include "MapScene.h"
#include "TownScene.h"
#include "ForestScene.h"
#include "character/Player.h"
#include "character/Npc/John.h"
#include "ui/clock.h"
#include "character/Npc/DialogSystem.h"


USING_NS_CC;

MapScene* MapScene::_instance = nullptr;
using namespace cocos2d;

void MapScene::JohnMove() {
    // 在场景中创建一个 John NPC
    auto john = John::create("npc/john.png");  // "john.png" 是你给 John NPC 的图片文件
    john->setPosition(Vec2(30 * 16 * RATIO, 30 * 16 * RATIO));  // 设置 John 的初始位置
    john->setSpeed(50.0f);  // 设置 John 的移动速度
    john->setPath({ Vec2(100, 100), Vec2(200, 200), Vec2(300, 300) });  // 设置 John 的移动路径
    this->addChild(john);  // 将 John 添加到场景中

    // 每10秒重新开始按路径走一遍
    this->schedule([=](float dt) {
        john->resetDailyMovement();  // 重置每日的移动
    }, 10, "reset_daily_movement");
}
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
    srand(time(NULL));

    // 加载地图
    map = cocos2d::TMXTiledMap::create("farm/farm.tmx");
    map->setAnchorPoint(cocos2d::Vec2(0, 0));  // 将锚点设置为中心
    map->setPosition(cocos2d::Vec2(0, 0));  // 设置地图的位置
    this->addChild(map);

    // 设置镜头初始高度
    setCameraHeight(50.0f);  // 根据需要调整这个值

    // 键盘事件监听器
    auto keyboardListener = cocos2d::EventListenerKeyboard::create();
    keyboardListener->onKeyPressed = CC_CALLBACK_2(MapScene::onKeyPressed, this);
    keyboardListener->onKeyReleased = CC_CALLBACK_2(MapScene::onKeyReleased, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    
    // 获取 ToolLayer 单例实例并添加到场景中
    auto toolLayer = ToolLayer::getInstance();
    if (!toolLayer) {
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
    }
    


    // 创建背包层
    auto inventoryLayer = InventoryLayer::getInstance();
    if (!inventoryLayer) {
        inventoryLayer->setVisible(false);  // 默认隐藏背包界面
        this->addChild(inventoryLayer, 3);  // 将背包界面添加到场景中
    }


    // 创建暂停层
    auto stoppingLayer = StoppingLayer::getInstance();
    if (!stoppingLayer) {
    stoppingLayer->setVisible(false);  // 默认隐藏暂停界面
    this->addChild(stoppingLayer, 1000);  // 将暂停界面添加到场景中
    }
    


    //键盘事件
    mouthEvent();
    JohnMove();

    auto wm = Crops::create(Watermelon);
    this->addChild(wm);
    wm->setPosition(Vec2(-100, -100));

    // 在场景中创建一个 John NPC
    auto john = John::create("npc/john.png");  // "john.png" 是你给 John NPC 的图片文件
    john->setPosition(Vec2(100, 100));  // 设置 John 的初始位置
    john->setSpeed(50.0f);  // 设置 John 的移动速度
    john->setPath({ Vec2(100, 100), Vec2(200, 200), Vec2(300, 300) });  // 设置 John 的移动路径
    this->addChild(john);  // 将 John 添加到场景中
    //// 创建并添加UI层
    //UILayer* uiLayer = UILayer::createLayer();
    //this->addChild(uiLayer, 100000);  // 确保它在最上层


    auto corn = Crops::create(Corn);
    this->addChild(corn);
    corn->setPosition(Vec2(800, 600));
    interactbales.push_back(corn);

    auto tomato = Crops::create(Tomato);
    this->addChild(tomato);
    tomato->setPosition(Vec2(800, 500));
    interactbales.push_back(tomato);

    auto potato = Crops::create(Potato);
    this->addChild(potato);
    potato->setPosition(Vec2(800, 550));
    interactbales.push_back(potato);

    auto watermelon = Crops::create(Watermelon);
    this->addChild(watermelon);
    watermelon->setPosition(Vec2(800, 450));
    interactbales.push_back(watermelon);


    // 每帧更新
    this->schedule([=](float deltaTime) {
        update(deltaTime);
      }, 0.02f, "update_key");
    this->addChild(DialogSystem::getInstance());
    return true;
}

//鼠标总体调用函数
void MapScene::mouthEvent()
{
    //创建一个鼠标监听器来检测点击
    auto mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MapScene::onMouseDown, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void MapScene::onMouseDown(Event* event)
{
    auto mouseEvent = static_cast<EventMouse*>(event);
    Vec2 clickPosition = mouseEvent->getLocation();
    clickPosition = this->convertToNodeSpace(clickPosition);
    // 获取当前节点的位置
    Vec2 nodePosition =  this->getPosition();

    // 手动计算本地坐标
    Vec2 localPosition = clickPosition - nodePosition;

    CropsType cropName = static_cast<CropsType>(rand() % 9 + 1);

    auto crop= Crops::create(cropName);
    this->addChild(crop);
    crop->setPosition(-localPosition);
    interactbales.push_back(crop);
}

void MapScene::update(float deltaTime) {
    auto player = Player::getInstance();
    if (moveDirection != cocos2d::Vec2::ZERO) {
        cocos2d::Vec2 newPosition = player->getPosition() + moveDirection * Player::getInstance()->getSpeed() * deltaTime;
        if (canMoveToPosition(newPosition)) {
            player->setPosition(newPosition);  // 只有可以移动时才更新位置
        }
    }
    checkMapSwitch(player->getPosition());

    // 更新镜头位置，确保镜头跟随角色
    updateCameraPosition();

    //背包处于打开状态时以任务为中心
    auto inventoryLayer = InventoryLayer::getInstance();
    if (inventoryLayer->isVisible()) {
        inventoryLayer->updatePosition(player->getPosition());
    }
    auto stoppingLayer = StoppingLayer::getInstance();
    if (stoppingLayer->isVisible()) {
        stoppingLayer->updatePosition(player->getPosition());
    }
    auto toolLayer = ToolLayer::getInstance();
    toolLayer->updatePosition(player->getPosition());

    //更新场景上的可交互物品
    for (auto interactable : interactbales)
    {
        interactable->update(deltaTime);
    }
}


void MapScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    auto inventoryLayer = InventoryLayer::getInstance();
    auto stoppingLayer = StoppingLayer::getInstance();
    auto toolLayer = ToolLayer::getInstance();
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
    if (keyCode >= cocos2d::EventKeyboard::KeyCode::KEY_1 && keyCode <= cocos2d::EventKeyboard::KeyCode::KEY_9) {
        int index = static_cast<int>(keyCode) - 77; // 计算工具索引
        if (index < toolLayer->getSize()) {
            toolLayer->switchTool(index);
        }
    }
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_B) {
        onBKeyPressed();
    }
    else if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_ESCAPE) {
        stoppingLayer->onEscPress();
    }
    else if (!stoppingLayer->isVisible() && keyCode == cocos2d::EventKeyboard::KeyCode::KEY_F)
    {
        auto player = Player::getInstance();
        auto pos = player->getPosition();
        
        if (!player->interactWithClickPosition(pos, interactbales))
        {
            CropsType cropName = static_cast<CropsType>(rand() % 9 + 1);

            auto crop = Crops::create(cropName);
            this->addChild(crop);
            crop->setPosition(pos);
            interactbales.push_back(crop);
        }
    }
    

}

void MapScene::onBKeyPressed() {
    auto stoppingLayer = StoppingLayer::getInstance();
    auto inventoryLayer = InventoryLayer::getInstance();
    // 处理 "B" 键被按下的逻辑
    if(!stoppingLayer->isVisible()) inventoryLayer->setVisible(!inventoryLayer->isVisible());
}


void MapScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == cocos2d::EventKeyboard::KeyCode::KEY_W ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_S ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_A ||
        keyCode == cocos2d::EventKeyboard::KeyCode::KEY_D) {
        moveDirection = cocos2d::Vec2::ZERO;  // 停止移动
    }
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
            float x = objMap["x"].asFloat();
            float y = objMap["y"].asFloat();
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

    DialogSystem::getInstance()->destroyInstance();
    // 2. 获取并移除时钟节点的父节点
    auto clock = Clock::getInstance();
    if (clock) {
        // 确保时钟有父节点且父节点是当前场景
        if (clock->getParent() == currentScene) {
            clock->removeFromParent();
            // 检查时钟是否已经成功移除
            if (clock->getParent() == nullptr) {
                CCLOG("123");
            }
        }
    }

    // 3. 从当前场景移除角色
    if (currentScene && player->getParent() == currentScene) {
        player->removeFromParent();
        StoppingLayer::getInstance()->removeFromParent();
        InventoryLayer::getInstance()->removeFromParent();
        ToolLayer::getInstance()->removeFromParent();
        
    }


    Scene* newScene;

    // 4. 创建新场景
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

    // 6. 将角色添加到新场景
    newScene->addChild(player);

    // 7. 切换到新场景
    cocos2d::Director::getInstance()->replaceScene(newScene);
}
//void MapScene::checkMapSwitch(const cocos2d::Vec2& position) {
//    if (position.x > FROM_FARM_TO_TOWN_X) {
//        auto townScene = TownScene::getInstance();
//        townScene->setPlayerPosition(cocos2d::Vec2(FROM_TOWN_TO_FARM_X + 16, FROM_TOWN_TO_FARM_Y));
//        moveDirection = cocos2d::Vec2::ZERO; // 停止角色移动
//        cocos2d::Director::getInstance()->pushScene(cocos2d::TransitionFade::create(0.3, TownScene::getInstance(), cocos2d::Color3B::WHITE));
//    }
//}

void MapScene::checkMapSwitch(const cocos2d::Vec2& position) {
    if (position.x > FROM_FARM_TO_TOWN_X) {
        goToNextScene("Town");
    }
    else if (position.y < FROM_FARM_TO_FOREST_Y) {
        goToNextScene("Forest");
    }
}

