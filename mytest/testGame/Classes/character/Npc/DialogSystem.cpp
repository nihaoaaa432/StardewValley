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

    // ����һ���Ի���ı���
    _dialogBackground = LayerColor::create(Color4B(0, 0, 0, 180)); // ��͸����ɫ����
    _dialogBackground->setContentSize(Size(800, 150)); // ���öԻ����С
    _dialogBackground->setPosition(Vec2(100, 50)); // ����λ�õ���Ļ�ײ�
    this->addChild(_dialogBackground);

    // �����Ի������ֱ�ǩ
    _dialogLabel = Label::createWithSystemFont("", "Arial", 24);
    _dialogLabel->setPosition(Vec2(400, 100)); // ����λ��
    _dialogBackground->addChild(_dialogLabel);

    // ��ʼ��ѡ��˵�
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
        _choicesMenu->setVisible(false); // ����ѡ��˵�
        _isDialogVisible = true;
        this->setVisible(true); // ��ʾ�Ի���
    }
}

void DialogSystem::showDialogWithChoices(const std::string& message,
    const std::vector<std::string>& choices,
    std::function<void(int)> onChoiceSelected) {
    if (!_isDialogVisible) {
        // ���öԻ�����Ϣ
        _dialogLabel->setString(message);
        _dialogLabel->setVisible(true);

        // ���֮ǰ��ѡ��
        _choicesMenu->removeAllChildren();

        // �����µ�ѡ��˵�
        for (size_t i = 0; i < choices.size(); ++i) {
            auto menuItem = MenuItemLabel::create(
                Label::createWithSystemFont(choices[i], "Arial", 20),
                [i, onChoiceSelected](Ref* sender) {
                    onChoiceSelected(i); // ִ��ѡ���Ļص�
                });
            menuItem->setPosition(Vec2(400, 50 - 40 * i)); // ����λ��
            _choicesMenu->addChild(menuItem);
        }

        _choicesMenu->setVisible(true); // ��ʾѡ��˵�
        _isDialogVisible = true;
        this->setVisible(true); // ��ʾ�Ի���
    }
}

void DialogSystem::hideDialog() {
    if (_isDialogVisible) {
        _dialogLabel->setVisible(false);
        _choicesMenu->setVisible(false);
        _isDialogVisible = false;
        this->setVisible(false); // ���ضԻ���
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
