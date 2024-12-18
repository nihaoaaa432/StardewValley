#ifndef __JOHN_H__
#define __JOHN_H__

#include "NPC.h"
#include "cocos2d.h"

using namespace cocos2d;

class John : public NPC {
public:
    // ���� John NPC ʵ��
    static John* create(const std::string& filename);

    // ��ʼ�� John ���е�����
    virtual bool init(const std::string& filename) override;

    // ���� John ��״̬�����ǻ���� update ����
    virtual void update(float deltaTime) override;

    // ������� John ���е���Ϊ
    void customBehavior(float deltaTime);

private:
    // John ���е����ԣ���������ҵĻ�����
    bool _isTalking;  // �Ƿ�������ҶԻ�
};

#endif // __JOHN_H__
