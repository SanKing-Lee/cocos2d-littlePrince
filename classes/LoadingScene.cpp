#include "LoadingScene.h"
#include "CommonData.h"
#include "GameScene.h"
#include <SimpleAudioEngine.h>
#include <cstring>

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

	//
	initData();

	//frame cache
	createFrameCache();

	//animation cache
	createAnimationCache();
	Audio->playBackgroundMusic("loading_bk.mp3");
	auto bg = Sprite::createWithSpriteFrameName("bg_loaing1.png");
	bg->setAnchorPoint(Point::ZERO);
	this->addChild(bg, -1);

	//添加开始游戏键盘
	auto bg22=Sprite::createWithSpriteFrameName("menu.png");

	//添加小人
	auto smallpri = Sprite::createWithSpriteFrameName("little_prince.png");
	//smallpri->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	smallpri->setPosition(VisSize.width/2, VisSize.height/6);

	this->addChild(smallpri,1,10);//


	//进入游戏
	auto menuItemBack = MenuItemSprite::create(bg22, bg22, [](Ref *){
		SimpleAudioEngine::getInstance()->playEffect("button.mp3");

		auto scene = GameBegin::createScene();//change the scene
		Director::getInstance()->replaceScene(scene);
	});
	float x = VisSize.width/2; 
	float y=VisSize.height/8;
	menuItemBack->setPosition(x,y);

	auto menu = Menu::create(menuItemBack, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu,1);

	auto sunset = Sprite::createWithSpriteFrameName("sun1.png");
	sunset->setPosition(VisSize.width/2, VisSize.height/2);
	this->addChild(sunset,0);
	auto sunanimation=Animation::create();
	for(int i=1;i<=12;i++)
	{
		auto sunset=StringUtils::format("sun%d.png",i);
		///	auto spriteFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName(sunset);
		sunanimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(sunset));
	}
	sunanimation->setDelayPerUnit(0.4f);
	sunset->runAction(Animate::create(sunanimation));

	///zwj 
	auto stars = Sprite::createWithSpriteFrameName("stars1.png");
	stars->setPosition(VisSize.width/2, VisSize.height/2);
	this->addChild(stars,0);
	sunanimation=Animation::create();
	for(int i=1;i<=21;i++)
	{
		auto stars=StringUtils::format("stars%d.png",i);
		///	auto spriteFrame=SpriteFrameCache::getInstance()->getSpriteFrameByName(sunset);
		sunanimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(stars));
	}
	sunanimation->setDelayPerUnit(0.08f);
	sunanimation->
		setLoops(-1);
	stars->runAction(Animate::create(sunanimation));
	//zwj

	this->scheduleUpdate();
	return true;

	//background
	//createBackground();

	//the hero plane
	//createHero(HeroOne);

	//loading animation
	//createLoadingAnimation();
}

void LoadingScene::initData(){
	if(!(MyUserDefault->getBoolForKey("isExist", false))){
		MyUserDefault->setBoolForKey("isExist", true);

		MyUserDefault->setIntegerForKey("Gold", 50);
		MyUserDefault->setIntegerForKey("HeroHP", 3);
		MyUserDefault->setIntegerForKey("Bomb", 0);
		MyUserDefault->setIntegerForKey("HeroLevel", 1);
		MyUserDefault->setBoolForKey("ProtectCover", false);
		MyUserDefault->setIntegerForKey("GameLevel", 1);
		MyUserDefault->setBoolForKey("SpeedDown", false);
	}
		MyUserDefault->setIntegerForKey("Score", 0);
}

void LoadingScene::preloadMusic(){
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->preloadEffect("out_prop.mp3");
	audio->preloadEffect("use_bomb.mp3");
	audio->preloadBackgroundMusic("background1.mp3");
	audio->preloadBackgroundMusic("background2.mp3");
	audio->preloadBackgroundMusic("background3.mp3");
	audio->preloadEffect("boss_boom.mp3");
	audio->preloadEffect("button.mp3");
	audio->preloadEffect("enemy_boom.mp3");
	audio->preloadEffect("gameover_bk.mp3");
	audio->preloadEffect("get_tool.mp3");
	audio->preloadEffect("hero_die_finally.mp3");
	/*audio->preloadEffect("hero_die_once.mp3");*/
	audio->preloadEffect("loadking_bk.mp3");
}

