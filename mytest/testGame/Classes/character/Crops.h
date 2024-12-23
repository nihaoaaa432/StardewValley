#ifndef _CROPS_H_
#define _CROPS_H_

#include "cocos2d.h"
#include <string>
#include "Interactable.h"

#define CROP_COUNT 10
#define SEASON_COUNT 4

// 存储每个作物在每个季节的生长间隔时间（单位：天）
const int growthIntervals[CROP_COUNT][SEASON_COUNT] = {
    // TREE
    {4, 5, 6, 7},               // 树木生长间隔（春、夏、秋、冬）
    // CARROT
    {3, 4, 5, 6},               // 胡萝卜生长间隔（春、夏、秋、冬）
    // TOMATO
    {3, 4, 5, 6},               // 番茄生长间隔（春、夏、秋、冬）
    // CORN
    {5, 6, 7, 8},               // 玉米生长间隔（春、夏、秋、冬）
    // STRAWBERRY
    {2, 3, 4, 5},               // 草莓生长间隔（春、夏、秋、冬）
    // POTATO
    {4, 5, 6, 7},               // 土豆生长间隔（春、夏、秋、冬）
    // PUMPKIN
    {4, 5, 6, 7},               // 南瓜生长间隔（春、夏、秋、冬）
    // WATERMELON
    {5, 6, 7, 8},               // 西瓜生长间隔（春、夏、秋、冬）
    // BEET
    {3, 4, 5, 6},               // 甜菜生长间隔（春、夏、秋、冬）
    // CABBAGE
    {4, 5, 6, 7}                // 卷心菜生长间隔（春、夏、秋、冬）
};

enum CropsType {
    Tree = 0,
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

const std::string harvest[CROP_COUNT] = {
    u8"Wood",u8"Carrot",u8"Tomato",u8"Corn",u8"Strawberry",u8"Potato",u8"Pumpkin",u8"Watermelon",u8"Beet",u8"Cabbage"
};

const int HQs[CROP_COUNT] = {
    8,7,6,5,20,6,1,1,10,2
};

class Crops :public Interactable {
public:

    static Crops* create(const CropsType& cropsName);

    // 初始化方法
    bool init()override;

    void update();//更新农作物的生长阶段，修改纹理和是否成熟

    //判断是否点击在精灵附近
    bool isClicked(const cocos2d::Vec2& clickPosition)override;

    void interact(Player* player)override;//重写交互函数

    void update(float deltaTime)override;

protected:
    cocos2d::Sprite* sprite;

    CropsType name;

    bool matured;            // 是否成熟
    int stage;//1-5，0表示种子，5表示成熟
    int growthInterval;       //生长至下一阶段的时间间隔
    int seedDay;//播种时间
    std::string harvestItem; // 收获物
    int harvestQuantity;     // 收获物数量
};

#endif // _CROPS_H_
