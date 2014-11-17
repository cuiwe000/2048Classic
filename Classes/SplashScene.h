//
//  SplashScene.h
//  PanBox
//
//  Created by adi on 14-8-25.
//
//

#ifndef __PanBox__SplashScene__
#define __PanBox__SplashScene__

//#include "cocos2d.h"
#include "newGameScene.h"
#include "SettingLayer.h"

class SplashScene :public cocos2d::Layer{
private:
    void showSetting();
    
    SettingLayer *setLayer;
public:
    Menu* mu;
    
    virtual bool init();
    static cocos2d::Scene *creatScene();
    CREATE_FUNC(SplashScene);
    void jumpToGame(GameStyle t);
};


#endif /* defined(__PanBox__SplashScene__) */
