#include "Player.h"
#include "layer/InventoryLayer.h"
#include "Interactable.h"

//#define ENABLE_ANIMATIONS  ���߶��� ���Ǹù��ܴ�������

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

    //��ʼ������
    sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("init_" + name + ".png"));
    //��ʼλ�þ�Ϊ0��0

    this->addChild(sprite);
    sprite->setPosition(0, 0);


#ifdef ENABLE_ANIMATIONS
    loadAnimations();
#endif

    return true;
}

void Player::loadAnimations()
{
    //����վ������
    Animations["stand_up"] = createIdleAnimation("up");
    Animations["stand_down"] = createIdleAnimation("down");
    Animations["stand_left"] = createIdleAnimation("left");
    Animations["stand_right"] = createIdleAnimation("right");

    // �������߶���
    Animations["walk_up"] = createWalkAnimation("up");
    Animations["walk_down"] = createWalkAnimation("down");
    Animations["walk_left"] = createWalkAnimation("left");
    Animations["walk_right"] = createWalkAnimation("right");
}

//�������߶���
Animate* Player::createWalkAnimation(const std::string& direction) {
    Vector<SpriteFrame*> animFrames;
    for (int i = 1; i <= 2; ++i) {  // ����ÿ�������� 2 �����߶���֡
        std::string frameName = "Abigail_walk_" + direction + "_" + std::to_string(i) + ".png";
        animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
    }

    // ��������
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);  // ÿ֡ 0.1 ��
    return Animate::create(animation);
}

//����վ������
Animate* Player::createIdleAnimation(const std::string& direction)
{
    Vector<SpriteFrame*> animFrames;
    std::string frameName = "Abigail_stand_" + direction + ".png";
    animFrames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));

    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    return Animate::create(animation);
}

// ͳһ���ƶ�����
void Player::moveInDirection(const cocos2d::Vec2& direction) {
    if (isTalking) {
        return;  // ������ڶԻ���ֹͣ�ƶ�
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
//��ɫ���ڶԻ�
void Player::setIsTalking(bool talking) {
    isTalking = talking;
}
// ֹͣ�ƶ���ͨ�����ö�����ֹͣ��ֹͣ�ƶ���
void Player::stopMoving() {
    if (isTalking) {
        return;  // ������ڶԻ���ֹͣ�ƶ�
    }

    isMoving = false;
    moveDirection = Vec2::ZERO;
#ifdef ENABLE_ANIMATIONS
    playIdleAnimation(lastDirection);
#endif
}
// �������߶���
void Player::playWalkAnimation(const std::string& direction) {
    stopAnimation();

    auto animation = "walk_" + direction;

    // ���Ż�������߶���
    if (Animations.find(animation) != Animations.end()) {
        currentAnimation = Animations[animation];
        // sprite->runAction(RepeatForever::create(  currentAnimation));

        //����RepeatForever����
        currentAction = RepeatForever::create(currentAnimation);

        if (currentAnimation != nullptr && sprite->getNumberOfRunningActions() == 0) {
            sprite->runAction(currentAction);
        }
    }

}

// ����վ��֡
void Player::playIdleAnimation(const std::string& direction) {

    stopAnimation();


    // ����վ��֡
    auto animation = "stand_" + direction;

    // ���Ż����վ������
    if (Animations.find(animation) != Animations.end()) {
        currentAnimation = Animations[animation];

        // ���� RepeatForever ����
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
// ֹͣ����
void Player::stopAnimation() {
    if (currentAnimation != nullptr) {
        // ֹͣ��ǰ�Ķ���

        sprite->stopAction(currentAction);

        currentAnimation = nullptr;
        currentAction = nullptr;
    }

}

Vec2& Player::getMoveDirection()
{
    return moveDirection;
}
bool Player::interactWithClickPosition(const Vec2& Position, std::vector<Interactable* >& interacts)//����λ�ý���
{
    //�����λ���Ƿ�����ĳ���ɽ����Ľ���ϣ��������ջ�
    for (auto& interact : interacts)
    {
        if (interact->isInteracted(Position))
        {
            //����ý�㱻���
            //������������Ʒ�ľ���
            float distance = this->getPosition().distance(interact->getPosition());
            const float interactionDistance = 100.0f;//�趨������������

            if (distance <= interactionDistance)
            {
                if (interact->interact(this))//�ջ�ɹ�
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
    //����һ��Label����ʾ��Ϣ
    auto hintLabel = Label::createWithSystemFont(message, "fronts/Arial", 24);
    hintLabel->setPosition(Vec2(this->getPosition().x, this->getPosition().y + 50)); // ��ʾ������Ϸ�
    hintLabel->setColor(Color3B::WHITE);
    this->getParent()->addChild(hintLabel);  // ��ӵ�������

    // 2����Զ���ʧ
    auto fadeOut = FadeOut::create(2.0f);  // ����2��󵭳�Ч��
    auto remove = CallFunc::create([hintLabel]() { hintLabel->removeFromParent(); }); // �����Ƴ�����

    // ִ�е������Ƴ�����
    hintLabel->runAction(Sequence::create(fadeOut, remove, nullptr));
}