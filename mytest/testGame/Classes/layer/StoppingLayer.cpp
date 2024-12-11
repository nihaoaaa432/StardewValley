#include "StoppingLayer.h"
#include "cocos2d.h"
USING_NS_CC;

// ��ͣ�㴴������
StoppingLayer* StoppingLayer::createLayer() {
    auto layer = new StoppingLayer();
    if (layer && layer->init()) {
        layer->autorelease();
        return layer;
    }
    else {
        delete layer;
        return nullptr;
    }
}

// ��ʼ������
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

    // ���ð�ť
    settingButton = ui::Button::create("sand.png", "sand.png");
    settingButton->setContentSize(Size(30, 20));
    settingButton->setPosition(Vec2(visibleSize.width / 2 + origin.x-60, visibleSize.height / 2 + origin.y-20));
    settingButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onSettingButton, this));
    this->addChild(settingButton,2);

    // �˳���ť
    quitButton = ui::Button::create("Quit.png", "Quit.png");
    quitButton->setContentSize(Size(30, 20));
    quitButton->setPosition(Vec2(visibleSize.width / 2 + origin.x+60, visibleSize.height / 2 + origin.y-20));
    quitButton->addClickEventListener(CC_CALLBACK_1(StoppingLayer::onQuitButton, this));
    this->addChild(quitButton,2);

    // ע������¼�������
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(StoppingLayer::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


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