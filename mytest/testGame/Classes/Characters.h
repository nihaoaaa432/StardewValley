#include "cocos2d.h"
#include <string>
#ifndef CHARACTER_H
#define CHARACTER_H

class Character : public cocos2d::Node
{
public:
    // ����һ���µ�Characterʵ��
    static Character* create(const std::string& filePath);
    //�ж��Ƿ�������ż���
    bool isWKeyPressed = false;
    // ��ʼ������
    bool init(const std::string& filePath);

    // ��ɫ�ƶ�����
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    // ���ý�ɫλ��
    void setPosition(float x, float y);

    // ���̼����ص�
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

protected:
    // ��ɫ����
    cocos2d::Sprite* _characterSprite;
};

#endif // CHARACTER_H