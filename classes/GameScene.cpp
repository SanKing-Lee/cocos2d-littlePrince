#include "GameScene.h"
#include "CommonData.h"
#include "OverScene.h"
#include <SimpleAudioEngine.h>

GameScene::GameScene(){
	m_isBossScene = false;
	m_GameLevel = 0;
	m_doubleBulletCount = 0;
	m_multiBulletCount = 0;
	m_BombCount = 0;
	m_EnemySpeedMulti = 1;
	m_isEnemeySpeedDown = false;
	m_isProtected = false;
	m_gold = 0;
	m_score = 0;
}

GameScene* GameScene::create()
{
	auto pp = new GameScene();
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

Scene* GameScene::createScene()
{
	auto scene = Scene::create();

	//"layer" is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	//return the scene
	return scene;
}

bool GameScene::init()
{
	//super init first
	if(!Layer::init())
	{
		return false;
	}
	m_isBossScene = false;
	m_GameLevel = 0;
	m_doubleBulletCount = 0;
	m_multiBulletCount = 0;
	m_BombCount = 0;
	m_EnemySpeedMulti = 1;
	m_isEnemeySpeedDown = false;
	m_isProtected = false;
	m_gold = 0;
	m_score = 0;
	data = Dictionary::create();
	Point e_smallGroupPosition = Point::ZERO;
	isCallenemy=0;
	isGoThrough = true;
	isBossDie = false;
	removeEnemy = true;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	
	//frame cache
	Enemy::clearLevelSpeed();
	readData();
	//background music
	playBackgroundMusic();

	//menu(pause and resume)
	createMenu_PauseAndResume();
	
	//display the bombs
	displayBombs();
	createGoldLabel();

	//background
	createBackground();

	//the hero plane
	createHero();

	//score
	createScoreLabel();

	//hero hp
	createHeroHP();
	//createBoss();
	//sprites
	createSprites();
	
	if(m_isProtected)
		createProtect();
	if(m_isEnemeySpeedDown)
		downEnemySpeed();

	//update the frame
	scheduleUpdate();
	return true;
}

void GameScene::update(float dt)
{
	//the moving of background
	moveBackground();
	updateHeroHP();
	updateBomb();
	flyBullets();
	flyEnemys();
	flyEnemyProp();
	updateProtect();
	updateGoldLabel();
	updateScoreLabel();
	updateSpeed();
    //crash check
	crashEnemyAndHeroAndBullet();
		//add zqh
	crashEnemybulletAndHero();
	//prop check
	crashPropAndHero();
}

//Bullet
void GameScene::createBullet(float) {
	auto hero =(Hero*) getChildByTag(HERO_TAG);
	if(hero->getAlive()){
	//Audio->playEffect("bullet.mp3");
	(m_multiBulletCount > 0)?createMultiBullet():
		((m_doubleBulletCount>0)?createDoubleBullet():createSingleBullet());
	}
}

void GameScene::createSingleBullet(){
	auto hero = this->getChildByTag(HERO_TAG);
	auto bullet = Bullet::create(SingleBullet);
	bullet->setPosition(hero->getPosition() + cocos2d::Point(0,hero->getContentSize().height / 2));
	this->addChild(bullet, BULLET_LAYER);
	//push this bullet into vector
	g_bullets.pushBack(bullet);
}

void GameScene::createDoubleBullet(){
	auto hero = this->getChildByTag(HERO_TAG);

	//left bullet
	auto leftBullet = Bullet::create(DoubleBullet);
	leftBullet->setPosition(hero->getPositionX()-hero->getContentSize().width/3,
		hero->getPositionY() + hero->getContentSize().height/3);
	this->addChild(leftBullet, BULLET_LAYER);
	this->g_bullets.pushBack(leftBullet);

	//right bullet
	auto rightBullet = Bullet::create(DoubleBullet);
	rightBullet->setPosition(hero->getPositionX()+hero->getContentSize().width/3,
		hero->getPositionY() + hero->getContentSize().height/3);
	this->addChild(rightBullet, BULLET_LAYER);
	this->g_bullets.pushBack(rightBullet);
	m_doubleBulletCount--;
}

void GameScene::createMultiBullet(){
	auto hero = this->getChildByTag(HERO_TAG);
	createSingleBullet();
	createDoubleBullet();
	m_multiBulletCount--;
}


//Enemy
void GameScene::createEnemy(EnemyType type) {
	if(m_isBossScene)
		return;
	float x, y;
	float leftMinX, rightMaxX;
	auto enemy = Enemy::create(type);
	auto size = enemy->getContentSize();
	switch (type)
	{
	case SmallEnemy2:
		//enemy->~Enemy();
		//return size;
		break;
	case SmallEnemy1:
	case MiddleEnemy:
	case BigEnemy:
		leftMinX = size.width / 2;
		rightMaxX = VisSize.width - leftMinX;
		x = rand() % (int)(rightMaxX - leftMinX + 1) + leftMinX;
		y = VisSize.height + size.height/2;
		enemy->setPosition(x, y);
		g_enemies.pushBack(enemy);
		this->addChild(enemy, ENEMY_LAYER);
		//enemy->move(0, 0);
		break;
	case FirstBoss_ENEMY:
	case SecondBoss_ENEMY:
	case ThirdBoss_ENEMY:
	case Boss:
		enemy->setPosition(VisSize.width/2, VisSize.height + size.height/2);
		g_enemies.pushBack(enemy);
		this->addChild(enemy, ENEMY_LAYER);
		break;
	default:
		leftMinX = size.width / 2;
		rightMaxX = VisSize.width - leftMinX;
		x = rand() % (int)(rightMaxX - leftMinX + 1) + leftMinX;
		y = VisSize.height + size.height/2;
		enemy->setPosition(x, y);
		g_enemies.pushBack(enemy);
		this->addChild(enemy, ENEMY_LAYER);
		break;
	}
}

void GameScene::createEnemy(EnemyType type, Point position)
{
	if(m_isBossScene)
		return;
	auto enemy = Enemy::create(type);
	enemy->setPosition(position);
	g_enemies.pushBack(enemy);
	this->addChild(enemy, ENEMY_LAYER);
	//enemy->move(0, 0);
}

void GameScene::createSmallEnemy1(float) 
{
	this->createEnemy(SmallEnemy1);  //直线小飞机
}

void GameScene::createSmallEnemy2Group(float)
{
	//一组初始坐标相同，方向相同
	int LeftOrRight = rand() % 2;
	auto enemy = Enemy::create(SmallEnemy2);
	auto size = enemy->getContentSize();
	Enemy::e_curveDirection = ((LeftOrRight == 0) ? CLeft : CRight);

	float x = -size.width/2 + (VisSize.width + size.width/2) * (LeftOrRight == 0 ? 0 : 1);
	float y = rand() % (int)(VisSize.height/4) + VisSize.height * 3/4 + size.height/2;

	e_smallGroupPosition = Point(x, y);
	schedule(schedule_selector(GameScene::createSmallEnemy2), SMALLENEMY2_INTERVAL, GROUP_SMALL_NUMBER, SMALLENEMY2_DELAY);
}

void GameScene::createSmallEnemy2(float)
{
	this->createEnemy(SmallEnemy2, e_smallGroupPosition);
}

void GameScene::createSmallEnemy(float) {
    this->createEnemy(SmallEnemy1);
}

void GameScene::createMiddleEnemy(float) {
	createEnemy(MiddleEnemy);
}

void GameScene::createBigEnemy(float) {
    this->createEnemy(BigEnemy);
}

//add zqh
void GameScene::createFortEnemy(float)
{
	this->createEnemy(FORT_ENEMY);
}

void GameScene::createTrackEnemy(float)
{
	if(m_isBossScene)
		return;
	srand((unsigned int)time(0));
	Point pos=Point(rand()%(int)VisSize.width,rand()%(int)VisSize.height/2+VisSize.height/2);
	auto startAction=Sprite::createWithSpriteFrameName("blackhole_1.png");
	startAction->setPosition(pos);
	this->addChild(startAction,ENEMY_LAYER);
	auto animation = AnimationCache::getInstance()->getAnimation("track come");
	auto animate = Animate::create(animation);
	animate->setDuration(2);
	auto callFuncN=cocos2d::CallFuncN::create([](Node* node){
		node->removeFromParentAndCleanup(true);
	});
	auto func=CallFunc::create([=](){
		auto trackEnemy=Enemy::create(TRACK_ENEMY);
		trackEnemy->setPosition(pos);
		this->addChild(trackEnemy,ENEMY_LAYER);
		g_enemies.pushBack(trackEnemy);
	});
	auto seq=Sequence::create(animate,callFuncN,func,NULL);
	startAction->runAction(seq);
}

void GameScene::createMeteoriteEnemy(float)
{
	this->createEnemy(Meteorite_ENEMY);
}

void GameScene::createFirstBossEnemy(float)
{
	this->createEnemy(FirstBoss_ENEMY);
}
void GameScene::createSecondBossEnemy(float)
{
	this->createEnemy(SecondBoss_ENEMY);
}
void GameScene::createThirdBossEnemy(float)
{
	this->createEnemy(ThirdBoss_ENEMY);
}
//add enemy bullet zqh
void GameScene::createEnemysingleBullet(float)
{
	for(auto enemy:this->g_enemies)
	{
		if(enemy->getEnemyType()==MiddleEnemy)
		{
			auto Enemybullet=Bullet::create(EnemyNormalBUllet);
			Enemybullet->setPosition(enemy->getPosition()-cocos2d::Point(0,enemy->getContentSize().height / 2));
			this->addChild(Enemybullet,BULLET_LAYER);
			e_bullets.pushBack(Enemybullet);
		}
	}
}

void GameScene::createEnemytribleBullet(float)
{
	for(auto enemy:this->g_enemies)
	{
		if(enemy->getEnemyType()==FirstBoss_ENEMY&& enemy->getHP() >= 5)
		{
			//middle bullet
			auto Enemybullet=Bullet::create(EnemyNormalBUllet);
			Enemybullet->setPosition(enemy->getPosition()-cocos2d::Point(0,enemy->getContentSize().height / 2));
			this->addChild(Enemybullet,BULLET_LAYER);
			e_bullets.pushBack(Enemybullet);

			//left bullet
			auto leftEnemyBullet = Bullet::create(BossSingleBUllet);
			leftEnemyBullet->setPosition(enemy->getPositionX()-enemy->getContentSize().width/3,
							enemy->getPositionY() - enemy->getContentSize().height/4);
			leftEnemyBullet->setRotation(0);
			this->addChild(leftEnemyBullet, BULLET_LAYER);
			e_left_bullets.pushBack(leftEnemyBullet);

			//right bullet
			auto rightEnemyBullet = Bullet::create(BossSingleBUllet);
			rightEnemyBullet->setPosition(enemy->getPositionX()+enemy->getContentSize().width/3,
				enemy->getPositionY() - enemy->getContentSize().height/4);
			rightEnemyBullet->setRotation(0);
			this->addChild(rightEnemyBullet, BULLET_LAYER);
			e_right_bullets.pushBack(rightEnemyBullet);
		}
	}
}

void GameScene::createEnemytrackBullet(float)
{
	for(auto enemy:this->g_enemies)
	{
		if(enemy->getEnemyType()==SecondBoss_ENEMY && enemy->getHP() >= 5)
		{
			auto Enemybullet=Bullet::create(EnemyTrackBullet);//need to change to TrackBullet
			Enemybullet->setPosition(enemy->getPosition()-cocos2d::Point(0,enemy->getContentSize().height / 2));
			this->addChild(Enemybullet,BULLET_LAYER);
			e_track_bullets.pushBack(Enemybullet);
		}
	}
}

void  GameScene::createEnemyFortBullet(float)
{
	auto hero=(Hero*) this->getChildByTag(HERO_TAG);
	for(auto enemy:this->g_enemies)
	{
		if(enemy->getEnemyType()==FORT_ENEMY)
		{
			auto EnemyFortBullet=Bullet::create(EnemyTrackBullet);
			EnemyFortBullet->setPosition(/*enemy->getPositionX()+enemy->getContentSize().width/2,
				enemy->getPositionY() + enemy->getContentSize().height/2*/enemy->getPosition());
			//set the Rotation
			auto bulletPos=EnemyFortBullet->getPosition();
			auto trackPos=EnemyFortBullet->getPosition();
			auto delta = ccpSub(hero->getPosition(),trackPos);
			auto distance=ccpDistance(hero->getPosition(),trackPos);
			float x=trackPos.x+(float)delta.x/distance;
			float y=trackPos.y+(float)delta.y/distance;
			float deltaRotation=90-atan2(y-trackPos.y,x-trackPos.x)*180/3.14;
			EnemyFortBullet->setRotation(deltaRotation);

			this->addChild(EnemyFortBullet,BULLET_LAYER);
			e_Fort_bullets.pushBack(EnemyFortBullet);
		}
	}
}

void GameScene::createEnemyBigBullet(float)
{
	for(auto enemy:this->g_enemies)
	{
		if(enemy->getEnemyType()==ThirdBoss_ENEMY && enemy->getHP() >= 5)
		{
			auto Enemybullet=Bullet::create(EnemyBigBullet);
			Enemybullet->setPosition(enemy->getPosition()-cocos2d::Point(0,enemy->getContentSize().height / 2));
			this->addChild(Enemybullet,BULLET_LAYER);
			e_Big_bullets.pushBack(Enemybullet);
		}
	}
}

//Enemy skills
void GameScene::callLittleEnemy(Enemy* enemy)
{
	if(enemy->getType()==SecondBoss_ENEMY &&enemy->getHP()<=200&&getisCallEnemy()<1)
	{
		auto enemy_left = Enemy::create(TRACK_ENEMY);
		auto enemy_right = Enemy::create(TRACK_ENEMY);

		enemy_left->setPosition(enemy->getPositionX()-50, enemy->getPositionY()-20);
		enemy_right->setPosition(enemy->getPositionX()+50, enemy->getPositionY()-20);
		little_enemies.pushBack(enemy_right);
		little_enemies.pushBack(enemy_left);

		this->addChild(enemy_left, HERO_LAYER);
		this->addChild(enemy_right, HERO_LAYER);
	}
	setisCallEnemy(getisCallEnemy()+1);
}

//Prop
void GameScene::createEnemyProp(PropType type, Point pos){
	auto prop = Prop::create(type);
	prop->setPosition(Point((pos + Point(2, 2)*(rand()%20))));
	this->addChild(prop, BULLET_LAYER);
	h_props.pushBack(prop);

	auto move1 = MoveBy::create(0.6f, Point(0, VisSize.height/12));
	auto propblin = Blink::create(5, 8);
	auto callFuncN = CallFuncN::create([=](Node* node){
		node->removeFromParentAndCleanup(true);
		h_props.eraseObject(prop);
	});
	prop->runAction(Sequence::create(move1, move1->reverse(), propblin, callFuncN, nullptr));
}

void GameScene::createPropwithSchedule(float){
	if(m_isBossScene)
		return;
	std::srand((unsigned)time(NULL));
	PropType ptype;
	auto randNumber = (int)rand()%PROPTYPE_NUMBER;
	switch(randNumber){
	case 0: ptype = Enhance_Bullet; break;
	case 1: ptype = Bomb; break;
	case 2: ptype = Hp; break;
	case 3: ptype = SpeedDown; break;
	case 4: ptype = SpeedDown; break;
	case 5: ptype = ProtectCover; break;
	default:ptype = SpeedDown; break;
	}
	auto prop = Prop::create(ptype);
	float minX = prop->getContentSize().width/2;
	float maxX = VisSize.width - minX;
	float x = rand()%(int)(maxX - minX + 1) + minX;
	prop->setPosition(x, VisSize.height + prop->getContentSize().height/2);
	this->addChild(prop, BULLET_LAYER);
	this->h_props.pushBack(prop);

	auto move1 = MoveBy::create(0.5f, Point(0, -VisSize.height/3));
	auto move2 = MoveTo::create(1, 
		Point(prop->getPositionX(), -prop->getContentSize().height/2));
	auto sequence = Sequence::create(move1, move1->reverse(),
		move2, RemoveSelf::create(), nullptr);
	prop->runAction(sequence);
}

void GameScene::createPropwhenEnemyDestroyed(Enemy* enemy){
	PropType ptype;
	auto randNumber = (int)rand()%PROPTYPE_NUMBER;
	auto pos = enemy->getPosition();
	switch(enemy->getType()){
	case SmallEnemy1:
		if(!rand()%5)
			createEnemyProp(Gold, pos); break;
	case MiddleEnemy:
		if(rand()%3){
		switch(randNumber){
				case 0: ptype = Enhance_Bullet; break;
				case 1: ptype = Bomb; break;
				case 2: ptype = Hp; break;
				case 3: ptype = SpeedDown; break;
				case 4: ptype = ProtectCover; break;
				default: ptype = Gold;break;
			}
			createEnemyProp(ptype, pos);
		}
	case	FORT_ENEMY:
		createEnemyProp(Bomb, pos);
		switch(randNumber){
		case 0: 
		case 1: ptype = ProtectCover; break;
		default: ptype = Gold; break;
		}
		createEnemyProp(ptype, pos);
		break;
	case TRACK_ENEMY:
		createEnemyProp(SpeedDown, pos);
		break;
	default:
		break;
	}
}
void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

//Pause and Resume
void GameScene::PauseAndResume(Ref* ref)
{
	auto toggle = (MenuItemToggle*) ref;
	auto hero = (Hero*)this->getChildByTag(HERO_TAG);
	if(toggle->getSelectedIndex() == 0)
	{
		Audio->playEffect("button.mp3");
		hero->setMove(true);
		Audio->resumeBackgroundMusic();
		Audio->resumeAllEffects();
		Director::getInstance()->resume();
	}
	else
	{
		Audio->playEffect("button.mp3");
		hero->setMove(false);
		Audio->pauseBackgroundMusic();
		Audio->pauseAllEffects();
		Director::getInstance()->pause();
	}
}

//use bomb
void GameScene::bomb(Ref* ref){
	if(Director::getInstance()->isPaused())
		return;
	if(m_BombCount <= 0)
		return;
	for(auto enemy:this->g_enemies)
	{
		enemy->setHP(enemy->getHP()-BOMB_ATTACK);
		switch(enemy->getType()){
		case FirstBoss_ENEMY:
		case SecondBoss_ENEMY:
		case ThirdBoss_ENEMY:
			if(enemy->getHP() <= 5)
			{
				enemy->setHP(5);
			}
			break;
		default:
			break;
		}
		if(enemy->isDestroyed()){
			removableEnemies.pushBack(enemy);
			m_score += enemy->getScore();
		}
		enemy->destroyedAnim();
	}
	//remove destroyed enemies
	for(auto enemy:removableEnemies){
		g_enemies.eraseObject(enemy);
	}
	auto lblScore = (Label *)this->getChildByTag(SL_TAG);
	lblScore->setString(StringUtils::format("%d", m_score));

	m_BombCount--;
	updateBomb();
	Audio->playEffect("use_bomb.mp3");
}

void GameScene::createHero(){
	HeroType htype;
	switch(m_GameLevel ){
	case 1:
		htype = HeroOne; break;
	case 2:
		htype = HeroTwo; break;
	case 3:
		htype = HeroThree; break;
	default:
		htype = HeroThree; break;
	}
	auto hero = Hero::create(HeroOne);
	hero->setPositionX(VisSize.width / 2);
	hero->setPositionY(VisSize.height / 6);
	this->addChild(hero, HERO_LAYER, HERO_TAG);
	hero->setLevel(m_heroLevel);
	hero->setHP(m_heroHP);
	hero->setHPLimit(m_heroHPLimit);
	hero->fly();
	hero->touchMove();
}

void GameScene::createBackground()
{
	//the first background picture
	Sprite* bg1;
	Sprite* bg2;
	switch(m_GameLevel)
	{
	case 1:
		Audio->playBackgroundMusic("background1.mp3");
		bg1 = cocos2d::Sprite::createWithSpriteFrameName("level1.png");
		bg2 = cocos2d::Sprite::createWithSpriteFrameName("level1.png");
		break;
	case 2:
		Audio->playBackgroundMusic("background2.mp3");
		bg1 = Sprite::createWithSpriteFrameName("level2.png");
		bg2 = Sprite::createWithSpriteFrameName("level2.png");
		break;
	case 3:
		Audio->playBackgroundMusic("background3.mp3");
		bg1 = Sprite::createWithSpriteFrameName("level3.png");
		bg2 = Sprite::createWithSpriteFrameName("level3.png");
		break;
	default:
		bg1 = cocos2d::Sprite::createWithSpriteFrameName("level1.png");
		bg2 = cocos2d::Sprite::createWithSpriteFrameName("level1.png");
		break;
	}
	bg1->setAnchorPoint(cocos2d::Point(0,0));
	bg1->getTexture()->setAliasTexParameters();
	this->addChild(bg1, BG_LAYER, BG1_TAG);

	bg2->setAnchorPoint(cocos2d::Point::ZERO);
	bg2->setPosition(0,bg1->getContentSize().height);
	bg2->getTexture()->setAliasTexParameters();
	this->addChild(bg2, BG_LAYER, BG2_TAG);
}

void GameScene::playBackgroundMusic()
{
	auto audio = CocosDenshion::SimpleAudioEngine::getInstance();
	audio->playBackgroundMusic("game_music.mp3", true);
}

void GameScene::createMenu_PauseAndResume()
{
		//pause
	auto spritePauseNormal = cocos2d::Sprite::createWithSpriteFrameName ("pause.png");
	auto spritePausePressed = cocos2d::Sprite::createWithSpriteFrameName("pause.png");
	auto menuItemPause = MenuItemSprite::create(spritePauseNormal, spritePausePressed);

	//resume
	auto spriteResumeNormal = cocos2d::Sprite::createWithSpriteFrameName("resume.png");
	auto spriteResumePressed = cocos2d::Sprite::createWithSpriteFrameName("resume.png");
	auto menuItemResume = MenuItemSprite::create(spriteResumeNormal, spriteResumePressed);
	
	//menuToggle
	auto menuItemToggle = MenuItemToggle::createWithCallback
		(CC_CALLBACK_1(GameScene::PauseAndResume, this), menuItemPause, menuItemResume, nullptr);
	menuItemToggle->setPosition(Point(VisSize -menuItemPause->getContentSize()));

	auto menu = Menu::create();
	menu->addChild(menuItemToggle);
	menu->setPosition(cocos2d::Vect::ZERO);
	this->addChild(menu, UI_LAYER, MENU_TAG);
}

void GameScene::displayBombs()
{
	auto menu = this->getChildByTag(MENU_TAG);
	auto spBomb = Sprite::createWithSpriteFrameName("clear_up.png");
	auto itemBomb = MenuItemSprite::create(spBomb, spBomb, 
		CC_CALLBACK_1(GameScene::bomb, this));

	itemBomb->setPosition(Point(spBomb->getContentSize()) - Point(VisSize.width/20, VisSize.height/20));
	menu->addChild(itemBomb, UI_LAYER, ITEM_BOMB_TAG);
	itemBomb->setVisible(false);

	auto lblBomb = Label::createWithSystemFont(StringUtils::format("%d", m_BombCount), "Arial", 28);
	lblBomb ->setPosition(itemBomb->getPositionX() + VisSize.width / 16, itemBomb->getPositionY());
	this->addChild(lblBomb, UI_LAYER, LABEL_BOMB_TAG);
	lblBomb->setVisible(false);
}

void GameScene::updateBomb(){
	auto menu = this->getChildByTag(MENU_TAG);
	auto itemBomb = menu->getChildByTag(ITEM_BOMB_TAG);
	auto lblBomb = (Label*)this->getChildByTag(LABEL_BOMB_TAG);
	lblBomb->setString(StringUtils::format("%d", m_BombCount));
	if(m_BombCount <=0)
	{
		itemBomb->setVisible(false);
		lblBomb->setVisible(false);
	}
	else if(m_BombCount == 1)
	{
		itemBomb->setVisible(true);
		lblBomb->setVisible(false);
	}
	else
	{
		itemBomb->setVisible(true);
		lblBomb->setVisible(true);
	}
}


void GameScene::createScoreLabel()
{
	auto gold = getChildByTag(GOLD_LABEL_TAG);
	//the "score" tag
	auto score = Sprite::createWithSpriteFrameName("score.png");
	score->setScale(0.6f);
	score->setPosition(gold->getPositionX(), gold->getPositionY() - score->getContentSize().height);
	addChild(score, UI_LAYER);

	//the score Label
	auto scoreLabel = Label::createWithSystemFont(StringUtils::format("%d", m_score), "Arial", 28);
	scoreLabel->setAnchorPoint(Vect::ANCHOR_MIDDLE_LEFT);
	scoreLabel->setPosition(VisSize.width/6, score->getPositionY());
	scoreLabel->setString(StringUtils::format("%d", m_score));
	this->addChild(scoreLabel, UI_LAYER, SL_TAG);
}

void GameScene::updateScoreLabel(){
	auto scoreLabel =(Label*)getChildByTag(SL_TAG);
	scoreLabel->setString(StringUtils::format("%d", m_score));
}

void GameScene::updateSpeed()
{
	Enemy::updateLevelSpeed(m_score / SPEED_LEVELUP_SCORE);
}

void GameScene::createHeroHP(){
	//the hero ph 
	for(int i = 0; i < HP_HERO; i++){
		auto heroHP = cocos2d::Sprite::createWithSpriteFrameName("Life.png");
		//heroPH->setScale(0.4f);
		heroHP->setPosition(cocos2d::Point(VisSize.width - (i+1)*(heroHP->getContentSize().width + 10), heroHP->getContentSize().height));	
		this->addChild(heroHP, UI_LAYER);
		hero_hp.pushBack(heroHP);
	}
}

void GameScene::updateHeroHP()
{
	auto hero =(Hero*) this->getChildByTag(HERO_TAG);
	for(int i = 0; i < HP_HERO; i++)
	{
		this->removeChild(hero_hp.at(i));
	}
	for(int i = 0; i < hero->getHP(); i++)
	{
		this->addChild(hero_hp.at(i));
	}
}

void GameScene::createSprites()
{
	//create bullets
	schedule(schedule_selector(GameScene::createBullet),HERO_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createPropwithSchedule), PROP_INTERVAL, REPEAT_FOREVER, PROP_DELAY); 
	switch(m_GameLevel){	
	//create enemies
	case 1:
		schedule(schedule_selector(GameScene::createSmallEnemy), SMALLENEMY1_INTERVAL, REPEAT_FOREVER, SMALLENEMY1_DELAY);
		schedule(schedule_selector(GameScene::createFirstBossEnemy), FIRSTBOSSENEMY_INTERVAL, 0, FIRSTBOSSENEMY_DELAY);
		schedule(schedule_selector(GameScene::createMeteoriteEnemy), METEORITEENEMY_INTERVAL, REPEAT_FOREVER, METEORITEENEMY_DELAY);
		schedule(schedule_selector(GameScene::createSmallEnemy2Group),SMALLENEMY2GROUP_INTERVAL, REPEAT_FOREVER, SMALLENEMY2GROUP_DELAY);
		break;
	case 2:
		schedule(schedule_selector(GameScene::createSmallEnemy), SMALLENEMY1_INTERVAL+2, REPEAT_FOREVER, SMALLENEMY1_DELAY-2);
		schedule(schedule_selector(GameScene::createMiddleEnemy), MIDDLEENEMY_INTERVAL, REPEAT_FOREVER, MIDDLEENEMY_DELAY);
		schedule(schedule_selector(GameScene::createTrackEnemy), TRACKENEMY_INTERVAL, REPEAT_FOREVER, TRACKENEMY_DELAY);
		schedule(schedule_selector(GameScene::createMeteoriteEnemy), METEORITEENEMY_INTERVAL+2, REPEAT_FOREVER, METEORITEENEMY_DELAY-2);
		schedule(schedule_selector(GameScene::createSecondBossEnemy), SECONDBOSSENEMY_INTERVAL, 0, SECONDBOSSENEMY_DELAY);
		schedule(schedule_selector(GameScene::createSmallEnemy2Group),SMALLENEMY2GROUP_INTERVAL+2, REPEAT_FOREVER, SMALLENEMY2GROUP_DELAY-2);
		break;
	case 3:
		schedule(schedule_selector(GameScene::createSmallEnemy), SMALLENEMY1_INTERVAL, REPEAT_FOREVER+4, SMALLENEMY1_DELAY);
		schedule(schedule_selector(GameScene::createMiddleEnemy), MIDDLEENEMY_INTERVAL, REPEAT_FOREVER+2, MIDDLEENEMY_DELAY);
		schedule(schedule_selector(GameScene::createTrackEnemy), TRACKENEMY_INTERVAL, REPEAT_FOREVER+2, 5);
		schedule(schedule_selector(GameScene::createMeteoriteEnemy), METEORITEENEMY_INTERVAL+3, REPEAT_FOREVER, METEORITEENEMY_DELAY);
		schedule(schedule_selector(GameScene::createThirdBossEnemy), SMALLENEMY1_INTERVAL, 0, THIRDBOSSENEMY_DELAY);
		schedule(schedule_selector(GameScene::createSmallEnemy2Group),SMALLENEMY2GROUP_INTERVAL+4, REPEAT_FOREVER, SMALLENEMY2GROUP_DELAY);
		schedule(schedule_selector(GameScene::createFortEnemy), FORTENEMY_INTERVAL, REPEAT_FOREVER, FORTENEMY_DELAY);
		break;
	default:
		schedule(schedule_selector(GameScene::createSmallEnemy), SMALLENEMY1_INTERVAL, REPEAT_FOREVER, SMALLENEMY1_DELAY);
		schedule(schedule_selector(GameScene::createFirstBossEnemy), FIRSTBOSSENEMY_INTERVAL, 0, FIRSTBOSSENEMY_DELAY);
		schedule(schedule_selector(GameScene::createMeteoriteEnemy), METEORITEENEMY_INTERVAL, REPEAT_FOREVER, METEORITEENEMY_DELAY);
		schedule(schedule_selector(GameScene::createSmallEnemy2Group),SMALLENEMY2GROUP_INTERVAL, REPEAT_FOREVER, SMALLENEMY2GROUP_DELAY);
		break;
	}
	//create prop
	

	//create enemies' bullet
	schedule(schedule_selector(GameScene::createEnemysingleBullet),ENEMY_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createEnemytribleBullet),ENEMY_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createEnemytrackBullet),ENEMY_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createEnemyFortBullet),ENEMY_BULLET_INTERVAL);
	schedule(schedule_selector(GameScene::createEnemyBigBullet),ENEMY_BULLET_INTERVAL+1);
}

