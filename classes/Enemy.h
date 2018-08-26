#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include <SimpleAudioEngine.h>

//敌机类型
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
    void destroyedAnim();

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
    //敌机移动速度
    float e_speed;
    //敌机血量
    int e_hp;   
	//score
	int e_score;
	static float e_LevelSpeed;
};
#endif