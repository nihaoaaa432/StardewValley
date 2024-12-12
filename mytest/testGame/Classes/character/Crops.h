#ifndef _CROPS_H_
#define _CROPS_H_

#include "character/Changers.h"

class Crops : public Changers {
public:
    // 静态工厂方法
    static Crops* createWithAttributes(const std::string& altasPath, const std::string& name, float growthSpeed, const std::string& harvestItem, int harvestQuantity);

    // 初始化方法
    bool initWithAttributes(const std::string& altasPath, const std::string& name, float growthSpeed, const std::string& harvestItem, int harvestQuantity);

    //收获农作物
    virtual bool harvest();



protected:
    bool matured;            // 是否成熟
    float growthSpeed;       // 生长速度（或成熟时间）
    std::string harvestItem; // 收获物
    int harvestQuantity;     // 收获物数量
};


#endif // _CROPS_H_
