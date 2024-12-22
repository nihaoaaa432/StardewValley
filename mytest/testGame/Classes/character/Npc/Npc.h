#ifndef __NPC_H__
#define __NPC_H__

#include "cocos2d.h"
#include <vector>
#include <string>

using namespace cocos2d;

class NPC : public Sprite {
public:
    // 创建 NPC 实例
    static NPC* create(const std::string& filename);

    // 初始化 NPC
    virtual bool init(const std::string& filename);

    // 设置 NPC 的路径
    void setPath(const std::vector<Vec2>& path);

    // 更新 NPC 状态（每帧调用）
    virtual void update(float deltaTime);

    // 设置 NPC 移动速度
    void setSpeed(float speed);

    // 判断 NPC 是否在移动
    bool isMoving() const;

protected:
    // NPC 的路径（路径点）
    std::vector<Vec2> _path;

    // 当前目标路径的索引
    int _currentTargetIndex;

    // NPC 是否正在移动
    bool _isMoving;

    // 移动速度
    float _speed;

    // 判断是否到达目标位置
    bool hasReachedTarget() const;

    // 移动到目标点
    void moveToTarget(float deltaTime);
};

#endif // __NPC_H__
