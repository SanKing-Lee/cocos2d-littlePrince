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
		b_speed = SP_HERO_BULLET;
		break;
	case DoubleBullet:
	case MultiBullet:
		Sprite::initWithSpriteFrameName("bullet2.png");
		b_attack = BULLET2_ATTACK;
		b_speed = SP_HERO_BULLET;
		break;
	case BossSingleBUllet:
		Sprite::initWithSpriteFrameName("bossSingleBullet.png");
		b_attack = BULLET2_ATTACK;
		b_speed = SP_ENEMY_BULLET;
		break;
	case BossDoubleBullet:
		Sprite::initWithSpriteFrameName("bossDoubleBullet.png");
		b_attack = BULLET2_ATTACK;
		b_speed = SP_ENEMY_BULLET;
		break;
	case EnemyNormalBUllet:
		Sprite::initWithSpriteFrameName("enemyNormalBUllet.png");
		b_attack = BULLET2_ATTACK;
		b_speed = SP_ENEMY_BULLET;
		break;
	case EnemyTrackBullet:
		Sprite::initWithSpriteFrameName("enemyTrackBullet.png");
		b_attack = BULLET2_ATTACK;
		b_speed = SP_ENEMY_BULLET;
		break;
	case EnemyBigBullet:
		Sprite::initWithSpriteFrameName("bossSupperBullet.png");
		b_attack = BULLET2_ATTACK;
		b_speed = SP_ENEMY_BULLET;
		break;

	default:
		break;
	}
	return true;
}

