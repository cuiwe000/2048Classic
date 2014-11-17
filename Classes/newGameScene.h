//
//  newGameScene.h
//  PanBox
//
//  Created by adi on 14-8-25.
//
//

#ifndef __PanBox__newGameScene__
#define __PanBox__newGameScene__

#include <iostream>
#include "cocos2d.h"
#include "GameDefine.h"
#include "numSprite.h"

#if UM_COCOS2DX_SOCIAL
// 引入相关的头文件
#include "CCUMSocialSDK.h"
#include "UMShareButton.h"
// 使用友盟命令空间
USING_NS_UM_SOCIAL;

#endif

#include "SettingLayer.h"

class newGameScene :public cocos2d::Layer{
private:
    LayerColor *layerbgColor;
    
    int map[G_R][G_C]; ///数据逻辑
    Vector<numSprite *>v_numSprite;
    
    bool m_startMove;///是否开启移动
    int m_x,m_y; ///touch坐标
    MOVE_DIR moveDir;///移动方向
    
    int g_score ;///最高分
    
    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();

    void newMoveSprite();////
    
    void backMenu();
    void showSetting();
    
    RenderTexture* cutScreen();
    
    void makeSound(bool mis);
    
    void SetLayerNotification(Ref* obj);
    
//    MenuItemImage *backMenu;

public:
    virtual bool init();

    static cocos2d::Scene *createScene(GameStyle gStyle);
    CREATE_FUNC(newGameScene);
    ~newGameScene();
    
    bool gameOver(); //true --game over false -- game continue
    
    void addScore(int score);
    
    GameStyle gameStyle;
    
    Label *scoreLabel;
    int Score;
//    void shareCallback(int platform, int stCode, std::string& errorMsg);
//    CC_SYNTHESIZE(SettingLayerDelegate*,_delegate,Delegate);//这一步不理解的看下面
    void removeADWO();
};

#endif /* defined(__PanBox__newGameScene__) */
