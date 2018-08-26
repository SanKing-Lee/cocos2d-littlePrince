#pragma once

#include <cocos2d.h>

typedef enum{
	SingleBullet,
	DoubleBullet
} BulletType;

class Bullet: public cocos2d::Sprite{
public:
	Bullet();
	static Bullet* create(BulletType);
	bool init(BulletType);
	BulletType getType(){return b_type;};
	void setType(BulletType type){b_type = type;};
private:
	BulletType b_type;
};