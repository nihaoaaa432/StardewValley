#include "cocos2d.h"
#include <string>
#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public cocos2d::Node
{
public:
    // 创建一个新的Character实例
    static Character* create(const std::string& filePath);
    //判断是否持续按着键盘
    bool isWKeyPressed = false;
    // 初始化函数
    bool init(const std::string& filePath);

    // 角色移动函数
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // 设置角色位置
    void setPosition(float x, float y);

    // 键盘监听回调
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

protected:
    // 角色精灵
    cocos2d::Sprite* _characterSprite;
};

#endif // CHARACTER_H