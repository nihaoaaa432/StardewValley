#include "Crops.h"

USING_NS_CC;

// 静态工厂方法实现
Crops* Crops::createWithAttributes(const std::string& altasPath, const std::string& name, float growthSpeed, const std::string& harvestItem, int harvestQuantity) {
    Crops* crop = new(std::nothrow) Crops();
    if (crop && crop->initWithAttributes(altasPath, name, growthSpeed, harvestItem, harvestQuantity)) {
        crop->autorelease();
        return crop;
    }
    delete crop;
    return nullptr;
}

// 初始化方法实现
bool Crops::initWithAttributes(const std::string& altasPath, const std::string& name, float growthSpeed, const std::string& harvestItem, int harvestQuantity) {
    if (!Changers::initWithAttributes(altasPath, name)) {
        return false;
    }

    // 初始化农作物的属性
    this->matured = false;
    this->growthSpeed = growthSpeed;
    this->harvestItem = harvestItem;
    this->harvestQuantity = harvestQuantity;

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


