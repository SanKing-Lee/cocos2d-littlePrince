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
	Dictionary* data;
	//Vector<String> dataItemNames;
private:
	//member vraibles
	//score
	int m_heroHPLimit;
	int m_heroHP;
	int m_heroLevel;
	int m_score;
	//gold
	int m_gold;
	//the number of double-bullets
	int m_doubleBulletCount;
	//the number of multi-bullets
	int m_multiBulletCount;
	//the number of bombs
	int m_BombCount;
	//whether down enemy speed
	bool m_isEnemeySpeedDown;
	float m_EnemySpeedMulti;
	bool m_isProtected;

	void readData();
	void writeData();

	//bullet
	//sum of bulltes created
	Vector<Bullet*> g_bullets;
	//sum of bulltes to be removed
	Vector<Bullet*> removableBullets;
	void createBullet(float); 	
	void createSingleBullet();
	void createDoubleBullet();
	void createMultiBullet();

	//enemy
    Vector<Enemy*> g_enemies; 
	Vector<Enemy*> removableEnemies;
    void createSmallEnemy(float);
    void createMiddleEnemy(float);
    void createBigEnemy(float);
    void createEnemy(EnemyType);

	//create prop
	Vector<Prop*> h_props;
	//props enemy carry
	Vector<Prop*> removableProps;
	void createEnemyProp(PropType type, Point pos);
	void createPropwithSchedule(float);
	void createPropwhenEnemyDestroyed(Enemy* enemy);

	//create hero
	void createHero();
	Vector<Sprite*> hero_hp;

	//create all the sprites above with schedule
	void createSprites();

	//Callback funcations
	void menuCloseCallback(Ref* pSender);
	void PauseAndResume(Ref* ref);
	void bomb(Ref* ref);

	//create layout
	void createBackground();
	void createFameCache();
	void createMenu_PauseAndResume();
	void playBackgroundMusic();

	void createHeroHP();
	void updateHeroHP();

	void displayBombs();
	void updateBomb();

	void createScoreLabel();
	void updateScoreLabel();
	void createGoldLabel();
	void updateGoldLabel();


	//enemy speed down
	void downEnemySpeed();
	void regainEnemySpeed(float);

	//hero protect cover
	void createProtect();
	void vanishProtect(float);
	void updateProtect();

	//animation
	void moveBackground();
	void flyBullets();
	void flyEnemys();
	void flyEnemyProp();

	//crash check
	void crashEnemyAndHeroAndBullet();
	void crashPropAndHero();

	void GameOver();
};
#endif