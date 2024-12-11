#ifndef _CHANGERS_H_
#define _CHANGERS_H_

#include "cocos2d.h"


class Changers : public cocos2d::Node { // 继承自 Node
protected:
    cocos2d::Sprite* sprite;//图像显示
    cocos2d::Label* nameLabel;//名称显示
    cocos2d::Animate* currentAnimation;//当前动画
    cocos2d::Action* currentAction;//当前动作
    std::map<std::string, cocos2d::Animate*> walkAnimations;//存储动画

public:
    static Changers* createWithAttributes(const std::string& atlas, const std::string& name);

    // 初始化角色，加载纹理和帧,科技城
    virtual bool initWithAttributes(const std::string& atlas, const std::string& name);

    //装载所有动画
    virtual void loadAnimations();

    //停止当前动画
    virtual void stopCurrentAnimation();

    //// 播放动画
    //void playAnimation(int startRow, int startCol, int frameCount, float frameDelay);

    //// 更新角色（子类可重写）
    //virtual void update(float dt);
};

#endif // _CHANGERS_H_
