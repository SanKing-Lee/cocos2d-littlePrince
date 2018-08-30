#pragma once

//libraries and namespace
#include <cocos2d.h>
#include <SimpleAudioEngine.h>
using namespace std;
using namespace cocos2d;
using namespace CocosDenshion;

//Singleton Object
#define VisSize				Director::getInstance()->getVisibleSize()
#define Audio				SimpleAudioEngine::getInstance()
#define MyAnimationCache	AnimationCache::getInstance()
#define MyUserDefault		UserDefault::getInstance()
#define MyFrameCache		SpriteFrameCache::getInstance()

//tag
#define BG1_TAG						1
#define BG2_TAG						2
#define HERO_TAG					3
#define SL_TAG						4
#define PROP_TAG					5
#define MENU_TAG					6
#define ITEM_BOMB_TAG				7
#define LABEL_BOMB_TAG				8
#define RESTART_TAG					9
#define RESTARTMENU_TAG				10
#define FINALSCORELABEL_TAG			11
#define HIGHSCORE_TAG				12
#define RANK_TAG					13
#define RANKMENU_TAG				14
#define RANKNAME_TAG				15
#define HEROPH_TAG					16
#define COVER_TAG                   17
#define GOLD_LABEL_TAG              18
#define GOLD_TAG                    19
#define RETURN_TAG                  20
#define RETURNMENU_TAG              21
#define MONEY_TAG                   22
#define MENUSTORE_TAG               23
#define SMALLHERO_TAG				24
#define  PROTECT_TAG 25
#define SPEEDDOWN_TAG 26
#define SNOW_SPRITE_TAG 27

//layer
#define BG_LAYER					-1
#define HERO_LAYER					0
#define BULLET_LAYER				1
#define ENEMY_LAYER					2
#define UI_LAYER					4

//hp
#define HP_METEORITE				10000
#define HP_SMALL					1
#define HP_MIDDLE					15
#define HP_BIG						30
#define HP_HERO						5	//default 3
#define HP_FORT                     8
#define HP_TRACK					2
#define HP_CURVE					1
#define HP_FIRST_BOSS				200
#define HP_SECOND_BOSS			350
#define HP_THIRD_BOSS				500
#define HP_BOSS 1000

//hero
#define HERO_ONE_HP					5	//default 3

//speed (px)
#define SP_BG						2
#define SP_METEORITE				3
#define SP_SMALL					4
#define SP_MIDDLE					1
#define SP_BIG						0.5f
#define SP_HERO_BULLET				12
#define SP_ENEMY_BULLET				1
#define SP_ENEMY_INCREMENT			0.1f
#define ENEMY_SPEED_DOWN_MULTI		0.5f
#define SP_TRACK					2
#define SP_FORT						1.5f
#define SP_CURVE					3
#define SP_FIRST_BOSS				1.0f
#define SP_SECOND_BOSS				1.0f
#define SP_THRID_BOSS				1.0f
#define SP_BOSS 2


//delay (s)
#define HIT_DELAY					0.2f
#define ENEMY_DESTROY_DELAY			0.1f
#define HERO_DESTROY_DELAY			0.2f
#define BIG_FLY_DELAY				0.2f
#define HERO_FLY_DELAY				0.1f
#define ENEMY_SPEED_REGAIN_DELAY    2
#define STAR_TWINKLE_DELAY          0.1f

//score lable off
#define SL_XOFF						20
#define SL_YOFF						20

//score
#define SCORE_METEORITE				5
#define SCORE_SMALL					10
#define SCORE_MIDDLE				50
#define SCORE_BIG					100
#define SCORE_FORT					100
#define SCORE_TRACK					100
#define SCORE_CURVE					100
#define SCORE_FIRST_BOSS			5000
#define SCORE_SECOND_BIG			6000
#define SCORE_THRID_BIG				7000
#define SPEED_LEVELUP_SCORE			500
#define SCORE_CREATEBOSS			100  //default 2000
#define SCORE_BOSS 2000

//create interval (s)
#define HERO_BULLET_INTERVAL		0.1f
#define ENEMY_BULLET_INTERVAL		1
#define SMALLENEMY1_INTERVAL		1.0f
#define SMALLENEMY2_INTERVAL		0.3f
#define SMALLENEMY2GROUP_INTERVAL	5	//default 10
#define MIDDLEENEMY_INTERVAL		8
#define BIGENEMY_INTERVAL			20
#define FORTENEMY_INTERVAL          15
#define TRACKENEMY_INTERVAL         9
#define CURVEENEMY_INTERVAL			7
#define METEORITEENEMY_INTERVAL     6
#define FIRSTBOSSENEMY_INTERVAL		1
#define SECONDBOSSENEMY_INTERVAL	1	
#define THIRDBOSSENEMY_INTERVAL		1
#define PROP_INTERVAL				8  //default 15


//repeate
#define REPEAT_FOREVER				-1

//create delay (s)
#define SMALLENEMY1_DELAY			2
#define SMALLENEMY2_DELAY			0
#define SMALLENEMY2GROUP_DELAY		5
#define MIDDLEENEMY_DELAY			5
#define BIGENEMY_DELAY				14
#define FORTENEMY_DELAY				10
#define TRACKENEMY_DELAY			10
#define METEORITEENEMY_DELAY		3
#define CURVEENEMY_DELAY			17
#define FIRSTBOSSENEMY_DELAY		20
#define SECONDBOSSENEMY_DELAY		40
#define THIRDBOSSENEMY_DELAY		40
#define PROP_DELAY					10


//limit
#define DOUBLEBULLET_NUMBER			40
#define MULTIBULLET_NUMBER			20
#define MAX_RANK_NUMBER				3
#define PROPTYPE_NUMBER				3
#define MAX_BOMB_NUMBER				10
#define OFFSET_NUMBER				100
#define SHOPITEMS					6

//the repetitions of scedule(), that means the number of small enemy is 4
#define GROUP_SMALL_NUMBER			3   

//attack
#define	BULLET1_ATTACK				1
#define BULLET2_ATTACK				2
#define BOMB_ATTACK					100
#define HERO_HIT_ATTACK				0	//default 50

//offset
#define X_OFFSET					2
#define Y_OFFSET					1