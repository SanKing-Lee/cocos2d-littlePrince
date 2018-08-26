#include "Bullet.h"

Bullet::Bullet(){
	b_type = SingleBullet;
}

Bullet* Bullet::create(BulletType type){
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
	this->b_type  = type;
	switch(type)
	{
	case SingleBullet:
		cocos2d::Sprite::initWithSpriteFrameName ("bullet1.png");
		break;
	case DoubleBullet:
		cocos2d::Sprite::initWithSpriteFrameName("bullet2.png");
		break;
	default:
		break;
	}
	return true;
}

