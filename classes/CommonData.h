#define VISIBLE_SIZE cocos2d::Director::getInstance()->getVisibleSize()
#define Audio CocosDenshion::SimpleAudioEngine::getInstance()
#define AnimationCacheInstance cocos2d::AnimationCache::getInstance()
#define UserDefaultInstance cocos2d::UserDefault::getInstance()

//tag
#define BG1_TAG 1
#define BG2_TAG 2
#define HERO_TAG 3
#define SL_TAG 4
#define PROP_TAG 5
#define MENU_TAG 6
#define ITEM_BOMB_TAG 7
#define LABEL_BOMB_TAG 8
#define RESTART_TAG 9
#define RESTARTMENU_TAG 10
#define FINALSCORELABEL_TAG 11
#define HIGHSCORE_TAG 12
#define RANK_TAG 13
#define RANKMENU_TAG 14
#define RANKNAME_TAG 15
#define HEROPH_TAG 16
#define COVER_TAG 17
#define GOLD_LABEL_TAG 18
#define GOLD_TAG 19
#define RETURN_TAG 20
#define RETURNMENU_TAG 21

//layout
#define BG_LAYOUT -1
#define HERO_LAYOUT 0
#define BULLET_LAYOUT 1
#define ENEMY_LAYOUT 2
#define UI_LAYOUT 4

//HP
#define HP_SMALL 1
#define HP_MIDDLE 10
#define HP_BIG 30
#define HP_HERO 3

//speed
#define SP_SMALL 4
#define SP_MIDDLE 1
#define SP_BIG 0.5f
#define SP_BULLET 12
#define SP_BG 2
#define BULLETS_SPEED				5

#define	ENEMY_SPEED_DOWN_MULTI 0.5
#define LEVEL_SCORE 200

//delay
#define HIT_DELAY 0.2f
#define DOWN_DELAY 0.1f
#define HERO_DOWN_DELAY 0.1f
#define ENEMY_SPEED_REGAIN_DELAY 2
#define STAR_TWINKLE_DELAY 0.1f

//score Label off
#define SL_XOFF 20
#define SL_YOFF 20

//score
#define SCORE_SMALL 10
#define SCORE_MIDDLE 100
#define SCORE_BIG 500

//create interval
#define BULLET_INTERVAL 0.1f
#define SMALLENEMY_INTERVAL 0.8f
#define MIDDLEENEMY_INTERVAL 10
#define BIGENEMY_INTERVAL 20
#define PROP_INTERVAL 10

//repeate
#define REPEAT_FOREVER -1

//create delay
#define SMALLENEMY_DELAY 2
#define MIDDLEENEMY_DELAY 8
#define BIGENEMY_DELAY 14
#define PROP_DELAY 3

//
#define DOUBLEBULLET_QUANTITY 100
#define TRIBULLET_QUANTITY 30

#define MAX_RANK 3
#define PROPTYPENUMBER 6
#define SHOPITEMS 6

//hero
#define HERO_ONE_HP 3

//attack
#define	BULLET1_ATTACK				1
#define BULLET2_ATTACK				2
#define BOMB_ATTACK					20
#define HERO_HIT_ATTACK				50

#include <cocos2d.h>
#include <SimpleAudioEngine.h>

USING_NS_CC;