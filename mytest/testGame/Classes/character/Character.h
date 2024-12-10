#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include "cocos2d.h"


class Character : public cocos2d::Node { // 继承自 Node
protected:
    cocos2d::Sprite* sprite;//图像显示
    cocos2d::Label* nameLabel;//名称显示

public:
    static Character* createWithAttributes(const char* imagePath, const char* name);

    // 初始化角色，加载纹理和帧,科技城
    virtual bool initWithAttributes(const char* imagePath, const char* name);

    //// 播放动画
    //void playAnimation(int startRow, int startCol, int frameCount, float frameDelay);

    //// 更新角色（子类可重写）
    //virtual void update(float dt);
};

#endif // _CHARACTER_H_
