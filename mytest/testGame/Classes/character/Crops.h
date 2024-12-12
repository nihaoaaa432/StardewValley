#ifndef _CROPS_H_
#define _CROPS_H_

#include "character/Changers.h"

class Crops : public Changers {
public:
    // ��̬��������
    static Crops* createWithAttributes(const std::string& altasPath, const std::string& name, float growthSpeed, const std::string& harvestItem, int harvestQuantity);

    // ��ʼ������
    bool initWithAttributes(const std::string& altasPath, const std::string& name, float growthSpeed, const std::string& harvestItem, int harvestQuantity);

    //�ջ�ũ����
    virtual bool harvest();



protected:
    bool matured;            // �Ƿ����
    float growthSpeed;       // �����ٶȣ������ʱ�䣩
    std::string harvestItem; // �ջ���
    int harvestQuantity;     // �ջ�������
};


#endif // _CROPS_H_
