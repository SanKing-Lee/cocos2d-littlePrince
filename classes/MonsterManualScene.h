pragma once
#include <cocos2d.h>
#include "CommonData.h"

class MonsterManualScene: public Layer{
public:
	MonsterManualScene();
	static Scene* createScene();
	static MonsterManualScene* create();
	bool init();
private:

};