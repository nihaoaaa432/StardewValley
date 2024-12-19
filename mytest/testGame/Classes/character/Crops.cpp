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

// ��ʼ������ʵ��
bool Crops::init() {
    if (!Node::init()) {
        return false;
    }

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Crops.plist");

    std::string sName = toString(name);

    if (name == Tree)
    {
       
        sprite->createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("init_" + sName + ".png"));


        // ��ʼ��ũ���������
        this->matured = false;
        this->growthSpeed = 1;
        this->harvestItem = "seed";
        this->harvestQuantity = 5;
    }
    else {
        //��������������Ϊ��ʼ��
        sprite=Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName( sName + "_0.png"));

        //���ݲ�ͬ������������
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

    //��ʼλ�þ�Ϊ0��0
    sprite->setPosition(0, 0);
    this->addChild(sprite);
    return true;
}

//�ջ�
bool Crops::harvest()
{
    if (!matured)//δ����
    {
        return false;
    }

    //��ʧ����

    return true;
}


