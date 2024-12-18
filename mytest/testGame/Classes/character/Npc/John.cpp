#include "John.h"
#include "character/Player.h"
#include "DialogSystem.h"

John* John::create(const std::string& filename) {
    John* john = new John();
    if (john && john->init(filename)) {
        john->autorelease();  // 使用自动释放
        return john;
    }
    else {
        delete john;
        return nullptr;
    }
}

bool John::init(const std::string& filename) {
    // 调用基类 NPC 的 init 函数来初始化 NPC（例如加载图片等）
    if (!NPC::init(filename)) {
        return false;
    }

    // 初始化 John 特有的属性
    _isTalking = false;  // 默认不与玩家对话
    return true;
}

void John::update(float deltaTime) {
    // 调用基类的 update 函数（执行基础的更新功能）
    NPC::update(deltaTime);

    // 执行 John 独有的行为
    customBehavior(deltaTime);
}

void John::customBehavior(float deltaTime) {
    // 获取玩家实例
    auto player = Player::getInstance();

    // 检查与玩家的距离，决定是否开始对话
    float distance = this->getPosition().distance(player->getPosition());
    if (distance <= 50.0f && !_isTalking) {
        _isTalking = true;

        // 启动对话框系统并显示对话内容
        DialogSystem::getInstance()->showDialogWithChoices(
            "John: Hello, Player! What do you want to do?",
            { "Ask about the town", "Ask for a quest", "Goodbye" },
            [this](int choice) {
                // 根据玩家的选择，更新对话内容
                switch (choice) {
                case 0:
                    DialogSystem::getInstance()->updateDialogText("John: The town is beautiful.");
                    break;
                case 1:
                    DialogSystem::getInstance()->updateDialogText("John: I have a quest for you!");
                    break;
                case 2:
                    DialogSystem::getInstance()->hideDialog(); // 结束对话
                    break;
                default:
                    break;
                }
            });
    }
    else if (distance > 50.0f && _isTalking) {
        // 玩家远离 NPC 时，结束对话
        _isTalking = false;
        DialogSystem::getInstance()->hideDialog();
    }
}
