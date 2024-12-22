#include "Player.h"
#include "layer/InventoryLayer.h"

//#define ENABLE_ANIMATIONS

USING_NS_CC;

Player* Player::_instance = nullptr;

float Player::getSpeed() {
    return speed;
}

Player* Player::getInstance()
{
    if (_instance == nullptr)
    {
        _instance = Player::create();
    }
    return _instance;
}

void Player::destroyInstance()
{
    if (_instance != nullptr)
    {
        _instance->release();
        _instance = nullptr;
    }
}

Player* Player::create() {
    Player* player = new(std::nothrow) Player();
    if (player)
    {
        player->name = "Abigail";
        if (player->init()) {
            // player->autorelease();
            return player;
        }
    }

    else {
        delete player;
        player = nullptr;
        return nullptr;
    }
}

bool Player::init() {
    if (!Node::init()) {
        return false;
    }

    //注册键盘事件
    //registerKeyboardEvent();

    //// 每 0.1 秒调用一次 update 方法
    //schedule([this](float delta) {
    //    this->update(delta);
    //   }, 0.1f, "player_update_key");
    // 每帧更新
    /*this->schedule([=](float deltaTime) {
        update(deltaTime);
        }, "update_key");*/
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Abigail.plist");

    isMoving = false;
    isInventoryOpen = false;
    moveDirection = Vec2::ZERO;
    speed = INIT_PLAYER_SPEED;

    //初始化纹理
    sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("init_" + name + ".png"));
    //初始位置均为0，0
    sprite->setPosition(0, 0);
    this->addChild(sprite);


#ifdef ENABLE_ANIMATIONS
    loadAnimations();
#endif
    //move(Vec2(0, 1));
    // playWalkAnimation("up");

    return true;
}

void Player::loadAnimations()
{
    //加载站立动画
    Animations["stand_up"] = createIdleAnimation("up");
    Animations["stand_down"] = createIdleAnimation("down");
    Animations["stand_left"] = createIdleAnimation("left");
    Animations["stand_right"] = createIdleAnimation("right");

    // 加载行走动画
    Animations["walk_up"] = createWalkAnimation("up");
    Animations["walk_down"] = createWalkAnimation("down");
    Animations["walk_left"] = createWalkAnimation("left");
    Animations["walk_right"] = createWalkAnimation("right");
}

//创建行走动画
Animate* Player::createWalkAnimation(const std::string& direction) {
    Vector<SpriteFrame*> animFrames;
    for (int i = 1; i <= 2; ++i) {  // 假设每个方向有 2 个行走动画帧
        std::string frameName = "Abigail_walk_" + direction + "_" + std::to_string(i) + ".png";
        animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }

    // 创建动画
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);  // 每帧 0.1 秒
    return Animate::create(animation);
}

//创建站立动画
Animate* Player::createIdleAnimation(const std::string& direction)
{
    Vector<SpriteFrame*> animFrames;
    std::string frameName = "Abigail_stand_" + direction + ".png";
    animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    return Animate::create(animation);
}

//void Player::onEnter()
//{
//      onEnter();
//    //确保监听器在场景进入时注册
//    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
//}
//
//void Player::onExit()
//{
//    //退出时注销键盘监听器
//    _eventDispatcher->removeEventListener(keyboardListener);
//      onExit();
//}
//
////注册键盘事件
//void Player::registerKeyboardEvent() {
//    // 创建键盘事件监听器
//    keyboardListener = EventListenerKeyboard::create();
//
//    // 定义按键按下的回调
//    keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
//        if (isInventoryOpen) {
//            if (keyCode == EventKeyboard::KeyCode::KEY_B) {
//                closeInventory();  // 关闭背包
//            }
//            return;  // 背包打开时，其他按键不响应
//        }
//
//        if (isMoving) {
//            return;
//        }
//
//        // 按下控制移动的按键时
//        switch (keyCode) {
//        case EventKeyboard::KeyCode::KEY_A:
//            moveInDirection(cocos2d::Vec2(-1, 0)); // 向左移动
//            break;
//        case EventKeyboard::KeyCode::KEY_D:
//            move(cocos2d::Vec2(1, 0)); // 向右移动
//            break;
//        case EventKeyboard::KeyCode::KEY_W:
//            moveInDirection(cocos2d::Vec2(0, 1)); // 向上移动
//            break;
//        case EventKeyboard::KeyCode::KEY_S:
//            moveInDirection(cocos2d::Vec2(0, -1)); // 向下移动
//            break;
//        case EventKeyboard::KeyCode::KEY_B:
//            openInventory();  // 打开背包
//            break;
//        default:
//            break;
//        }
//        };
//
//    // 定义按键松开的回调
//    keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
//        if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D ||
//            keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S) {
//            stopMoving();
//        }
//        };
//}

