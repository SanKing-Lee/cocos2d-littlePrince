#include "GameBegin.h"
#include "SimpleAudioEngine.h"
#include "CommonData.h"
using namespace CocosDenshion;
USING_NS_CC;

int GameBegin::m_money=0;

GameBegin::GameBegin(){

}
GameBegin::~GameBegin(){

}

Scene* GameBegin::createScene(){
	auto scene=Scene::create();
	auto layer=GameBegin::create();
	scene->addChild(layer);
	return scene;
}

GameBegin* GameBegin::create(){
	auto gameBegin=new GameBegin();
	if(gameBegin && gameBegin->init()){
		gameBegin->autorelease();
		return gameBegin;
	}else{
		delete gameBegin;
		gameBegin=NULL;
		return NULL;
	}
}

void GameBegin::changeMoney(int number){
	GameBegin::m_money+=number;
}

bool GameBegin::init(){
	do{
		if(!cocos2d::Layer::init()){
			return false;
		}
		srand((unsigned int)time(0));//时间种子
		auto bg = Sprite::create("Background_begin.png");
		Point origin = Director::getInstance()->getVisibleOrigin();//询问可视窗口原点
		bg->setPosition(VisSize.width/2+origin.x,VisSize.height/2+origin.y);
		this->addChild(bg,-1);

		//玫瑰花初始化
		auto gold = MyUserDefault->getIntegerForKey("Gold", 0);
		auto flower=Sprite::create("moneyLogo.png");
		flower->setPosition(flower->getContentSize().width,VisSize.height-flower->getContentSize().height);
		this->addChild(flower,0);
		auto lblMoneyNumber=cocos2d::Label::createWithSystemFont(StringUtils::format("%d", gold),"Arial",28);
		lblMoneyNumber->setPosition(flower->getContentSize().width+ VisSize.width/10,VisSize.height-flower->getContentSize().height);
		lblMoneyNumber->setColor(Color3B::WHITE);
		this->addChild(lblMoneyNumber,0,MONEY_TAG);

		auto menu=Menu::create();

		//开始旅程菜单
		auto begin=Sprite::create("travel_begin.png");
		auto menuItemBegin=MenuItemSprite::create(begin,begin,[](Ref*){
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			auto scene=ThirdScene::createScene();//################
			Director::getInstance()->replaceScene(scene);
		});
		menuItemBegin->setPosition(VisSize.width/2,VisSize.height-begin->getContentSize().height/2-150);
		menu->addChild(menuItemBegin);
		menu->setPosition(Point::ZERO);
		//帮助菜单
		auto help=Sprite::create("help.png");
		auto menuItemHelp=MenuItemSprite::create(help,help,[](Ref*){
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			auto scene=GameHelpScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
		menuItemHelp->setPosition(Point(menuItemBegin->getPosition()-Point(0,help->getContentSize().height/2+50)));
		menu->addChild(menuItemHelp);
		//退出菜单
		auto over=Sprite::create("over.png");
		auto menuItemOver=MenuItemSprite::create(over,over,[](Ref*){
		     SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
				MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
				return false;
		    #endif
			Director::getInstance()->end();
			#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
				exit(0);
		    #endif
		});
		menuItemOver->setPosition(Point(menuItemHelp->getPosition()-Point(0,over->getContentSize().height/2+50)));
		menu->addChild(menuItemOver);

		//商店
		auto store=Sprite::create("shopLogo.png");
		auto menuItemStore=MenuItemSprite::create(store,store,[](Ref*){
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			auto scene=GameStoreScene::createScene();
			Director::getInstance()->replaceScene(scene);
		});
		menuItemStore->setPosition(VisSize.width-store->getContentSize().width/2,VisSize.height/3);
		menu->addChild(menuItemStore,1,MENUSTORE_TAG);

		this->addChild(menu,1,MENU_TAG);
//		CCActionInterval* actionTo=CCRotateTo::create(0.5f,20);
////		CCActionInterval* actionBack=actionTo->reverse();
//		CCActionInterval* actionTo2=CCRotateTo::create(1.0f,-20);
//		CCActionInterval* actionTo0=CCRotateTo::create(0.5f,0);
//		FiniteTimeAction* seq=Sequence::create(actionTo,actionTo2,NULL);
//		ActionInterval* repeatForever=RepeatForever::create((ActionInterval*)seq);
		//menuItemStore->runAction(repeatForever);
//		//this->scheduleUpdate();//定时器，每帧调用一次update函数
		return true;
	}while(0);
	return false;
}

void GameBegin::update(float){
	auto menu=this->getChildByTag(MENU_TAG);
	auto store=menu->getChildByTag(MENUSTORE_TAG);
	CCActionInterval* actionTo=CCRotateBy::create(0.5f,10);
	CCActionInterval* actionBack=actionTo->reverse();
	CCActionInterval* actionTo2=CCRotateBy::create(0.5f,-10);
	CCActionInterval* actionTo0=CCRotateTo::create(0.5f,0);
	store->runAction(CCSequence::create(actionTo,actionBack,NULL));
}