#ifndef THIRDSCENE__H__
#define THIRDSCENE__H__
#include"cocos2d.h"
#include "GameBegin.h"
#include "GameScene.h"

using namespace cocos2d;

class ThirdScene:public cocos2d::Layer{
public:
	bool init();
	static Scene *createScene();
	static ThirdScene *create();
	void initLevel();
	void writeLevel(int level);
	int getLevel(){ return historyLevel;};
	void setLevel(int lv) { historyLevel = lv;};
private:
	int historyLevel;
};

#endif