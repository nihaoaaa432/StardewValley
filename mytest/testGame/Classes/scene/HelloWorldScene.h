#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#define NameOfGame u8"��¶������"

//�ֱ���
#define DESIGN_RESOLUTION_WIDTH 1280
#define DESIGN_RESOLUTION_HEIGHT 720
#define SMALL_RESOLUTION_WIDTH 480
#define SMALL_RESOLUTION_HIGHT 320
#define NEDIUM_RESOLUTION_WIDTH 1024
#define NEDIUM_RESOLUTION_HEIGHT 768
#define LARGE_RESOLUTION_WIDTH 2048
#define LARGE_RESOLUTION_HEIGHT 1536

//����
#define TEXT_SIZE 30
#define COLOR_RED 0
#define COLOR_GREEN 32
#define COLOR_BLUE 96
#define ALPHA 255


class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    //ͨ����дinit�������г�ʼ��
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
