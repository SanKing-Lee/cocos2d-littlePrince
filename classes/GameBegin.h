#ifndef _GAMEBEGIN_H_
#define _GAMEBEGIN_H_

#include "cocos2d.h"
//#include "Game.h"
#include "GameHelpScene.h"
#include "GameScene.h"
#include "GameStoreScene.h"
#include "ThirdScene.h"
USING_NS_CC;

class GameBegin : public cocos2d::Layer{
public:
	GameBegin();
	~GameBegin();
	static Scene* createScene();
	static GameBegin* create();
	void update(float);
	bool init();
	static int m_money;
	static void changeMoney(int);
};


#endif