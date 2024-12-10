#include "Player.h"
#include "InventoryLayer.h"

USING_NS_CC;

////��̬��������
//Player* Player::create(const char* filename)
//{
//	Player* player = new Player();
//	if (player != nullptr && player->initWithFile(filename)) 
//	{
//		player->autorelease();
//		player->initPlayer();//��ʼ���������
//		return player;
//	}
//	CC_SAFE_DELETE(player);
//	return nullptr;
//}
//
////��ʼ������
//void Player::initPlayer()
//{
//	this->m_health = INIT_PLAYER_HEALTH;
//	this->m_money = INIT_PLAYER_MONEY;
//	this->m_speed = INIT_PLAYER_SPEED;
//    this->m_direction = Vec2::ZERO;
//
//	//��ʼ������
//	this->initAnimations();
//
//	//��ʼ��������ײ����
//
//}
//// ���º���
//void Player::update(float delta)
//{
//    // TODO: ʵ�ֶ�̬���ܣ������������ġ�λ�ø��µ�
//}
//
//// �����ƶ�����
//void Player::move()
//{
//    auto newPosition = this->getPosition() + m_direction * m_speed;
//    this->setPosition(newPosition);
//
//    // TODO: ��ӱ߽������Ƭ��ͼ����
//}
//
////�������ﳯ��
//void Player::setDirection(const Vec2& d)
//{
//    // ����Ƕȣ����ݷ������������������ת�Ƕ�
//    float angle = CC_RADIANS_TO_DEGREES(atan2(d.y, d.x));
//    this->setRotation(-angle);  // ��ʱ����ת����ΪĬ�ϵ�Cocos2d����ת����ʱ�룩
//    m_direction = d;
//}
//
//
//
//// �����˺�����
//void Player::takeDamage(int damage) 
//{
//    this->m_health -= damage;
//    if (this->m_health <= 0) {
//        this->die();
//    }
//}
//
//// ��ȡ�������ֵ
//int Player::getHealth() const 
//{
//    return this->m_health;
//}
//
//// ��ȡ��ҽ�Ǯ
//int Player::getMoney() const 
//{
//    return this->m_money;
//}
//
//// ���ӽ�Ǯ
//void Player::addMoney(int amount)
//{
//    this->m_money += amount;
//}
//
//// ��������߼�
//void Player::die() 
//{
//    // TODO: ʵ����������߼������紥����Ϸ�����򸴻����
//}
//
//// ��ʼ������
//void Player::initAnimations()
//{
//    // TODO: �����������ҵĶ���֡���������ߡ���������
//}
//
//// ��ʼ��������ײ��
//void Player::initPhysics() 
//{
//    auto physicsBody = PhysicsBody::createBox(this->getContentSize());
//    physicsBody->setDynamic(true);
//    this->setPhysicsBody(physicsBody);
//
//    // TODO: �����������ԣ�������ײ��ʶ���������õ�
//}

Player* Player::createWithAttributes(const char* imagePath,const char* name) {
    Player* player = new Player();
    if (player && player->initWithAttributes(imagePath,name)) {
        player->autorelease();
        return player;
    }
    delete player;
    return nullptr;
}

bool Player::initWithAttributes(const char* imagePath,const char*name) {
    if (!Character::initWithAttributes(imagePath,name)){
        return false;
    }

    //ע������¼�
    registerKeyboardEvent();

    isMoving = false;
    isInventoryOpen = false;
    moveDirection = Vec2::ZERO;
    speed = INIT_PLAYER_SPEED;

    return true;
}

void Player::onEnter()
{
    Character::onEnter();
    //ȷ���������ڳ�������ʱע��
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Player::onExit()
{
    //�˳�ʱע�����̼�����
    _eventDispatcher->removeEventListener(keyboardListener);
    Character::onExit();
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

        // ���¿����ƶ��İ���ʱ
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
            startMoving(cocos2d::Vec2(-1, 0)); // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_D:
            startMoving(cocos2d::Vec2(1, 0)); // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_W:
            startMoving(cocos2d::Vec2(0, 1)); // �����ƶ�
            break;
        case EventKeyboard::KeyCode::KEY_S:
            startMoving(cocos2d::Vec2(0, -1)); // �����ƶ�
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
void Player::startMoving(const cocos2d::Vec2& direction) {
    if (!isMoving || moveDirection != direction) {
        moveDirection = direction;
        isMoving = true;

        // �����ƶ�������½�ɫ����
        if (direction.y > 0) {  // ����
            sprite->setRotation(0); // ����
        }
        else if (direction.y < 0) {  // ����
            sprite->setRotation(180); // ����
        }
        else if (direction.x > 0) {  // ����
            sprite->setRotation(90);  // ����
        }
        else if (direction.x < 0) {  // ����
            sprite->setRotation(-90); // ����
        }

        // ����Ŀ��λ��
        auto targetPosition = this->getPosition() + moveDirection * speed*0.02f; // 0.02f��ÿ֡ʱ��ĵ�λ

        // �����ƶ�������ʹ�� MoveTo��
        auto moveAction = cocos2d::MoveTo::create(0.2f, targetPosition); // 0.2���ƶ���Ŀ��λ��
        this->runAction(moveAction); // ִ�ж���
    }
}

// ֹͣ�ƶ���ͨ�����ö�����ֹͣ��ֹͣ�ƶ���
void Player::stopMoving() {
    isMoving = false;
    moveDirection = cocos2d::Vec2::ZERO;
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