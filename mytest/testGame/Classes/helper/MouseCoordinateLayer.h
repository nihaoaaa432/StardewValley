#ifndef __MOUSE_COORDINATE_LAYER_H__
#define __MOUSE_COORDINATE_LAYER_H__

#include "cocos2d.h"

class MouseCoordinateLayer : public cocos2d::Layer {
public:
    // 创建层
    static MouseCoordinateLayer* createLayer();

    // 初始化层
    virtual bool init();

    // 鼠标移动事件处理函数
    void onMouseMove(cocos2d::Event* event);

    CREATE_FUNC(MouseCoordinateLayer);

private:
    // 显示坐标的标签
    cocos2d::Label* coordinateLabel;
};

#endif // __MOUSE_COORDINATE_LAYER_H__
