#include "Crops.h"

USING_NS_CC;

// ��̬��������ʵ��
Crops* Crops::createWithAttributes(const std::string& altasPath, const std::string& name, float growthSpeed, const std::string& harvestItem, int harvestQuantity) {
    Crops* crop = new(std::nothrow) Crops();
    if (crop && crop->initWithAttributes(altasPath, name, growthSpeed, harvestItem, harvestQuantity)) {
        crop->autorelease();
        return crop;
    }
    delete crop;
    return nullptr;
}

// ��ʼ������ʵ��
bool Crops::initWithAttributes(const std::string& altasPath, const std::string& name, float growthSpeed, const std::string& harvestItem, int harvestQuantity) {
    if (!Changers::initWithAttributes(altasPath, name)) {
        return false;
    }

    // ��ʼ��ũ���������
    this->matured = false;
    this->growthSpeed = growthSpeed;
    this->harvestItem = harvestItem;
    this->harvestQuantity = harvestQuantity;

    return true;
}

//�ջ�
bool Crops::harvest()
{
    if (!matured)//δ����
    {
        return false;
    }

    //��ʧ����

    return true;
}


