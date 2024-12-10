#ifndef __INVENTORY_LAYER_H__
#define __INVENTORY_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class InventoryLayer : public cocos2d::Layer {
public:
    // ������
    static InventoryLayer* createLayer();

    // ��ʼ����
    virtual bool init();

    // �л�ҳ��
    void switchToPage(int pageIndex);

    // ������¼�������
    void onMouseDown(cocos2d::Event* event);

    // �رյ�ǰ��
    void closeInventoryLayer(Ref* sender);

    CREATE_FUNC(InventoryLayer);

private:
    // ҳ������
    cocos2d::Node* itemPage;    // ��Ʒҳ��
    cocos2d::Node* socialPage;  // �罻��ϵҳ��
    int currentPage;            // ��ǰҳ������
};

#endif // __INVENTORY_LAYER_H__
