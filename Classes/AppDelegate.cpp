#include "AppDelegate.h"
//#include "HelloWorldScene.h"
//#include "GameScene.h"

#if UMANALISIS
#include "MobClickCpp.h"
#endif

#include "SplashScene.h"
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
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }
#if DEBUG
    // turn on display FPS
    director->setDisplayStats(true);
#endif
    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = SplashScene::creatScene();

    // run
    director->runWithScene(scene);
    
//    MOBCLICKCPP_START_WITH_APPKEY_AND_CHANNEL(UMAPPKEY, "123456");
#if UMANALISIS

    MOBCLICKCPP_START_WITH_APPKEY(UMAPPKEY);
    umeng::MobClickCpp::setLogEnabled(ISLOG);
#endif
    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
#if UMANALISIS

    umeng::MobClickCpp::applicationDidEnterBackground();
#endif
    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
#if UMANALISIS

    umeng::MobClickCpp::applicationWillEnterForeground();
#endif
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
