#ifndef __INVENTORY_LAYER_H__
#define __INVENTORY_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class CinventoryLayer : public cocos2d::Layer {
public:
    // 创建层
    static CinventoryLayer* createLayer();

    // 初始化层
    virtual bool init();

    // 切换页面
    void SwitchToPage(int pageIndex);

    // 鼠标点击事件处理函数
    void OnMouseDown(cocos2d::Event* event);

    // 关闭当前层
    void CloseInventoryLayer(Ref* sender);

    CREATE_FUNC(CinventoryLayer);

private:
    // 页面容器
    cocos2d::Node* itemPage;    // 物品页面
    cocos2d::Node* socialPage;  // 社交关系页面
    int currentPage;            // 当前页面索引
};

#endif // __INVENTORY_LAYER_H__
