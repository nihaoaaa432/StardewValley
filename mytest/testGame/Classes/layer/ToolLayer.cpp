#include "ToolLayer.h"

USING_NS_CC;

// 初始化单例实例
ToolLayer* ToolLayer::instance = nullptr;

ToolLayer* ToolLayer::getInstance() {
    if (!instance) {
        instance = new ToolLayer();
        if (instance && instance->init()) {
            // 初始化工具栏时需要传入工具图片列表
        }
        else {
            CC_SAFE_DELETE(instance);
            instance = nullptr;
        }
    }
    return instance;
}

ToolLayer::ToolLayer() {
    // 私有构造函数
}

ToolLayer::~ToolLayer() {
    // 私有析构函数
}

bool ToolLayer::init() {
    // 调用父类的 init 方法
    if (!Layer::init()) {
        return false;
    }

    // 创建显示当前工具索引的标签
    currentToolLabel = Label::createWithSystemFont("Current Tool: 1", "Arial", 24);
    currentToolLabel->setPosition(Vec2(Director::getInstance()->getVisibleSize().width / 2, 155));
    this->addChild(currentToolLabel);

    // 监听键盘事件
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = CC_CALLBACK_2(ToolLayer::onKeyPressed, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

void ToolLayer::initToolBar(const std::vector<std::string>& toolImages) {
    // 创建工具栏容器
    auto toolLayout = ui::Layout::create();
    toolLayout->setContentSize(Size(Director::getInstance()->getVisibleSize().width, 100));
    toolLayout->setPosition(Vec2(0, 0));

    // 添加背景图
    auto backgroundSprite = Sprite::create("ToolLayer.png"); // 背景图
    backgroundSprite->setPosition(Vec2(toolLayout->getContentSize().width / 2, toolLayout->getContentSize().height / 2+25));
    toolLayout->addChild(backgroundSprite, -1); // 将背景图添加到工具栏容器的最底层

    //// 设置背景颜色（可选）
    //toolLayout->setBackGroundColor(Color3B::GRAY);
    //toolLayout->setBackGroundColorType(ui::Layout::BackGroundColorType::SOLID);

    this->addChild(toolLayout);

    // 根据工具数量动态创建工具槽
    int toolCount = toolImages.size();
    for (int i = 0; i < toolCount; ++i) {
        auto toolSlot = ui::Button::create(); // 工具槽背景图片
        toolSlot->setContentSize(Size(40, 40));
        toolSlot->setPosition(Vec2(262+ i * 75, 30)); // 工具槽位置
        toolLayout->addChild(toolSlot);

        // 添加工具图片
        auto toolSprite = Sprite::create(toolImages[i]);
        toolSprite->setPosition(Vec2(40, 40)); // 工具图片在槽中的位置
        toolSlot->addChild(toolSprite);

        // 保存工具槽
        toolSlots.push_back(toolSlot);

        // 绑定工具槽点击事件
        toolSlot->addClickEventListener([this, i](Ref* sender) {
            this->switchTool(i);
            });

        // 绑定工具槽拖拽事件
        auto touchListener = EventListenerTouchOneByOne::create();
        touchListener->onTouchBegan = CC_CALLBACK_2(ToolLayer::onToolSlotDragStart, this); // 使用 CC_CALLBACK_2
        touchListener->onTouchMoved = CC_CALLBACK_2(ToolLayer::onToolSlotDragMove, this);
        touchListener->onTouchEnded = CC_CALLBACK_2(ToolLayer::onToolSlotDragEnd, this);
        _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, toolSlot);
    }

    // 默认选中第一个工具
    if (toolCount > 0) {
        switchTool(0);
    }
}

void ToolLayer::switchTool(int index) {
    if (index < 0 || index >= toolSlots.size()) {
        return;
    }

    // 更新当前选中的工具索引
    currentToolIndex = index;

    // 更新UI显示（例如高亮当前选中的工具槽）
    for (int i = 0; i < toolSlots.size(); ++i) {
        if (i == currentToolIndex) {
            toolSlots[i]->setColor(Color3B::YELLOW); // 高亮选中工具槽
        }
        else {
            toolSlots[i]->setColor(Color3B::WHITE); // 恢复其他工具槽颜色
        }
    }

    // 更新标签显示当前选中的工具索引
    currentToolLabel->setString("Current Tool: " + std::to_string(currentToolIndex + 1));


    // 打印当前选中的工具
    CCLOG("Selected tool: %d", currentToolIndex + 1);
}

void ToolLayer::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event) {
    // 判断按下的数字键
    if (keyCode >= EventKeyboard::KeyCode::KEY_1 && keyCode <= EventKeyboard::KeyCode::KEY_9) {
        int index = static_cast<int>(keyCode) - 49; // 计算工具索引
        if (index < toolSlots.size()) {
            switchTool(index);
        }
    }
}

void ToolLayer::onToolSlotClicked(Ref* sender) {
    auto button = static_cast<ui::Button*>(sender);
    for (int i = 0; i < toolSlots.size(); ++i) {
        if (toolSlots[i] == button) {
            switchTool(i);
            break;
        }
    }
}

bool ToolLayer::onToolSlotDragStart(Touch* touch, Event* event) {
    auto target = static_cast<ui::Button*>(event->getCurrentTarget());
    auto touchPoint = touch->getLocation();

    // 检查触摸点是否在工具槽内
    if (target->getBoundingBox().containsPoint(touchPoint)) {
        target->setColor(Color3B::GREEN); // 拖拽开始时高亮工具槽
        return true; // 返回 true 表示继续处理后续的拖拽事件
    }

    return false; // 返回 false 表示不处理后续的拖拽事件
}

void ToolLayer::onToolSlotDragMove(Touch* touch, Event* event) {
    auto target = static_cast<ui::Button*>(event->getCurrentTarget());
    auto touchPoint = touch->getLocation();
    target->setPosition(target->getPosition() + touch->getDelta());
}

void ToolLayer::onToolSlotDragEnd(Touch* touch, Event* event) {
    auto target = static_cast<ui::Button*>(event->getCurrentTarget());
    auto touchPoint = touch->getLocation();
    target->setColor(Color3B::WHITE); // 拖拽结束时恢复工具槽颜色

    // 检查是否拖拽到其他工具槽
    for (int i = 0; i < toolSlots.size(); ++i) {
        if (toolSlots[i] != target && toolSlots[i]->getBoundingBox().containsPoint(touchPoint)) {
            // 交换工具槽的位置
            auto tempPos = target->getPosition();
            target->setPosition(toolSlots[i]->getPosition());
            toolSlots[i]->setPosition(tempPos);

            // 交换工具槽的索引
            std::swap(toolSlots[currentToolIndex], toolSlots[i]);
            break;
        }
    }
}

// 更新背包界面位置
void ToolLayer::updatePosition(cocos2d::Vec2 position) {
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto backpackSize = this->getContentSize(); // 假设背包界面有getContentSize()方法
    position = position - Vec2(backpackSize.width / 2, backpackSize.height / 2);
    this->setPosition(position);
};