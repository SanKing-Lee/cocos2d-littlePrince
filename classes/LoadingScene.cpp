#include "LoadingScene.h"
#include "CommonData.h"
#include "GameScene.h"
#include <SimpleAudioEngine.h>

USING_NS_CC;

LoadingScene::LoadingScene(){
	
}

LoadingScene* LoadingScene::create(){
	auto pp = new LoadingScene();
	if(pp && pp->init())
	{
		pp->autorelease();
		return pp;
	}
	else
	{
		delete pp;
		pp = NULL;
		return NULL;
	}
}

cocos2d::Scene* LoadingScene::createScene(){
	auto scene = cocos2d::Scene::create();

	//"layer" is an autorelease object
	auto layer = LoadingScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	//return the scene
	return scene;
}

bool LoadingScene::init(){
	srand((unsigned)(time(NULL)));

	//preload backgroundmusic and effect
	preloadMusic();

	//frame cache
	createFrameCache();

	//animation cache
	createAnimationCache();

	//background
	createBackground();

	//the hero plane
	createHero();

	//loading animation
	createLoadingAnimation();
	return true;
}

void LoadingScene::preloadMusic(){
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadBackgroundMusic("game_music.mp3");
	audio->preloadEffect ("big_spaceship_fly.mp3");
	audio->preloadEffect("bullet.mp3");
	for(int i = 0; i < 3; i++)
	{
		auto	effectName = StringUtils::format("enemy%d_down.mp3", i+1);
	}
	audio->preloadEffect("game_over.mp3");
	audio->preloadEffect("get_bomb.mp3");
	audio->preloadEffect("get_double_laser.mp3");
	audio->preloadEffect("out_prop.mp3");
	audio->preloadEffect("use_bomb.mp3");
}

void LoadingScene::createAnimationCache(){
	//hero fly
	auto heroFly = Animation::create();
	heroFly->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
	heroFly->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));

	heroFly->setDelayPerUnit(0.1f);
	heroFly->setLoops(-1);	
	AnimationCacheInstance->addAnimation(heroFly, "Hero Fly");

	//big enemy fly
	auto bigEnemyFly = Animation::create();	
	bigEnemyFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("enemy3_n1.png"));
	bigEnemyFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("enemy3_n2.png"));

	bigEnemyFly->setDelayPerUnit(0.2f);
	bigEnemyFly->setLoops(-1);
	AnimationCacheInstance->addAnimation(bigEnemyFly, "Big Enemy Fly");

	//enemy hurt
	//middle enemy
	auto middleEnemyHurt = Animation::create();
    middleEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
        getSpriteFrameByName("enemy2_hit.png"));
    middleEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
        getSpriteFrameByName("enemy2.png"));
	middleEnemyHurt->setDelayPerUnit(HIT_DELAY);
	AnimationCacheInstance->addAnimation(middleEnemyHurt, "Middle Enemy Hurt");

	//big enemy
	auto bigEnemyHurt = Animation::create();
    bigEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->    
        getSpriteFrameByName("enemy3_hit.png"));
    bigEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
        getSpriteFrameByName("enemy3_n1.png"));
	bigEnemyHurt->setDelayPerUnit(HIT_DELAY);
	AnimationCacheInstance->addAnimation(bigEnemyHurt, "Big Enemy Hurt");


	//hero down
	auto heroDown = Animation::create();
	for(int i = 0; i < 4; i ++){
            auto png = cocos2d::StringUtils::format("hero_blowup_n%d.png", i+1);
            heroDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
	heroDown->setDelayPerUnit(HERO_DOWN_DELAY);
	AnimationCacheInstance->addAnimation(heroDown, "Hero Down");

	//enemy down
	//small enemy down
	auto smallEnemyDown = Animation::create();
	for (int i = 0; i < 4; i++)
    {
        auto png = cocos2d::StringUtils::format("enemy1_down%d.png", i+1);
        smallEnemyDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
    }
	smallEnemyDown->setDelayPerUnit(DOWN_DELAY);
	//auto animate = Animate::create(animation);
	AnimationCacheInstance->addAnimation(smallEnemyDown, "Small Enemy Down");
	
	//middle enemy down
	auto middleEnemyDown = Animation::create();
	for (int i = 0; i < 4; i++)
    {
        auto png = cocos2d::StringUtils::format("enemy2_down%d.png", i+1);
        middleEnemyDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
    }   
	middleEnemyDown->setDelayPerUnit(DOWN_DELAY);
	AnimationCacheInstance->addAnimation(middleEnemyDown, "Middle Enemy Down");

	//big enemy down
	auto bigEnemyDown = Animation::create();
	for (int i = 0; i < 4; i++)
    {
        auto png = cocos2d::StringUtils::format("enemy3_down%d.png", i+1);
        bigEnemyDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
    }   
	bigEnemyDown->setDelayPerUnit(DOWN_DELAY);
	AnimationCacheInstance->addAnimation(bigEnemyDown, "Big Enemy Down");
}

void LoadingScene::createFrameCache(){
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
}

void LoadingScene::createBackground(){
	//the first background picture
	auto bg1 = cocos2d::Sprite::createWithSpriteFrameName("background.png");
	bg1->setAnchorPoint(cocos2d::Point(0,0));
	bg1->getTexture()->setAliasTexParameters();
	this->addChild(bg1, BG_LAYOUT, BG1_TAG);
}

void LoadingScene::createHero(){
	auto bg1 = this->getChildByTag(BG1_TAG);
	auto hero = Hero::create();
	hero->setPositionX( VISIBLE_SIZE.width / 2);
	hero->setPositionY(VISIBLE_SIZE.height / 6);
	hero->fly(); 
	this->addChild(hero, HERO_LAYOUT, HERO_TAG);
}

void LoadingScene::createLoadingAnimation(){
	cocos2d::Vector<SpriteFrame* > frames;
	for (int i = 0; i < 4; i++)
	{
		auto frameName = StringUtils::format("game_loading%d.png", i+1);
		frames.pushBack(SpriteFrameCache::getInstance()->getSpriteFrameByName(frameName));
	}
	auto loadAni = Animation::createWithSpriteFrames(frames, 0.2f, 2);

	auto loading = Sprite::create();
	loading->setPosition(Point(VISIBLE_SIZE/2));
	this->addChild(loading);
	
	auto seq = Sequence::create(Animate::create(loadAni), CallFunc::create([](){
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	), nullptr);

	loading->runAction(seq);	
}