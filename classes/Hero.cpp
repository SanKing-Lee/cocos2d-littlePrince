#include "Hero.h"
#include "CommonData.h"
#include "Hero.h"

Hero::Hero(){
	this->h_hp = 3;
	this->canMove = true;
	this->active = true;
	this->h_vec = cocos2d::Vect::ZERO;
}

Hero* Hero::create(){
	auto hero = new Hero();
	if(hero&& hero->init()){
		hero ->autorelease();
		return hero;
	}
	delete hero;
	hero = nullptr;
	return nullptr;
}

bool Hero::init(){
	this->cocos2d::Sprite::initWithSpriteFrameName("hero1.png");
	//set the position
	return true;
}

void Hero::fly(){
	auto animation = AnimationCacheInstance->getAnimation("Hero Fly");
	auto animate = cocos2d::Animate::create(animation);
	this->runAction(animate);
}

void Hero::touchMove(){
	//touch 
	auto touchListener = cocos2d::EventListenerTouchOneByOne::create();

	touchListener->onTouchBegan = [=](cocos2d::Touch* touch, cocos2d::Event*) {
	//if the game is paused
	if(cocos2d::Director::getInstance()->isPaused() || !canMove){
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
		if(!canMove)
			return;
		auto desP = touch->getLocation() + this->h_vec;
		this->setPosition(MAX(minX,MIN(desP.x, maxX)), MAX(minY,MIN(desP.y, maxY)));
	};
	touchListener->onTouchEnded = [=](cocos2d::Touch* touch, cocos2d::Event*){
	};
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener,this);

}

void Hero::down(){
	auto animation = AnimationCacheInstance->getAnimation("Hero Down");
    auto animate = cocos2d::Animate::create(animation);
	this->runAction(animate);
}

void Hero::rebirthHero(){
	h_hp--;
	auto stopHero = cocos2d::CallFunc::create([=](){
		setActive(false);
		setMove(false);
	});
	auto animation = AnimationCacheInstance->getAnimation("Hero Down");
	auto animate = cocos2d::Animate::create(animation);
	auto getBack = cocos2d::CallFunc::create([=](){
		setPositionX(VISIBLE_SIZE.width / 2);
		setPositionY(VISIBLE_SIZE.height / 8);
	});
	auto activeHero = cocos2d::CallFunc::create([=](){
		setActive(true);
	});
	auto moveHero = cocos2d::CallFunc::create([=](){
		canMove = true;
	});
	auto blin = cocos2d::Blink::create(2, 6);
	this->runAction(cocos2d::Sequence::create(stopHero, animate, getBack, moveHero, blin, activeHero, nullptr));
}