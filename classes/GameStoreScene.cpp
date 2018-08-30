#include "GameStoreScene.h"

#include "CommonData.h"
#include "PopupLayer.h"
#include "GameBegin.h"
using namespace CocosDenshion;
USING_NS_CC;
USING_NS_CC_EXT;


GameStoreScene::GameStoreScene(){
	this->number=6;
//	m_position[0]=Point(VisSize.width/3,VisSize.height/2);
	//m_position[1]=Point(VisSize.width/3*2,VisSize.height/2);
//	m_position[0].setPoint(VisSize.width/3,VisSize.height/2);
//	m_position[1].setPoint(VisSize.width/3*2,VisSize.height/2);
//	m_position.pushBack(Point(VisSize.width/3,VisSize.height/2));
	//m_position.pushBack(Point(VisSize.width/3*2,VisSize.height/2));
}
GameStoreScene::~GameStoreScene(){

}

Scene* GameStoreScene::createScene(){
	auto scene=Scene::create();
	auto layer=GameStoreScene::create();
	scene->addChild(layer);
	return scene;
}

GameStoreScene* GameStoreScene::create(){
	auto gameStoreScene=new GameStoreScene();
	if(gameStoreScene && gameStoreScene->init()){
		gameStoreScene->autorelease();
		return gameStoreScene;
	}else{
		delete gameStoreScene;
		gameStoreScene=NULL;
		return NULL;
	}
}

bool GameStoreScene::init(){
	srand((unsigned int)time(0));//时间种子
	do{
		if(!Layer::init()){
			return false;
		}

		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ShopScene.plist");
		auto bg=Sprite::createWithSpriteFrameName("bg_Shop1.png");
		Point origin = Director::getInstance()->getVisibleOrigin();//询问可视窗口原点
		bg->setPosition(VisSize.width/2+origin.x,VisSize.height/2+origin.y);
		this->addChild(bg,-1);

		CCActionInterval* actionTo=CCRotateTo::create(0.5f,20);
		CCActionInterval* actionBack=CCRotateTo::create(1.0f,-20);
		FiniteTimeAction* seq=Sequence::create(actionTo,actionBack,NULL);
		ActionInterval* repeatForever=RepeatForever::create((ActionInterval*)seq);
		CCActionInterval* actionTo1=CCRotateTo::create(0.5f,-20);
		CCActionInterval* actionBack1=CCRotateTo::create(1.0f,20);
		FiniteTimeAction* seq1=Sequence::create(actionTo1,actionBack1,NULL);
		ActionInterval* repeatForever1=RepeatForever::create((ActionInterval*)seq1);
		CCActionInterval* actionTo2=CCRotateTo::create(0.5f,20);
		CCActionInterval* actionBack2=CCRotateTo::create(1.0f,-20);
		FiniteTimeAction* seq2=Sequence::create(actionTo2,actionBack2,NULL);
		ActionInterval* repeatForever2=RepeatForever::create((ActionInterval*)seq2);
		CCActionInterval* actionTo3=CCRotateTo::create(0.5f,-20);
		CCActionInterval* actionBack3=CCRotateTo::create(1.0f,20);
		FiniteTimeAction* seq3=Sequence::create(actionTo3,actionBack3,NULL);
		ActionInterval* repeatForever3=RepeatForever::create((ActionInterval*)seq3);
		CCActionInterval* actionTo4=CCRotateTo::create(0.5f,20);
		CCActionInterval* actionBack4=CCRotateTo::create(1.0f,-20);
		FiniteTimeAction* seq4=Sequence::create(actionTo4,actionBack4,NULL);
		ActionInterval* repeatForever4=RepeatForever::create((ActionInterval*)seq4);
		CCActionInterval* actionTo5=CCRotateTo::create(0.5f,-20);
		CCActionInterval* actionBack5=CCRotateTo::create(1.0f,20);
		FiniteTimeAction* seq5=Sequence::create(actionTo5,actionBack5,NULL);
		ActionInterval* repeatForever5=RepeatForever::create((ActionInterval*)seq5);

		m_gold = MyUserDefault->getIntegerForKey("Gold");
		//玫瑰花初始化
		auto flower=Sprite::create("moneyLogo.png");
		flower->setPosition(flower->getContentSize().width,VisSize.height-flower->getContentSize().height);
		this->addChild(flower,0);
		auto lblMoneyNumber=cocos2d::Label::createWithSystemFont(StringUtils::format("%d", m_gold),"Arial",28);
		lblMoneyNumber->setPosition(flower->getContentSize().width+ VisSize.width/10, VisSize.height-flower->getContentSize().height);
		lblMoneyNumber->setColor(Color3B::WHITE);
		this->addChild(lblMoneyNumber,0,MONEY_TAG);

		auto menu=Menu::create();
		menu->setPosition(Point::ZERO);
		auto commodity1=Sprite::createWithSpriteFrameName("freeze.png");
		auto commodityMenu1=MenuItemSprite::create(commodity1,commodity1,[=](Ref*){
				SimpleAudioEngine::getInstance()->playEffect("button.mp3");
				CCLOG("======BuyCommodity1 Begin======");
				buy(SpeedDown);
		});
		commodityMenu1->setPosition(VisSize.width*8.2f/16.5f,VisSize.height*(1-6.2f/22.3f));
		menu->addChild(commodityMenu1,1);
		commodityMenu1->runAction(repeatForever1);

		auto commodity2=Sprite::createWithSpriteFrameName("hp_up.png");
		auto commodityMenu2=MenuItemSprite::create(commodity2,commodity2,[=](Ref*){
				SimpleAudioEngine::getInstance()->playEffect("button.mp3");
				CCLOG("======BuyCommodity2 Begin======");
				buy(Hp);
		});
		commodityMenu2->setPosition(VisSize.width*2.3f/16.5f,VisSize.height*10.8f/22.3f);
		menu->addChild(commodityMenu2,1);
		commodityMenu2->runAction(repeatForever2);

		auto commodity3=Sprite::createWithSpriteFrameName("protective.png");
		auto commodityMenu3=MenuItemSprite::create(commodity3,commodity3,[=](Ref*){
				SimpleAudioEngine::getInstance()->playEffect("button.mp3");
				CCLOG("======BuyCommodity3 Begin======");
				buy(ProtectCover);
		});
		commodityMenu3->setPosition(VisSize.width*14.4f/16.5f,VisSize.height*10.8f/22.3f);
		menu->addChild(commodityMenu3,1);
		commodityMenu3->runAction(repeatForever3);

		auto commodity4=Sprite::createWithSpriteFrameName("clear_up.png");
		auto commodityMenu4=MenuItemSprite::create(commodity4,commodity4,[=](Ref*){
				SimpleAudioEngine::getInstance()->playEffect("button.mp3");
				CCLOG("======BuyCommodity4 Begin======");
				buy(Bomb);
		});
		commodityMenu4->setPosition(VisSize.width/2,VisSize.height/2);
		menu->addChild(commodityMenu4,1);
		commodityMenu4->runAction(repeatForever4);

		auto noCommodity1=Sprite::createWithSpriteFrameName("bubble.png");
		noCommodity1->setPosition(VisSize.width*4.4f/16.5f,VisSize.height*4.1f/22.3f);
		this->addChild(noCommodity1);
		auto noCommodity2=Sprite::createWithSpriteFrameName("bubble.png");
		noCommodity2->setPosition(VisSize.width*12.4f/16.5f,VisSize.height*4.1f/22.3f);
		this->addChild(noCommodity2);
		auto back=Sprite::createWithSpriteFrameName("back2.png");
		back->setScale(1.3f);
		auto backMenu=MenuItemSprite::create(back,back,[=](Ref*){
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			MyUserDefault->setIntegerForKey("Gold", m_gold);
			auto scene=GameBegin::createScene();
			Director::getInstance()->replaceScene(scene);
		});
		backMenu->setPosition(VisSize.width-back->getContentSize().width/2-20,VisSize.height-back->getContentSize().height/2-20);
		menu->addChild(backMenu,1);
		this->addChild(menu);
		return true;
	}while(0);
	return false;
}

