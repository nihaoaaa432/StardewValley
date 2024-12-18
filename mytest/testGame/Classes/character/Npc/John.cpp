#include "John.h"
#include "character/Player.h"
#include "DialogSystem.h"

John* John::create(const std::string& filename) {
    John* john = new John();
    if (john && john->init(filename)) {
        john->autorelease();  // ʹ���Զ��ͷ�
        return john;
    }
    else {
        delete john;
        return nullptr;
    }
}

bool John::init(const std::string& filename) {
    // ���û��� NPC �� init ��������ʼ�� NPC���������ͼƬ�ȣ�
    if (!NPC::init(filename)) {
        return false;
    }

    // ��ʼ�� John ���е�����
    _isTalking = false;  // Ĭ�ϲ�����ҶԻ�
    return true;
}

void John::update(float deltaTime) {
    // ���û���� update ������ִ�л����ĸ��¹��ܣ�
    NPC::update(deltaTime);

    // ִ�� John ���е���Ϊ
    customBehavior(deltaTime);
}

void John::customBehavior(float deltaTime) {
    // ��ȡ���ʵ��
    auto player = Player::getInstance();

    // �������ҵľ��룬�����Ƿ�ʼ�Ի�
    float distance = this->getPosition().distance(player->getPosition());
    if (distance <= 50.0f && !_isTalking) {
        _isTalking = true;

        // �����Ի���ϵͳ����ʾ�Ի�����
        DialogSystem::getInstance()->showDialogWithChoices(
            "John: Hello, Player! What do you want to do?",
            { "Ask about the town", "Ask for a quest", "Goodbye" },
            [this](int choice) {
                // ������ҵ�ѡ�񣬸��¶Ի�����
                switch (choice) {
                case 0:
                    DialogSystem::getInstance()->updateDialogText("John: The town is beautiful.");
                    break;
                case 1:
                    DialogSystem::getInstance()->updateDialogText("John: I have a quest for you!");
                    break;
                case 2:
                    DialogSystem::getInstance()->hideDialog(); // �����Ի�
                    break;
                default:
                    break;
                }
            });
    }
    else if (distance > 50.0f && _isTalking) {
        // ���Զ�� NPC ʱ�������Ի�
        _isTalking = false;
        DialogSystem::getInstance()->hideDialog();
    }
}
