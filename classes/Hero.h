#pragma once

#include <cocos2d.h>
#include "CommonData.h"

typedef enum{
	HeroOne,
	HeroTwo,
	HeroThree
} HeroType;

class Hero:public cocos2d::Sprite{
private:
	HeroType h_type;
	int h_hp;
	bool h_canMove;
	bool h_isActive;
	bool h_isAlive;
	int h_level;
	int h_HPLimit;
	Point h_vec;
public:
	static Hero* create(HeroType type);
	bool init(HeroType);
	int getHP(){return h_hp;};
	void setHP(int hp){h_hp = hp;};
	void touchMove();
	void fly();
	void down();
	void setActive(bool isActive){h_isActive = isActive;};
	void setMove(bool move){h_canMove = move;};
	bool getActive(){return h_isActive;};

	bool getAlive(){return h_isAlive;};
	void setAlive(bool ali){h_isAlive = ali;};
	void rebirthHero();

	int getLevel() { return h_level;};
	void setLevel(int lv) { h_level = lv; };

	int getHPLimit() { return h_HPLimit;};
	void setHPLimit(int l) {h_HPLimit = l;};

	//void displayPH();
};