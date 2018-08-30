#include "SuccessScene.h"
#include "OverScene.h"
#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "CommonData.h"

using namespace CocosDenshion;

SuccessScene *SuccessScene::create() {
	auto success = new SuccessScene();
	if (success && success->init())
	{
		success->autorelease();
		return success;
	}
	delete success;
	success = NULL;
	return NULL;
}

Scene* SuccessScene::createScene()
{
	auto scene = Scene::create();
	auto layer = SuccessScene::create();
	scene->addChild(layer);
	return scene;
}

bool SuccessScene::init(){
	SimpleAudioEngine::getInstance()->stopBackgroundMusic();
	SimpleAudioEngine::getInstance()->playEffect("gameover.mp3");

	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("game_over.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("EndingScene.plist");
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sunset.plist");
	//���ر���ͼ
	auto bg=Sprite::createWithSpriteFrameName("bg_ending1.png");
	bg->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	bg->setPosition(VisSize.width/2,VisSize.height);
	this->addChild(bg,-1);

	//���ر���ͼ
	auto story=Sprite::createWithSpriteFrameName("content.png");
	story->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);
	story->setPosition(VisSize.width/2,VisSize.height);
	this->addChild(story,-1);

	//����õ�廨
	auto rose=Sprite::createWithSpriteFrameName("rose.png");
	rose->setAnchorPoint(Point::ANCHOR_BOTTOM_RIGHT);
	rose->setPosition(VisSize.width*3/4 - 35,VisSize.height/4 + 30);
	this->addChild(rose,2);

	//�ճ�����
	auto sunrise = Sprite::createWithSpriteFrameName("sunset1.png");
	sunrise->setPosition(VisSize.width/2, VisSize.height/2);
	this->addChild (sunrise,0);

	auto animation = Animation::create();
		for (int i = 1; i <= 10; i++)
		{
			auto png = StringUtils::format("sunset%d.png", i);
			auto spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(png);
			animation->addSpriteFrame(spriteFrame);
		}
	animation->setLoops(-1);
	animation->setDelayPerUnit(0.3f);	
	auto animate = Animate::create(animation);
	sunrise->runAction(animate);

	//���Ƕ���
	auto star=Sprite::createWithSpriteFrameName("bingling_1.png");
	star->setAnchorPoint(Point::ZERO);
	star->setPosition(Point::ZERO);
	this->addChild(star,1);

	auto animation1 = Animation::create();
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bingling_1.png"));
	animation1->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("blingbling_2.png"));
	animation1->setLoops(-1);
	animation1->setDelayPerUnit(0.2f);
	animate = Animate::create(animation1);
	star->runAction(animate);

	//��ת����������
	auto next = Sprite::createWithSpriteFrameName("back2_n2.png");

	auto menuItemNext = MenuItemSprite::create(next, next, [=](Ref *){
		SimpleAudioEngine::getInstance()->playEffect("button.mp3");
		auto scene = OverScene::createScene();
		Director::getInstance()->replaceScene(scene);
	});
	float x = VisSize.width - next->getContentSize().width - 10;
	float y = next->getContentSize().height + 10;
	menuItemNext->setPosition(x, y);

	auto nextmenu = Menu::create(menuItemNext, NULL);
	nextmenu->setPosition(Point::ZERO);
	this->addChild(nextmenu);

	return true;
}
