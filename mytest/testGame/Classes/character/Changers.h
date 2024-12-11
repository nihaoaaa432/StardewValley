#ifndef _CHANGERS_H_
#define _CHANGERS_H_

#include "cocos2d.h"


class Changers : public cocos2d::Node { // �̳��� Node
protected:
    cocos2d::Sprite* sprite;//ͼ����ʾ
    cocos2d::Label* nameLabel;//������ʾ
    cocos2d::Animate* currentAnimation;//��ǰ����
    cocos2d::Action* currentAction;//��ǰ����
    std::map<std::string, cocos2d::Animate*> walkAnimations;//�洢����

public:
    static Changers* createWithAttributes(const std::string& atlas, const std::string& name);

    // ��ʼ����ɫ�����������֡,�Ƽ���
    virtual bool initWithAttributes(const std::string& atlas, const std::string& name);

    //װ�����ж���
    virtual void loadAnimations();

    //ֹͣ��ǰ����
    virtual void stopCurrentAnimation();

    //// ���Ŷ���
    //void playAnimation(int startRow, int startCol, int frameCount, float frameDelay);

    //// ���½�ɫ���������д��
    //virtual void update(float dt);
};

#endif // _CHANGERS_H_
