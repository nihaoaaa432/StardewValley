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

    // ��ʼ������
    bool init()override;

    //�ջ�ũ����
    virtual bool harvest();



protected:
    cocos2d::Sprite* sprite;

    CropsType name;

    bool matured;            // �Ƿ����
    float growthSpeed;       // �����ٶȣ������ʱ�䣩
    std::string harvestItem; // �ջ���
    int harvestQuantity;     // �ջ�������
};
#define CREATE_TREE Crops::create(Tree)

#endif // _CROPS_H_
