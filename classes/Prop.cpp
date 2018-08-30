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
		Sprite::initWithSpriteFrameName("double_bullet.png");
		break;
	case Bomb:
		Sprite::initWithSpriteFrameName("clear_up.png");
		break;
	case Hp:
		Sprite::initWithFile("hp_up.png");
		break;
	case Gold:
		Sprite::initWithFile("money.png");
		break;
	case ProtectCover:
		Sprite::initWithFile("protective.png");
		break;
	case SpeedDown:
		Sprite::initWithFile("freeze.png");
		break;
	default:
		break;
	}
	return true;
}