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
    //初始化失败返回false
    if ( !Scene::init() )
    {
        return false;
    }
    //获取游戏的窗口大小
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //获取屏幕的原点位置，即左下角坐标，通常是（0,0）
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("StartScene.jpg");
    Size originalSize = background->getContentSize(); // 图片的原始大小
    Size targetSize = Size(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT); // 目标大小

    // 计算缩放比例
    float scaleX = targetSize.width / originalSize.width;
    float scaleY = targetSize.height / originalSize.height;

    // 设置缩放比例
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
