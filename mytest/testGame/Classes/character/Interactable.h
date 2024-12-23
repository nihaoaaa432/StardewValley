#ifndef _INTERACTABLE_H_
#define _INTERACTABLE_H_

#include "cocos2d.h"
#include "Player.h"

class Interactable:public cocos2d::Node {
    friend class Player;
public:
    Interactable() {}
protected:
    virtual ~Interactable() {};

    // �ж��Ƿ񱻵����
    virtual bool isInteracted(const cocos2d::Vec2& clickPosition) = 0;

    // ִ�н�����Ϊ
    virtual bool interact(Player* player) = 0;
};
#endif //_INTERACTABLE_H_
