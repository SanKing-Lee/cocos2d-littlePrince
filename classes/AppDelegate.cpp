#include "AppDelegate.h"
#include "GameScene.h"
#include "LoadingScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("Star Risk");
        director->setOpenGLView(glview);
    }

	//glview设置设备尺寸和屏幕拉升解决策略--适应宽度
	glview->setFrameSize(480,640);
	glview->setDesignResolutionSize(480,640,ResolutionPolicy::FIXED_WIDTH);

	//FileUtils添加查找资源树
	cocos2d::FileUtils::getInstance()->addSearchPath("ui");
	cocos2d::FileUtils::getInstance()->addSearchPath("font");
	cocos2d::FileUtils::getInstance()->addSearchPath("sound");
	cocos2d::FileUtils::getInstance()->addSearchPath("ShopScene");
	cocos2d::FileUtils::getInstance()->addSearchPath("background");
	cocos2d::FileUtils::getInstance()->addSearchPath("bullet");
	cocos2d::FileUtils::getInstance()->addSearchPath("button");
	cocos2d::FileUtils::getInstance()->addSearchPath("heroAndEnemy");
	cocos2d::FileUtils::getInstance()->addSearchPath("Loading");
	cocos2d::FileUtils::getInstance()->addSearchPath("tool");
	cocos2d::FileUtils::getInstance()->addSearchPath("Music");

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = LoadingScene::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
