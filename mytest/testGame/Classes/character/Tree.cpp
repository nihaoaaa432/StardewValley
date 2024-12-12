#include "Tree.h"

USING_NS_CC;

//#define ENABLE_ANIMATIONS

//静态工厂函数
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

//初始化函数
bool Tree::init()
{
	if (!Crops::initWithAttributes("Tree.plist", "Tree", 1, "seed", 5))
	{
		return false;
	}

	loadAnimations();
	return true;
}

//加载动画
void Tree::loadAnimations()
{
	//加载生长动画,分1、2两段
	Vector<SpriteFrame*> Frames;
	for (int i = 1; i <= 3; i++)
	{
		std::string FrameName = "Tree_grow_1." + std::to_string(i) + ".png";
		Frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(FrameName));
	}

     Changers::Animations["Tree_grow_1"]=Animate::create(Animation::createWithSpriteFrames(Frames, 0.1f));  // 每帧 0.1 秒
	
	 Frames.clear();

	 for (int i = 1; i <= 3; i++)
	 {
		 std::string FrameName = "Tree_grow_2." + std::to_string(i) + ".png";
		 Frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(FrameName));
	 }

	 Changers::Animations["Tree_grow_2"] = Animate::create(Animation::createWithSpriteFrames(Frames, 0.1f));

	//加载死亡动画
	 Frames.clear();
	 for (int i = 1; i <= 3; i++)
	 {
		 std::string FrameName = "Tree_die_" + std::to_string(i) + ".png";
		 Frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(FrameName));
	 }

	 Changers::Animations["Tree_die"] = Animate::create(Animation::createWithSpriteFrames(Frames, 0.1f));

}


//切换树的状态
void Tree::switchToStatus(const std::string& status)
{
	if (currentStatus == status)//此时的状态就是需要切换的状态
	{
		return;
	}

	//从精灵帧缓存中替换
	Changers::sprite->setSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(status+"_Tree.png"));
	currentStatus = status;
}

//生长阶段1
void Tree::growthStage1()
{
	//播放动画
	auto animation = "Tree_grow_1";
	if (Changers::Animations.find(animation) != Changers::Animations.end()) {

		auto action = Changers::Animations[animation]->clone(); // 创建动作的副本
		this->runAction(action);
	}

}
//生长阶段2
void Tree::growthStage2()
{
	//播放动画
	auto animation = "Tree_grow_2";
	if (Changers::Animations.find(animation) != Changers::Animations.end()) {
		this->runAction(Changers::Animations[animation]);
	}
}

//死亡阶段1
void Tree::death()
{
	//播放动画
#if ENABLE_ANIMATIONS
	auto animation = "Tree_die";
	if (Changers::Animations.find(animation) != Changers::Animations.end()) {
		this->runAction(Changers::Animations[animation]);
	}
#endif
	switchToStatus("death");
}