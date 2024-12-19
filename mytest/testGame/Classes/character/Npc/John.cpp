// John.cpp

#include "John.h"
#include "ui/clock.h"

John* John::create(const std::string& filename) {
    John* john = new John();
    if (john && john->init(filename)) {
        john->autorelease();
        return john;
    }
    else {
        delete john;
        return nullptr;
    }
}

bool John::init(const std::string& filename) {
    if (!NPC::init(filename)) {
        return false;
    }

    // ��ʼ�� John ���е�����
    _isTalking = false;
    _isMoving = true;
    _currentPathIndex = 0;

    return true;
}

void John::update(float deltaTime) {
    // ��ִ�л����ĸ��¹���
    NPC::update(deltaTime);

    // �����������ҶԻ���ֹͣ�ƶ�
    if (_isTalking) {
        _isMoving = false;
    }
    else {
        _isMoving = true;
    }

    // ��������ƶ��������ƶ�·��
    if (_isMoving && !_path.empty()) {
        customBehavior(deltaTime);
    }
}

void John::customBehavior(float deltaTime) {
    if (_path.empty()) {
        return;
    }

    // �ƶ�����ǰ·����
    Vec2 target = _path[_currentPathIndex];
    float distance = this->getPosition().distance(target);

    // �������Ŀ���ܽ����л�����һ��·����
    if (distance < 5.0f) {
        _currentPathIndex = (_currentPathIndex + 1) % _path.size();  // ѭ��·��
    }

    // ���㳯��Ŀ���ķ����ƶ�
    Vec2 direction = target - this->getPosition();
    direction.normalize();
    this->setPosition(this->getPosition() + direction * _speed * deltaTime);

    // �ж��Ƿ�����ҽӽ�������ʼ/�����Ի�
    auto player = Player::getInstance();
    if (this->getPosition().distance(player->getPosition()) <= 50.0f && !_isTalking) {
        _isTalking = true;
        DialogSystem::getInstance()->startDialog("Hello, Player!");  // �����Ի���
    }
    else if (this->getPosition().distance(player->getPosition()) > 50.0f && _isTalking) {
        _isTalking = false;
        DialogSystem::getInstance()->endDialog();  // �����Ի���
    }
}

void John::resetDailyMovement() {
    // ÿ������·�������״̬
    _currentPathIndex = 0; // ��·���Ŀ�ʼλ�����¿�ʼ
    _isMoving = true;  // ���¿�ʼ�ƶ�
    // �����Ҫ�������������·������������ÿ��ѭ���Ķ���
}
