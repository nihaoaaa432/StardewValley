#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "MapScene.h"
#include "TownScene.h"
USING_NS_CC;
std::string playerName = "";
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
    if (!Scene::init())
    {
        return false;
    }


    //创建背景
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
    background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);

    this->addChild(background, 0);

    //添加艺术字
    auto sprite = Sprite::create("begin.png");
    if (sprite == nullptr)
    {
        problemLoading("begin.png");
    }
    else
    {
        sprite->setScale(0.75);
        // position the sprite on the center of the screen
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 3 / 4 + origin.y));

        // add the sprite as a child to this layer
        this->addChild(sprite, 0);
    }

    // 创建文本框
    auto textField = cocos2d::ui::TextField::create(u8"请输入您的游戏昵称", "../Resources/fonts/DingDingJinBuTi.ttf", TEXT_SIZE);
    textField->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2));
    textField->setMaxLength(6);
    textField->setMaxLengthEnabled(true);
    textField->setTextColor(cocos2d::Color4B(0, 32, 96, 255));
    this->addChild(textField);
    // 创建标签
    auto promptLabel = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", TEXT_SIZE);
    promptLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
    promptLabel->setTextColor(cocos2d::Color4B(COLOR_RED, COLOR_GREEN, COLOR_BLUE, ALPHA));
    this->addChild(promptLabel);

    // 为文本框添加事件监听器
    textField->addEventListener([promptLabel](Ref* sender, cocos2d::ui::TextField::EventType type) {
        // 使用 Lambda 表达式为文本框添加事件监听器。Lambda 表达式捕获了外部的 promptLabel 对象，这样可以在事件处理中修改这个标签的内容。
        // Lambda 表达式会处理两种事件类型：文本插入（INSERT_TEXT）和文本删除（DELETE_BACKWARD）。

        if (type == cocos2d::ui::TextField::EventType::INSERT_TEXT || type == cocos2d::ui::TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<cocos2d::ui::TextField*>(sender);
            std::string nickname = textField->getString();
            std::string text = u8"欢迎来到星露谷物语！" + nickname;
            promptLabel->setString(text);
        }
        });

    //创建按钮
    auto startButton = ui::Button::create("CreateANewRole.png", "CreateANewRoleSelect.png");
    float stratButtonX = targetSize.width / originalSize.width;
    float stratButtonY = targetSize.height / originalSize.height;

    // 设置缩放比例和位置
    startButton->setScale(stratButtonX, stratButtonY);
    startButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5));
    this->addChild(startButton);

    // 创建标签
    auto nameLabel = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", TEXT_SIZE);
    nameLabel->setPosition(stratButtonX, stratButtonY + 50);
    nameLabel->setVisible(false);
    nameLabel->setTextColor(cocos2d::Color4B(COLOR_RED, COLOR_GREEN, COLOR_BLUE, ALPHA));

    // 为按钮添加事件
    startButton->addClickEventListener([this,nameLabel,textField](Ref* sender) {
        std::string nickname = textField->getString();
        if (nickname.empty()) {
            nameLabel->setString(u8"游戏昵称不能为空");
            nameLabel->setVisible(true);
            this->scheduleOnce([nameLabel](float dt) {
                nameLabel->setVisible(false);
                }, 1.5, "HideEmptyPromptLabel");
        }
        else {

            playerName = nickname;
            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.3, MapScene::createScene(), cocos2d::Color3B::WHITE));
        }
        });
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
