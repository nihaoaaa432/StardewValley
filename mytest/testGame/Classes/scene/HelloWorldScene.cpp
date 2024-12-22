#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include "MapScene.h"
#include "character/Player.h"

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
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto background = Sprite::create("StartScene.jpg");
    Size originalSize = background->getContentSize();
    Size targetSize = Size(DESIGN_RESOLUTION_WIDTH, DESIGN_RESOLUTION_HEIGHT);

    // 计算缩放比例
    float scaleX = targetSize.width / originalSize.width;
    float scaleY = targetSize.height / originalSize.height;

    // 设置缩放比例
    background->setScale(scaleX, scaleY);
    background->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
    this->addChild(background, 0);

    // 添加艺术字
    auto sprite = Sprite::create("begin.png");
    if (sprite == nullptr)
    {
        problemLoading("begin.png");
    }
    else
    {
        sprite->setScale(0.75);
        sprite->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height * 3 / 4 + origin.y));
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
        if (type == cocos2d::ui::TextField::EventType::INSERT_TEXT || type == cocos2d::ui::TextField::EventType::DELETE_BACKWARD) {
            auto textField = dynamic_cast<cocos2d::ui::TextField*>(sender);
            std::string nickname = textField->getString();
            std::string text = u8"欢迎来到星露谷物语！" + nickname;
            promptLabel->setString(text);
        }
        });

    // 创建按钮
    auto startButton = ui::Button::create("CreateANewRole.png", "CreateANewRoleSelect.png");
    float startButtonX = targetSize.width / originalSize.width;
    float startButtonY = targetSize.height / originalSize.height;

    startButton->setScale(startButtonX, startButtonY);
    startButton->setPosition(Vec2(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 5));
    this->addChild(startButton);

    // 创建标签，用于提示昵称为空
    auto nameLabel = Label::createWithTTF("", "../Resources/Fonts/DingDingJinBuTi.ttf", TEXT_SIZE);
    nameLabel->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 5 + 50));
    nameLabel->setVisible(false);
    nameLabel->setTextColor(cocos2d::Color4B(COLOR_RED, COLOR_GREEN, COLOR_BLUE, ALPHA));
    this->addChild(nameLabel);

    // 为按钮添加点击事件
    startButton->addClickEventListener([this, nameLabel, textField](Ref* sender) {
        std::string nickname = textField->getString();

        // 判断昵称是否为空
        if (nickname.empty()) {
            // 显示提示信息
            nameLabel->setString(u8"游戏昵称不能为空");
            nameLabel->setVisible(true);

            // 1.5秒后隐藏提示信息
            this->scheduleOnce([nameLabel](float dt) {
                nameLabel->setVisible(false);
                }, 1.5, "HideEmptyPromptLabel");

            // 禁用按钮，防止重复点击
            auto startButton = dynamic_cast<ui::Button*>(sender);
            startButton->setEnabled(false);

            // 1.5秒后重新启用按钮
            this->scheduleOnce([startButton](float dt) {
                startButton->setEnabled(true);
                }, 1.5, "EnableStartButton");

        }
        else {
            // 若昵称有效，更新玩家姓名并切换场景
            playerName = nickname;
            auto player = Player::getInstance();
           player->setPosition(25 * 16 * RATIO, 25 * 16 * RATIO);
           //player->setPosition(0,0);

            auto mapScene = MapScene::getInstance();
            mapScene->addChild(Player::getInstance());

            cocos2d::Director::getInstance()->replaceScene(cocos2d::TransitionFade::create(0.3, mapScene, cocos2d::Color3B::WHITE));
        }
        });

    return true;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //关闭游戏场景并退出应用
    Director::getInstance()->end();
}
