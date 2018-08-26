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


//delay
#define HIT_DELAY 0.2f
#define DOWN_DELAY 0.1f
#define HERO_DOWN_DELAY 0.2f

//score lable off
#define SL_XOFF 20
#define SL_YOFF 20

//score
#define SCORE_SMALL 100
#define SCORE_MIDDLE 1000
#define SCORE_BIG 5000

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

#define MAX_RANK 8
#define PROPTYPENUMBER 3