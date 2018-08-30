#include "Enemy.h"
#include "CommonData.h"
#include "OverScene.h"

float Enemy::e_LevelSpeed =  0;


CurveDirection Enemy::e_curveDirection = CNone;

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

Enemy::Enemy()
{
	e_type = SmallEnemy1;
	e_speed = 0;
	e_hp = 0;
	e_score = 0;
	e_bigFlySoundId = 0;
	e_canMove = true;
	e_lineDirection = LStraight;
	cnt = 0;
	e_bossDirection = None;
}


Enemy::~Enemy()
{
	//stop music
	if (e_type == BigEnemy)
	{
		Audio->stopEffect(e_bigFlySoundId);
	}
}

//根据不同的敌机建立不同的图片效果
bool Enemy::init(EnemyType type) {
      e_type = type;
    switch (type)
    {
   	case  Meteorite_ENEMY:
		e_hp = HP_METEORITE;
		e_speed = SP_METEORITE;      
		e_score = SCORE_METEORITE;
		cocos2d::Sprite::initWithSpriteFrameName("Meteorite_ENEMY.png");
		break;
	case  SmallEnemy1:
		e_hp = HP_SMALL;
		e_speed = SP_SMALL;      
		e_score = SCORE_SMALL;
		cocos2d::Sprite::initWithSpriteFrameName("SmallEnemy.png");
		break;
	case  MiddleEnemy:
		e_hp = HP_MIDDLE;
		e_speed = SP_MIDDLE;
		e_score = SCORE_MIDDLE;
		e_lineDirection = (rand()%2)?LLeft:LRight;
		cocos2d::Sprite::initWithSpriteFrameName("MiddleEnemy_n1.png");

		break;
	case  BigEnemy:
		e_hp = HP_BIG;
		e_speed = SP_BIG;
		e_score = SCORE_BIG;
		cocos2d::Sprite::initWithSpriteFrameName("Battery_n1.png");
		//Audio->playEffect("big_spaceship_flay.mp3");
	case  FORT_ENEMY:
		e_hp=HP_FORT;
		e_speed=SP_FORT;
		e_score=SCORE_FORT;
		cocos2d::Sprite::initWithSpriteFrameName("Battery_n1.png");
		{
			//fly animation
			/*auto animation = MyAnimationCache->getAnimation("Fort fly");
			this->runAction(Animate::create(animation));*/
			//fly music
		}
		break;
	case TRACK_ENEMY:
		e_hp=HP_TRACK;
		e_speed=SP_TRACK;
		e_score=SCORE_TRACK;
		cocos2d::Sprite::initWithSpriteFrameName("Creature.png");
		{
			//fly animation
			/*auto animation = MyAnimationCache->getAnimation("Track fly");
			this->runAction(Animate::create(animation));*/
			//fly music
		}
		break;
		
	case SmallEnemy2:
		e_hp = HP_CURVE;
		e_speed = SP_CURVE;      
		e_score = SCORE_CURVE;
		cocos2d::Sprite::initWithSpriteFrameName("Curve_ENEMY_n1.png");
		{
			//fly animation
			//auto animation = MyAnimationCache->getAnimation("Curve fly");
			//this->runAction(Animate::create(animation));
			//fly music
		}
		move2();
		break;
	case FirstBoss_ENEMY:
		e_hp = HP_FIRST_BOSS;
		e_speed = SP_FIRST_BOSS;      
		e_score = SCORE_FIRST_BOSS;
		e_bossDirection = Down;
		cocos2d::Sprite::initWithSpriteFrameName("BigEnemy1_n1.png");
		{
			////fly animation
			//auto animation = MyAnimationCache->getAnimation("first boss fly");
			//this->runAction(Animate::create(animation));
			////fly music
		}
		break;
	case SecondBoss_ENEMY:
		e_hp = HP_SECOND_BOSS;
		e_speed = SP_SECOND_BOSS;      
		e_score = SCORE_SECOND_BIG;
		e_bossDirection = Down;
		cocos2d::Sprite::initWithSpriteFrameName("BigEnemy2_n1.png");
		{
			////fly animation
			//auto animation = MyAnimationCache->getAnimation("second boss fly");
			//this->runAction(Animate::create(animation));
			////fly music
		}
		break;
	case ThirdBoss_ENEMY:
		e_hp = HP_THIRD_BOSS;
		e_speed = SP_THRID_BOSS;      
		e_score = SCORE_THRID_BIG;
		e_bossDirection = Down;
		cocos2d::Sprite::initWithSpriteFrameName("BigEnemy3_n1.png");
		{
			////fly animation
			//auto animation = MyAnimationCache->getAnimation("third boss fly");
			//this->runAction(Animate::create(animation));
			////fly music
		}
		break;
	case Boss:
		e_hp = HP_BOSS;
		e_speed = SP_BOSS;  //Y offset
		e_score = SCORE_BOSS;
		e_bossDirection = Down;

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
    	case MiddleEnemy:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Middle Enemy Hurt");
		break;
	case BigEnemy:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Big Enemy Hurt");
		break;
	case Meteorite_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Meteorite Enemy Hurt");
		break;
	case FORT_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Fort Enemy Hurt");
		break;
	case FirstBoss_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("First Boss Hurt");
		break;
	case SecondBoss_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Second Boss Hurt");
		break;
	case ThirdBoss_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Third Boss Hurt");
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
    case SmallEnemy1:       
		animation=cocos2d::AnimationCache::getInstance()->getAnimation("Small Enemy Down");
		//Audio->playEffect("small_down.mp3");
		break;
	case MiddleEnemy:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Middle Enemy Down");
		//Audio->playEffect("middle_down.mp3");
		Audio->playEffect("enemy_boom.mp3");
		break;
	case BigEnemy:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Big Enemy Down");
		//Audio->playEffect("big_down.mp3");
		break;
	case FORT_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Fort Enemy Down");
		//Audio->playEffect("fort_down.mp3");
		Audio->playEffect("enemy_boom.mp3");
		break;
	case TRACK_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Track Enemy Down");
		//Audio->playEffect("track_down.mp3");
		Audio->playEffect("enemy_boom.mp3");
		break;
	case SmallEnemy2:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Curve Enemy Down");
		//Audio->playEffect("curve_down.mp3");
		break;
	case FirstBoss_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Firstboss Enemy Down");
		//Audio->playEffect("fisrtboss_down.mp3");
		Audio->playEffect("boss_boom.mp3");
		break;
	case SecondBoss_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Secondboss Enemy Down");
		//Audio->playEffect("secondboss_down.mp3");
		Audio->playEffect("boss_boom.mp3");
		break;
	case ThirdBoss_ENEMY:
		animation = cocos2d::AnimationCache::getInstance()->getAnimation("Thirdboss Enemy Down");
		//Audio->playEffect("thirdboss_down.mp3");
		Audio->playEffect("boss_boom.mp3");
		break;
	default:
		break;
	}
	auto animate = cocos2d::Animate::create(animation);
	auto callFuncN = cocos2d::CallFuncN::create([](Node* node) {
		node->removeFromParentAndCleanup(true);
	});

	if (isDestroyed())
	{
		this->runAction(Sequence::create(animate, callFuncN, NULL));
	}
	else
	{
		this->runAction(animate);
	}
}