void GameScene::moveBackground(){
	auto bg1 = this->getChildByTag(BG1_TAG);
	auto bg2 = this->getChildByTag(BG2_TAG);

	//the moving of background
	bg1->setPosition(bg1->getPositionX(),bg1->getPositionY() - SP_BG);
	bg2->setPositionY(bg1->getPositionY() + bg1->getContentSize().height);
	if(bg2->getPositionY()<0)
	{
		bg1->setPositionY(0);
	}
}

void GameScene::flyBullets(){
	//display the bullet and clean bullets fly out
	auto hero=(Hero*)this->getChildByTag(HERO_TAG);
	for(auto bullet: g_bullets) 
	{		
		bullet->setPositionY(bullet->getPositionY() + SP_HERO_BULLET);
		if(bullet->getPositionY() >= VisSize.height)
		{
			this->removeChild(bullet);
			removableBullets.pushBack(bullet);
		}
	}
	clearCrossBullet(g_bullets,removableBullets);


	//enemy normal bullet
	for(auto ebullet: e_bullets) 
	{		
		ebullet->setPositionY(ebullet->getPositionY() -(SP_ENEMY_BULLET+SP_SMALL));
		if(ebullet->getPositionY() <= 0)
		{
			this->removeChild(ebullet);
			removableBullets_e1.pushBack(ebullet);
		}
	}
	//enemy left bullet
	for(auto e_left_bullet: e_left_bullets) 
	{		
		e_left_bullet->setPosition(e_left_bullet->getPositionX()-1,
			e_left_bullet->getPositionY() - 6*(SP_ENEMY_BULLET-Enemy::getLevelSpeed()));
		if(e_left_bullet->getPositionY() <= 0||e_left_bullet->getPositionX()>=VisSize.width||
			e_left_bullet->getPositionX()<=0)
		{
			this->removeChild(e_left_bullet);
			removableBullets_e2.pushBack(e_left_bullet);
		}
	}

	//enemy right bullet
	for(auto e_right_bullet: e_right_bullets)
	{		
		e_right_bullet->setPosition(e_right_bullet->getPositionX() + 1,
			e_right_bullet->getPositionY() - 6*(SP_ENEMY_BULLET-Enemy::getLevelSpeed()));
		if(e_right_bullet->getPositionY() <= 0||e_right_bullet->getPositionX()>=VisSize.width||
			e_right_bullet->getPositionX()<=0)
		{
			this->removeChild(e_right_bullet);
			removableBullets_e3.pushBack(e_right_bullet);
		}
	}
	//enemy track bullet
	for(auto e_track_bullet: e_track_bullets)
	{		
		auto trackpos=e_track_bullet->getPosition();
		auto delta = ccpSub(hero->getPosition(),trackpos);
		auto distance=ccpDistance(hero->getPosition(),trackpos);
		float speed=3;
		float x=trackpos.x+speed*(float)delta.x/distance;
		float y=trackpos.y+speed*(float)delta.y/distance;

		float deltaRotation=90-atan2(y-trackpos.y,x-trackpos.x)*180/3.14;
		e_track_bullet->setPosition(x,y);
		e_track_bullet->setRotation(deltaRotation);
		schedule(schedule_selector(GameScene::cleartrackBullet),3,-1,4);
	}
	//enemy fort bullet
	for(auto e_Fort_bullet:e_Fort_bullets)
	{
		auto hero=(Hero*)this->getChildByTag(HERO_TAG);
		auto test=hero->getPosition();
		auto trackPos=e_Fort_bullet->getPosition();
		auto rotation = e_Fort_bullet->getRotation();
		float x=10*sin((e_Fort_bullet->getRotation())/57.3248);
		float y=10*cos((e_Fort_bullet->getRotation())/57.3248);
		e_Fort_bullet->setPosition(trackPos.x+x,trackPos.y+y);
		if(e_Fort_bullet->getPositionY() <= 0||e_Fort_bullet->getPositionX()>=VisSize.width||
			e_Fort_bullet->getPositionX()<=0)
		{
			this->removeChild(e_Fort_bullet);
			removableBullets_e4.pushBack(e_Fort_bullet);
		}
	}
	for(auto e_big_bullet:e_Big_bullets)
	{
		e_big_bullet->setPositionY(e_big_bullet->getPositionY() - 7*(SP_ENEMY_BULLET+Enemy::getLevelSpeed()));
		if(e_big_bullet->getPositionY() <= 0)
		{
			this->removeChild(e_big_bullet);
			removableBullets_e6.pushBack(e_big_bullet);
		}
	}

	//clear crossedge bullet
	clearCrossBullet(e_bullets,removableBullets_e1);
	clearCrossBullet(e_left_bullets,removableBullets_e2);
	clearCrossBullet(e_right_bullets,removableBullets_e3);
	clearCrossBullet(e_Fort_bullets,removableBullets_e4);
	clearCrossBullet(e_track_bullets,removableBullets_e5);
	clearCrossBullet(e_Big_bullets,removableBullets_e6);

}

