#pragma once

#include <cocos2d.h>

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
	cocos2d::Point h_vec;
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

	//void displayPH();
};