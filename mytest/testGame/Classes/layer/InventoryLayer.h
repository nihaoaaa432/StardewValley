#ifndef __INVENTORY_LAYER_H__
#define __INVENTORY_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class CinventoryLayer : public cocos2d::Layer {
public:
    // ������
    static CinventoryLayer* createLayer();

    // ��ʼ����
    virtual bool init();

    // �л�ҳ��
    void SwitchToPage(int pageIndex);

    // ������¼�������
    void OnMouseDown(cocos2d::Event* event);

    // �رյ�ǰ��
    void CloseInventoryLayer(Ref* sender);

    CREATE_FUNC(CinventoryLayer);

private:
    // ҳ������
    cocos2d::Node* itemPage;    // ��Ʒҳ��
    cocos2d::Node* socialPage;  // �罻��ϵҳ��
    int currentPage;            // ��ǰҳ������
};

#endif // __INVENTORY_LAYER_H__
