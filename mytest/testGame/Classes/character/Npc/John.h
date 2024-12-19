// John.h

#ifndef __JOHN_H__
#define __JOHN_H__

#include "NPC.h"
#include "cocos2d.h"
#include "character/Player.h"
#include "character/Npc/DialogSystem.h"

using namespace cocos2d;

class John : public NPC {
public:
    // ���� John NPC ʵ��
    static John* create(const std::string& filename);

    // ��ʼ�� John ���е�����
    virtual bool init(const std::string& filename) override;

    // ���� John ��״̬�����ǻ���� update ����
    virtual void update(float deltaTime) override;

    // �����ƶ�·��
    void setPath(const std::vector<Vec2>& path) { _path = path; }

    // �����ƶ��ٶ�
    void setSpeed(float speed) { _speed = speed; }

    // �����Ƿ�������ҵĶԻ���
    void setTalking(bool talking) { _isTalking = talking; }

    // ������� John ���е���Ϊ
    void customBehavior(float deltaTime);

    // ����·����������ԣ�ÿ�����ã�
    void resetDailyMovement();

private:
    bool _isTalking = false;  // �Ƿ�����ҶԻ�
    bool _isMoving = true;     // �Ƿ������ƶ�
    std::vector<Vec2> _path;  // John ���ƶ�·��
    float _speed = 100.0f;     // �ƶ��ٶ�
    size_t _currentPathIndex = 0; // ��ǰ·��������
};

#endif // __JOHN_H__
