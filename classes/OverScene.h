#pragma once

#include <cocos2d.h>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

class OverScene: public cocos2d::Layer{
public:
	OverScene(int score);
	static cocos2d::Scene* createScene(int score);
	static OverScene* create(int score);
	static cocos2d::Scene* createWithScore(int score);
	bool init();
	void setScore(int score){o_score = score;};
	void writeScore();
	void readScore();
	void createBackground();
	void displayScore();
	void createMenu_Restart();
	void createMenu_Rank();
	//sort prescend
private:
	int o_score;
	std::vector<int> scores;
};