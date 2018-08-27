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
		Sprite::initWithSpriteFrameName("ufo1.png");
		break;
	case Bomb:
		Sprite::initWithSpriteFrameName("ufo2.png");
		break;
	case Hp:
		Sprite::initWithFile("propHP.png");
		break;
	case Gold:
		Sprite::initWithFile("CloseNormal.png");
		break;
	case ProtectCover:
		Sprite::initWithFile("CloseSelected.png");
		break;
	case SpeedDown:
		Sprite::initWithFile("Rank.png");
		break;
	default:
		break;
	}
	return true;
}