void Enemy::updateLevelSpeed(int multi)
{
	if(Enemy::e_LevelSpeed >= 10)
	{
		return;
	}
	Enemy::e_LevelSpeed = SP_ENEMY_INCREMENT * multi;
}

void Enemy::clearLevelSpeed(){
	Enemy::e_LevelSpeed = 0; 
}

void Enemy::move(float x, float y)
{
	if (e_canMove)
	{
		switch(e_type)
		{
		case SmallEnemy1:
		case MiddleEnemy:
		case BigEnemy:
			{
				float dx, dy;
				if (this->e_lineDirection != LStraight)
				{
					cnt++;
				}
				if (canChangeLineDirection())
				{
					changeLineDirection();
				}
				switch (e_lineDirection)
				{
				case LLeft:
					dx = -x;
					dy = -y;
					break;
				case LRight:
					dx = x;
					dy = -y;
					break;
				case LStraight:
					dx = 0;
					dy = -y;
					break;
				default:
					dx = 0;
					dy = 0;
					break;
				}
				this->setPosition(this->getPosition() + Point(dx, dy));
			}
			break;
		case FirstBoss_ENEMY:
		case SecondBoss_ENEMY:
		case ThirdBoss_ENEMY:
			float dx, dy;
			if (e_bossDirection != Up && e_bossDirection != Down)
			{
				updateBossDirection();
			}
			else
			{
				cnt++;
			}
			switch (e_bossDirection)
			{
			case LeftUp:
				dx = -x;
				dy = y;
				break;
			case LeftDown:
				dx = -x;
				dy = -y;
				break;
			case RightUp:
				dx = x;
				dy = y;
				break;
			case RightDown:
				dx = x;
				dy = -y;
				break;
			case Down:
				if (cnt >= (int)(VisSize.height/2 + this->getContentSize().height/2))
				{
					e_bossDirection = Up;
					cnt = 0;
					return;
				}
				else
				{
					dx = 0;
					dy = -1;
				}
				break;
			case Up:
				if (cnt >= 200)
				{
					int randnum = rand() % 4;
					if (randnum == 0)
					{
						e_bossDirection = LeftUp;
					}
					else if (randnum == 1)
					{
						e_bossDirection = LeftDown;
					}
					else if (randnum == 2)
					{
						e_bossDirection == RightUp;
					}
					else if (randnum == 3)
					{
						e_bossDirection == RightDown;
					}
					cnt = 0;
					return;
				}
				else
				{
					dx = 0;
					dy = 1;
				}
				break;
			default:
				dx = 0;
				dy = 0;
				break;
			}
			this->setPosition(this->getPosition() + Point(dx, dy));
		case SmallEnemy2:
			break;
		default:
			break;
		}
	}
	else
	{
		return;
	}
}

