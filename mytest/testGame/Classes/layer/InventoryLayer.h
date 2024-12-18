#ifndef __INVENTORY_LAYER_H__
#define __INVENTORY_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class InventoryLayer : public cocos2d::Layer {
public:
    // 获取单例对象
    static InventoryLayer* getInstance();

    // 初始化单例对象
    virtual bool init();

    // 切换页面
    void switchToPage(int pageIndex);

    // 鼠标点击事件
    void onMouseDown(cocos2d::Event* event);

    // 关闭背包界面
    void closeInventoryLayer(cocos2d::Ref* sender);

    // 更新背包界面位置
    void updatePosition(cocos2d::Vec2 position);

    // 设置可见性
    void setVisible(bool visible) override;

    CREATE_FUNC(InventoryLayer);

private:
    // 销毁单例对象
    static void destroyInstance();

    static InventoryLayer* _instance; // 单例对象指针

    cocos2d::Node* buttonBar;  //侧边栏
    cocos2d::Layer* itemPage;    // 物品页面
    cocos2d::Layer* socialPage;  // 社交页面


    int currentPage;            // 当前页面索引
};

#endif // __INVENTORY_LAYER_H__