void GameScene::flyEnemys(){
	//fly the enemies
	//for(auto enemy:g_enemies){
 //       enemy->setPositionY(enemy->getPositionY() - (enemy->getSpeed())*m_EnemySpeedMulti);
 //       //clean
 //       if(enemy->getPositionY() + enemy->getContentSize().height/2 <= 0) { 
 //           this->removeChild(enemy);
	//		removableEnemies.pushBack(enemy);
 //       } 
 //   }
	//for(auto enemy:removableEnemies){
	//	g_enemies.eraseObject(enemy);
	//}
	//removableEnemies.clear();
		//fly the enemies
	for(auto enemy:g_enemies)
	{
		switch (enemy->getType())
		{
		case FirstBoss_ENEMY:
		case SecondBoss_ENEMY:
		case ThirdBoss_ENEMY:
			if(enemy->getType()== SecondBoss_ENEMY&&enemy->getHP()<=200&&getisCallEnemy()<1)
			{
				callLittleEnemy(enemy);
			}
			jumpToBoss();
		case SmallEnemy1:
		case MiddleEnemy:
		case SmallEnemy2:
			enemy->move(X_OFFSET, enemy->getSpeed()*m_EnemySpeedMulti);
			//clean
			if(enemy->beyondLimitY() || enemy->beyondLimitX()) 
			{ 
				removableEnemies.pushBack(enemy);
				this->removeChild(enemy);
			} 
			break;
		case TRACK_ENEMY:
			trackEnemyMove(enemy);
			break;
		default:
			enemy->setPosition(enemy->getPositionX(),enemy->getPositionY() - enemy->getSpeed()*m_EnemySpeedMulti);
			//clean
			if(enemy->beyondLimitY() || enemy->beyondLimitX())
			{
				this->removeChild(enemy);
				removableEnemies.pushBack(enemy);
			}
			break;
		}
	}

	for(auto enemy:removableEnemies)
	{
		g_enemies.eraseObject(enemy);
	}
	removableEnemies.clear();
	for(auto enemy:little_enemies)
	{
		g_enemies.pushBack(enemy);
	}
	little_enemies.clear();
	for(auto enemy:removableEnemies)
	{
		g_enemies.eraseObject(enemy);
	}
	removableEnemies.clear();
}