void Enemy::move2()
{
	if (e_canMove)
	{
		if (e_type == SmallEnemy2)
		{
			auto w = VisSize.width, h = VisSize.height; 
			ccBezierConfig bezier;
			Point p1 = Point(w*3/4, h/3),
				p2 = Point(w/4, h/3),
				p3 = Point(w/8, h*2/3),
				p4 = Point(0, h),
				p5 = Point(w, h),
				p6 = Point(w*7/8, h*2/3),
				p7 = Point(w/4, h/5),
				p8 = Point(-this->getContentSize().width-10, h/5),
				p9 = Point(w*3/4, h/5),
				p10 = Point(w+this->getContentSize().width+10, h/5);
			if (e_curveDirection == CRight)
			{
				bezier.controlPoint_1 = p1;
				bezier.controlPoint_2 = p2;
				bezier.endPosition = p3;
				auto move1 = BezierTo::create(2.0f, bezier);
				bezier.controlPoint_1 = p4;
				bezier.controlPoint_2 = p5;
				bezier.endPosition = p6;
				auto move2 = BezierTo::create(2.0f, bezier);
				bezier.controlPoint_1 = p1;
				bezier.controlPoint_2 = p7;
				bezier.endPosition = p8;
				auto move3 = BezierTo::create(2.0f, bezier);
				this->runAction(Sequence::create(move1, move2, move3, NULL));
			}
			else if (e_curveDirection == CLeft)
			{
				bezier.controlPoint_1 = p2;
				bezier.controlPoint_2 = p1;
				bezier.endPosition = p6;
				auto move1 = BezierTo::create(2.0f, bezier);
				bezier.controlPoint_1 = p5;
				bezier.controlPoint_2 = p4;
				bezier.endPosition = p3;
				auto move2 = BezierTo::create(2.0f, bezier);
				bezier.controlPoint_1 = p2;
				bezier.controlPoint_2 = p9;
				bezier.endPosition = p10;
				auto move3 = BezierTo::create(2.0f, bezier);
				this->runAction(Sequence::create(move1, move2, move3, NULL));
			}
			e_canMove = false;
		}
	}
	else
	{
		return;
	}
}

