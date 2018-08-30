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
	Size visibleSize = Director::getInstance()->getVisibleSize();//���Ӵ��ڵĴ�С
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("LevelChoseScene.plist");


	auto bg = Sprite::createWithSpriteFrameName("level_backgroud.png");//("thirdscene.png");//����������ı���ͼ
	bg->setAnchorPoint(Point::ANCHOR_MIDDLE_TOP);		
	bg->setPosition(visibleSize.width/2, visibleSize.height);//�������ñ����Զ������������Ļ
	this->addChild(bg, -1);//����-1��

	auto star1 = Sprite::createWithSpriteFrameName("planet1_1.png");//("star1.png");//����1��ͼƬ
	star1->setPosition(Point(visibleSize.width/4,visibleSize.height/4));
	this->addChild(star1,3);
	auto star2_n = Sprite::createWithSpriteFrameName("planet2_gray.png");//("star2_n.png");//����2��ͼƬ
	star2_n->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
	this->addChild(star2_n,3);//��ͼ��3
	auto star3_n = Sprite::createWithSpriteFrameName("planet3_gray.png");//("star3_n.png");//����3��ͼƬ
	star3_n->setPosition(Point(visibleSize.width-visibleSize.width/4,visibleSize.height-visibleSize.height/4));
	this->addChild(star3_n,3);//��ͼ��3
		

	auto name1 = Sprite::createWithSpriteFrameName("planet1_name.png");//("title.png");//�ؿ���ͼƬ
	name1->setPosition(Point(visibleSize.width/4,visibleSize.height/4 - visibleSize.height/10));
	this->addChild(name1,3);

	auto name2 = Sprite::createWithSpriteFrameName("planet2_name.png");//("title.png");//�ؿ���ͼƬ
	name2->setPosition(Point(visibleSize.width/2,visibleSize.height/2 - visibleSize.height/10));
	this->addChild(name2,3);

	auto name3 = Sprite::createWithSpriteFrameName("planet3_name.png");//("title.png");//�ؿ���ͼƬ
	name3->setPosition(Point(visibleSize.width-visibleSize.width/4,visibleSize.height-visibleSize.height/4 - visibleSize.height/10));
	this->addChild(name3,3);
		
	auto menu_xzx = Menu::create();
	menu_xzx->setPosition(Point::ZERO);


	//���ذ��ؽ��桢��������������������������������������������������������������������������������������������������������������
	auto back = Sprite::create("back2.png");//WithSpriteFrameName
	auto toSec = MenuItemSprite::create(back, back, [=](Ref *){
	auto scene = GameBegin::createScene();//GameScene1::createScene();
	Director::getInstance()->replaceScene(scene);			
	});
	toSec->setPosition(Point(visibleSize.width/6,visibleSize.height-visibleSize.height/14));
	menu_xzx->addChild(toSec);//������Ϸ1�İ�ť��ӵ�menuxzx	
	//,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,,


	//blingbling�ı���
	auto animation = Animation::create();
	auto star = Sprite::createWithSpriteFrameName("blingbling1.png");//("star1.png");
		//star->setAnchorPoint();//����starê��
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


	//�������ļ��ж�ȡͨ����������û���򷵻�Ĭ��ֵ0
	initLevel();
		
	if((historyLevel == 1)||(historyLevel == 2)||(historyLevel == 3))//ֱ����ת����һ�ص���Ϸ������
	{	
		auto star1_y = Sprite::createWithSpriteFrameName("planet1_1.png");//WithSpriteFrameName
		auto toStar1 = MenuItemSprite::create(star1_y, star1_y, [=](Ref *){
			writeLevel(1);
			auto scene = GameScene::createScene();//GameScene1::createScene();
			Director::getInstance()->replaceScene(scene);			
		});
		toStar1->setPosition(Point(visibleSize.width/4,visibleSize.height/4));
		menu_xzx->addChild(toStar1);//������Ϸ1�İ�ť��ӵ�menuxzx	

		//ת��������1
		animation = Animation::create();
		auto rool_1 = Sprite::createWithSpriteFrameName("planet1_1.png");//("star1.png");
			//star->setAnchorPoint();//����starê��
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
				
	if((historyLevel == 2)||(historyLevel == 3)){//ͨ����һ�أ��ڶ����������ͼ�㸲�ǵڶ��������ɫͼ�㲢����ת���ڶ�����Ϸ������
		auto star2_y = Sprite::createWithSpriteFrameName("planet2_1.png");//("star2_y.png");//����2������ͼƬWithSpriteFrameName
		auto toStar2 = MenuItemSprite::create(star2_y, star2_y, [=](Ref *){
				writeLevel(2);
			auto scene = GameScene::createScene();//GameScene2::createScene();
			Director::getInstance()->replaceScene(scene);			
		});
		toStar2->setPosition(Point(visibleSize.width/2,visibleSize.height/2));			
		menu_xzx->addChild(toStar2);//������Ϸ2�İ�ť��ӵ�menuxzx	

			//ת��������2
		animation = Animation::create();
		auto rool_2 = Sprite::createWithSpriteFrameName("planet2_1.png");//("star1.png");
			//star->setAnchorPoint();//����starê��
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
	
	if((historyLevel == 3)){//ͨ���ڶ��أ��������������ͼ�㸲�ǵ����������ɫͼ�㲢����ת����������Ϸ������

		auto star3_y = Sprite::createWithSpriteFrameName("planet3_1.png");//("star3_y.png");//����3������ͼƬ->ͨ��������WithSpriteFrameName
		auto toStar3 = MenuItemSprite::create(star3_y, star3_y, [=](Ref *){
			writeLevel(3);
			auto scene = GameScene::createScene();//GameScene3::createScene();
			Director::getInstance()->replaceScene(scene);			
		});
		toStar3->setPosition(Point(visibleSize.width-visibleSize.width/4,visibleSize.height-visibleSize.height/4));		
		menu_xzx->addChild(toStar3);//������Ϸ3�İ�ť��ӵ�menuxzx	

			
		//ת��������3
		animation = Animation::create();
		auto rool_3 = Sprite::createWithSpriteFrameName("planet3_1.png");//("star1.png");
			//star->setAnchorPoint();//����starê��
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
	this->addChild(menu_xzx,4);	//,4��menu_xzx���ڵ�����
	return true;
} 


void ThirdScene::initLevel(){
	historyLevel = MyUserDefault->getIntegerForKey("HistoryGameLevel", 1);
}

void ThirdScene::writeLevel(int level){
	MyUserDefault->setIntegerForKey("GameLevel", level);
}
