#ifndef _TREE_H_
#define _TREE_H_

#include "Crops.h"

class Tree :public Crops {
public:
	static Tree* create();
	bool init();

	//�����׶�1
	void growthStage1();

	//�����׶�2
	void growthStage2();

	//����Ȼ����
	void death();

private:
	void loadAnimations();

	//�л�����״̬������������
	void switchToStatus(const std::string& status);


	std::string currentStatus;//��ǰ״̬�����硢��������������׮

};

#endif // _TREE_H_
