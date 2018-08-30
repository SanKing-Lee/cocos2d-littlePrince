#include "OverScene.h"

USING_NS_CC;

OverScene::OverScene(){
}

OverScene* OverScene::create(){
	auto pp = new OverScene();
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

Scene* OverScene::createScene(){
	auto scene = Scene::create();

	//"layer" is an autorelease object
	auto layer = OverScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	//return the scene
	return scene;
}

bool OverScene::init(){
	//background
	createBackground();
	Audio->playBackgroundMusic("gameover_bk.mp3");
	//score
	readScore();
	displayScore();
	displayGold();

	//Restart
	//createMenu_Restart();

	//Ranking
	createMenu_Rank();
	createMenu_Return2MainMenu();
	createMenu_Quit();
	writeScore();

	return true;
}

void OverScene::writeScore(){
	if(MyUserDefault->getBoolForKey("isExist")){
		MyUserDefault->setIntegerForKey("ScoreNumbers", scores.size());
		for(int i = 1; i <= scores.size(); i++){
			MyUserDefault->setIntegerForKey(StringUtils::format("score_%dth", i).c_str(), scores.at(i-1));
		}
		scores.clear();
	}

	else {
		log("Write scores failed");
	}
}

void OverScene::readScore(){
	//xml exists

	if(MyUserDefault->getBoolForKey("isExist", false)){
		for( int i = 1; i <= MyUserDefault->getIntegerForKey("ScoreNumbers", 0); i++){
			scores.push_back( MyUserDefault->getIntegerForKey
				(StringUtils::format("score_%dth", i).c_str(), 0)
			);
		}
		o_score = MyUserDefault->getIntegerForKey("Score", 0);
		o_gold = MyUserDefault->getIntegerForKey("Gold", 0);
		scores.push_back(o_score);

	}
	//xml not exists
	else{
		MyUserDefault->setBoolForKey("isExist", true);
		for(int i = 1; i <= MAX_RANK_NUMBER; i++){
			MyUserDefault->setIntegerForKey(StringUtils::format("scores_%dth", i).c_str(), 0);
		}
	}
}

void OverScene::createBackground(){
	auto bg=Sprite::createWithSpriteFrameName("bg_GameOver.png");
	bg->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	bg->setPosition(VisSize.width/2,VisSize.height);
	this->addChild(bg, BG_LAYER);
}

void OverScene::displayScore(){
	std::sort(std::begin(scores), std::end(scores), std::greater<int>());
	while(scores.size() > MAX_RANK_NUMBER)
	{ 
		scores.pop_back();
	}
	auto lblScore=Label::createWithSystemFont(StringUtils::format("%d", o_score), "Arial", 28);
	lblScore->setPosition(VisSize.width/2,VisSize.height*2/3 - 10);
	this->addChild(lblScore);
	lblScore->setColor(Color3B(0,0,0));
}

void OverScene::displayGold(){
	auto goldLabel = Sprite::create("moneyLogo.png");
	goldLabel->setPosition(goldLabel->getContentSize().width, VisSize.height-goldLabel->getContentSize().height);
	addChild(goldLabel, UI_LAYER, GOLD_LABEL_TAG);

	//the score Label
	auto gold = Label::createWithSystemFont(StringUtils::format("%d", o_gold),"Arial",28);
	gold->setPosition(goldLabel-> getContentSize().width + VisSize.width/10,  VisSize.height-goldLabel->getContentSize().height);
	gold->setString(StringUtils::format("%d", o_gold));
	this->addChild(gold, UI_LAYER, GOLD_TAG);
}

void OverScene::createMenu_Restart(){
	auto spRestart = Sprite::createWithSpriteFrameName("back.png");
	auto itemRestart = MenuItemSprite::create(spRestart, spRestart, [](Ref *) {
		LoadingScene::initData();
		auto scene = GameScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	auto menuRestart = Menu::create();
	menuRestart->addChild(itemRestart, UI_LAYER, RESTART_TAG);
	menuRestart->setPosition(VisSize.width-80, 40);
	this->addChild(menuRestart, UI_LAYER, RESTARTMENU_TAG);
}

void OverScene::createMenu_Rank(){
	/*auto spRank = Sprite::create("Rank3.png");
	auto itemRank = MenuItemSprite::create(spRank, spRank, [](Ref*){
		auto rankScene = RankScene::createScene();
		Director::getInstance()->pushScene(rankScene);
	});
	auto menuRank = Menu::create();
	menuRank->addChild(itemRank, UI_LAYER, RANK_TAG);
	menuRank->setPosition(VisSize.width-80, VisSize.height-40);
	this->addChild(menuRank, UI_LAYER, RANKMENU_TAG);*/
		//²é¿´ÅÅÐÐ°ñ
	auto rank = Sprite::createWithSpriteFrameName("level_list.png");
	auto menuItemRank = MenuItemSprite::create(rank, rank, [](Ref *){
		SimpleAudioEngine::getInstance()->playEffect("button.mp3");
		auto scene = RankScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	float x2 = VisSize.width*3/4 - 30;
	float y2 = VisSize.height/2 + 60;
	menuItemRank->setPosition(x2, y2);

	auto rankmenu = Menu::create(menuItemRank, NULL);
	rankmenu->setPosition(Point::ZERO);
	this->addChild(rankmenu);
}

void OverScene::createMenu_Return2MainMenu(){
	auto back = Sprite::createWithSpriteFrameName("backmenu.png");
	auto menuItemBack = MenuItemSprite::create(back, back, [](Ref *){
		SimpleAudioEngine::getInstance()->playEffect("button.mp3");
		auto scene = GameBegin::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	float x1 = VisSize.width/2 + 10;
	float y1 = VisSize.height/3 + 30 ;
	menuItemBack->setPosition(x1, y1);
	auto quit = Sprite::createWithSpriteFrameName("quit.png");
	auto menuItemQuit = MenuItemSprite::create(quit, quit, CC_CALLBACK_1(OverScene::gameQuitCallback, this));
	menuItemQuit->setPosition(x1, y1-110);
	
	auto endmenu = Menu::create(menuItemBack, menuItemQuit, NULL);
	endmenu->setPosition(Point::ZERO);
	this->addChild(endmenu);
}

void OverScene::createMenu_Quit(){

}

void OverScene::gameQuitCallback(Ref* pSender)
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