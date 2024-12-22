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
    // 创建 John NPC 实例
    static John* create(const std::string& filename);

    // 初始化 John 特有的属性
    virtual bool init(const std::string& filename) override;

    // 更新 John 的状态，覆盖基类的 update 函数
    virtual void update(float deltaTime) override;

    // 设置移动路径
    void setPath(const std::vector<Vec2>& path) { _path = path; }

    // 设置移动速度
    void setSpeed(float speed) { _speed = speed; }

    // 设置是否处于与玩家的对话中
    void setTalking(bool talking) { _isTalking = talking; }

    // 可以添加 John 独有的行为
    void customBehavior(float deltaTime);

    // 重置路径和相关属性（每天重置）
    void resetDailyMovement();

private:
    bool _isTalking = false;  // 是否与玩家对话
    bool _isMoving = true;     // 是否允许移动
    std::vector<Vec2> _path;  // John 的移动路径
    float _speed = 100.0f;     // 移动速度
    size_t _currentPathIndex = 0; // 当前路径的索引
};

#endif // __JOHN_H__
