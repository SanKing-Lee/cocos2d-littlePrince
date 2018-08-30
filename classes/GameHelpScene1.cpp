#include "GameHelpScene1.h"
#include "SimpleAudioEngine.h"
#include "CommonData.h"
#include "GameHelpScene.h"
using namespace CocosDenshion;
USING_NS_CC;


GameHelpScene1::GameHelpScene1(){

}
GameHelpScene1::~GameHelpScene1(){

}

Scene* GameHelpScene1::createScene(){
	auto scene=Scene::create();
	auto layer=GameHelpScene1::create();
	scene->addChild(layer);
	return scene;
}

GameHelpScene1* GameHelpScene1::create(){
	auto gameHelpScene=new GameHelpScene1();
	if(gameHelpScene && gameHelpScene->init()){
		gameHelpScene->autorelease();
		return gameHelpScene;
	}else{
		delete gameHelpScene;
		gameHelpScene=NULL;
		return NULL;
	}
}

bool GameHelpScene1::init(){
	do{
		if(!Layer::init()){
			return false;
		}
		auto bg=Sprite::create("background_help2.png");
		Point origin = Director::getInstance()->getVisibleOrigin();//询问可视窗口原点
		bg->setPosition(VisSize.width/2+origin.x,VisSize.height/2+origin.y);
		this->addChild(bg,-1);
		//回到上一页
		auto re_begin=Sprite::create("backToPage.png");
		auto menuItemRe_begin=MenuItemSprite::create(re_begin,re_begin,[](Ref*){
			SimpleAudioEngine::getInstance()->playEffect("button.mp3");
			auto scene=GameHelpScene::createScene();
		//	Director::getInstance()->replaceScene(TransitionMoveInL::create(2.0f,scene));
			Director::getInstance()->replaceScene(TransitionFade::create(1.0f,scene,Color3B(100,100,60)));
		});
		menuItemRe_begin->setPosition(re_begin->getContentSize().width/2+15,re_begin->getContentSize().height/2+15);

		auto menu=Menu::create(menuItemRe_begin,NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);

		return true;
	}while(0);
	return false;
}