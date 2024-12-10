#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Character.h"
#include "cocos2d.h"
//
//class Player :public cocos2d::Sprite {
//public:
//	//��̬��������
//	static Player* create(const char* filename);
//
//	//��ҳ�ʼ������
//	void initPlayer();
//
//    // ���º���
//    void update(float delta);
//
//    //���ݵ�ǰ������ٶ��ƶ�����
//    void move();
//
//    //�������ﳯ����ת��
//    void setDirection(const cocos2d::Vec2& d);
//
//
//    // �����˺�����
//    void takeDamage(int damage);
//
//    // ��ȡ���״̬
//    int getHealth() const;
//    int getMoney() const;
//
//    // ���ӽ�Ǯ
//    void addMoney(int amount);
//
//    // ��������߼�
//    void die();
//    
//private:
//    // ˽������
//    int m_health;          // ����ֵ
//    int m_money;           // ��Ǯ
//    float m_speed;         // �ƶ��ٶ�
//    cocos2d::Vec2 m_direction;      //���ﳯ��
//    // ˽�з�������չ���ܿ���������
//    void initAnimations(); // ��ʼ����Ҷ���
//    void initPhysics();    // ��ʼ��������ײ��
//
//};

//��ҳ�ʼ������
#define INIT_PLAYER_HEALTH  100
#define INIT_PLAYER_MONEY  0
#define INIT_PLAYER_SPEED 100.0f

//�̳���Character��Player��
class Player :public Character {
public:
	//��̬��������
	static Player* createWithAttributes(const char* imagePath, const char* name);

	//��д�ĳ�ʼ������
	bool initWithAttributes(const char* imagePath, const char* name)override;

	void onEnter()override;//���볡��ʱע����̼�����

	void onExit()override;//�Ƴ�������ע�����̼�����

	void registerKeyboardEvent();//ע������¼�

	void startMoving(const cocos2d::Vec2& direction);//��ʼ�ƶ�

	void stopMoving();//ֹͣ�ƶ�

	void openInventory();//�򿪱���

	void closeInventory();//�رձ���


private:
	bool isMoving;//�Ƿ����ƶ�
	bool isInventoryOpen;//�����Ƿ��
	float speed;//�ƶ��ٶ�
	cocos2d::Vec2 moveDirection;//�ƶ�����
	cocos2d::EventListenerKeyboard* keyboardListener;//�����¼�������
};

#endif  //_PLAYER_H_


