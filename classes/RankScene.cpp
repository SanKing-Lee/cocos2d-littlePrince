#include "RankScene.h"
#include <fstream>
#include "CommonData.h"
#include "GameScene.h"
#include "OverScene.h"
#pragma once

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
	auto scene = Scene::create();

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
	createMenu_Back2Over();

	//Label
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
	auto bg = Sprite::createWithSpriteFrameName("level_list_background.png");
	bg->setAnchorPoint(Point::ANCHOR_TOP_LEFT);
	bg->setPosition(0, VISIBLE_SIZE.height);
	this->addChild(bg, BG1_TAG);


	auto star = Sprite::create();
	star->setPosition(Point(VISIBLE_SIZE.width/2,VISIBLE_SIZE.height/40*33));
	addChild(star,UI_LAYOUT);
	star->runAction(Animate::create(AnimationCacheInstance->getAnimation("star twinkle")));
}

void RankScene::createMenu_Back2Over(){
	auto Back = Sprite::create("back.png");
	
	auto itemBack = MenuItemSprite::create(Back, Back, [](Ref *) {
		auto scene = OverScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	auto r_menuRestart = Menu::create();
	r_menuRestart->addChild(itemBack, UI_LAYOUT, RESTART_TAG);
	r_menuRestart->setPosition(VISIBLE_SIZE.width-80, 40);
	this->addChild(r_menuRestart, UI_LAYOUT, RESTARTMENU_TAG);
}

void RankScene::displayRank(){
	auto str = StringUtils::format("%d\n\n\n\n", r_scores.at(0));
	for(int i = 1; i < MIN(r_scores.size(), MAX_RANK); i++)
	{
		str += StringUtils::format("%d\n\n\n\n", r_scores.at(i)); 
	}
	auto score2 = Label::createWithBMFont("font.fnt","0");
	score2->setString(str);
	score2->setAnchorPoint(Vect::ANCHOR_TOP_LEFT);
	score2->setPosition(VISIBLE_SIZE.width/5*2, VISIBLE_SIZE.height/40*29);
	this->addChild(score2, UI_LAYOUT);
}
