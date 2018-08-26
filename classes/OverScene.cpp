#include "OverScene.h"
#include "CommonData.h"
#include "GameScene.h"
#include <SimpleAudioEngine.h>
#include "RankScene.h"

USING_NS_CC;

OverScene::OverScene(int score){
	o_score = score;
}

OverScene* OverScene::create(int score){
	auto pp = new OverScene(score);
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

cocos2d::Scene* OverScene::createWithScore(int score){
	auto scene = cocos2d::Scene::create();

	//"layer" is an autorelease object
	auto layer = OverScene::create(score);

	// add layer as a child to scene
	scene->addChild(layer);

	//return the scene
	return scene;
}



bool OverScene::init(){
	//background
	createBackground();

	//score
	displayScore();

	//Restart
	createMenu_Restart();

	//Ranking
	createMenu_Rank();

	return true;
}

void OverScene::writeScore(){
	if(UserDefaultInstance->getBoolForKey("isExist")){
		UserDefaultInstance->setIntegerForKey("ScoreNumbers", scores.size());
		for(int i = 1; i <= scores.size(); i++){
			UserDefaultInstance->setIntegerForKey(StringUtils::format("score_%dth", i).c_str(), scores.at(i-1));
		}
	}
	else {
		log("Write scores failed");
	}
}

void OverScene::readScore(){
	//xml exists
	if(UserDefaultInstance->getBoolForKey("isExist", false)){
		for( int i = 1; i <= UserDefaultInstance->getIntegerForKey("ScoreNumbers", 0); i++){
			scores.push_back( UserDefaultInstance->getIntegerForKey
				(StringUtils::format("score_%dth", i).c_str(), 0)
			);
		}
	}
	//xml not exists
	else{
		UserDefaultInstance->setBoolForKey("isExist", true);
		for(int i = 1; i <= MAX_RANK; i++){
			UserDefaultInstance->setIntegerForKey(StringUtils::format("scores_%dth", i).c_str(), 0);
		}
	}
}

void OverScene::createBackground(){
	auto bg = Sprite::createWithSpriteFrameName("gameover.png");
	bg->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	bg->setPosition(0, VISIBLE_SIZE.height);
	this->addChild(bg, BG1_TAG);
}

void OverScene::displayScore(){
	auto scoreLable = Label::createWithBMFont("font.fnt","0");
	scoreLable->setAnchorPoint(cocos2d::Vect::ANCHOR_MIDDLE);
	scoreLable->setPosition(VISIBLE_SIZE.width / 2, VISIBLE_SIZE.height / 3);
	scoreLable->setColor(Color3B::BLACK);
	scoreLable->setScale(0.8);
	scoreLable->setString(StringUtils::format("%d", o_score));
	this->addChild(scoreLable, UI_LAYOUT, FINALSCORELABEL_TAG);

	readScore();
	scores.push_back(o_score);
	std::sort(std::begin(scores), std::end(scores), std::greater<int>());
	while(scores.size() > MAX_RANK)
	{ 
		scores.pop_back();
	}
	auto lblHighScore = Label::createWithBMFont("font.fnt", StringUtils:: format("%d",scores.front()));	
	lblHighScore->setPosition(Point(VISIBLE_SIZE)/2 + Point(0, 200));
	lblHighScore->setColor(Color3B::BLACK);
	this->addChild(lblHighScore, UI_LAYOUT, HIGHSCORE_TAG);	
	writeScore();
}

void OverScene::createMenu_Restart(){
	auto spRestart = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto itemRestart = MenuItemSprite::create(spRestart, spRestart, [](Ref *) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	auto menuRestart = Menu::create();
	menuRestart->addChild(itemRestart, UI_LAYOUT, RESTART_TAG);
	menuRestart->setPosition(VISIBLE_SIZE.width-80, 40);
	this->addChild(menuRestart, UI_LAYOUT, RESTARTMENU_TAG);
}

void OverScene::createMenu_Rank(){
	auto spRank = Sprite::create("Rank3.png");
	auto itemRank = MenuItemSprite::create(spRank, spRank, [](Ref*){
		auto rankScene = RankScene::createScene();
		Director::getInstance()->replaceScene(rankScene);
	});
	auto menuRank = Menu::create();
	menuRank->addChild(itemRank, UI_LAYOUT, RANK_TAG);
	menuRank->setPosition(VISIBLE_SIZE.width-80, VISIBLE_SIZE.height-40);
	this->addChild(menuRank, UI_LAYOUT, RANKMENU_TAG);
}