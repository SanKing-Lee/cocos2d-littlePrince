#pragma once
#include <cocos2d.h>
#include "Hero.h"
#include "GameBegin.h"

class LoadingScene:public cocos2d::Layer{
public:
	LoadingScene();
	static cocos2d::Scene* createScene();
	static LoadingScene* create();
	bool init();
	static void initData();
	void preloadMusic();
	void createAnimationCache();
	void createFrameCache();
	void createBackground();
	void createHero(HeroType htype);
	void createLoadingAnimation();
	void update(float);
private:
};