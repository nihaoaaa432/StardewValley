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

// 初始化方法实现
bool Crops::init() {
    if (!Node::init()) {
        return false;
    }

    //加载图集
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Crops.plist");

    //获取当前播种季节
    auto season = Clock::getInstance()->getCurrentSeason();//获得当前季节

    this->seedDay = Clock::getInstance()->getCurrentDays();//获得种子落地日期
    this->growthInterval = growthIntervals[static_cast<int>(name)][static_cast<int>(season)];//从数组中获得成长间隔
    this->stage = 1;//初始阶段为1
    this->matured = false;//初始为未成熟
    this->harvestItem = harvest[name];
    this->harvestQuantity = HQs[name];


    //将枚举类转换为string
    std::string sName = toString(name);

    if (name == Tree)
    {

        sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("init_" + sName + ".png"));
        // 初始化农作物的属性
    }
    else {
        //除了树均以刚种下为初始化
        sprite = Sprite::createWithSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sName + "_1.png"));
    }

    //初始位置均为0，0
    this->addChild(sprite);
    sprite->setPosition(Vec2(0, 0));
    return true;
}





void Crops::update(float deltaTime)
{
    if (!matured)//不成熟才需要判断成长
    {
        int growDays = Clock::getInstance()->getCurrentDays() - seedDay;

        int targetStage = growDays / growthInterval + 1;//成长时间/间隔+1为当前成长阶段

        if (targetStage >= 1 && targetStage <= 5 && targetStage != stage)
        {
            stage = targetStage;
            sprite->setSpriteFrame(toString(name) + "_" + std::to_string(stage) + ".png");//重新设置精灵帧
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
    //如果成熟，执行收获操作
    if (matured)
    {
        this->removeFromParent();
        //修改Player,使其获得收获物

        //显示提示
        player->showHint(u8"收获" + harvestItem + std::to_string(harvestQuantity) + u8"个");
    }
    else
    {
        std::string sName = toString(name);
        player->showHint(sName + u8"尚未成熟，无法收获");
    }
}
