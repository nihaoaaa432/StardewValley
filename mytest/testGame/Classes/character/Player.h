#ifndef _PLAYER_H_
#define _PLAYER_H_

class Interactable;//只做前向声明

#include "cocos2d.h"
#include <vector>

//玩家初始化数据
#define INIT_PLAYER_HEALTH  100
#define INIT_PLAYER_MONEY  0
#define INIT_PLAYER_SPEED 500.0f

//继承自Character的Player类
class Player :public cocos2d::Node {
public:

	static Player* getInstance();//获取单例指针

	static void destroyInstance();//销毁单例指针

	//静态创建工厂
	static Player* create();

	//重写的初始化函数
	bool init();

	//void onEnter()override;//进入场景时注册键盘监听器

	//void onExit()override;//推出场景是注销键盘监听器

	//void registerKeyboardEvent();//注册键盘事件

	void moveInDirection(const cocos2d::Vec2& direction);//移动

	void stopMoving();//停止移动

	//void update(float delta)override;//每帧更新，连续移动

	void openInventory();//打开背包

	void closeInventory();//关闭背包

	void loadAnimations();//预加载所有动画

	void showHint(const std::string& message);//显示提示，例如收获提示

	cocos2d::Animate* createWalkAnimation(const std::string& direction);//创建行走动画

	cocos2d::Animate* createIdleAnimation(const std::string& direction);//创建站立动画

	void playWalkAnimation(const std::string& direciton);//播放行走动画

	void playIdleAnimation(const std::string& direciton);//站立

	void stopAnimation();

	float getSpeed();

	cocos2d::Vec2& getMoveDirection();//获取移动方向
	void setIsTalking(bool talking);

	bool interactWithClickPosition(const cocos2d::Vec2& clickPosition, std::vector< Interactable* >& interacts);//与点击位置交互
private:
	static Player* _instance;//静态单例指针

	cocos2d::Sprite* sprite;

	//基本移动相关
	bool isMoving;//是否在移动
	bool isInventoryOpen;//背包是否打开
	float speed;//移动速度
	cocos2d::Vec2 moveDirection;//移动方向
	//cocos2d::EventListenerKeyboard* keyboardListener;//键盘事件监听器
	bool isTalking;
	//动画相关
	std::string lastDirection;//最后的移动方向，用于选择站立动画；
	std::map<std::string, cocos2d::Animate*> Animations;//存储动画
	cocos2d::Animate* currentAnimation;//当前动画
	cocos2d::Action* currentAction;//当前动作
	std::string name;
};

#endif  //_PLAYER_H_


