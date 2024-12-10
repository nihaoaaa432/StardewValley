#include "Characters.h"

// 创建一个新的Character实例
Character* Character::create(const std::string& filePath)
{
    auto character = new (std::nothrow) Character();
    if (character && character->init(filePath))
    {
        character->autorelease();
        return character;
    }
    CC_SAFE_DELETE(character);
    return nullptr;
}

// 初始化函数
bool Character::init(const std::string& filePath)
{
    if (!Node::init())
    {
        return false;
    }

    // 创建角色精灵
    _characterSprite = cocos2d::Sprite::create(filePath);
    if (_characterSprite == nullptr)
    {
        return false;
    }

    // 将角色精灵添加到节点
    this->addChild(_characterSprite);
    return true;
}

// 角色移动函数
void Character::moveLeft()
{
    setPosition(getPosition().x - 20, getPosition().y);
}

void Character::moveRight()
{
    setPosition(getPosition().x + 20, getPosition().y);
}

void Character::moveUp()
{
    setPosition(getPosition().x, getPosition().y - 20);
}

void Character::moveDown()
{
    setPosition(getPosition().x, getPosition().y + 20);
}

// 设置角色位置
void Character::setPosition(float x, float y)
{
    Node::setPosition(cocos2d::Vec2(x, y));
}

// 键盘监听回调
void Character::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    switch (keyCode)
    {
    case cocos2d::EventKeyboard::KeyCode::KEY_W:
        moveUp();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_S:
        moveDown();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_A:
        moveLeft();
        break;
    case cocos2d::EventKeyboard::KeyCode::KEY_D:
        moveRight();
        break;
    default:
        break;
    }
}

void Character::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
    // You can handle key release events here if needed.
}