void GameScene::flyEnemyProp(){
	for(auto eprop: h_props){
		eprop->setPositionY(eprop->getPositionY()-SP_BG);
		if(eprop->getPositionY() + eprop->getContentSize().height/2 <= 0){
			this->removeChild(eprop);
			removableProps.pushBack(eprop);
		}
	}
	for(auto eprop:removableProps)
	{
		h_props.eraseObject(eprop);
	}
	removableProps.clear();
}

void GameScene::crashEnemyAndHeroAndBullet()
{
	auto hero = (Hero*)this->getChildByTag(HERO_TAG);
	auto sl = (Label*)this->getChildByTag(SL_TAG);
	//crash check
    //march destroyed enemies
	for(auto enemy : g_enemies)
	{
		if(m_isBossScene)
		{	
			if(removeEnemy){
			for(auto enemy: g_enemies){
				switch(enemy->getType())
				{
				case FirstBoss_ENEMY:
				case SecondBoss_ENEMY:
				case ThirdBoss_ENEMY:
					break;
				default:
					enemy->setHP(0);
					enemy->destroyedAnim();
					break;
				}
				removeEnemy = false;
			}
			}
		}
		switch(enemy->getType()){
			case FirstBoss_ENEMY:
			case SecondBoss_ENEMY:
			case ThirdBoss_ENEMY:
				if(enemy->getHP() <= 5)
				{					
					if(isGoThrough){
						hero->setAlive(false);
						hero->setActive(false);
						hero->setMove(false);
						auto destroye = CallFunc::create([=](){
							enemy->setHP(0);
							enemy->destroyedAnim();
						});
					//enemy->removeFromParentAndCleanup(true);
						for(auto bullet:g_bullets){
							removeChild(bullet);
							removableBullets.pushBack(bullet);
						}
						for(auto bullet:removableBullets){
							g_bullets.eraseObject(bullet);
						}
						removableBullets.clear();
						isGoThrough = false;
					auto jumpto = CallFunc::create([=](){
						goThrough();
					});
					enemy->runAction(Sequence::create(destroye, jumpto, nullptr));
				}
			}
					break;
			default:
					break;
		}
		//hero and enemy
		if((enemy)->getBoundingBox().intersectsRect(hero->getBoundingBox()) && hero->getActive())
		{

			//enemy is hit by hero
			enemy->setHP(enemy->getHP() - HERO_HIT_ATTACK);
			enemy->hitAnim();
			if(enemy->isDestroyed()) 
			{ 
				removableEnemies.pushBack(enemy);
			}
			if(m_isProtected){}
				//vanishProtect(0.0);
			else{
				if(hero->getHP() <= 1)
				{
					GameOver();
				}
				else
				{
					hero->rebirthHero(isBossDie);
				}
			}
		}
        //march destroyed bullets
        for(auto bullet : g_bullets)
		{
            //crash
            if(bullet->getBoundingBox().intersectsRect(enemy->getBoundingBox())) 
			{  
            //clean the bullet and set flag to ture
				removableBullets.pushBack(bullet);
                this->removeChild((bullet));                                
				
				enemy->hitAnim();
				//get hurt
				enemy->setHP(enemy->getHP() - bullet->getAttack()); 

				if(enemy->isDestroyed()) 
				{ 
					//update the score
					createPropwhenEnemyDestroyed(enemy);
					m_score += enemy->getScore();
					//display the socre
					sl->setString(StringUtils::format("%d", m_score));
					enemy->destroyedAnim();    
					removableEnemies.pushBack(enemy);
				}
            } 
        }       
		
    }

	for(auto bullet:removableBullets)
	{
		g_bullets.eraseObject(bullet);
	}
	removableBullets.clear();

	for(auto enemy:removableEnemies)
	{
		g_enemies.eraseObject(enemy);
	}
	removableEnemies.clear();
}

