#ifndef __INVENTORY_LAYER_H__
#define __INVENTORY_LAYER_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class InventoryLayer : public cocos2d::Layer {
public:
    // ��ȡ��������
    static InventoryLayer* getInstance();

    // ��ʼ����������
    virtual bool init();

    // �л�ҳ��
    void switchToPage(int pageIndex);

    // ������¼�
    void onMouseDown(cocos2d::Event* event);

    // �رձ�������
    void closeInventoryLayer(cocos2d::Ref* sender);

    // ���±�������λ��
    void updatePosition(cocos2d::Vec2 position);

    // ���ÿɼ���
    void setVisible(bool visible) override;

    CREATE_FUNC(InventoryLayer);

private:
    // ���ٵ�������
    static void destroyInstance();

    static InventoryLayer* _instance; // ��������ָ��

    cocos2d::Node* buttonBar;  //�����
    cocos2d::Layer* itemPage;    // ��Ʒҳ��
    cocos2d::Layer* socialPage;  // �罻ҳ��


    int currentPage;            // ��ǰҳ������
};

#endif // __INVENTORY_LAYER_H__