#include "RankScene.h"
#include <fstream>
#include "CommonData.h"
#include "GameScene.h"

USING_NS_CC;

RankScene::RankScene(){
	readScore();
}

RankScene* RankScene::create(){
	auto pp = new RankScene();
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

cocos2d::Scene* RankScene::createScene(){
	auto scene = cocos2d::Scene::create();

	//"layer" is an autorelease object
	auto layer = RankScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	//return the scene
	return scene;
}

bool RankScene::init(){
	//background
	createBackground();

	//Restart
	createMenu_Restart();

	//lable
	displayRank();

	return true;
}


void RankScene::readScore(){
	if(UserDefaultInstance->getBoolForKey("isExist", false)){
		for( int i = 1; i <= UserDefaultInstance->getIntegerForKey("ScoreNumbers", 0); i++){
			r_scores.push_back( UserDefaultInstance->getIntegerForKey
				(StringUtils::format("score_%dth", i).c_str(), 0)
			);
		}
	}
}

void RankScene::createBackground(){
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot.plist");
	cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile("shoot_background.plist");
	auto bg = cocos2d::Sprite::createWithSpriteFrameName("background.png");
	bg->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	bg->setPosition(0, VISIBLE_SIZE.height);
	this->addChild(bg, BG1_TAG);
}

void RankScene::createMenu_Restart(){
	auto r_spRestart = Sprite::createWithSpriteFrameName("btn_finish.png");
	auto r_itemRestart = MenuItemSprite::create(r_spRestart, r_spRestart, [](Ref *) {
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	auto r_menuRestart = Menu::create();
	r_menuRestart->addChild(r_itemRestart, UI_LAYOUT, RESTART_TAG);
	r_menuRestart->setPosition(VISIBLE_SIZE.width-80, 40);
	this->addChild(r_menuRestart, UI_LAYOUT, RESTARTMENU_TAG);
}

void RankScene::displayRank(){
	auto RankName = LabelTTF::create ("RANK", "Arial", 48);
	RankName->setColor(Color3B::BLACK);
	RankName->setPosition(VISIBLE_SIZE.width/2, VISIBLE_SIZE.height/10*9);
	this->addChild(RankName, UI_LAYOUT, RANKNAME_TAG);

	int j = 0;
	auto str1 = StringUtils::format("%d.\n\n", j+1);
	for(j = 1; j < MIN(r_scores.size(), MAX_RANK); j++)
	{
		str1 += StringUtils::format("%d.\n\n", j+1);
	}
	auto score1 = Label::createWithBMFont("font.fnt","0");
	score1->setAnchorPoint(Vect::ANCHOR_TOP_LEFT);
	score1 ->setPosition(VISIBLE_SIZE.width/4, VISIBLE_SIZE.height/10*8);
	score1 ->setString(str1);
	this->addChild(score1, UI_LAYOUT);

	auto str2 = StringUtils::format("%d\n\n", r_scores.at(0));
	for(int i = 1; i < MIN(r_scores.size(), MAX_RANK); i++)
	{
		str2 += StringUtils::format("%d\n\n", r_scores.at(i)); 
	}
	auto score2 = Label::createWithBMFont("font.fnt","0");
	score2->setString(str2);
	score2->setAnchorPoint(Vect::ANCHOR_TOP_LEFT);
	score2->setPosition(VISIBLE_SIZE.width/2, VISIBLE_SIZE.height/10*8);
	this->addChild(score2, UI_LAYOUT);
}
