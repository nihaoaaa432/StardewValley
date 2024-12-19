#ifndef _CROPS_H_
#define _CROPS_H_

#include "cocos2d.h"
#include <string>

enum CropsType {
    Tree,
    Carrot,
    Tomato,
    Corn,
    Strawberry,
    Potato,
    Pumpkin,
    Watermelon,
    Beet,
    Cabbage
};


class Crops : public cocos2d::Node {
public:

    static Crops* create(const CropsType& cropsName);

    // 初始化方法
    bool init()override;

    //收获农作物
    virtual bool harvest();



protected:
    cocos2d::Sprite* sprite;

    CropsType name;

    bool matured;            // 是否成熟
    float growthSpeed;       // 生长速度（或成熟时间）
    std::string harvestItem; // 收获物
    int harvestQuantity;     // 收获物数量
};
#define CREATE_TREE Crops::create(Tree)

#endif // _CROPS_H_
