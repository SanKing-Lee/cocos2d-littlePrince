#pragma once
#include <cocos2d.h>
#include "Hero.h"

class LoadingScene:public cocos2d::Layer{
public:
	LoadingScene();
	static cocos2d::Scene* createScene();
	static LoadingScene* create();
	bool init();
	void preloadMusic();
	void createAnimationCache();
	void createFrameCache();
	void createBackground();
	void createHero(HeroType htype);
	void createLoadingAnimation();
private:

};