void GameScene::crashEnemybulletAndHero()
{
	auto hero = (Hero*)this->getChildByTag(HERO_TAG);
	if(!hero->getActive())
		return;
	for(auto ebullet:e_bullets)
	{
		collisionDetection(hero,ebullet,removableBullets_e1);
	}

	for(auto ebullet:e_left_bullets)
	{
		collisionDetection(hero,ebullet,removableBullets_e2);
	}

	for(auto ebullet:e_right_bullets)
	{
		collisionDetection(hero,ebullet,removableBullets_e3);
	}

	for(auto ebullet:e_Fort_bullets)
	{
		collisionDetection(hero,ebullet,removableBullets_e4);
	}

	for(auto ebullet:e_track_bullets)
	{
		collisionDetection(hero,ebullet,removableBullets_e5);
	}
	for(auto ebullet:e_Big_bullets)
	{
		collisionDetection(hero,ebullet,removableBullets_e6);
	}
	clearCrossBullet(e_bullets,removableBullets_e1);
	clearCrossBullet(e_left_bullets,removableBullets_e2);
	clearCrossBullet(e_right_bullets,removableBullets_e3);
	clearCrossBullet(e_Fort_bullets,removableBullets_e4);
	clearCrossBullet(e_track_bullets,removableBullets_e5);
	clearCrossBullet(e_Big_bullets,removableBullets_e6);
}

