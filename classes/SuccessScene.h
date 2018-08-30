#ifndef __SUCCESSSCENE__H__
#define __SUCCESSSCENE__H__
#include"cocos2d.h"
using namespace cocos2d;

class SuccessScene:public Layer
{
public:
	bool init();
	static SuccessScene* create();
	static Scene* createScene();
};

#endif