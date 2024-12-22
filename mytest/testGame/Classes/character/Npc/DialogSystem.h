#ifndef __DIALOG_SYSTEM_H__
#define __DIALOG_SYSTEM_H__

#include "cocos2d.h"

class DialogSystem : public cocos2d::Node {
public:
    // ��ȡ DialogSystem �ĵ���ʵ��
    static DialogSystem* getInstance();

    // �����Ի���
    void startDialog(const std::string& dialogText);

    // �����Ի���
    void endDialog();

    // ���¶Ի����ı�
    void updateDialog(const std::string& dialogText);

    // ����ʵ���������Ҫ��
    static void destroyInstance();

    // ���캯��
    DialogSystem();

    // ��������
    ~DialogSystem();

private:
    // ��ʾ�����ضԻ���
    void showDialog(bool show);

    // �Ի��򱳾�
    cocos2d::Sprite* _dialogBox;

    // �Ի����ı���ǩ
    cocos2d::Label* _dialogLabel;

    // �Ƿ񼤻�Ի���
    bool _isDialogActive;

    // ����ʵ��
    static DialogSystem* instance;
};

#endif // __DIALOG_SYSTEM_H__
