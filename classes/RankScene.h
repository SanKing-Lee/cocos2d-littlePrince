#pragma once

#include <cocos2d.h>

USING_NS_CC;

class RankScene:public Layer{
private:
	std::vector<int> r_scores;
public:
	RankScene();
	static Scene* createScene();
	static RankScene* create();
	bool init();
	void readScore();
	void createBackground();
	void createMenu_Back2Over();
	void displayRank();
};