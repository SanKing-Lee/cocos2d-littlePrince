#include "Hero.h"
#include "CommonData.h"
#include "Hero.h"

Hero* Hero::create(HeroType type){
	auto hero = new Hero();
	if(hero&& hero->init(type)){
		hero ->autorelease();
		return hero;
	}
	delete hero;
	hero = nullptr;
	return nullptr;
}

bool Hero::init(HeroType type){
	h_canMove = true;
	h_isActive = true;
	h_vec = Vect::ZERO;
	h_type = type;
	h_isAlive = true;
	h_level = 0;
	h_hp = HERO_ONE_HP;
	switch(h_type){
	case HeroOne:
		this->cocos2d::Sprite::initWithFile("hero1_n1.png");
		break;
	case HeroTwo:
		this->cocos2d::Sprite::initWithFile("hero2_n1.png");
		break;
	case HeroThree:
		this->cocos2d::Sprite::initWithFile("Hero3_n1.png");
		break;
	default:
		this->cocos2d::Sprite::initWithFile("Hero3_n1.png");
		break;
	//set the position
	return true;
	}
}

void Hero::fly(){
	Animation* animation;
	switch(h_level){
	case 1: animation = MyAnimationCache->getAnimation("Hero1 Fly"); break;
	case 2:	animation = MyAnimationCache->getAnimation("Hero2 Fly"); break;
	case 3:	animation = MyAnimationCache->getAnimation("Hero3 Fly"); break;
	default: animation = MyAnimationCache->getAnimation("Hero3 Fly"); break;
	}
	auto animate = cocos2d::Animate::create(animation);
	this->runAction(animate);
}

void Hero::touchMove(){
	//touch 
	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event*) {
	//if the game is paused
	if(cocos2d::Director::getInstance()->isPaused() || !h_canMove){
		return false;
	}

	this->h_vec = this->getPosition() - touch->getLocation();
	bool isContain = this->getBoundingBox().containsPoint(touch->getLocation());
	return isContain;
	};

	//the boundary of this moving
	float minX = this->getContentSize().width/2;
	float maxX = cocos2d::Director::getInstance()->getVisibleSize().width - minX;
	float minY = this->getContentSize().height/2;
	float maxY = cocos2d::Director::getInstance()->getVisibleSize().height - minY;

	//move
	touchListener->onTouchMoved = [=](cocos2d::Touch* touch, cocos2d::Event*) {
		if(!h_canMove)
			return;
		auto desP = touch->getLocation() + this->h_vec;
		this->setPosition(MAX(minX,MIN(desP.x, maxX)), MAX(minY,MIN(desP.y, maxY)));
	};
	touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event*){
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);

}

void Hero::down(){
	auto animation = Animation::create();
	//switch(h_type){
	//case HeroOne:
		animation = MyAnimationCache->getAnimation("Hero1 Down");
	//case HeroTwo:
	//	animation = MyAnimationCache->getAnimation("Hero2 Down"); break;
	//case HeroThree:
	//	animation = MyAnimationCache->getAnimation("Hero3 Down"); break;
	//default:
	//	animation = MyAnimationCache->getAnimation("Hero3 Down"); break;
	//}
    auto animate = cocos2d::Animate::create(animation);
	this->runAction(animate);
}

void Hero::rebirthHero(int isBossDie){
	h_hp--;
	auto stopHero = cocos2d::CallFunc::create([=](){
		setActive(false);
		setMove(false);
		h_isAlive = false;
	});
	if(isBossDie)
		return;
	auto animation = MyAnimationCache->getAnimation("Hero1 Down");
	//switch(h_type){
	////case HeroOne:
	//	animation = MyAnimationCache->getAnimation("Hero1 Down");
	//case HeroTwo:
	//	animation = MyAnimationCache->getAnimation("Hero2 Down"); break;
	//case HeroThree:
	//	animation = MyAnimationCache->getAnimation("Hero3 Down"); break;
	//default:
	//	animation = MyAnimationCache->getAnimation("Hero3 Down"); break;
	//}
	auto animate = cocos2d::Animate::create(animation);
	auto getBack = cocos2d::CallFunc::create([=](){
		setPositionX(VisSize.width / 2);
		setPositionY(VisSize.height / 8);
	});
	auto activeHero = cocos2d::CallFunc::create([=](){
		setActive(true);
	});
	auto moveHero = cocos2d::CallFunc::create([=](){
		h_canMove = true;
		h_isAlive = true;
	});
	auto blin = cocos2d::Blink::create(2, 6);
	this->runAction(cocos2d::Sequence::create(stopHero, animate, getBack, moveHero, blin, activeHero, nullptr));
}