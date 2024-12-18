#ifndef __DIALOG_SYSTEM_H__
#define __DIALOG_SYSTEM_H__

#include "cocos2d.h"
#include <vector>
#include <string>
#include <functional>

class DialogSystem : public cocos2d::Node {
public:
    static DialogSystem* getInstance();
    static void destroyInstance();

    bool init();
    void showDialog(const std::string& message);
    void showDialogWithChoices(const std::string& message,
        const std::vector<std::string>& choices,
        std::function<void(int)> onChoiceSelected);
    void hideDialog();
    void updateDialogText(const std::string& message);

    ~DialogSystem();

private:
    DialogSystem();

    bool _isDialogVisible;
    cocos2d::Label* _dialogLabel;
    cocos2d::Menu* _choicesMenu;
    cocos2d::LayerColor* _dialogBackground; // ¶Ô»°¿ò±³¾°

    static DialogSystem* _instance;
};

#endif // __DIALOG_SYSTEM_H__
