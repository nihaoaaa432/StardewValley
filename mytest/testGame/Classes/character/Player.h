#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "cocos2d.h"
#include "cstring"

//��ҳ�ʼ������
#define INIT_PLAYER_HEALTH  100
#define INIT_PLAYER_MONEY  0
#define INIT_PLAYER_SPEED 500.0f

//�̳���Character��Player��
class Player :public cocos2d::Node {
public:

	static Player* getInstance();//��ȡ����ָ��

	static void destroyInstance();//���ٵ���ָ��

	//��̬��������
	static Player* create();

	//��д�ĳ�ʼ������
	bool init();

	//void onEnter()override;//���볡��ʱע����̼�����

	//void onExit()override;//�Ƴ�������ע�����̼�����

	//void registerKeyboardEvent();//ע������¼�

	void moveInDirection(const cocos2d::Vec2& direction);//�ƶ�

	void stopMoving();//ֹͣ�ƶ�

	//void update(float delta)override;//ÿ֡���£������ƶ�

	void openInventory();//�򿪱���

	void closeInventory();//�رձ���

	void loadAnimations();//Ԥ�������ж���

	cocos2d::Animate* createWalkAnimation(const std::string& direction);//�������߶���

	cocos2d::Animate* createIdleAnimation(const std::string& direction);//����վ������

	void playWalkAnimation(const std::string& direciton);//�������߶���

	void playIdleAnimation(const std::string& direciton);//վ��

	void stopAnimation();

	float getSpeed();

	cocos2d::Vec2& getMoveDirection();//��ȡ�ƶ�����
	void setIsTalking(bool talking);
private:
	static Player* _instance;//��̬����ָ��

	cocos2d::Sprite* sprite;

	//�����ƶ����
	bool isMoving;//�Ƿ����ƶ�
	bool isInventoryOpen;//�����Ƿ��
	float speed;//�ƶ��ٶ�
	cocos2d::Vec2 moveDirection;//�ƶ�����
	//cocos2d::EventListenerKeyboard* keyboardListener;//�����¼�������
	bool isTalking;
	//�������
	std::string lastDirection;//�����ƶ���������ѡ��վ��������
	std::map<std::string, cocos2d::Animate*> Animations;//�洢����
	cocos2d::Animate* currentAnimation;//��ǰ����
	cocos2d::Action* currentAction;//��ǰ����
	std::string name;
};

#endif  //_PLAYER_H_


