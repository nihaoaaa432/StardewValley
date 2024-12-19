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

    // 初始化 John 特有的属性
    _isTalking = false;
    _isMoving = true;
    _currentPathIndex = 0;

    return true;
}

void John::update(float deltaTime) {
    // 先执行基础的更新功能
    NPC::update(deltaTime);

    // 如果正在与玩家对话，停止移动
    if (_isTalking) {
        _isMoving = false;
    }
    else {
        _isMoving = true;
    }

    // 如果允许移动，更新移动路径
    if (_isMoving && !_path.empty()) {
        customBehavior(deltaTime);
    }
}

void John::customBehavior(float deltaTime) {
    if (_path.empty()) {
        return;
    }

    // 移动到当前路径点
    Vec2 target = _path[_currentPathIndex];
    float distance = this->getPosition().distance(target);

    // 如果距离目标点很近，切换到下一个路径点
    if (distance < 5.0f) {
        _currentPathIndex = (_currentPathIndex + 1) % _path.size();  // 循环路径
    }

    // 计算朝向目标点的方向并移动
    Vec2 direction = target - this->getPosition();
    direction.normalize();
    this->setPosition(this->getPosition() + direction * _speed * deltaTime);

    // 判断是否与玩家接近，并开始/结束对话
    auto player = Player::getInstance();
    if (this->getPosition().distance(player->getPosition()) <= 50.0f && !_isTalking) {
        _isTalking = true;
        DialogSystem::getInstance()->startDialog("Hello, Player!");  // 启动对话框
    }
    else if (this->getPosition().distance(player->getPosition()) > 50.0f && _isTalking) {
        _isTalking = false;
        DialogSystem::getInstance()->endDialog();  // 结束对话框
    }
}

void John::resetDailyMovement() {
    // 每天重置路径和相关状态
    _currentPathIndex = 0; // 从路径的开始位置重新开始
    _isMoving = true;  // 重新开始移动
    // 如果需要可以在这里更改路径，或做其他每日循环的动作
}
