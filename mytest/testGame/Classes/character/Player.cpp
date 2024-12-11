#include "Player.h"
#include "InventoryLayer.h"

USING_NS_CC;

Player* Player::createWithAttributes(const std::string& imagePath,const std::string& name) {
    Player* player = new(std::nothrow) Player();
    if (player && player->initWithAttributes(imagePath,name)) {
        player->autorelease();
        return player;
    }
    delete player;
    return nullptr;
}

bool Player::initWithAttributes(const std::string& imagePath,const std::string&name) {
    if (!Changers::initWithAttributes(imagePath,name)){
        return false;
    }

    //注册键盘事件
    registerKeyboardEvent();

    // 每 0.1 秒调用一次 update 方法
    //schedule([this](float delta) {
      //  this->update(delta);
      //  }, 0.1f, "player_update_key");

    isMoving = false;
    isInventoryOpen = false;
    moveDirection = Vec2::ZERO;
    speed = INIT_PLAYER_SPEED;

    loadAnimations();

   move(Vec2(0, 1));
   move(Vec2(0, 1));
   move(Vec2(0, 1));
   stopMoving();
   move(Vec2(1, 0));
   move(Vec2(-1, 0));
   move(Vec2(0, -1));
   //playWalkAnimation("up");

    //设置初始站立动画
    //playIdleAnimation("down");

    return true;
}

void Player::loadAnimations()
{
    //加载站立动画
    Changers::walkAnimations["stand_up"] = createIdleAnimation("up");
    Changers::walkAnimations["stand_down"] = createIdleAnimation("down");
    Changers::walkAnimations["stand_left"] = createIdleAnimation("left");
    Changers::walkAnimations["stand_right"] = createIdleAnimation("right");

    // 加载行走动画
    Changers::walkAnimations["walk_up"] = createWalkAnimation("up");
    Changers::walkAnimations["walk_down"] = createWalkAnimation("down");
    Changers::walkAnimations["walk_left"] = createWalkAnimation("left");
    Changers::walkAnimations["walk_right"] = createWalkAnimation("right");
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

void Player::onEnter()
{
    Changers::onEnter();
    //确保监听器在场景进入时注册
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Player::onExit()
{
    //退出时注销键盘监听器
    _eventDispatcher->removeEventListener(keyboardListener);
    Changers::onExit();
}

//注册键盘事件
void Player::registerKeyboardEvent() {
    // 创建键盘事件监听器
    keyboardListener = EventListenerKeyboard::create();

    // 定义按键按下的回调
    keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        if (isInventoryOpen) {
            if (keyCode == EventKeyboard::KeyCode::KEY_B) {
                closeInventory();  // 关闭背包
            }
            return;  // 背包打开时，其他按键不响应
        }

        if (isMoving) {
            return;
        }

        // 按下控制移动的按键时
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
            move(cocos2d::Vec2(-1, 0)); // 向左移动
            break;
        case EventKeyboard::KeyCode::KEY_D:
            move(cocos2d::Vec2(1, 0)); // 向右移动
            break;
        case EventKeyboard::KeyCode::KEY_W:
            move(cocos2d::Vec2(0, 1)); // 向上移动
            break;
        case EventKeyboard::KeyCode::KEY_S:
            move(cocos2d::Vec2(0, -1)); // 向下移动
            break;
        case EventKeyboard::KeyCode::KEY_B:
            openInventory();  // 打开背包
            break;
        default:
            break;
        }
        };

    // 定义按键松开的回调
    keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D ||
            keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S) {
            stopMoving();
        }
        };
}

// 统一的移动方法
void Player::move(const cocos2d::Vec2& direction) {
        moveDirection = direction;
        isMoving = true;

        // 根据移动方向更新角色朝向
        if (direction.y > 0) {  // 向上
            lastDirection = "up";
        }
        else if (direction.y < 0) {  // 向下
            lastDirection = "down";
        }
        else if (direction.x > 0) {  // 向右
            lastDirection = "right";
        }
        else if (direction.x < 0) {  // 向左
            lastDirection = "left";
        }

        //播放行走动画
        playWalkAnimation(lastDirection);

        //// 计算目标位置
        //auto targetPosition = Changers::sprite->getPosition() + moveDirection * speed*0.02f; // 0.02f是每帧时间的单位

        //// 创建移动动画（使用 MoveTo）
        //auto moveAction = cocos2d::MoveTo::create(0.2f, targetPosition); // 0.2秒移动到目标位置
        //Changers::sprite->runAction(moveAction); // 执行动作
}

// 停止移动（通过调用动作的停止来停止移动）
void Player::stopMoving() {
    isMoving = false;
    moveDirection = cocos2d::Vec2::ZERO;

    //停止动画并设置站立帧
    //stopAnimation();
    playIdleAnimation(lastDirection);
}

// 播放行走动画
void Player::playWalkAnimation(const std::string& direction) {
    stopAnimation();

    auto animation = "walk_" + direction;

    // 播放缓存的行走动画
    if (Changers::walkAnimations.find(animation) != Changers::walkAnimations.end()) {
        Changers::currentAnimation = Changers::walkAnimations[animation];
        // sprite->runAction(RepeatForever::create(Changers::currentAnimation));

        //创建RepeatForever动作
        Changers::currentAction = RepeatForever::create(Changers::currentAnimation);

        if (Changers::currentAnimation !=nullptr&& Changers::sprite->getNumberOfRunningActions()==0) {
            Changers::sprite->runAction(currentAction);
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
    if (Changers::walkAnimations.find(animation) != Changers::walkAnimations.end()) {
        Changers::currentAnimation = Changers::walkAnimations[animation];

        // 创建 RepeatForever 动作
        Changers::currentAction = RepeatForever::create(Changers::currentAnimation);

        Changers::sprite->runAction(currentAction);
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

void Player::update(float delta)
{
    if (isMoving)
    {
       // playWalkAnimation(lastDirection);
    }
}

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
    if(Changers::currentAnimation!=nullptr){
        // 停止当前的动画

        Changers::sprite->stopAction(Changers::currentAction);

        Changers::currentAnimation = nullptr;
        Changers::currentAction = nullptr;
    }
 
}