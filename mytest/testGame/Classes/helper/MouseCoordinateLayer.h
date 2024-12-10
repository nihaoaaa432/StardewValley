#ifndef __MOUSE_COORDINATE_LAYER_H__
#define __MOUSE_COORDINATE_LAYER_H__

#include "cocos2d.h"

class MouseCoordinateLayer : public cocos2d::Layer {
public:
    // ������
    static MouseCoordinateLayer* createLayer();

    // ��ʼ����
    virtual bool init();

    // ����ƶ��¼�������
    void onMouseMove(cocos2d::Event* event);

    CREATE_FUNC(MouseCoordinateLayer);

private:
    // ��ʾ����ı�ǩ
    cocos2d::Label* coordinateLabel;
};

#endif // __MOUSE_COORDINATE_LAYER_H__
