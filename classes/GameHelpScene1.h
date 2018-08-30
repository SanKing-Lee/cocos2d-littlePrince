#pragma once

#include "cocos2d.h"
USING_NS_CC;

class GameHelpScene1 : public cocos2d::Layer{
public:
	GameHelpScene1();
	~GameHelpScene1();
	static Scene* createScene();
	static GameHelpScene1* create();
	bool init();
};