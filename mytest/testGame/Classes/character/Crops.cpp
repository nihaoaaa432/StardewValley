#include "Crops.h"
#include "ui/clock.h"

USING_NS_CC;

std::string toString(const CropsType& crops)
{
    switch (crops)
    {
    case Tree:
        return u8"Tree";
    case Carrot:
        return u8"Carrot";
    case Tomato:
        return u8"Tomato";
    case Corn:
        return u8"Corn";
    case Strawberry:
        return u8"Strawberry";
    case Potato:
        return u8"Potato";
    case Pumpkin:
        return u8"Pumpkin";
    case Watermelon:
        return u8"Watermelon";
    case Beet:
        return u8"Beet";
    case Cabbage:
        return u8"Cabbage";
    default:
        break;
    }
    return "";
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

    //����ͼ��
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Crops.plist");

    //��ȡ��ǰ���ּ���
    auto season = Clock::getInstance()->getCurrentSeason();//��õ�ǰ����

    this->seedDay = Clock::getInstance()->getCurrentDays();//��������������
    this->growthInterval = growthIntervals[static_cast<int>(name)][static_cast<int>(season)];//�������л�óɳ����
    this->stage = 1;//��ʼ�׶�Ϊ1
    this->matured = false;//��ʼΪδ����
    this->harvestItem = harvest[name];
    this->harvestQuantity = HQs[name];


    //��ö����ת��Ϊstring
    std::string sName = toString(name);

    if (name == Tree)
    {

        sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("init_" + sName + ".png"));
        // ��ʼ��ũ���������
    }
    else {
        //���������Ը�����Ϊ��ʼ��
        sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sName + "_1.png"));
    }

    //��ʼλ�þ�Ϊ0��0
    this->addChild(sprite);
    sprite->setPosition(Vec2(0, 0));
    return true;
}





void Crops::update(float deltaTime)
{
    if (!matured)//���������Ҫ�жϳɳ�
    {
        int growDays = Clock::getInstance()->getCurrentDays() - seedDay;

        int targetStage = growDays / growthInterval + 1;//�ɳ�ʱ��/���+1Ϊ��ǰ�ɳ��׶�

        if (targetStage >= 1 && targetStage <= 5 && targetStage != stage)
        {
            stage = targetStage;
            sprite->setSpriteFrame(toString(name) + "_" + std::to_string(stage) + ".png");//�������þ���֡
            if (targetStage >= 5)
                matured = true;
        }
    }
}


bool Crops::isClicked(const cocos2d::Vec2& clickPosition)
{
    return this->getBoundingBox().containsPoint(clickPosition);
}

void Crops::interact(Player* player)
{
    //������죬ִ���ջ����
    if (matured)
    {
        this->removeFromParent();
        //�޸�Player,ʹ�����ջ���

        //��ʾ��ʾ
        player->showHint(u8"�ջ�" + harvestItem + std::to_string(harvestQuantity) + u8"��");
    }
    else
    {
        std::string sName = toString(name);
        player->showHint(sName + u8"��δ���죬�޷��ջ�");
    }
}
