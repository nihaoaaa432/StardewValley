#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "proj.win32/constant.h"
USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //��ʼ��ʧ�ܷ���false
    if ( !Scene::init() )
    {
        return false;
    }
    //��ȡ��Ϸ�Ĵ��ڴ�С
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //��ȡ��Ļ��ԭ��λ�ã������½����꣬ͨ���ǣ�0,0��
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("StartScene.jpg");
    Size originalSize = background->getContentSize(); // ͼƬ��ԭʼ��С
    Size targetSize = Size(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT); // Ŀ���С

    // �������ű���
    float scaleX = targetSize.width / originalSize.width;
    float scaleY = targetSize.height / originalSize.height;

    // �������ű���
    background->setScale(scaleX, scaleY);
    background->setPosition(origin.x+ visibleSize.width / 2, origin.y+ visibleSize.height / 2);

    this->addChild(background, 0);
    auto sprite = Sprite::create("begin.png");
    if (sprite == nullptr)
    {
        problemLoading("'begin.png'");
    }
    else
    {
        sprite->setScale(0.75);
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height*3/4 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }
    //auto button = MenuItemImage::create("CreateANewRole",)
    //auto startNode = Menu::create()
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
