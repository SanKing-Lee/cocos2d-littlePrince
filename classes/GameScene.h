#ifndef _GAMESCENE_H_ //∑¿÷π÷ÿ∂®“Â
#define _GAMESCENE_H_
#include "cocos2d.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Prop.h"
#include "Hero.h"
#include "OverScene.h"
#include "GameStoreScene.h"
#include "SuccessScene.h"

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
	Point e_smallGroupPosition;
	int m_GameLevel;
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
	bool m_isBossScene;
	bool m_isProtected;
	int isCallenemy;
	bool isGoThrough;
	bool isBossDie;
	bool removeEnemy;

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

	
	Vector<Bullet*> e_bullets;
	Vector<Bullet*> e_left_bullets;
	Vector<Bullet*> e_right_bullets;
	Vector<Bullet*> e_track_bullets;
	Vector<Bullet*> e_Fort_bullets;
	Vector<Bullet*> e_Big_bullets;

	Vector<Bullet*> removableBullets_e1;
	Vector<Bullet*> removableBullets_e2;
	Vector<Bullet*> removableBullets_e3;
	Vector<Bullet*> removableBullets_e4;
	Vector<Bullet*> removableBullets_e5;
	Vector<Bullet*> removableBullets_e6;

	void createEnemysingleBullet(float);
	void createEnemytribleBullet(float);
	void createEnemytrackBullet(float);
	void createEnemyFortBullet(float);
	void createEnemyBigBullet(float);
	//zqh add skill
	void callLittleEnemy(Enemy*);
	//collision detection
	void collisionDetection(Hero*,Bullet*,Vector<Bullet*>&);

	void clearCrossBullet(Vector<Bullet*>&,Vector<Bullet*>&);
	//

	//enemy
    Vector<Enemy*> g_enemies; 
	Vector<Enemy*> removableEnemies;
	Vector<Enemy*> little_enemies;
    void createSmallEnemy(float);
    void createMiddleEnemy(float);
    void createBigEnemy(float);
    void createEnemy(EnemyType);
	void createTrackEnemy(float);
	void trackEnemyMove(Enemy*);
	void createMeteoriteEnemy(float);
	void createFortEnemy(float);
	void createFirstBossEnemy(float);
	void createSecondBossEnemy(float);
	void createThirdBossEnemy(float);

    void createSmallEnemy1(float);
	void createSmallEnemy2(float);
	void createSmallEnemy2Group(float);
	void createEnemy(EnemyType, Point);
	//add zqh 
	void setisCallEnemy(int count) { isCallenemy = count; };
	int getisCallEnemy() { return isCallenemy; };
	void cleartrackBullet(float);
	void crashEnemybulletAndHero();
	//

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

	void updateSpeed();


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

	//boss
	bool canCreateBoss();
	void createBoss();
	void GameOver();
	void jumpToBoss();

	void goThrough();
};
#endif