void GameScene::cleartrackBullet(float)
{
	for(auto e_track_bullet:e_track_bullets)
	{
		this->removeChild(e_track_bullet);
	}
	e_track_bullets.clear();
}

void GameScene::crashPropAndHero(){
	auto hero = (Hero*)this->getChildByTag(HERO_TAG);
	//prop check
	for (auto prop : this->h_props)
	{ 
		if (prop->getBoundingBox().intersectsRect(hero->getBoundingBox()) )
		{ 
			Audio->playEffect("get_tool.mp3");
			switch(prop->getType()){
			case Enhance_Bullet:
				
				(m_doubleBulletCount > 0)?(m_multiBulletCount = MULTIBULLET_NUMBER)
					:(m_doubleBulletCount = DOUBLEBULLET_NUMBER);
				break;
			case Bomb:
				if(m_BombCount < 3){
					m_BombCount++;
					updateBomb();
				}
				break;
			case Hp:
				{
						hero->setHP(hero->getHP()+1);
						break;
				}
				break;
			case SpeedDown:
				{
					downEnemySpeed();
				}
				break;
			case ProtectCover:
				createProtect();
				break;
			case Gold:
				m_gold++;
			default:
				break;
			}
			this->removeChild(prop);
			removableProps.pushBack(prop);
		}

		if(prop->getPositionY() ==  -prop->getContentSize().height/2)
		{
			removableProps.pushBack(prop);
		}
	}

	for(auto prop : removableProps) {
		this->h_props.eraseObject(prop);
	}
	removableProps.clear();

}

