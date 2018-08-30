#include"ThirdScene.h"
//#include"first.h"
USING_NS_CC;
using namespace cocos2d;


ThirdScene *ThirdScene::create() {
	auto gameOver = new ThirdScene();
	if (gameOver && gameOver->init())
	{
		gameOver->autorelease();
		return gameOver;
	}
	delete gameOver;
	gameOver = nullptr;
	return nullptr;
}

Scene* ThirdScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ThirdScene::create(); 
	scene->addChild(layer);
	return scene;
}
bool ThirdScene::init(){
	if(!Layer::init()) return false; 
	Size visibleSize = Director::getInstance()->getVisibleSize();//可视窗口的大小
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("LevelChoseScene.plist");


	auto bg = Sprite::createWithSpriteFrameName("level_backgroud.png");//("thirdscene.png");//第三个界面的背景图
	bg->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);		
	bg->setPosition(visibleSize.width/2, visibleSize.height);//这里设置背景以顶部中央对齐屏幕
	this->addChild(bg, -1);//放在-1层

	auto star1 = Sprite::createWithSpriteFrameName("planet1_1.png");//("star1.png");//星球1的图片
	star1->setPosition(Point(visibleSize.width/4,visibleSize.height/4));
	this->addChild(star1,3);
	auto star2_n = Sprite::createWithSpriteFrameName("planet2_gray.png");//("star2_n.png");//星球2的图片
	star2_n->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(star2_n,3);//在图层3
	auto star3_n = Sprite::createWithSpriteFrameName("planet3_gray.png");//("star3_n.png");//星球3的图片
	star3_n->setPosition(Point(visibleSize.width-visibleSize.width/4,visibleSize.height-visibleSize.height/4));
	this->addChild(star3_n,3);//在图层3
		

	auto name1 = Sprite::createWithSpriteFrameName("planet1_name.png");//("title.png");//关卡的图片
	name1->setPosition(Point(visibleSize.width/4,visibleSize.height/4 - visibleSize.height/10));
	this->addChild(name1,3);

	auto name2 = Sprite::createWithSpriteFrameName("planet2_name.png");//("title.png");//关卡的图片
	name2->setPosition(Point(visibleSize.width/2,visibleSize.height/2 - visibleSize.height/10));
	this->addChild(name2,3);

	auto name3 = Sprite::createWithSpriteFrameName("planet3_name.png");//("title.png");//关卡的图片
	name3->setPosition(Point(visibleSize.width-visibleSize.width/4,visibleSize.height-visibleSize.height/4 - visibleSize.height/10));
	this->addChild(name3,3);
		
	auto menu_xzx = Menu::create();
	menu_xzx->setPosition(Point::ZERO);


	//返回柏蓉界面、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、、
	auto back = Sprite::create("back2.png");//WithSpriteFrameName
	auto toSec = MenuItemSprite::create(back, back, [=](Ref *){
	auto scene = GameBegin::createScene();//GameScene1::createScene();
	Director::getInstance()->replaceScene(scene);			
	});
	toSec->setPosition(Point(visibleSize.width/6,visibleSize.height-visibleSize.height/14));
	menu_xzx->addChild(toSec);//将到游戏1的按钮添加到menuxzx	
	//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,


	//blingbling的背景
	auto animation = Animation::create();
	auto star = Sprite::createWithSpriteFrameName("blingbling1.png");//("star1.png");
		//star->setAnchorPoint();//设置star锚点
		star->setPosition(visibleSize.width/2, visibleSize.height/2);
		this->addChild(star,2);
	animation = Animation::create();
	for (int i = 0; i < 2; i++)
	{
		auto png = StringUtils::format("blingbling%d.png",i+1);//("star%d.png", i+1);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
	}
		animation->setDelayPerUnit(0.5f);
		animation->setLoops(-1);
	star->runAction(Animate::create(animation));


	//从配置文件中读取通关情况，如果没有则返回默认值0
	initLevel();
		
	if((historyLevel == 1)||(historyLevel == 2)||(historyLevel == 3))//直接跳转到第一关的游戏场景中
	{	
		auto star1_y = Sprite::createWithSpriteFrameName("planet1_1.png");//WithSpriteFrameName
		auto toStar1 = MenuItemSprite::create(star1_y, star1_y, [=](Ref *){
			writeLevel(1);
			auto scene = GameScene::createScene();//GameScene1::createScene();
			Director::getInstance()->replaceScene(scene);			
		});
		toStar1->setPosition(Point(visibleSize.width/4,visibleSize.height/4));
		menu_xzx->addChild(toStar1);//将到游戏1的按钮添加到menuxzx	

		//转动的星球1
		animation = Animation::create();
		auto rool_1 = Sprite::createWithSpriteFrameName("planet1_1.png");//("star1.png");
			//star->setAnchorPoint();//设置star锚点
			rool_1->setPosition(visibleSize.width/4,visibleSize.height/4);
			this->addChild(rool_1,6);
		animation = Animation::create();
		for (int i = 0; i < 9; i++)
		{
			auto png = StringUtils::format("planet1_%d.png",i+1);//("star%d.png", i+1);
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
			animation->setDelayPerUnit(0.2f);
			animation->setLoops(-1);
		rool_1->runAction(Animate::create(animation));
			
	}
				
	if((historyLevel == 2)||(historyLevel == 3)){//通过第一关：第二个星球点亮图层覆盖第二个星球灰色图层并且跳转到第二个游戏场景中
		auto star2_y = Sprite::createWithSpriteFrameName("planet2_1.png");//("star2_y.png");//星球2点亮的图片WithSpriteFrameName
		auto toStar2 = MenuItemSprite::create(star2_y, star2_y, [=](Ref *){
				writeLevel(2);
			auto scene = GameScene::createScene();//GameScene2::createScene();
			Director::getInstance()->replaceScene(scene);			
		});
		toStar2->setPosition(Point(visibleSize.width/2,visibleSize.height/2));			
		menu_xzx->addChild(toStar2);//将到游戏2的按钮添加到menuxzx	

			//转动的星球2
		animation = Animation::create();
		auto rool_2 = Sprite::createWithSpriteFrameName("planet2_1.png");//("star1.png");
			//star->setAnchorPoint();//设置star锚点
			rool_2->setPosition(visibleSize.width/2,visibleSize.height/2);
			this->addChild(rool_2,6);
		animation = Animation::create();
		for (int i = 0; i < 9; i++)
		{
			auto png = StringUtils::format("planet2_%d.png",i+1);//("star%d.png", i+1);
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
			animation->setDelayPerUnit(0.2f);
			animation->setLoops(-1);
		rool_2->runAction(Animate::create(animation));

	}
	
	if((historyLevel == 3)){//通过第二关：第三个星球点亮图层覆盖第三个星球灰色图层并且跳转到第三个游戏场景中

		auto star3_y = Sprite::createWithSpriteFrameName("planet3_1.png");//("star3_y.png");//星球3点亮的图片->通往第三关WithSpriteFrameName
		auto toStar3 = MenuItemSprite::create(star3_y, star3_y, [=](Ref *){
			writeLevel(3);
			auto scene = GameScene::createScene();//GameScene3::createScene();
			Director::getInstance()->replaceScene(scene);			
		});
		toStar3->setPosition(Point(visibleSize.width-visibleSize.width/4,visibleSize.height-visibleSize.height/4));		
		menu_xzx->addChild(toStar3);//将到游戏3的按钮添加到menuxzx	

			
		//转动的星球3
		animation = Animation::create();
		auto rool_3 = Sprite::createWithSpriteFrameName("planet3_1.png");//("star1.png");
			//star->setAnchorPoint();//设置star锚点
		rool_3->setPosition(visibleSize.width-visibleSize.width/4,visibleSize.height-visibleSize.height/4);
		this->addChild(rool_3,6);
		animation = Animation::create();
		for (int i = 0; i < 9; i++)
		{
			auto png = StringUtils::format("planet3_%d.png",i+1);//("star%d.png", i+1);
			animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName(png));
		}
			animation->setDelayPerUnit(0.2f);
			animation->setLoops(-1);
			rool_3->runAction(Animate::create(animation));

	}
	this->addChild(menu_xzx,4);	//,4把menu_xzx放在第三层
	return true;
} 


void ThirdScene::initLevel(){
	historyLevel = MyUserDefault->getIntegerForKey("HistoryGameLevel", 1);
}

void ThirdScene::writeLevel(int level){
	MyUserDefault->setIntegerForKey("GameLevel", level);
}
