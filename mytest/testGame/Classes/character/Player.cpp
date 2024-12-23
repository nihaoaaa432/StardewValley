#include "Player.h"
#include "layer/InventoryLayer.h"
#include "Interactable.h"

//#define ENABLE_ANIMATIONS  行走动画 但是该功能存在问题

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

    delete player;
    player = nullptr;
    return nullptr;

}

bool Player::init() {
    if (!Node::init()) {
        return false;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Abigail.plist");

    isMoving = false;
    isInventoryOpen = false;
    moveDirection = Vec2::ZERO;
    speed = INIT_PLAYER_SPEED;

    //初始化纹理
    sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("init_" + name + ".png"));
    //初始位置均为0，0

    this->addChild(sprite);
    sprite->setPosition(0, 0);


#ifdef ENABLE_ANIMATIONS
    loadAnimations();
#endif

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
#ifdef ENABLE_ANIMATIONS
    playWalkAnimation(lastDirection);
#endif

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
#ifdef ENABLE_ANIMATIONS
    playIdleAnimation(lastDirection);
#endif
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
        auto inventoryLayer = InventoryLayer::getInstance();
        inventoryLayer->setName("inventoryLayer");
        this->getParent()->addChild(inventoryLayer);

        isInventoryOpen = true;
    }
}


void Player::closeInventory() {
    if (isInventoryOpen) {
        auto inventoryLayer = dynamic_cast<InventoryLayer*>(this->getParent()->getChildByName("inventoryLayer"));
        if (inventoryLayer) {
            inventoryLayer->removeFromParent();
        }

        isInventoryOpen = false;
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
bool Player::interactWithClickPosition(const Vec2& Position, std::vector<Interactable* >& interacts)//与点击位置交互
{
    //检查点击位置是否点击在某个可交互的结点上，并尝试收获
    for (auto& interact : interacts)
    {
        if (interact->isInteracted(Position))
        {
            //如果该结点被点击
            //计算人物与物品的距离
            float distance = this->getPosition().distance(interact->getPosition());
            const float interactionDistance = 100.0f;//设定交互的最大距离

            if (distance <= interactionDistance)
            {
                if (interact->interact(this))//收获成功
                {
                    interacts.erase(std::remove(interacts.begin(), interacts.end(), interact), interacts.end());
                }
                return true;
            }

        }
    }
    return false;
}

void Player::showHint(const std::string& message)
{
    //创建一个Label来显示信息
    auto hintLabel = Label::createWithSystemFont(message, "fronts/Arial", 24);
    hintLabel->setPosition(Vec2(this->getPosition().x, this->getPosition().y + 50)); // 显示在玩家上方
    hintLabel->setColor(Color3B::WHITE);
    this->getParent()->addChild(hintLabel);  // 添加到场景中

    // 2秒后自动消失
    auto fadeOut = FadeOut::create(2.0f);  // 创建2秒后淡出效果
    auto remove = CallFunc::create([hintLabel]() { hintLabel->removeFromParent(); }); // 创建移除操作

    // 执行淡出和移除操作
    hintLabel->runAction(Sequence::create(fadeOut, remove, nullptr));
}