void LoadingScene::createFrameCache(){
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("level_list.plist");
	MyFrameCache->addSpriteFramesWithFile("ShopScene.plist");
	MyFrameCache->addSpriteFramesWithFile("LevelChoseScene.plist");
	MyFrameCache->addSpriteFramesWithFile("background.plist");
	MyFrameCache->addSpriteFramesWithFile("bullet.plist");
	MyFrameCache->addSpriteFramesWithFile("button.plist");
	MyFrameCache->addSpriteFramesWithFile("heroAndEnemy.plist");
	MyFrameCache->addSpriteFramesWithFile("loading.plist");
	MyFrameCache->addSpriteFramesWithFile("loadingScene.plist");
	MyFrameCache->addSpriteFramesWithFile("sunset.plist");
	MyFrameCache->addSpriteFramesWithFile("tool.plist");
	MyFrameCache->addSpriteFramesWithFile("game_over.plist");
}

void LoadingScene::createAnimationCache(){

	//Rank Star blink
	auto starTwinkling = Animation::create();
	for(int i = 0; i < 7; i ++){
            auto png = StringUtils::format("star%d.png", i+1);
            starTwinkling->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
	starTwinkling->setDelayPerUnit(STAR_TWINKLE_DELAY);
	starTwinkling->setLoops(-1);	
	MyAnimationCache->addAnimation(starTwinkling, "star twinkle");

	//hero1 fly
	auto hero1Fly = Animation::create();
	hero1Fly->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1_n1.png"));
	hero1Fly->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1_n2.png"));

	hero1Fly->setDelayPerUnit(0.3f);
	hero1Fly->setLoops(-1);	
	MyAnimationCache->addAnimation(hero1Fly, "Hero1 Fly");

	//hero2 fly
	auto hero2Fly = Animation::create();
	hero2Fly->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_n1.png"));
	hero2Fly->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2_n2.png"));

	hero2Fly->setDelayPerUnit(0.3f);
	hero2Fly->setLoops(-1);	
	MyAnimationCache->addAnimation(hero2Fly, "Hero2 Fly");

	//hero3 fly
	auto hero3Fly = Animation::create();
	hero3Fly->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("hero3_n1.png"));
	hero3Fly->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName("hero3_n2.png"));

	hero3Fly->setDelayPerUnit(0.3f);
	hero3Fly->setLoops(-1);	
	MyAnimationCache->addAnimation(hero3Fly, "Hero3 Fly");

	//first boss fly
	auto fbossFly = Animation::create();	
	fbossFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("BigEnemy1_n1.png"));
	fbossFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("BigEnemy1_n2.png"));

	fbossFly->setDelayPerUnit(0.2f);
	fbossFly->setLoops(-1);
	MyAnimationCache->addAnimation(fbossFly, "first boss Fly");

	//second boss fly
	auto sbossFly = Animation::create();	
	sbossFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("BigEnemy2_n1.png"));
	sbossFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("BigEnemy2_n2.png"));

	sbossFly->setDelayPerUnit(0.2f);
	sbossFly->setLoops(-1);
	MyAnimationCache->addAnimation(sbossFly, "second boss Fly");

	//third boss fly
	auto tbossFly = Animation::create();	
	tbossFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("BigEnemy3_n1.png"));
	tbossFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("BigEnemy3_n2.png"));

	tbossFly->setDelayPerUnit(0.2f);
	tbossFly->setLoops(-1);
	MyAnimationCache->addAnimation(tbossFly, "third boss Fly");

	//Curve fly
	auto CurveFly = Animation::create();	
	CurveFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("Curve_ENEMY_n1.png"));
	CurveFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("Curve_ENEMY_n2.png"));

	CurveFly->setDelayPerUnit(0.2f);
	CurveFly->setLoops(-1);
	MyAnimationCache->addAnimation(CurveFly, "Curve Fly");

	//Track fly
	auto TrackFly = Animation::create();	
	TrackFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("Creature_n1.png"));
	TrackFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("Creature_n2.png"));

	TrackFly->setDelayPerUnit(0.2f);
	TrackFly->setLoops(-1);
	MyAnimationCache->addAnimation(TrackFly, "Track Fly");

	//Fort fly
	auto FortFly = Animation::create();	
	FortFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("Battery_n1.png"));
	FortFly->addSpriteFrame(cocos2d::SpriteFrameCache::
		getInstance()->getSpriteFrameByName("Battery_n2.png"));

	FortFly->setDelayPerUnit(0.2f);
	FortFly->setLoops(-1);
	MyAnimationCache->addAnimation(FortFly, "Fort Fly");

	//enemy hurt
	//middle enemy
	auto middleEnemyHurt = Animation::create();
	middleEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("MiddleEnemy_hit.png"));
	middleEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("MiddleEnemy_n1.png"));
	middleEnemyHurt->setDelayPerUnit(HIT_DELAY);
	MyAnimationCache->addAnimation(middleEnemyHurt, "Middle Enemy Hurt");

	//Meteorite enemy
	auto MetroriteEnemyHurt = Animation::create();
	MetroriteEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("Meteorite_ENEMY_hit.png"));
	MetroriteEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("Meteorite_ENEMY.png"));
	MetroriteEnemyHurt->setDelayPerUnit(HIT_DELAY);
	MyAnimationCache->addAnimation(MetroriteEnemyHurt, "Meteorite Enemy Hurt");

	//Fort enemy
	auto FortEnemyHurt = Animation::create();
	FortEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("Battery_hit.png"));
	FortEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("Battery_n2.png"));
	FortEnemyHurt->setDelayPerUnit(HIT_DELAY);
	MyAnimationCache->addAnimation(FortEnemyHurt, "Fort Enemy Hurt");

	//first boss
	auto fbossEnemyHurt = Animation::create();
	fbossEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("BigEnemy1_hit.png"));
	fbossEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("BigEnemy1_n1.png"));
	fbossEnemyHurt->setDelayPerUnit(HIT_DELAY);
	MyAnimationCache->addAnimation(fbossEnemyHurt, "First Boss Hurt");

	//second boss
	auto sbossEnemyHurt = Animation::create();
	sbossEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("BigEnemy2_hit.png"));
	sbossEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("BigEnemy2_n1.png"));
	sbossEnemyHurt->setDelayPerUnit(HIT_DELAY);
	MyAnimationCache->addAnimation(sbossEnemyHurt, "Second Boss Hurt");

	//third boss
	auto tbossEnemyHurt = Animation::create();
	tbossEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("BigEnemy3_hit.png"));
	tbossEnemyHurt->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->
		getSpriteFrameByName("BigEnemy3_n1.png"));
	tbossEnemyHurt->setDelayPerUnit(HIT_DELAY);
	MyAnimationCache->addAnimation(tbossEnemyHurt, "Third Boss Hurt");

	//hero down animation
	//hero1 down
	auto hero1Down = Animation::create();
	for(int i = 0; i < 3; i ++){
		auto png = cocos2d::StringUtils::format("hero1_boom%d.png", i+1);
		hero1Down->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
	hero1Down->setDelayPerUnit(HERO_DESTROY_DELAY);
	MyAnimationCache->addAnimation(hero1Down, "Hero1 Down");

	//hero2 down
	auto hero2Down = Animation::create();
	for(int i = 0; i < 3; i ++){
		auto png = cocos2d::StringUtils::format("hero2_boom%d.png", i+1);
		hero2Down->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
	hero2Down->setDelayPerUnit(HERO_DESTROY_DELAY);
	MyAnimationCache->addAnimation(hero2Down, "Hero2 Down");

	//hero3 down
	auto hero3Down = Animation::create();
	for(int i = 0; i < 3; i ++){
		auto png = cocos2d::StringUtils::format("hero3_boom%d.png", i+1);
		hero3Down->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
	hero3Down->setDelayPerUnit(HERO_DESTROY_DELAY);
	MyAnimationCache->addAnimation(hero3Down, "Hero3 Down");


	//enemy down
	//small enemy down
	auto smallEnemyDown = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto png = cocos2d::StringUtils::format("SmallEnemy_boom%d.png", i+1);
		smallEnemyDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
	smallEnemyDown->setDelayPerUnit(ENEMY_DESTROY_DELAY);
	//auto animate = Animate::create(animation);
	MyAnimationCache->addAnimation(smallEnemyDown, "Small Enemy Down");

	//middle enemy down
	auto middleEnemyDown = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto png = cocos2d::StringUtils::format("MiddleEnemy_boom%d.png", i+1);
		middleEnemyDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}   
	middleEnemyDown->setDelayPerUnit(ENEMY_DESTROY_DELAY);
	MyAnimationCache->addAnimation(middleEnemyDown, "Middle Enemy Down");

	//fort enmey down
	auto fortEnemyDown = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto png = cocos2d::StringUtils::format("Battery_boom%d.png", i+1);
		fortEnemyDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}   
	fortEnemyDown->setDelayPerUnit(ENEMY_DESTROY_DELAY);
	MyAnimationCache->addAnimation(fortEnemyDown, "Fort Enemy Down");

	//track enemy down
	auto trackEnemyDown = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto png = cocos2d::StringUtils::format("Creature_boom%d.png", i+1);
		trackEnemyDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}   
	trackEnemyDown->setDelayPerUnit(ENEMY_DESTROY_DELAY);
	MyAnimationCache->addAnimation(trackEnemyDown, "Track Enemy Down");

	//curve enemy down

	auto curveEnemyDown = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto png = cocos2d::StringUtils::format("Curve_ENEMY_boom%d.png", i+1);
		curveEnemyDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}   
	curveEnemyDown->setDelayPerUnit(ENEMY_DESTROY_DELAY);
	MyAnimationCache->addAnimation(curveEnemyDown, "Curve Enemy Down");

	// first boos down
	auto firstBossDown = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto png = cocos2d::StringUtils::format("BigEnemy1_boom%d.png", i+1);
		firstBossDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}   
	firstBossDown->setDelayPerUnit(ENEMY_DESTROY_DELAY);
	MyAnimationCache->addAnimation(firstBossDown, "Firstboss Enemy Down");


	// secon boss down
	auto SecondBossDown = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto png = cocos2d::StringUtils::format("BigEnemy2_boom%d.png", i+1);
		SecondBossDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}   
	SecondBossDown->setDelayPerUnit(ENEMY_DESTROY_DELAY);
	MyAnimationCache->addAnimation(SecondBossDown, "Secondboss Enemy Down");


	// third boss down

	auto ThirdBossDown = Animation::create();
	for (int i = 0; i < 3; i++)
	{
		auto png = cocos2d::StringUtils::format("BigEnemy3_boom%d.png", i+1);
		ThirdBossDown->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}   
	ThirdBossDown->setDelayPerUnit(ENEMY_DESTROY_DELAY);
	MyAnimationCache->addAnimation(ThirdBossDown, "Thirdboss Enemy Down");

	//Track come now
	auto trackcome = Animation::create();
	for (int i = 0; i < 6; i++)
	{
		auto png = cocos2d::StringUtils::format("blackhole_%d.png", i+1);
		trackcome->addSpriteFrame(cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}   
	trackcome->setDelayPerUnit(ENEMY_DESTROY_DELAY);
	MyAnimationCache->addAnimation(trackcome, "track come");

	//EnemySpeedDown
	auto speedDown = Animation::create();
	for(int i = 0; i < 3; i++)
	{
		auto png = cocos2d::StringUtils::format("snow%d.png", i+1);
		speedDown->addSpriteFrame(MyFrameCache->getSpriteFrameByName(png));
	}
	speedDown->setDelayPerUnit(0.1f);
	speedDown->setLoops(-1);
	MyAnimationCache->addAnimation(speedDown, "SpeedDown");
}



