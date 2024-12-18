#ifndef __JOHN_H__
#define __JOHN_H__

#include "NPC.h"
#include "cocos2d.h"

using namespace cocos2d;

class John : public NPC {
public:
    // 创建 John NPC 实例
    static John* create(const std::string& filename);

    // 初始化 John 特有的属性
    virtual bool init(const std::string& filename) override;

    // 更新 John 的状态，覆盖基类的 update 函数
    virtual void update(float deltaTime) override;

    // 可以添加 John 独有的行为
    void customBehavior(float deltaTime);

private:
    // John 特有的属性，例如与玩家的互动等
    bool _isTalking;  // 是否在与玩家对话
};

#endif // __JOHN_H__