// 统一的移动方法
void Player::moveInDirection(const cocos2d::Vec2& direction) {
    if (isTalking) {
        return;  // 如果正在对话，停止移动
    }

    moveDirection = direction;
    isMoving = true;

    if (direction.y > 0) {
        lastDirection = "up";
    }
    else if (direction.y < 0) {
        lastDirection = "down";
    }
    else if (direction.x > 0) {
        lastDirection = "right";
    }
    else if (direction.x < 0) {
        lastDirection = "left";
    }

   // playWalkAnimation(lastDirection);

    auto targetPosition = this->getPosition() + moveDirection * speed * 0.02f;
    this->setPosition(targetPosition);
}
//角色正在对话
void Player::setIsTalking(bool talking) {
    isTalking = talking;
}
// 停止移动（通过调用动作的停止来停止移动）
void Player::stopMoving() {
    if (isTalking) {
        return;  // 如果正在对话，停止移动
    }

    isMoving = false;
    moveDirection = Vec2::ZERO;

    //playIdleAnimation(lastDirection);
}
// 播放行走动画
void Player::playWalkAnimation(const std::string& direction) {
    stopAnimation();

    auto animation = "walk_" + direction;

    // 播放缓存的行走动画
    if (Animations.find(animation) != Animations.end()) {
        currentAnimation = Animations[animation];
        // sprite->runAction(RepeatForever::create(  currentAnimation));

        //创建RepeatForever动作
        currentAction = RepeatForever::create(currentAnimation);

        if (currentAnimation != nullptr && sprite->getNumberOfRunningActions() == 0) {
            sprite->runAction(currentAction);
        }
    }
    //}
}

// 播放站立帧
void Player::playIdleAnimation(const std::string& direction) {

    stopAnimation();


    // 播放站立帧
    auto animation = "stand_" + direction;

    // 播放缓存的站立动画
    if (Animations.find(animation) != Animations.end()) {
        currentAnimation = Animations[animation];

        // 创建 RepeatForever 动作
        currentAction = RepeatForever::create(currentAnimation);

        sprite->runAction(currentAction);
    }
}

void Player::openInventory() {
    if (!isInventoryOpen) {
        auto inventoryLayer = InventoryLayer::createLayer();
        inventoryLayer->setName("inventoryLayer");
        this->getParent()->addChild(inventoryLayer);

        isInventoryOpen = true;
        // 禁用键盘事件，除非是 B 键
        //_eventDispatcher->removeEventListener(keyboardListener);

        //监听背包的关闭事件
    }
}
//
//void Player::update(float delta)
//{
//    if (isMoving)
//    {
//        this->moveInDirection(moveDirection);
//    }
//}

void Player::closeInventory() {
    if (isInventoryOpen) {
        auto inventoryLayer = dynamic_cast<InventoryLayer*>(this->getParent()->getChildByName("inventoryLayer"));
        if (inventoryLayer) {
            inventoryLayer->removeFromParent();
        }

        isInventoryOpen = false;
        // 恢复键盘事件监听
        //_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    }

}
// 停止动画
void Player::stopAnimation() {
    if (currentAnimation != nullptr) {
        // 停止当前的动画

        sprite->stopAction(currentAction);

        currentAnimation = nullptr;
        currentAction = nullptr;
    }

}

Vec2& Player::getMoveDirection()
{
    return moveDirection;
}