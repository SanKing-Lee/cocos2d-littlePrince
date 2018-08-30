#ifndef _GAMEHELPSCENE_H_
#define _GAMEHELPSCENE_H_

#include "cocos2d.h"
#include "GameBegin.h"
#include "GameHelpScene1.h"
USING_NS_CC;

class GameHelpScene : public cocos2d::Layer{
public:
	GameHelpScene();
	~GameHelpScene();
	static Scene* createScene();
	static GameHelpScene* create();
	bool init();
};


#endif