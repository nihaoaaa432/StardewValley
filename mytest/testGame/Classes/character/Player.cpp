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

    //ע������¼�
    registerKeyboardEvent();

    // ÿ 0.1 �����һ�� update ����
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

    //���ó�ʼվ������
    //playIdleAnimation("down");

    return true;
}

void Player::loadAnimations()
{
    //����վ������
    Changers::walkAnimations["stand_up"] = createIdleAnimation("up");
    Changers::walkAnimations["stand_down"] = createIdleAnimation("down");
    Changers::walkAnimations["stand_left"] = createIdleAnimation("left");
    Changers::walkAnimations["stand_right"] = createIdleAnimation("right");

    // �������߶���
    Changers::walkAnimations["walk_up"] = createWalkAnimation("up");
    Changers::walkAnimations["walk_down"] = createWalkAnimation("down");
    Changers::walkAnimations["walk_left"] = createWalkAnimation("left");
    Changers::walkAnimations["walk_right"] = createWalkAnimation("right");
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

void Player::onEnter()
{
    Changers::onEnter();
    //ȷ���������ڳ�������ʱע��
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Player::onExit()
{
    //�˳�ʱע�����̼�����
    _eventDispatcher->removeEventListener(keyboardListener);
    Changers::onExit();
}

//ע������¼�
void Player::registerKeyboardEvent() {
    // ���������¼�������
    keyboardListener = EventListenerKeyboard::create();

    // ���尴�����µĻص�
    keyboardListener->onKeyPressed = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        if (isInventoryOpen) {
            if (keyCode == EventKeyboard::KeyCode::KEY_B) {
                closeInventory();  // �رձ���
            }
            return;  // ������ʱ��������������Ӧ
        }

        if (isMoving) {
            return;
        }

        // ���¿����ƶ��İ���ʱ
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
            move(cocos2d::Vec2(-1, 0)); // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_D:
            move(cocos2d::Vec2(1, 0)); // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_W:
            move(cocos2d::Vec2(0, 1)); // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_S:
            move(cocos2d::Vec2(0, -1)); // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_B:
            openInventory();  // �򿪱���
            break;
        default:
            break;
        }
        };

    // ���尴���ɿ��Ļص�
    keyboardListener->onKeyReleased = [this](EventKeyboard::KeyCode keyCode, Event* event) {
        if (keyCode == EventKeyboard::KeyCode::KEY_A || keyCode == EventKeyboard::KeyCode::KEY_D ||
            keyCode == EventKeyboard::KeyCode::KEY_W || keyCode == EventKeyboard::KeyCode::KEY_S) {
            stopMoving();
        }
        };
}

// ͳһ���ƶ�����
void Player::move(const cocos2d::Vec2& direction) {
        moveDirection = direction;
        isMoving = true;

        // �����ƶ�������½�ɫ����
        if (direction.y > 0) {  // ����
            lastDirection = "up";
        }
        else if (direction.y < 0) {  // ����
            lastDirection = "down";
        }
        else if (direction.x > 0) {  // ����
            lastDirection = "right";
        }
        else if (direction.x < 0) {  // ����
            lastDirection = "left";
        }

        //�������߶���
        playWalkAnimation(lastDirection);

        //// ����Ŀ��λ��
        //auto targetPosition = Changers::sprite->getPosition() + moveDirection * speed*0.02f; // 0.02f��ÿ֡ʱ��ĵ�λ

        //// �����ƶ�������ʹ�� MoveTo��
        //auto moveAction = cocos2d::MoveTo::create(0.2f, targetPosition); // 0.2���ƶ���Ŀ��λ��
        //Changers::sprite->runAction(moveAction); // ִ�ж���
}

// ֹͣ�ƶ���ͨ�����ö�����ֹͣ��ֹͣ�ƶ���
void Player::stopMoving() {
    isMoving = false;
    moveDirection = cocos2d::Vec2::ZERO;

    //ֹͣ����������վ��֡
    //stopAnimation();
    playIdleAnimation(lastDirection);
}

// �������߶���
void Player::playWalkAnimation(const std::string& direction) {
    stopAnimation();

    auto animation = "walk_" + direction;

    // ���Ż�������߶���
    if (Changers::walkAnimations.find(animation) != Changers::walkAnimations.end()) {
        Changers::currentAnimation = Changers::walkAnimations[animation];
        // sprite->runAction(RepeatForever::create(Changers::currentAnimation));

        //����RepeatForever����
        Changers::currentAction = RepeatForever::create(Changers::currentAnimation);

        if (Changers::currentAnimation !=nullptr&& Changers::sprite->getNumberOfRunningActions()==0) {
            Changers::sprite->runAction(currentAction);
        }
    }
    //}
}


// ����վ��֡
void Player::playIdleAnimation(const std::string& direction) {

     stopAnimation();


    // ����վ��֡
    auto animation = "stand_" + direction;
    
    // ���Ż����վ������
    if (Changers::walkAnimations.find(animation) != Changers::walkAnimations.end()) {
        Changers::currentAnimation = Changers::walkAnimations[animation];

        // ���� RepeatForever ����
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
        // ���ü����¼��������� B ��
        //_eventDispatcher->removeEventListener(keyboardListener);

        //���������Ĺر��¼�
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
        // �ָ������¼�����
        //_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
    }

}
// ֹͣ����
void Player::stopAnimation() {
    if(Changers::currentAnimation!=nullptr){
        // ֹͣ��ǰ�Ķ���

        Changers::sprite->stopAction(Changers::currentAction);

        Changers::currentAnimation = nullptr;
        Changers::currentAction = nullptr;
    }
 
}