#ifndef _TREE_H_
#define _TREE_H_

#include "Crops.h"

class Tree :public Crops {
public:
	static Tree* create();
	bool init();

	//生长阶段1
	void growthStage1();

	//生长阶段2
	void growthStage2();

	//非自然死亡
	void death();

private:
	void loadAnimations();

	//切换树的状态，并更新纹理
	void switchToStatus(const std::string& status);


	std::string currentStatus;//当前状态，幼苗、中树、大树、树桩

};

#endif // _TREE_H_
