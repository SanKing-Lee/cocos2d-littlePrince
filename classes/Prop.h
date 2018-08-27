#pragma once
#include <cocos2d.h>
typedef enum{
	Gold,
	SpeedDown,
	Enhance_Bullet,
	Bomb,
	ProtectCover,
	Hp
}PropType;

class Prop: public cocos2d::Sprite {
private:
	PropType p_type;
public:
	Prop();
	static Prop* create(PropType type);
	bool init(PropType type);
	PropType getType(){return p_type;};
};