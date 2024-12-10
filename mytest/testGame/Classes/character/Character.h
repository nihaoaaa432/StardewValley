#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"


class Character : public cocos2d::Node { // �̳��� Node
protected:
    cocos2d::Sprite* sprite;//ͼ����ʾ
    cocos2d::Label* nameLabel;//������ʾ

public:
    static Character* createWithAttributes(const char* imagePath, const char* name);

    // ��ʼ����ɫ�����������֡,�Ƽ���
    virtual bool initWithAttributes(const char* imagePath, const char* name);

    //// ���Ŷ���
    //void playAnimation(int startRow, int startCol, int frameCount, float frameDelay);

    //// ���½�ɫ���������д��
    //virtual void update(float dt);
};

#endif // _CHARACTER_H_
