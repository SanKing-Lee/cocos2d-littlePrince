#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include <SimpleAudioEngine.h>
#include "Prop.h"

//µÐ»úÀàÐÍ
typedef enum 
{
   /* SmallEnemy1,
	SmallEnemy2,
    MiddleEnemy,
    BigEnemy,*/
	Boss,
	Meteorite_ENEMY,//down only
	SmallEnemy1,//one bullet
	MiddleEnemy,//double bullet
	BigEnemy,//trible bullet
	FORT_ENEMY,//set a fort to attack
	TRACK_ENEMY,//set a enemy which can track you 
	SmallEnemy2,// Curve come
	FirstBoss_ENEMY,
	SecondBoss_ENEMY,
	ThirdBoss_ENEMY,
}EnemyType;

enum CurveDirection
{
	CLeft,
	CRight,
	CNone
};

enum LineDirection
{
	LLeft,
	LRight,
	LStraight
};

enum BossDirection
{
	LeftUp,
	LeftDown,
	RightUp,
	RightDown,
	Up,
	Down,
	None
};


class Enemy : public cocos2d::Sprite {
public:
	Enemy();
	~Enemy();
    static Enemy* create(EnemyType);
    bool init(EnemyType);

    void hitAnim();
    void destroyedAnim();

	//type visitor
	EnemyType getType(){return e_type;};
	void setType(EnemyType type){ e_type = type;};
	EnemyType getEnemyType(){return e_type;};
	//speed visitor
	float getSpeed(){return e_speed + e_LevelSpeed;}
	void setSpeed(float sp){ e_speed = sp;};
	static float getLevelSpeed() {return e_LevelSpeed;}
	//hp visitor
	int getHP(){return e_hp;}
	void setHP(int hp){
		if(e_type == FirstBoss_ENEMY || e_type == SecondBoss_ENEMY || e_type == ThirdBoss_ENEMY)
			e_hp = hp;
		else{
			if(hp >= 0) 
				e_hp = hp;
			else 
				e_hp = 0;
		}
	};
	//score visitor
	int getScore(){return e_score;};
	void setScore(int score){e_score = score;};

	//
	bool isDestroyed() { return e_hp <= 0; };

	static void updateLevelSpeed(int);
	static void clearLevelSpeed();

	//small enemy 2
	void move2();
	//others
	void move(float x, float y);

	bool canChangeLineDirection();
	//line direction visitor
	LineDirection getLineDirection() { return e_lineDirection; };
	void changeLineDirection();

	void updateBossDirection();

	//judge whether the enemy is out of screen
	bool beyondLimitX();
	bool beyondLimitY();
	bool beyondLimitMinX();
	bool beyondLimitMaxX();

	bool bossBeyondLimitMinX();
	bool bossBeyondLimitMinY();
	bool bossBeyondLimitMaxX();
	bool bossBeyondLimitMaxY();

	static CurveDirection e_curveDirection;

private:
    EnemyType e_type;

    float e_speed;
	
	int e_bigFlySoundId;

    int e_hp;   
	//score
	int e_score;
	//the prop that enemy catch
	PropType e_prop;
	static float e_LevelSpeed;
	bool e_canMove;

	LineDirection e_lineDirection;

	int cnt;

	BossDirection e_bossDirection;
};
#endif