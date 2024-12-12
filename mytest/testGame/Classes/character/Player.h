#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Changers.h"
#include "cocos2d.h"
#include "cstring"

//��ҳ�ʼ������
#define INIT_PLAYER_HEALTH  100
#define INIT_PLAYER_MONEY  0
#define INIT_PLAYER_SPEED 500.0f

//�̳���Character��Player��
class Player :public Changers {
public:

	static Player* getInstance();//��ȡ����ָ��

	static void destroyInstance();//���ٵ���ָ��

	//��̬��������
	static Player* createWithAttributes(const std::string& imagePath, const std::string& name);

	//��д�ĳ�ʼ������
	bool initWithAttributes(const std::string& imagePath, const std::string& name)override;

	//void onEnter()override;//���볡��ʱע����̼�����

	//void onExit()override;//�Ƴ�������ע�����̼�����

	//void registerKeyboardEvent();//ע������¼�

	void moveInDirection(const cocos2d::Vec2& direction);//�ƶ�

	void stopMoving();//ֹͣ�ƶ�

	//void update(float delta)override;//ÿ֡���£������ƶ�

	void openInventory();//�򿪱���

	void closeInventory();//�رձ���

	void loadAnimations()override;//Ԥ�������ж���

	cocos2d::Animate* createWalkAnimation(const std::string& direction);//�������߶���

	cocos2d::Animate* createIdleAnimation(const std::string& direction);//����վ������

	void playWalkAnimation(const std::string& direciton);//�������߶���

	void playIdleAnimation(const std::string& direciton);//վ��

	void stopAnimation();

	float getSpeed();

	cocos2d::Vec2& getMoveDirection();//��ȡ�ƶ�����

private:
	static Player* _instance;//��̬����ָ��

	//�����ƶ����
	bool isMoving;//�Ƿ����ƶ�
	bool isInventoryOpen;//�����Ƿ��
	float speed;//�ƶ��ٶ�
	cocos2d::Vec2 moveDirection;//�ƶ�����
	//cocos2d::EventListenerKeyboard* keyboardListener;//�����¼�������

	//�������
	std::string lastDirection;//�����ƶ���������ѡ��վ��������

};

#endif  //_PLAYER_H_


