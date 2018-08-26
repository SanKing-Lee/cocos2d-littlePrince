#pragma once

#include <cocos2d.h>

class Hero:public cocos2d::Sprite{
private:
	int h_hp;
	bool canMove;
	bool active;
	cocos2d::Point h_vec;
public:
	Hero();
	static Hero* create();
	bool init();
	int getHP(){return h_hp;};
	void setHP(int hp){h_hp = hp;};
	void touchMove();
	void fly();
	void down();
	void setActive(bool isActive){active = isActive;};
	void setMove(bool move){canMove = move;};
	bool getActive(){return active;};
	void rebirthHero();
	//void displayPH();
};