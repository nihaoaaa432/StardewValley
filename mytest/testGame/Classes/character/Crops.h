#ifndef _CROPS_H_
#define _CROPS_H_

#include "cocos2d.h"
#include <string>
#include "Interactable.h"

#define CROP_COUNT 10
#define SEASON_COUNT 4

// �洢ÿ��������ÿ�����ڵ��������ʱ�䣨��λ���죩
const int growthIntervals[CROP_COUNT][SEASON_COUNT] = {
    // TREE
    {4, 5, 6, 7},               // ��ľ��������������ġ������
    // CARROT
    {3, 4, 5, 6},               // ���ܲ���������������ġ������
    // TOMATO
    {3, 4, 5, 6},               // ������������������ġ������
    // CORN
    {5, 6, 7, 8},               // ������������������ġ������
    // STRAWBERRY
    {2, 3, 4, 5},               // ��ݮ��������������ġ������
    // POTATO
    {4, 5, 6, 7},               // ������������������ġ������
    // PUMPKIN
    {4, 5, 6, 7},               // �Ϲ���������������ġ������
    // WATERMELON
    {5, 6, 7, 8},               // ������������������ġ������
    // BEET
    {3, 4, 5, 6},               // �����������������ġ������
    // CABBAGE
    {4, 5, 6, 7}                // ���Ĳ���������������ġ������
};

enum CropsType {
    Tree = 0,
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

const std::string harvest[CROP_COUNT] = {
    u8"Wood",u8"Carrot",u8"Tomato",u8"Corn",u8"Strawberry",u8"Potato",u8"Pumpkin",u8"Watermelon",u8"Beet",u8"Cabbage"
};

const int HQs[CROP_COUNT] = {
    8,7,6,5,20,6,1,1,10,2
};

class Crops :public Interactable {
public:

    static Crops* create(const CropsType& cropsName);

    // ��ʼ������
    bool init()override;

    void update();//����ũ����������׶Σ��޸�������Ƿ����

    //�ж��Ƿ����ھ��鸽��
    bool isClicked(const cocos2d::Vec2& clickPosition)override;

    void interact(Player* player)override;//��д��������

    void update(float deltaTime)override;

protected:
    cocos2d::Sprite* sprite;

    CropsType name;

    bool matured;            // �Ƿ����
    int stage;//1-5��0��ʾ���ӣ�5��ʾ����
    int growthInterval;       //��������һ�׶ε�ʱ����
    int seedDay;//����ʱ��
    std::string harvestItem; // �ջ���
    int harvestQuantity;     // �ջ�������
};

#endif // _CROPS_H_
