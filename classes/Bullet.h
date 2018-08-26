#pragma once

#include <cocos2d.h>
#include "CommonData.h"

typedef enum{
	SingleBullet,
	DoubleBullet,
	MultiBullet
} BulletType;

class Bullet: public cocos2d::Sprite{
public:

	static Bullet* create(BulletType);
	bool init(BulletType);

	//type visitor
	BulletType getType(){return b_type;};
	void setType(BulletType type){b_type = type;};

	//speed visitor
	float getSpeed(){return b_speed;};
	void setSpeed(int sp){b_speed = sp;};

	//attack visitor
	int getAttack(){return b_attack;};
	void setAttack(int at){b_attack = at;}

private:
	BulletType b_type;
	float b_speed;
	int b_attack;
};