void GameScene::downEnemySpeed(){
	m_isEnemeySpeedDown = true;
	m_EnemySpeedMulti = ENEMY_SPEED_DOWN_MULTI;
	auto snowSprite = Sprite::create();
	snowSprite->setAnchorPoint(Vect::ZERO);
	snowSprite->setPosition(Vect::ZERO);
	this->addChild(snowSprite, UI_LAYER, SNOW_SPRITE_TAG);
	auto snow = MyAnimationCache->getAnimation("SpeedDown");
	auto animate = Animate::create(snow);
	snowSprite->runAction(animate);
	schedule(schedule_selector(GameScene::regainEnemySpeed), 0, 1, ENEMY_SPEED_REGAIN_DELAY);
}

void GameScene::collisionDetection(Hero* hero,Bullet* ebullet,Vector<Bullet*>& removableBullets)
{
	if((ebullet)->getBoundingBox().intersectsRect((hero)->getBoundingBox())&& hero->getActive()) 
	{  
		//clean the bullet and set flag to ture
		this->removeChild((ebullet));                                
		removableBullets.pushBack(ebullet);
		if(m_isProtected){
		}
		else{
			if(hero->getHP() <= 1)
			{
				GameOver();
			}
			else
				hero->rebirthHero(isBossDie);
		}

	} 
}

