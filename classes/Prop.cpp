#include "Prop.h"

Prop::Prop(){
	p_type = Enhance_Bullet;
}

Prop* Prop::create(PropType type){
	auto prop = new Prop();
	if(prop && prop->init(type)){
		prop->autorelease();
		return prop;
	}
	delete prop;
	prop = nullptr;
	return nullptr;
}

bool Prop::init(PropType type){
	p_type = type;
	switch(type){
	case  Enhance_Bullet:
		cocos2d::Sprite::initWithSpriteFrameName("ufo1.png");
		break;
	case Bomb:
		cocos2d::Sprite::initWithSpriteFrameName("ufo2.png");
		break;
	case Hp:
		cocos2d::Sprite::initWithFile("propHP.png");
		break;
	default:
		break;
	}
	return true;
}