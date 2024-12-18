#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"
#include <vector>
#include <string>

using namespace cocos2d;

class NPC : public Sprite {
public:
    // ���� NPC ʵ��
    static NPC* create(const std::string& filename);

    // ��ʼ�� NPC
    virtual bool init(const std::string& filename);

    // ���� NPC ��·��
    void setPath(const std::vector<Vec2>& path);

    // ���� NPC ״̬��ÿ֡���ã�
    virtual void update(float deltaTime);

    // ���� NPC �ƶ��ٶ�
    void setSpeed(float speed);

    // �ж� NPC �Ƿ����ƶ�
    bool isMoving() const;

protected:
    // NPC ��·����·���㣩
    std::vector<Vec2> _path;

    // ��ǰĿ��·��������
    int _currentTargetIndex;

    // NPC �Ƿ������ƶ�
    bool _isMoving;

    // �ƶ��ٶ�
    float _speed;

    // �ж��Ƿ񵽴�Ŀ��λ��
    bool hasReachedTarget() const;

    // �ƶ���Ŀ���
    void moveToTarget(float deltaTime);
};

#endif // __NPC_H__
