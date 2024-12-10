#include "Character.h"

USING_NS_CC;

Character* createWithAttributes(const char* imagePath, const char* name)
{
    Character* character = new Character();
    if (character != nullptr && character->initWithAttributes(imagePath, name))
    {
        character->autorelease();
        return character;
    }
    delete character;
    return nullptr;
}

bool Character::initWithAttributes(const char* imagePath, const char* name) {
    if (!Node::init()) {
        return false;
    }
    sprite = Sprite::create(imagePath);
    //初始位置均为0，0
    sprite->setPosition(0, 0);
    this->addChild(sprite);

    nameLabel = Label::createWithSystemFont(name, "Arial", 24);
    nameLabel->setPosition(0, 100);
    this->addChild(nameLabel);//此时会显示名称

    return true;
}
