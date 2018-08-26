#include "Bullet.h"

Bullet* Bullet::create(BulletType type)
{
	auto bullet = new Bullet();
	if(bullet&&bullet->init(type)){
		bullet->autorelease();
		return bullet;
	}
	delete bullet;
	bullet = nullptr;
	return nullptr;
}

bool Bullet::init(BulletType type){
	b_type  = type;
	switch(type)
	{
	case SingleBullet:
		Sprite::initWithSpriteFrameName ("bullet1.png");
		b_attack = BULLET1_ATTACK;
		b_speed = BULLETS_SPEED;
		break;
	case DoubleBullet:
	case MultiBullet:
		Sprite::initWithSpriteFrameName("bullet2.png");
		b_attack = BULLET2_ATTACK;
		b_speed = BULLETS_SPEED;
		break;
	default:
		break;
	}
	return true;
}

