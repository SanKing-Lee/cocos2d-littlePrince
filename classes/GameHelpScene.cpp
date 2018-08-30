#include "GameHelpScene.h"
#include "SimpleAudioEngine.h"
#include "CommonData.h"
using namespace CocosDenshion;
USING_NS_CC;


GameHelpScene::GameHelpScene(){

}
GameHelpScene::~GameHelpScene(){

}

Scene* GameHelpScene::createScene(){
	auto scene=Scene::create();
	auto layer=GameHelpScene::create();
	scene->addChild(layer);
	return scene;
}

GameHelpScene* GameHelpScene::create(){
	auto gameHelpScene=new GameHelpScene();
	if(gameHelpScene && gameHelpScene->init()){
		gameHelpScene->autorelease();
		return gameHelpScene;
	}else{
		delete gameHelpScene;
		gameHelpScene=NULL;
		return NULL;
	}
}

bool GameHelpScene::init(){
	do{
		if(!Layer::init()){
			return false;
		}
		auto bg=Sprite::create("background_help1.png");
		Point origin = Director::getInstance()->getVisibleOrigin();//询问可视窗口原点
		bg->setPosition(VisSize.width/2+origin.x,VisSize.height/2+origin.y);
		this->addChild(bg,-1);
		//回到开始菜单
		auto re_begin=Sprite::create("backToBegin.png");
		auto menuItemRe_begin=MenuItemSprite::create(re_begin,re_begin,[](Ref*){
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			auto scene=GameBegin::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f,scene,Color3B(100,100,60)));
		});
		menuItemRe_begin->setPosition(re_begin->getContentSize().width/2+15,re_begin->getContentSize().height/2+15);

		auto next=Sprite::create("goToPage.png");
		auto menuItem_next=MenuItemSprite::create(next,next,[](Ref*){
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			auto scene=GameHelpScene1::createScene();
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f,scene,Color3B(100,100,60)));
		//	Director::getInstance()->replaceScene(TransitionMoveInR::create(1.5f,scene));
		//	Director::getInstance()->replaceScene(TransitionFlipX::create(2.0f,scene,kCCTransitionOrientationLeftOver));
		});
		menuItem_next->setPosition(VisSize.width-(next->getContentSize().width/2)-15,next->getContentSize().height/2+15);

		auto menu=Menu::create(menuItem_next,menuItemRe_begin,NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);

		return true;
	}while(0);
	return false;
}