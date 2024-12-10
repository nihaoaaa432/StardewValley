#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Character.h"
#include "cocos2d.h"
//
//class Player :public cocos2d::Sprite {
//public:
//	//静态创建函数
//	static Player* create(const char* filename);
//
//	//玩家初始化函数
//	void initPlayer();
//
//    // 更新函数
//    void update(float delta);
//
//    //根据当前方向和速度移动人物
//    void move();
//
//    //设置人物朝向（旋转）
//    void setDirection(const cocos2d::Vec2& d);
//
//
//    // 处理伤害函数
//    void takeDamage(int damage);
//
//    // 获取玩家状态
//    int getHealth() const;
//    int getMoney() const;
//
//    // 增加金钱
//    void addMoney(int amount);
//
//    // 玩家死亡逻辑
//    void die();
//    
//private:
//    // 私有属性
//    int m_health;          // 生命值
//    int m_money;           // 金钱
//    float m_speed;         // 移动速度
//    cocos2d::Vec2 m_direction;      //人物朝向
//    // 私有方法（扩展功能可添加在这里）
//    void initAnimations(); // 初始化玩家动画
//    void initPhysics();    // 初始化物理碰撞体
//
//};

//玩家初始化数据
#define INIT_PLAYER_HEALTH  100
#define INIT_PLAYER_MONEY  0
#define INIT_PLAYER_SPEED 100.0f

//继承自Character的Player类
class Player :public Character {
public:
	//静态创建工厂
	static Player* createWithAttributes(const char* imagePath, const char* name);

	//重写的初始化函数
	bool initWithAttributes(const char* imagePath, const char* name)override;

	void onEnter()override;//进入场景时注册键盘监听器

	void onExit()override;//推出场景是注销键盘监听器

	void registerKeyboardEvent();//注册键盘事件

	void startMoving(const cocos2d::Vec2& direction);//开始移动

	void stopMoving();//停止移动

	void openInventory();//打开背包

	void closeInventory();//关闭背包


private:
	bool isMoving;//是否在移动
	bool isInventoryOpen;//背包是否打开
	float speed;//移动速度
	cocos2d::Vec2 moveDirection;//移动方向
	cocos2d::EventListenerKeyboard* keyboardListener;//键盘事件监听器
};

#endif  //_PLAYER_H_


