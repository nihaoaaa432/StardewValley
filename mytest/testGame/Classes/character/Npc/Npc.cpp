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
    // 使用传入的图片初始化 NPC
    if (!Sprite::initWithFile(filename)) {
        return false;
    }

    _isMoving = false;
    _currentTargetIndex = 0;
    _speed = 100.0f;  // 默认速度为 100
    return true;
}

void NPC::setPath(const std::vector<Vec2>& path) {
    _path = path;
    if (!_path.empty()) {
        _isMoving = true;
        _currentTargetIndex = 0;
        this->setPosition(_path[0]);  // 设置 NPC 初始位置
    }
}

void NPC::setSpeed(float speed) {
    _speed = speed;  // 设置 NPC 的移动速度
}

bool NPC::isMoving() const {
    return _isMoving;
}

bool NPC::hasReachedTarget() const {
    if (_path.empty()) {
        return false;
    }
    // 计算当前 NPC 位置与目标点之间的距离
    auto currentPosition = this->getPosition();
    auto targetPosition = _path[_currentTargetIndex];
    float distance = currentPosition.distance(targetPosition);
    return distance < _speed * 0.02f;  // 如果距离小于速度的一定比例，表示到达目标
}

void NPC::moveToTarget(float deltaTime) {
    if (!_path.empty() && _isMoving) {
        auto currentPosition = this->getPosition();
        auto targetPosition = _path[_currentTargetIndex];
        Vec2 direction = targetPosition - currentPosition;
        direction.normalize();  // 计算方向

        // 移动 NPC
        this->setPosition(currentPosition + direction * _speed * deltaTime);

        if (hasReachedTarget()) {
            _currentTargetIndex++;  // 目标到达后更新索引
            if (_currentTargetIndex >= _path.size()) {
                _isMoving = false;  // 如果所有目标都到达，则停止移动
            }
        }
    }
}

void NPC::update(float deltaTime) {
    if (_isMoving) {
        moveToTarget(deltaTime);  // 如果 NPC 在移动，则调用移动函数
    }
}
