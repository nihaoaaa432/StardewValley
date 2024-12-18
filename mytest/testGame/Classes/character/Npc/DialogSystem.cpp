#include "DialogSystem.h"
#include "cocos2d.h"

using namespace cocos2d;

DialogSystem* DialogSystem::_instance = nullptr;

DialogSystem::DialogSystem()
    : _isDialogVisible(false), _dialogLabel(nullptr), _choicesMenu(nullptr), _dialogBackground(nullptr) {}

DialogSystem* DialogSystem::getInstance() {
    if (_instance == nullptr) {
        _instance = new DialogSystem();
        if (_instance && _instance->init()) {
            _instance->autorelease();
        }
        else {
            delete _instance;
            _instance = nullptr;
        }
    }
    return _instance;
}

void DialogSystem::destroyInstance() {
    if (_instance) {
        _instance->removeFromParent();
        _instance = nullptr;
    }
}

bool DialogSystem::init() {
    if (!Node::init()) {
        return false;
    }

    // 创建一个对话框的背景
    _dialogBackground = LayerColor::create(Color4B(0, 0, 0, 180)); // 半透明黑色背景
    _dialogBackground->setContentSize(Size(800, 150)); // 设置对话框大小
    _dialogBackground->setPosition(Vec2(100, 50)); // 设置位置到屏幕底部
    this->addChild(_dialogBackground);

    // 创建对话框文字标签
    _dialogLabel = Label::createWithSystemFont("", "Arial", 24);
    _dialogLabel->setPosition(Vec2(400, 100)); // 居中位置
    _dialogBackground->addChild(_dialogLabel);

    // 初始化选择菜单
    _choicesMenu = Menu::create();
    _choicesMenu->setPosition(Vec2::ZERO);
    _dialogBackground->addChild(_choicesMenu);

    this->setVisible(false);
    return true;
}

void DialogSystem::showDialog(const std::string& message) {
    if (!_isDialogVisible) {
        _dialogLabel->setString(message);
        _dialogLabel->setVisible(true);
        _choicesMenu->setVisible(false); // 隐藏选择菜单
        _isDialogVisible = true;
        this->setVisible(true); // 显示对话框
    }
}

void DialogSystem::showDialogWithChoices(const std::string& message,
    const std::vector<std::string>& choices,
    std::function<void(int)> onChoiceSelected) {
    if (!_isDialogVisible) {
        // 设置对话框消息
        _dialogLabel->setString(message);
        _dialogLabel->setVisible(true);

        // 清空之前的选择
        _choicesMenu->removeAllChildren();

        // 创建新的选择菜单
        for (size_t i = 0; i < choices.size(); ++i) {
            auto menuItem = MenuItemLabel::create(
                Label::createWithSystemFont(choices[i], "Arial", 20),
                [i, onChoiceSelected](Ref* sender) {
                    onChoiceSelected(i); // 执行选择后的回调
                });
            menuItem->setPosition(Vec2(400, 50 - 40 * i)); // 调整位置
            _choicesMenu->addChild(menuItem);
        }

        _choicesMenu->setVisible(true); // 显示选择菜单
        _isDialogVisible = true;
        this->setVisible(true); // 显示对话框
    }
}

void DialogSystem::hideDialog() {
    if (_isDialogVisible) {
        _dialogLabel->setVisible(false);
        _choicesMenu->setVisible(false);
        _isDialogVisible = false;
        this->setVisible(false); // 隐藏对话框
    }
}

void DialogSystem::updateDialogText(const std::string& message) {
    if (_isDialogVisible) {
        _dialogLabel->setString(message);
    }
}

DialogSystem::~DialogSystem() {
    _instance = nullptr;
}
