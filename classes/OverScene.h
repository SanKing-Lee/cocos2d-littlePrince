#pragma once

#include <cocos2d.h>
#include <string>
#include <vector>
#include <algorithm>
#include "LoadingScene.h"

class OverScene: public cocos2d::Layer{
public:
	OverScene();
	static cocos2d::Scene* createScene();
	static OverScene* create();
	bool init();
	void setScore(int score){o_score = score;};
	void writeScore();
	void readScore();
	void createBackground();
	void displayScore();
	void displayGold();
	void createMenu_Restart();
	void createMenu_Rank();
	//sort prescend
private:
	int o_score;
	std::vector<int> scores;
};