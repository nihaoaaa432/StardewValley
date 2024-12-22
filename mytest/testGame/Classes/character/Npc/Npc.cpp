#include "NPC.h"

NPC* NPC::create(const std::string& filename) {
    NPC* npc = new NPC();
    if (npc && npc->init(filename)) {
        npc->autorelease();
        return npc;
    }
    else {
        delete npc;
        return nullptr;
    }
}

bool NPC::init(const std::string& filename) {
    // ʹ�ô����ͼƬ��ʼ�� NPC
    if (!Sprite::initWithFile(filename)) {
        return false;
    }

    _isMoving = false;
    _currentTargetIndex = 0;
    _speed = 100.0f;  // Ĭ���ٶ�Ϊ 100
    return true;
}

void NPC::setPath(const std::vector<Vec2>& path) {
    _path = path;
    if (!_path.empty()) {
        _isMoving = true;
        _currentTargetIndex = 0;
        this->setPosition(_path[0]);  // ���� NPC ��ʼλ��
    }
}

void NPC::setSpeed(float speed) {
    _speed = speed;  // ���� NPC ���ƶ��ٶ�
}

bool NPC::isMoving() const {
    return _isMoving;
}

bool NPC::hasReachedTarget() const {
    if (_path.empty()) {
        return false;
    }
    // ���㵱ǰ NPC λ����Ŀ���֮��ľ���
    auto currentPosition = this->getPosition();
    auto targetPosition = _path[_currentTargetIndex];
    float distance = currentPosition.distance(targetPosition);
    return distance < _speed * 0.02f;  // �������С���ٶȵ�һ����������ʾ����Ŀ��
}

void NPC::moveToTarget(float deltaTime) {
    if (!_path.empty() && _isMoving) {
        auto currentPosition = this->getPosition();
        auto targetPosition = _path[_currentTargetIndex];
        Vec2 direction = targetPosition - currentPosition;
        direction.normalize();  // ���㷽��

        // �ƶ� NPC
        this->setPosition(currentPosition + direction * _speed * deltaTime);

        if (hasReachedTarget()) {
            _currentTargetIndex++;  // Ŀ�굽����������
            if (_currentTargetIndex >= _path.size()) {
                _isMoving = false;  // �������Ŀ�궼�����ֹͣ�ƶ�
            }
        }
    }
}

void NPC::update(float deltaTime) {
    if (_isMoving) {
        moveToTarget(deltaTime);  // ��� NPC ���ƶ���������ƶ�����
    }
}
