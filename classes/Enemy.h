#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include <SimpleAudioEngine.h>
#include "Prop.h"

//µ–ª˙¿‡–Õ
typedef enum 
{
    SMALL_ENEMY,
    MIDDLE_ENEMY,
    BIG_ENEMY
}EnemyType;

class Enemy : public cocos2d::Sprite {
public:

    static Enemy* create(EnemyType);
    bool init(EnemyType);

    void hitAnim();
    void destroyedAnim(int);

	//type visitor
	EnemyType getType(){return e_type;};
	void setType(EnemyType type){ e_type = type;};

	//speed visitor
	float getSpeed(){return e_speed + e_LevelSpeed;}
	void setSpeed(float sp){ e_speed = sp;};

	//hp visitor
	int getHP(){return e_hp;}
	void setHP(int hp){e_hp = hp;}

	//score visitor
	int getScore(){return e_score;}
	void setScore(int score){e_score = score;};

	//
	bool isDestroyed() { return e_hp <= 0; };

	static void increeLevelSpeed(int);
	static void clearLevelSpeed();

private:
    EnemyType e_type;

    float e_speed;


    int e_hp;   
	//score
	int e_score;
	//the prop that enemy catch
	PropType e_prop;
	static float e_LevelSpeed;
};
#endif