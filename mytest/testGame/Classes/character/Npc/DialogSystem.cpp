#include "DialogSystem.h"
#include "cocos2d.h"
#include "character/Player.h"
// 静态实例
DialogSystem* DialogSystem::instance = nullptr;

DialogSystem* DialogSystem::getInstance() {
    if (!instance) {
        instance = new DialogSystem();  // 如果实例不存在，创建一个新的实例
    }
    return instance;
}

DialogSystem::DialogSystem()
    : _isDialogActive(false) {
    // 获取屏幕的可见区域大小
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    // 初始化对话框背景（Sprite）
    _dialogBox = cocos2d::Sprite::create("npc/Dialog.png");
    _dialogBox->setAnchorPoint(cocos2d::Vec2(0, 0));
    _dialogBox->setPosition(cocos2d::Vec2(Player::getInstance()->getPosition().x-visibleSize.width/2, Player::getInstance()->getPosition().y-visibleSize.height/2));

    //对话框的位置是相对于地图的
    _dialogBox->setContentSize(cocos2d::Size(visibleSize.width,100));  // 调整背景框的宽度和高度
    this->addChild(_dialogBox);

    // 创建对话框文本标签
    _dialogLabel = cocos2d::Label::createWithTTF("", "fonts/DingDingJinBuTi.ttf", 24);
    _dialogLabel->setAnchorPoint(cocos2d::Vec2(0, 0));
    _dialogLabel->setPosition(_dialogBox->getPosition());

    _dialogLabel->setDimensions(500, 100);  // 控制文本框的大小
    _dialogLabel->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
    _dialogLabel->setTextColor(cocos2d::Color4B::BLACK);
    this->addChild(_dialogLabel);

    // 隐藏对话框
    _dialogBox->setVisible(false);
    _dialogLabel->setVisible(false);
}

DialogSystem::~DialogSystem() {
    // 销毁时进行清理
    if (_dialogBox) {
        _dialogBox->release();
    }
    if (_dialogLabel) {
        _dialogLabel->release();
    }
}

void DialogSystem::startDialog(const std::string& dialogText) {
    showDialog(true);
    updateDialog(dialogText);
}

void DialogSystem::endDialog() {
    showDialog(false);
}

void DialogSystem::updateDialog(const std::string& dialogText) {
    if (_isDialogActive) {
        _dialogLabel->setString(dialogText);
    }
}

void DialogSystem::showDialog(bool show) {
    _isDialogActive = show;
    _dialogBox->setVisible(show);
    _dialogLabel->setVisible(show);
}

void DialogSystem::destroyInstance() {
    if (instance) {
        instance->release();  // 释放资源
        instance = nullptr;   // 重置实例
    }
}
