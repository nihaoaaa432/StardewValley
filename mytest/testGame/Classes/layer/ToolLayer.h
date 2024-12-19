#ifndef ToolLayer_h
#define ToolLayer_h

#include "cocos2d.h"
#include "ui/CocosGUI.h"

class ToolLayer : public cocos2d::Layer {
public:
    // 获取单例实例
    static ToolLayer* getInstance();

    // 初始化工具栏
    void initToolBar(const std::vector<std::string>& toolImages); // 传入工具图片列表

    // 切换工具
    void switchTool(int index);

    // 更新背包界面位置
    void updatePosition(cocos2d::Vec2 position);

private:
    // 构造函数和析构函数私有化，防止外部创建实例
    ToolLayer();
    ~ToolLayer();

    // 工具栏槽位
    std::vector<cocos2d::ui::Button*> toolSlots;
    // 当前选中的工具索引
    int currentToolIndex = 0;

    // 显示当前工具索引的标签
    cocos2d::Label* currentToolLabel = nullptr;


    // 键盘事件处理
    void onKeyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);

    // 工具槽点击事件处理
    void onToolSlotClicked(Ref* sender);

    // 工具槽拖拽事件处理
    bool onToolSlotDragStart(cocos2d::Touch* touch, cocos2d::Event* event); // 返回 bool
    void onToolSlotDragMove(cocos2d::Touch* touch, cocos2d::Event* event);
    void onToolSlotDragEnd(cocos2d::Touch* touch, cocos2d::Event* event);

    // 单例实例
    static ToolLayer* instance;

    // 重写 init 方法
    virtual bool init() override;
};

#endif /* ToolLayer_h */