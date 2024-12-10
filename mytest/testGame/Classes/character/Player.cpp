#include "Player.h"
#include "InventoryLayer.h"

USING_NS_CC;

////静态创建函数
//Player* Player::create(const char* filename)
//{
//	Player* player = new Player();
//	if (player != nullptr && player->initWithFile(filename)) 
//	{
//		player->autorelease();
//		player->initPlayer();//初始化玩家属性
//		return player;
//	}
//	CC_SAFE_DELETE(player);
//	return nullptr;
//}
//
////初始化函数
//void Player::initPlayer()
//{
//	this->m_health = INIT_PLAYER_HEALTH;
//	this->m_money = INIT_PLAYER_MONEY;
//	this->m_speed = INIT_PLAYER_SPEED;
//    this->m_direction = Vec2::ZERO;
//
//	//初始化动画
//	this->initAnimations();
//
//	//初始化物理碰撞物体
//
//}
//// 更新函数
//void Player::update(float delta)
//{
//    // TODO: 实现动态功能，例如体力消耗、位置更新等
//}
//
//// 键盘移动函数
//void Player::move()
//{
//    auto newPosition = this->getPosition() + m_direction * m_speed;
//    this->setPosition(newPosition);
//
//    // TODO: 添加边界检测或瓦片地图交互
//}
//
////设置人物朝向
//void Player::setDirection(const Vec2& d)
//{
//    // 计算角度，根据方向向量设置人物的旋转角度
//    float angle = CC_RADIANS_TO_DEGREES(atan2(d.y, d.x));
//    this->setRotation(-angle);  // 逆时针旋转（因为默认的Cocos2d的旋转是逆时针）
//    m_direction = d;
//}
//
//
//
//// 处理伤害函数
//void Player::takeDamage(int damage) 
//{
//    this->m_health -= damage;
//    if (this->m_health <= 0) {
//        this->die();
//    }
//}
//
//// 获取玩家生命值
//int Player::getHealth() const 
//{
//    return this->m_health;
//}
//
//// 获取玩家金钱
//int Player::getMoney() const 
//{
//    return this->m_money;
//}
//
//// 增加金钱
//void Player::addMoney(int amount)
//{
//    this->m_money += amount;
//}
//
//// 玩家死亡逻辑
//void Player::die() 
//{
//    // TODO: 实现玩家死亡逻辑，例如触发游戏结束或复活机制
//}
//
//// 初始化动画
//void Player::initAnimations()
//{
//    // TODO: 在这里加载玩家的动画帧，例如行走、攻击动画
//}
//
//// 初始化物理碰撞体
//void Player::initPhysics() 
//{
//    auto physicsBody = PhysicsBody::createBox(this->getContentSize());
//    physicsBody->setDynamic(true);
//    this->setPhysicsBody(physicsBody);
//
//    // TODO: 配置物理属性，例如碰撞标识、重力设置等
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

    //注册键盘事件
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
    //确保监听器在场景进入时注册
    _eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void Player::onExit()
{
    //退出时注销键盘监听器
    _eventDispatcher->removeEventListener(keyboardListener);
    Character::onExit();
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

        // 按下控制移动的按键时
        switch (keyCode) {
        case EventKeyboard::KeyCode::KEY_A:
            startMoving(cocos2d::Vec2(-1, 0)); // 向左移动
            break;
        case EventKeyboard::KeyCode::KEY_D:
            startMoving(cocos2d::Vec2(1, 0)); // 向右移动
            break;
        case EventKeyboard::KeyCode::KEY_W:
            startMoving(cocos2d::Vec2(0, 1)); // 向上移动
            break;
        case EventKeyboard::KeyCode::KEY_S:
            startMoving(cocos2d::Vec2(0, -1)); // 向下移动
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
void Player::startMoving(const cocos2d::Vec2& direction) {
    if (!isMoving || moveDirection != direction) {
        moveDirection = direction;
        isMoving = true;

        // 根据移动方向更新角色朝向
        if (direction.y > 0) {  // 向上
            sprite->setRotation(0); // 朝上
        }
        else if (direction.y < 0) {  // 向下
            sprite->setRotation(180); // 朝下
        }
        else if (direction.x > 0) {  // 向右
            sprite->setRotation(90);  // 朝右
        }
        else if (direction.x < 0) {  // 向左
            sprite->setRotation(-90); // 朝左
        }

        // 计算目标位置
        auto targetPosition = this->getPosition() + moveDirection * speed*0.02f; // 0.02f是每帧时间的单位

        // 创建移动动画（使用 MoveTo）
        auto moveAction = cocos2d::MoveTo::create(0.2f, targetPosition); // 0.2秒移动到目标位置
        this->runAction(moveAction); // 执行动作
    }
}

// 停止移动（通过调用动作的停止来停止移动）
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
        // 禁用键盘事件，除非是 B 键
        //_eventDispatcher->removeEventListener(keyboardListener);

        //监听背包的关闭事件
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