#include "Characters.h"

// ����һ���µ�Characterʵ��
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

// ��ʼ������
bool Character::init(const std::string& filePath)
{
    if (!Node::init())
    {
        return false;
    }

    // ������ɫ����
    _characterSprite = cocos2d::Sprite::create(filePath);
    if (_characterSprite == nullptr)
    {
        return false;
    }

    // ����ɫ������ӵ��ڵ�
    this->addChild(_characterSprite);
    return true;
}

// ��ɫ�ƶ�����
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

// ���ý�ɫλ��
void Character::setPosition(float x, float y)
{
    Node::setPosition(cocos2d::Vec2(x, y));
}

// ���̼����ص�
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