void GameScene::clearCrossBullet(Vector<Bullet*>& bullets,Vector<Bullet*>& removableBullets)
{
	for(auto bullet:removableBullets)
	{
		e_bullets.eraseObject(bullet);
	}
	removableBullets.clear();
}

void GameScene::trackEnemyMove(Enemy* enemy)
{
	auto hero=this->getChildByTag(HERO_TAG);
	auto pos=enemy->getPosition();
	auto delta=ccpSub(hero->getPosition(),pos);
	auto distance=ccpDistance(hero->getPosition(),pos);
	float speed=5;
	float x=pos.x+speed*(float)delta.x/distance;
	float y=pos.y+speed*(float)delta.y/distance;

	float deltaRotation=90-atan2(y-pos.y,x-pos.x)*180/3.14;
	enemy->setPosition(x,y);
	enemy->setRotation(deltaRotation);
}

void GameScene::regainEnemySpeed(float dt){
	auto snow = getChildByTag(SNOW_SPRITE_TAG);
	removeChild(snow);
	m_isEnemeySpeedDown = false;
	m_EnemySpeedMulti = 1;
}

void GameScene::createProtect(){
	if(m_isProtected)
	{
		vanishProtect(0.0);
	}
	m_isProtected = true;
	auto hero = getChildByTag(HERO_TAG);
	auto cover = Sprite::create("protective.png");
	cover->setPosition(hero->getPosition());
	this->addChild(cover, UI_LAYER, COVER_TAG);
	schedule(schedule_selector(GameScene::vanishProtect), 0, 0, 5);
}

void GameScene::vanishProtect(float dt){
	m_isProtected = false;
	removeChildByTag(COVER_TAG);
}

void GameScene::updateProtect(){
	if(m_isProtected)
	{
		auto cover = getChildByTag(COVER_TAG);
		auto hero = getChildByTag(HERO_TAG);
		cover->setPosition(hero->getPosition());
	}
	else
	{

	}
}

void GameScene::createGoldLabel(){
	auto goldLabel = Sprite::create("moneyLogo.png");
	goldLabel->setPosition(goldLabel->getContentSize().width, VisSize.height-goldLabel->getContentSize().height);
	addChild(goldLabel, UI_LAYER, GOLD_LABEL_TAG);

	//the score Label
	auto gold = Label::createWithSystemFont(StringUtils::format("X%d", m_gold),"Arial",28);
	gold->setAnchorPoint(Vect::ANCHOR_MIDDLE_LEFT);
	gold->setPosition( VisSize.width/6,  VisSize.height-goldLabel->getContentSize().height);
	this->addChild(gold, UI_LAYER, GOLD_TAG);
}

void GameScene::updateGoldLabel(){
	auto gold = (Label*)getChildByTag(GOLD_TAG);
	gold->setString(StringUtils::format("%d",  m_gold));
}

void GameScene::readData(){
	if(MyUserDefault->getBoolForKey("isExist", false)){
		m_score = MyUserDefault->getIntegerForKey("Score", 0);
		m_gold = MyUserDefault->getIntegerForKey("Gold", 0);
		m_BombCount = MyUserDefault->getIntegerForKey("Bomb", 0);
		m_heroHP = MyUserDefault->getIntegerForKey("HeroHP", 0);
		m_heroLevel = MyUserDefault->getIntegerForKey("HeroLevel", 0);
		m_isProtected =MyUserDefault->getBoolForKey("ProtectCover", false);
		m_GameLevel = MyUserDefault->getIntegerForKey("GameLevel", 1);
		m_isEnemeySpeedDown = MyUserDefault->getBoolForKey("SpeedDown", false);
	}
}

void GameScene::GameOver(){
	/*SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect("gameover.mp3");*/
	auto hero = (Hero*) getChildByTag(HERO_TAG);
	hero->setMove(false);
	hero->setActive(false);
	hero->setAlive(false);
	Audio->playEffect("hero_die_finally.mp3");
	auto animation = MyAnimationCache->getAnimation("Hero1 Down");
	auto animate = Animate::create(animation);
	auto jumptoOver = CallFunc::create([=](){
		auto scene = OverScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	writeData();
	hero->runAction(Sequence::create(animate, jumptoOver, nullptr));
}

//write the 
void GameScene::writeData(){
	auto history = MyUserDefault->getIntegerForKey("HistoryGameLevel");
	if(m_GameLevel> history && m_GameLevel <= 3)
		MyUserDefault->setIntegerForKey("HistoryGameLevel", m_GameLevel);
	MyUserDefault->setIntegerForKey("Score", m_score);
	MyUserDefault->setIntegerForKey("Gold", m_gold);
	MyUserDefault->setIntegerForKey("Bomb", m_BombCount);
	MyUserDefault->setIntegerForKey("HeroHP", m_heroHP);
	MyUserDefault->setIntegerForKey("HeroLevel", m_heroLevel);
	MyUserDefault->setBoolForKey("ProtectCover", false);
	MyUserDefault->setIntegerForKey("GameLevel", m_GameLevel);
	MyUserDefault->setBoolForKey("SpeedDown", false);
}

void GameScene::jumpToBoss(){

	m_isBossScene = true;
}

void GameScene::goThrough(){
	auto hero =(Hero*) getChildByTag(HERO_TAG);

	if(m_GameLevel <= 3)
			m_GameLevel++;
	auto move = MoveBy::create(2, Point(0, VisSize.height-hero->getPositionY()+hero->getContentSize().height/2));
	writeData();
	auto jump = CallFunc::create([=](){

		auto shopScene = GameScene::createScene();
		Director::getInstance()->replaceScene(shopScene);
	});
	auto jumptoSuccess = CallFunc::create([=](){
		auto scene = SuccessScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});

	(m_GameLevel == 4)?(hero->runAction(Sequence::create(DelayTime::create(1), move, jumptoSuccess, nullptr)))
		:( hero->runAction(Sequence::create(DelayTime::create(1), move,  jump, nullptr)));

}

bool GameScene::canCreateBoss()
{
	return (m_score >= SCORE_CREATEBOSS) && (m_score % SCORE_CREATEBOSS == 0);
}