#ifndef ToolLayer_h
#define ToolLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ToolLayer : public cocos2d::Layer {
public:
    // ��ȡ����ʵ��
    static ToolLayer* getInstance();

    // ��ʼ��������
    void initToolBar(const std::vector<std::string>& toolImages); // ���빤��ͼƬ�б�

    // �л�����
    void switchTool(int index);

    // ���±�������λ��
    void updatePosition(cocos2d::Vec2 position);

private:
    // ���캯������������˽�л�����ֹ�ⲿ����ʵ��
    ToolLayer();
    ~ToolLayer();

    // ��������λ
    std::vector<cocos2d::ui::Button*> toolSlots;
    // ��ǰѡ�еĹ�������
    int currentToolIndex = 0;

    // ��ʾ��ǰ���������ı�ǩ
    cocos2d::Label* currentToolLabel = nullptr;


    // �����¼�����
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // ���߲۵���¼�����
    void onToolSlotClicked(Ref* sender);

    // ���߲���ק�¼�����
    bool onToolSlotDragStart(cocos2d::Touch* touch, cocos2d::Event* event); // ���� bool
    void onToolSlotDragMove(cocos2d::Touch* touch, cocos2d::Event* event);
    void onToolSlotDragEnd(cocos2d::Touch* touch, cocos2d::Event* event);

    // ����ʵ��
    static ToolLayer* instance;

    // ��д init ����
    virtual bool init() override;
};

#endif /* ToolLayer_h */