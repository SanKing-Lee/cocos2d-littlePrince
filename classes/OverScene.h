#pragma once

#include <cocos2d.h>
#include <string>
#include <vector>
#include <algorithm>
#include "LoadingScene.h"
#include "CommonData.h"
#include "GameBegin.h"
#include "GameScene.h"
#include <SimpleAudioEngine.h>
#include "RankScene.h"

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
	void createMenu_Return2MainMenu();
	void createMenu_Quit();
	void gameQuitCallback(Ref* pSender);
	//sort prescend
private:
	int o_score;
	int o_gold;
	std::vector<int> scores;
};