void LoadingScene::createBackground(){
	//the first background picture
	//auto bg1 = cocos2d::Sprite::createWithSpriteFrameName("background.png");
	//bg1->setAnchorPoint(cocos2d::Point(0,0));
	//bg1->getTexture()->setAliasTexParameters();
	//this->addChild(bg1, BG_LAYER, BG1_TAG);
}

void LoadingScene::createHero(HeroType htype){
	auto bg1 = this->getChildByTag(BG1_TAG);
	auto hero = Hero::create(htype);
	hero->setPositionX( VisSize.width / 2);
	hero->setPositionY(VisSize.height / 6);
	hero->fly(); 
	this->addChild(hero, HERO_LAYER, HERO_TAG);
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
	loading->setPosition(Point(VisSize/2));
	this->addChild(loading);
	
	auto seq = Sequence::create(Animate::create(loadAni), CallFunc::create([](){
		auto scene = GameBegin::createScene();
		Director::getInstance()->replaceScene(scene);
	}
	), nullptr);

	loading->runAction(seq);	
}

void LoadingScene::update(float)
{
	auto smallpri1=this->getChildByTag(10);
	//->setPositionY(smallpri1->getPositionY()+6);
	//smallpri1->setPosition(visiSize.width/3, visiSize.height/5);
	if(smallpri1->getPositionY()<=VisSize.height*0.85)
	{
		smallpri1->setPositionY(smallpri1->getPositionY()+1.5);
	}
	else
	{
		auto bgsecond = Sprite::createWithSpriteFrameName("bg_loaing2.png");
		bgsecond->setAnchorPoint(Point::ZERO);
		this->addChild(bgsecond, -1);
	}
}