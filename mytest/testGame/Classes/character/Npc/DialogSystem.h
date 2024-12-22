#ifndef __DIALOG_SYSTEM_H__
#define __DIALOG_SYSTEM_H__

#include "cocos2d.h"

class DialogSystem : public cocos2d::Node {
public:
    // 获取 DialogSystem 的单例实例
    static DialogSystem* getInstance();

    // 启动对话框
    void startDialog(const std::string& dialogText);

    // 结束对话框
    void endDialog();

    // 更新对话框文本
    void updateDialog(const std::string& dialogText);

    // 销毁实例（如果需要）
    static void destroyInstance();

    // 构造函数
    DialogSystem();

    // 析构函数
    ~DialogSystem();

private:
    // 显示或隐藏对话框
    void showDialog(bool show);

    // 对话框背景
    cocos2d::Sprite* _dialogBox;

    // 对话框文本标签
    cocos2d::Label* _dialogLabel;

    // 是否激活对话框
    bool _isDialogActive;

    // 单例实例
    static DialogSystem* instance;
};

#endif // __DIALOG_SYSTEM_H__
