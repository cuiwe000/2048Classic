//
//  GameScene.h
//  PanBox
//
//  Created by adi on 14-7-31.
//
//

#ifndef __PanBox__GameScene__
#define __PanBox__GameScene__

#include "cocos2d.h"
#include "CardSprite.h"

class GameScene :public cocos2d::Layer{
public:
    static cocos2d::Scene* creatScene();
    
    virtual bool init();
    
//    void menuCloseCallback(cocos2d::Ref* pSender);

    CREATE_FUNC(GameScene);
    
    virtual bool onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event);
    virtual void onTouchEnded(cocos2d::Touch *touch,cocos2d::Event *unused_event);
    
    bool doUp();
    bool doDown();
    bool doLeft();
    bool doRight();
    
    //创建卡片
    void createCardSprite(cocos2d::Size size);
    //自动生成卡片
    void autoCreateCardNumber();
    //判断游戏是否还能继续
    void doCheckGameOver();
private:
    //点击元素
    int firstX,firstY,endX,endY;
    
    //创建一个卡片二位数组
    CardSprite* cardArr[4][4];
    //游戏总分
    int score;
    
    //定义显示分数的控件
    cocos2d::LabelTTF* labelTTFCardNumber;
};
#endif /* defined(__PanBox__GameScene__) */