void Enemy::changeLineDirection()
{
	if (beyondLimitMinX())
	{
		e_lineDirection = LRight;
	}
	else if (beyondLimitMaxX())
	{
		e_lineDirection = LLeft;
	}
	else
	{
		switch (e_lineDirection)
		{
		case LLeft:
			e_lineDirection = LRight;
			break;
		case LRight:
			e_lineDirection = LLeft;
			break;
		case LStraight:
			break;
		default:
			break;
		}
	}
	cnt = 0;
}

void Enemy::updateBossDirection()
{
	if (bossBeyondLimitMinX())
	{
		switch (e_bossDirection)
		{
		case LeftUp:
			e_bossDirection = RightUp;
			break;
		case LeftDown:
			e_bossDirection = RightDown;
			break;
		default:
			break;
		}
		if (bossBeyondLimitMinY())
		{
			e_bossDirection = RightUp;
		}
		else if (bossBeyondLimitMaxY())
		{
			e_bossDirection = RightDown;
		}
	}
	else if (bossBeyondLimitMaxX())
	{
		switch (e_bossDirection)
		{
		case RightUp:
			e_bossDirection = LeftUp;
			break;
		case RightDown:
			e_bossDirection = LeftDown;
			break;
		default:
			break;
		}
		if (bossBeyondLimitMinY())
		{
			e_bossDirection = LeftUp;
		}
		else if (bossBeyondLimitMaxY())
		{
			e_bossDirection = LeftDown;
		}
	}
	else if (bossBeyondLimitMinY())
	{
		switch (e_bossDirection)
		{
		case LeftDown:
			e_bossDirection = LeftUp;
			break;
		case RightDown:
			e_bossDirection = RightUp;
			break;
		default:
			break;
		}
	}
	else if (bossBeyondLimitMaxY())
	{
		switch (e_bossDirection)
		{
		case LeftUp:
			e_bossDirection = LeftDown;
			break;
		case RightUp:
			e_bossDirection = RightDown;
			break;
		default:
			break;
		}
	}
}

bool Enemy::canChangeLineDirection()
{
	return cnt == OFFSET_NUMBER || beyondLimitMinX() || beyondLimitMaxX();
}

bool Enemy::beyondLimitX()
{
	return this->getPositionX() + this->getContentSize().width/2 < 0 ||
		this->getPositionX() - this->getContentSize().width/2 > VisSize.width;
}

bool Enemy::beyondLimitMinX()
{
	return this->getPositionX() - this->getContentSize().width/2 < 0;
}

bool Enemy::beyondLimitMaxX()
{
	return this->getPositionX() + this->getContentSize().width/2 > VisSize.width;
}

bool Enemy::beyondLimitY()
{
	return this->getPositionY() + this->getContentSize().height/2 < 0;
}

bool Enemy::bossBeyondLimitMinX()
{
	return this->getPositionX() - this->getContentSize().width/2 <= 0;
}

bool Enemy::bossBeyondLimitMaxX()
{
	return this->getPositionX() + this->getContentSize().width/2 >= VisSize.width;
}

bool Enemy::bossBeyondLimitMinY()
{
	return this->getPositionY() - this->getContentSize().height/2 <= VisSize.height/2;
}

bool Enemy::bossBeyondLimitMaxY()
{
	return this->getPositionY() + this->getContentSize().height/2 >= VisSize.height;
}