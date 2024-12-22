#include "DialogSystem.h"
#include "cocos2d.h"
#include "character/Player.h"
// ��̬ʵ��
DialogSystem* DialogSystem::instance = nullptr;

DialogSystem* DialogSystem::getInstance() {
    if (!instance) {
        instance = new DialogSystem();  // ���ʵ�������ڣ�����һ���µ�ʵ��
    }
    return instance;
}

DialogSystem::DialogSystem()
    : _isDialogActive(false) {
    // ��ȡ��Ļ�Ŀɼ������С
    cocos2d::Size visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
    // ��ʼ���Ի��򱳾���Sprite��
    _dialogBox = cocos2d::Sprite::create("npc/Dialog.png");
    _dialogBox->setAnchorPoint(cocos2d::Vec2(0, 0));
    _dialogBox->setPosition(cocos2d::Vec2(Player::getInstance()->getPosition().x-visibleSize.width/2, Player::getInstance()->getPosition().y-visibleSize.height/2));

    //�Ի����λ��������ڵ�ͼ��
    _dialogBox->setContentSize(cocos2d::Size(visibleSize.width,100));  // ����������Ŀ�Ⱥ͸߶�
    this->addChild(_dialogBox);

    // �����Ի����ı���ǩ
    _dialogLabel = cocos2d::Label::createWithTTF("", "fonts/DingDingJinBuTi.ttf", 24);
    _dialogLabel->setAnchorPoint(cocos2d::Vec2(0, 0));
    _dialogLabel->setPosition(_dialogBox->getPosition());

    _dialogLabel->setDimensions(500, 100);  // �����ı���Ĵ�С
    _dialogLabel->setAlignment(cocos2d::TextHAlignment::CENTER, cocos2d::TextVAlignment::CENTER);
    _dialogLabel->setTextColor(cocos2d::Color4B::BLACK);
    this->addChild(_dialogLabel);

    // ���ضԻ���
    _dialogBox->setVisible(false);
    _dialogLabel->setVisible(false);
}

DialogSystem::~DialogSystem() {
    // ����ʱ��������
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
        instance->release();  // �ͷ���Դ
        instance = nullptr;   // ����ʵ��
    }
}
