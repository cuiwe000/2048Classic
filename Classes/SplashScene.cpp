//
//  SplashScene.cpp
//  PanBox
//
//  Created by adi on 14-8-25.
//
//

#include "SplashScene.h"
USING_NS_CC;
Scene *SplashScene::creatScene(){
    auto sence = Scene::create();
    auto layer = SplashScene::create();
    sence->addChild(layer);
    return sence;
}

bool SplashScene::init(){
    if(!Layer::init())
    {
        return false;
    }

    Color4B color = Color4B(183,219,194,255);
    LayerColor *layerColor =LayerColor::create(color) ;
    this->addChild(layerColor);
        
    //显示游戏名称
    auto labelGame=Label::createWithBMFont("futura-48.fnt", "2048");
    labelGame->setPosition(Point(DEVICE_WIDTH/2,DEVICE_HEIGHT-100));
    this->addChild(labelGame);
    labelGame->setScale(1.5);

    auto jdMenuItem = MenuItemImage::create("jingdian.png","jingdian.png",
                                                            CC_CALLBACK_0(SplashScene::jumpToGame, this,DAT));
    jdMenuItem->setPosition(Point(DEVICE_WIDTH/2,DEVICE_HEIGHT-250));
    
    auto jdMenuItem2 = MenuItemImage::create("caodai.png","caodai.png",
                                            CC_CALLBACK_0(SplashScene::jumpToGame, this,HISTORY));
    jdMenuItem2->setPosition(Point(DEVICE_WIDTH/2,jdMenuItem->getPositionY()-250));
    
    auto jdMenuItem3 = MenuItemImage::create("setting.png","setting.png",
                                             CC_CALLBACK_0(SplashScene::showSetting, this));
    jdMenuItem3->setPosition(Point(DEVICE_WIDTH/2,jdMenuItem2->getPositionY()-200));
    
    mu = Menu::create(jdMenuItem,jdMenuItem2,jdMenuItem3,NULL);
    mu->setPosition(Point::ZERO);
    this->addChild(mu);
//    this->scheduleOnce(schedule_selector(SplashScene::jumpToGame), 1);

    return true;
}

void SplashScene::jumpToGame(GameStyle t){
    clog("jum= %d",t);
    Scene * newScene = newGameScene::createScene(t);
    auto transitions = TransitionMoveInR::create(0.2f, newScene);
    auto director = Director::getInstance();
    director->pushScene(transitions)   ;
}

void SplashScene::showSetting(){
    clog("showSetting");
//    mu->setEnabled(false);
//    this->setTouchEnabled(false);
    setLayer = SettingLayer::create();
    //    setLayer->
    this->addChild(setLayer);
}