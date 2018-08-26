#ifndef __ENEMY_H__
#define __ENEMY_H__
#include "cocos2d.h"
#include <SimpleAudioEngine.h>

//�л�����
typedef enum 
{
    SMALL_ENEMY,
    MIDDLE_ENEMY,
    BIG_ENEMY
}EnemyType;

class Enemy : public cocos2d::Sprite {
public:
    Enemy();
    static Enemy* create(EnemyType);
    bool init(EnemyType);

    //��ײ
    void hit();
    //�ݻ�
    void down();

	EnemyType getType(){return e_type;};

	float getStep(){return e_step + levelSpeed;}

	int getHP(){return e_hp;}
	void setHP(int hp){e_hp = hp;}
	int getScore(){return e_score;}
	static void increeLevelSpeed();
	static void clearLevelSpeed();
	void fly();
private:
    EnemyType e_type;
    //�л��ƶ��ٶ�
    float e_step;
    //�л�Ѫ��
    int e_hp;   
	//score
	int e_score;
	static float levelSpeed;
};
#endif