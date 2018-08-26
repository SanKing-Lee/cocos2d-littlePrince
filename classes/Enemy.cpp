#include "Enemy.h"
#include "CommonData.h"
#include "OverScene.h"

float Enemy::e_LevelSpeed =  0;

Enemy* Enemy::create(EnemyType type) {
    auto enemy = new Enemy();
    if( enemy && enemy->init(type) ) {
        enemy->autorelease();
        return enemy;
    }
    delete enemy;
    enemy = NULL;
    return NULL;
}

//根据不同的敌机建立不同的图片效果
bool Enemy::init(EnemyType type) {
    e_type = type;
    switch (type)
    {
    case  SMALL_ENEMY:
        e_hp = HP_SMALL;
       e_speed = SP_SMALL;      
		e_score = SCORE_SMALL;
        cocos2d::Sprite::initWithSpriteFrameName("enemy1.png");
        break;
    case  MIDDLE_ENEMY:
        e_hp = HP_MIDDLE;
       e_speed = SP_MIDDLE;
		e_score = SCORE_MIDDLE;
        cocos2d::Sprite::initWithSpriteFrameName("enemy2.png");
        break;
    case  BIG_ENEMY:
        e_hp = HP_BIG;
       e_speed = SP_BIG;
		e_score = SCORE_BIG;
		cocos2d::Sprite::initWithSpriteFrameName("enemy3_n1.png");
		{
			auto animation = AnimationCacheInstance->getAnimation("Big Enemy Fly");
			this->runAction(cocos2d::Animate::create(animation));
			Audio->playEffect("big_spaceship_flay.mp3");
		}
        break;
    default:
        break;
    }
    return true;
}

//打击效果
void Enemy::hitAnim() { 
    auto animation = cocos2d::Animation::create();
    switch (this->e_type)
    {
    case MIDDLE_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Middle Enemy Hurt");
                break;
    case BIG_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Big Enemy Hurt");
            break;
    default:
            break;
    }
    auto animate = cocos2d::Animate::create(animation);
    this->runAction(animate);
}   

//摧毁效果
void Enemy::destroyedAnim() {
    auto animation = cocos2d::Animation::create();
    switch(this->e_type) {
    case SMALL_ENEMY:       
		animation=cocos2d::AnimationCache::getInstance()->getAnimation("Small Enemy Down");
		Audio->playEffect("enemy1_down.mp3");
        break;
    case MIDDLE_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Middle Enemy Down");
		Audio->playEffect("enemy2_down.mp3");
        break;
    case BIG_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Big Enemy Down");
		Audio->playEffect("enemy3_down.mp3");
        break;
    default:
        break;
    }
    auto animate = cocos2d::Animate::create(animation);
    auto callFuncN = cocos2d::CallFuncN::create([](Node* node) {
		node->removeFromParentAndCleanup(true);
    });

   (isDestroyed())?runAction(cocos2d::Sequence::create(animate, callFuncN, NULL))
	   :runAction(animate);
}

void Enemy::increeLevelSpeed(int multi){
	if(Enemy::e_LevelSpeed >= 10)
	{
		return;
	}
	Enemy::e_LevelSpeed += 0.01f*multi;
}

void Enemy::clearLevelSpeed(){
	Enemy::e_LevelSpeed = 0; 
}