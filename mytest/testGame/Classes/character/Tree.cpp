#include "Tree.h"

USING_NS_CC;

//#define ENABLE_ANIMATIONS

//��̬��������
Tree* Tree::create()
{
	Tree* tree = new(std::nothrow) Tree();
	if (tree && tree->init())
	{
		tree->autorelease();
		return tree;
	}
	delete tree;
	return nullptr;
}

//��ʼ������
bool Tree::init()
{
	if (!Crops::initWithAttributes("Tree.plist", "Tree", 1, "seed", 5))
	{
		return false;
	}

	loadAnimations();
	return true;
}

//���ض���
void Tree::loadAnimations()
{
	//������������,��1��2����
	Vector<SpriteFrame*> Frames;
	for (int i = 1; i <= 3; i++)
	{
		std::string FrameName = "Tree_grow_1." + std::to_string(i) + ".png";
		Frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(FrameName));
	}

     Changers::Animations["Tree_grow_1"]=Animate::create(Animation::createWithSpriteFrames(Frames, 0.1f));  // ÿ֡ 0.1 ��
	
	 Frames.clear();

	 for (int i = 1; i <= 3; i++)
	 {
		 std::string FrameName = "Tree_grow_2." + std::to_string(i) + ".png";
		 Frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(FrameName));
	 }

	 Changers::Animations["Tree_grow_2"] = Animate::create(Animation::createWithSpriteFrames(Frames, 0.1f));

	//������������
	 Frames.clear();
	 for (int i = 1; i <= 3; i++)
	 {
		 std::string FrameName = "Tree_die_" + std::to_string(i) + ".png";
		 Frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(FrameName));
	 }

	 Changers::Animations["Tree_die"] = Animate::create(Animation::createWithSpriteFrames(Frames, 0.1f));

}


//�л�����״̬
void Tree::switchToStatus(const std::string& status)
{
	if (currentStatus == status)//��ʱ��״̬������Ҫ�л���״̬
	{
		return;
	}

	//�Ӿ���֡�������滻
	Changers::sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(status+"_Tree.png"));
	currentStatus = status;
}

//�����׶�1
void Tree::growthStage1()
{
	//���Ŷ���
	auto animation = "Tree_grow_1";
	if (Changers::Animations.find(animation) != Changers::Animations.end()) {

		auto action = Changers::Animations[animation]->clone(); // ���������ĸ���
		this->runAction(action);
	}

}
//�����׶�2
void Tree::growthStage2()
{
	//���Ŷ���
	auto animation = "Tree_grow_2";
	if (Changers::Animations.find(animation) != Changers::Animations.end()) {
		this->runAction(Changers::Animations[animation]);
	}
}

//�����׶�1
void Tree::death()
{
	//���Ŷ���
#if ENABLE_ANIMATIONS
	auto animation = "Tree_die";
	if (Changers::Animations.find(animation) != Changers::Animations.end()) {
		this->runAction(Changers::Animations[animation]);
	}
#endif
	switchToStatus("death");
}