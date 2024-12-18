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
    background->setScale(0.5);
    background->setPosition(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y);
    this->addChild(background, 1);

    // ���ð�ť
    auto settingButton = ui::Button::create("sand.png", "sand.png");
    settingButton->setContentSize(Size(30, 20));
    settingButton->setPosition(Vec2(visibleSize.width / 2 + origin.x - 60, visibleSize.height / 2 + origin.y - 20));
    settingButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onSettingButton, this));
    this->addChild(settingButton, 2);

    // �˳���ť
    auto quitButton = ui::Button::create("Quit.png", "Quit.png");
    quitButton->setScale(0.4f);
    quitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x + 150, visibleSize.height / 2 + origin.y - 80));
    quitButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onQuitButton, this));
    this->addChild(quitButton, 2);

    // ע������¼�������
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(StoppingLayer::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

// ������ͣ����λ��
void StoppingLayer::updatePosition(cocos2d::Vec2 position) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto backpackSize = this->getContentSize(); // ���豳��������getContentSize()����
    position = position - Vec2(backpackSize.width / 2, backpackSize.height / 2);
    this->setPosition(position);
};

// ��Ӧ���ð�ť����¼�
void StoppingLayer::onSettingButton(cocos2d::Ref* sender) {
    // �л������ó���
    auto settingScene = Scene::create();
    Director::getInstance()->replaceScene(settingScene);
}

// ��Ӧ�˳���ť����¼�
void StoppingLayer::onQuitButton(cocos2d::Ref* sender) {
    // �˳���Ϸ
    Director::getInstance()->end();
}

// ��Ӧ�����¼�
void StoppingLayer::onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event) {
    if (keyCode == EventKeyboard::KeyCode::KEY_ESCAPE) {
        currentPage = (currentPage == 0) ? 1 : 0; // �л���ǰҳ������
        this->setVisible(currentPage == 1); // ���ݵ�ǰҳ��������ʾ������
    }
}