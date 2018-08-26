#ifndef _GAMESCENE_H_ //∑¿÷π÷ÿ∂®“Â
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
	static Scene* createScene();
	static GameScene* create();
	bool init();
	void update(float dt);

private:
	int m_score;
	int m_doubleBulletCount;
	int m_multiBulletCount;
	int m_BombCount;
	Vector<Bullet*> h_bullets;
	Vector<Bullet*> removableBullets;
	void createBullet(float); 	
	void createSingleBullet();
	void createDoubleBullet();
	void createMultiBullet();

    Vector<Enemy*> h_enemies; 
	Vector<Enemy*> removableEnemies;
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
	void createHero(HeroType htype);
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