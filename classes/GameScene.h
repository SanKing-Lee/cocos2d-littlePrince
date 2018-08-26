#ifndef _GAMESCENE_H_ //防止重定义
#define _GAMESCENE_H_
#include "cocos2d.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Prop.h"
#include "Hero.h"

USING_NS_CC;

class GameScene:public Layer {
public:
	GameScene();
	//CREATE_FUNC(GameScene);
	static Scene* createScene();
	static GameScene* create();
	bool init();
	
	//定时器函数必须是void返回类型，必须有一个float类型的参数，刷新图片必用
	void update(float dt);

private:
	//the score
	int m_score;
	//cocos2d::Point m_vec;
	int m_doubleBulletCount;
	int m_triBulletCount;
	int m_BombCount;

	//英雄子弹集合
	Vector<Bullet*> h_bullets;
	Vector<Bullet*> removableBullets;
	//创建子弹
	void createBullet(float); 	
	void createSingleBullet();
	void createDoubleBullet();
	void createTriBullet();

	//敌机集合
    Vector<Enemy*> h_enemies; 
	Vector<Enemy*> removableEnemies;
    //创建敌机
    void createSmallEnemy(float);
    void createMiddleEnemy(float);
    void createBigEnemy(float);
    void createEnemy(EnemyType);

	void menuCloseCallback(Ref* pSender);
	void PauseAndResume(Ref* ref);
	void bomb(Ref* ref);

	//create prop
	Vector<Prop*> h_props;
	Vector<Prop*> removableProps;
	void createProp(float);

	//create hero
	void createHero();
	Vector<Sprite*> hero_hp;

	//create background
	void createBackground();
	void createFameCache();
	void playBackgroundMusic();
	void createMenu_PauseAndResume();
	void displayBombs();
	void displayScore();
	void updateHeroHP();
	void createSprites();
	void createHeroHP();
	void updateBomb();

	//
	void moveBackground();
	void flyBullets();
	void flyEnemys();
	void crashEnemyAndHeroAndBullet();
	void crashPropAndHero();
};
#endif