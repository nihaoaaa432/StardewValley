#include "Changers.h"

USING_NS_CC;

Changers* createWithAttributes(const std::string& altasPath, const std::string& name)
{
    Changers* changer = new(std::nothrow) Changers();
    if (changer != nullptr && changer->initWithAttributes(altasPath, name))
    {
        changer->autorelease();
        return changer;
    }
    delete changer;
    return nullptr;
}

bool Changers::initWithAttributes(const std::string& altas, const std::string& name) {
    if (!Node::init()) {
        return false;
    }
    currentAction = nullptr;
    currentAnimation = nullptr;
    //加载图集
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile(altas);

    sprite = Sprite::create("init_"+name + ".png");
    //初始位置均为0，0
    sprite->setPosition(0, 0);
    this->addChild(sprite);

    //nameLabel = Label::createWithSystemFont(name, "Abigail", 10);
    //nameLabel->setPosition(0, 10);
    //this->addChild(nameLabel);//此时会显示名称

    return true;
}

void Changers::stopCurrentAnimation()
{
    if (currentAnimation) {
        this->stopAction(currentAnimation);  // 停止当前动画
        currentAnimation = nullptr;  // 清空当前动画
    }
}

void Changers::loadAnimations(){}