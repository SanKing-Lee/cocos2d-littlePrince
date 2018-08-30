#ifndef _GAMESTORESCENE_H_
#define _GAMESTORESCENE_H_

#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "GameBegin.h"
#include "Prop.h"

USING_NS_CC;
USING_NS_CC_EXT;

const int HPPrice = 20;
const int BombPrice = 40;
const int FreezePrice = 20;
const int ProtectPrice = 30;

class GameStoreScene : public cocos2d::CCLayer{
public:
	GameStoreScene();
	~GameStoreScene();
	static Scene* createScene();
	static GameStoreScene* create();
	bool init();
	void buy(PropType type);//购买商品
	void updateMoney();
//	Point* m_position;//商品的位置,构造函数设置
	int number;//商品的数量
	void buttonCallback(cocos2d::Node *pNode);
	int m_gold;
	void writeData(PropType);
};


#endif