void GameStoreScene::buy(PropType type){
//	//弹出对话框  
	auto pl = PopupLayer::create("bg_Shop_Tankuang.png",Size(200,200));  
	pl->setCallbackFunc(this, callfuncN_selector(GameStoreScene::buttonCallback));

	auto menu=Menu::create();
	auto buttonOk=Sprite::create("buy.png");
	auto menuOk=MenuItemSprite::create(buttonOk,buttonOk,[=](Ref*){
		SimpleAudioEngine::getInstance()->playEffect("button.mp3");
		int price = 20;
		//switch(type){
		//case Hp: price = HPPrice; break;
		//case ProtectCover: price = ProtectPrice; break;
		//case Bomb: price = BombPrice; break;
		//case SpeedDown: price = FreezePrice; break;
		//default: price = 1000000000; break;
		//}
		if(m_gold >= price)
		{
			m_gold -= price;
			updateMoney();
			writeData(type);
		}
		pl->removeFromParent();
	});
	menuOk->setPosition(pl->getPositionX()-60,pl->getPositionY()-50);
	menu->addChild(menuOk);

	auto buttonNo=Sprite::create("cancle.png");
	auto menuNo=MenuItemSprite::create(buttonNo,buttonNo,[=](Ref* pSpender){
		SimpleAudioEngine::getInstance()->playEffect("button.mp3");
		pl->removeFromParent();
	});
	menuNo->setPosition(pl->getPositionX()+60,pl->getPositionY()-50);
	menu->addChild(menuNo);
	pl->addChild(menu);
	this->addChild(pl);  
}

void GameStoreScene::buttonCallback(cocos2d::Node *pNode){
    CCLog("button call back. tag: %d", pNode->getTag());
}

void GameStoreScene::updateMoney(){
	auto money = (Label*) getChildByTag(MONEY_TAG);
	money->setString(StringUtils::format("X%d", m_gold));
}

void GameStoreScene::writeData(PropType type){
	switch(type){
	case Bomb:
		MyUserDefault->setIntegerForKey("Bomb", MyUserDefault->getIntegerForKey("Bomb") + 1);
		break;
	case ProtectCover:
		MyUserDefault->setBoolForKey("ProtectCover", true);
		break;
	case SpeedDown:
		MyUserDefault->setBoolForKey("SpeedDown", true);
		break;
	case Hp:
		MyUserDefault->setIntegerForKey("HeroHP", MyUserDefault->getIntegerForKey("HeroHP") + 1);
		break;
	default:
		break;
	}
}