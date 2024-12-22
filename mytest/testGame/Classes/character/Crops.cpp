#include "Crops.h"

USING_NS_CC;

std::string toString(const CropsType& crops)
{
    switch (crops)
    {
    case Tree:
        return "Tree";
    case Carrot:
        return "Carrot";
    case Tomato:
        return "Tomato";
    case Corn:
        return "Corn";
    case Strawberry:
        return "Strawberry";
    case Potato:
        return "Potato";
    case Pumpkin:
        return "Pumpkin";
    case Watermelon:
        return "Watermelon";
    case Beet:
        return "Beet";
    case Cabbage:
        return "Cabbage";
    default:
        break;
    }
}

Crops* Crops::create(const CropsType& cropsName)
{
    Crops* crops = new(std::nothrow) Crops();
    if (crops)
    {
        crops->name = cropsName;
        if (crops->init()) {
            crops->autorelease();
            return crops;
        }
    }
 
    delete crops;
    return nullptr;
}

// 初始化方法实现
bool Crops::init() {
    if (!Node::init()) {
        return false;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Crops.plist");

    std::string sName = toString(name);

    if (name == Tree)
    {
       
        sprite->createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("init_" + sName + ".png"));


        // 初始化农作物的属性
        this->matured = false;
        this->growthSpeed = 1;
        this->harvestItem = "seed";
        this->harvestQuantity = 5;
    }
    else {
        //除了树均以种子为初始化
        sprite=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName( sName + "_0.png"));

        //根据不同作物设置属性
        switch (name)
        {

        case Tree:
            break;
        case Carrot:
            break;
        case Tomato:
            break;
        case Corn:
            break;
        case Strawberry:
            break;
        case Potato:
            break;
        case Pumpkin:
            break;
        case Watermelon:
            break;
        case Beet:
            break;
        case Cabbage:
            break;
        default:
            break;
        }
    }

    //初始位置均为0，0
    sprite->setPosition(0, 0);
    this->addChild(sprite);
    return true;
}

//收获
bool Crops::harvest()
{
    if (!matured)//未成熟
    {
        return false;
    }

    //消失动画

    return true;
}


