#include "StoppingLayer.h"
#include "cocos2d.h"
USING_NS_CC;

// ��������ָ���ʼ��Ϊnullptr
StoppingLayer* StoppingLayer::_instance = nullptr;


// ��ȡ��������
StoppingLayer* StoppingLayer::getInstance() {
    if (_instance == nullptr) {
        _instance = new StoppingLayer;
        if (!_instance->init()) {
            delete _instance;
            _instance = nullptr;
            CCLOG("StoppingLayer initialization failed!");
        }
    }
    return _instance;
}


// ��ʼ����������
bool StoppingLayer::init() {
    if (!Layer::init()) {
        return false;
    }

    currentPage = 0; // Ĭ�ϲ���ʾ��ͣ��

    // ��ȡ��Ļ�ߴ�
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();

    // ��ͣ�㱳��
    auto background = Sprite::create("Stopping.png");
    background->setScale(0.7);
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background, 1);

    // �������ý���
    settingLayer = Layer::create();
    this->addChild(settingLayer,3);
    auto settingBackground = Sprite::create("Stopping.png");
    settingBackground->setScale(0.7);
    settingLayer->setVisible(false);
    settingBackground->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    settingLayer->addChild(settingBackground);

    // ���ְ�ť
    auto musicButton = ui::Button::create("MusicButtonOff.png", "MusicButtonOff.png"); // ��ʼΪ�ر�״̬
    musicButton->setScale(1.4f);
    musicButton->setPosition(Vec2(visibleSize.width / 2 + origin.x + 200, visibleSize.height / 2 + origin.y - 100));
    settingLayer->addChild(musicButton);
    musicButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onMusicButton, this));
    // ������ͣ���水ť
    auto backButton = ui::Button::create("BackButton.png", "BackButton.png");
    backButton->setScale(1.4f);
    backButton ->setPosition(Vec2(visibleSize.width / 2 + origin.x - 180, visibleSize.height / 2 + origin.y - 100));
    settingLayer->addChild(backButton);
    backButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onBackButton, this));


    // ���ð�ť
    auto settingButton = ui::Button::create("SettingButton.png", "SettingButton.png");
    settingButton->setScale(1.2f);
    settingButton->setPosition(Vec2(visibleSize.width / 2 + origin.x - 180, visibleSize.height / 2 + origin.y - 100));
    settingButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onSettingButton, this));
    this->addChild(settingButton, 2);

    // �˳���ť
    auto quitButton = ui::Button::create("Quit.png", "Quit.png");
    quitButton->setScale(0.4f);
    quitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x +200, visibleSize.height / 2 + origin.y - 100));
    quitButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onQuitButton, this));
    this->addChild(quitButton, 2);

    return true;
}

// ������ͣ����λ��
void StoppingLayer::updatePosition(cocos2d::Vec2 position) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto backpackSize = this->getContentSize(); 
    position = position - Vec2(backpackSize.width / 2, backpackSize.height / 2);
    this->setPosition(position);
};

// ��Ӧ���ð�ť����¼�
void StoppingLayer::onSettingButton(cocos2d::Ref* sender) {
    // �л������ó���
    if(!settingLayer->isVisible()) settingLayer->setVisible(true);
}

// ��Ӧ�˳���ť����¼�
void StoppingLayer::onQuitButton(cocos2d::Ref* sender) {
    // �˳���Ϸ
    if(!settingLayer->isVisible())   Director::getInstance()->end();
}

// ��Ӧ���ð�ť����¼�
void StoppingLayer::onMusicButton(cocos2d::Ref* sender) {
    // �л���ť��ͼƬ
    auto button = dynamic_cast<ui::Button*>(sender);
    if (button->getNormalFile().file == "MusicButtonOff.png") {
        button->loadTextures("MusicButtonOn.png", "MusicButtonOn.png"); // �л�������״̬
    }
    else {
        button->loadTextures("MusicButtonOff.png", "MusicButtonOff.png"); // �л����ر�״̬
    }
    
}

// ��Ӧ���ð�ť����¼�
void StoppingLayer::onBackButton(cocos2d::Ref* sender) {
    // �ر����ý���
    if (settingLayer->isVisible()) settingLayer->setVisible(false);
}

// ����esc����
void StoppingLayer::onEscPress() {
    if (settingLayer->isVisible())  settingLayer->setVisible(false);
    else  this->setVisible(!this->isVisible());
}