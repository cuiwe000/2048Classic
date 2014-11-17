//
//  numSprite.cpp
//  PanBox
//
//  Created by adi on 14-8-28.
//
//

#include "numSprite.h"
#include "GameDefine.h"
#include "newGameScene.h"

bool numSprite::init(){
    if (!Sprite::init()) {
        return false;
    }
    auto bk = LayerColor::create(Color4B::GREEN,SpriteWH,SpriteWH);
    bk->setTag(110);

    this->addChild(bk);
    
    int n= rand()%10;
    m_num = n>0?2:4;
    m_n = 0;
//    auto label;
//    auto label = Label::createWithTTF(StringUtils::format("%d",this->m_num), "雅痞-简", 40);
    auto label = Label::createWithTTF("", "YuppySC-Regular.otf", 40);

//    label->setScale(2);
//    label->setString(StringUtils::format("%d",this->m_num));
//    label->setColor(Color3B::RED);
    bk->addChild(label);
    label->setTag(10);
    clog("%f",getContentSize().width);
    label->setPosition(Point(bk->getContentSize().width/2,bk->getContentSize().height/2));
   
// 精灵慢慢变大
    ActionInterval*  actionTo = ScaleTo::create(0.0f, 0.2f);
    ActionInterval*  actionTo1 = ScaleTo::create(0.3f, 1.0f);
    //    ActionInterval*  actionTo2 = ScaleTo::create(0.2f, 1.0f);
    bk->runAction(Sequence::create(actionTo,actionTo1, NULL));
    
    return true;
}

void numSprite::moveTo(int r, int c){
    this->m_r = r;
    this->m_c = c;
    float XX = m_c*SpriteWH+SPACE*(m_c+1);
    float YY = m_r*SpriteWH+SPACE*(m_r+1);
    this->setPosition(XX, YY);
}

void numSprite::setPoint(float xx, float yy){
    this->m_r = xx;
    this->m_c = yy;
    float XX = m_c*SpriteWH+SPACE*(m_c+1);
    float YY = m_r*SpriteWH+SPACE*(m_r+1);
    this->setPosition(XX, YY);
}

void numSprite::doubleNumber(){
    m_num*=2;
    auto bk = this->getChildByTag(110);
//    Label *label = (Label *)bk->getChildByTag(10);
//    label->setString(StringUtils::format("%d",m_num));
    SpriteColor(m_num);

    ActionInterval*  actionTo = ScaleTo::create(0.1f, 1.2f);
    ActionInterval*  actionTo1 = ScaleTo::create(0.2f, 1.0f);
//    ActionInterval*  actionTo2 = ScaleTo::create(0.2f, 1.0f);
    bk->runAction(Sequence::create(actionTo,actionTo1, NULL));
    
    Label *scLabel= Label::createWithSystemFont(StringUtils::format("+%d",m_num), "宋体", 30);
    scLabel->setTag(111);
    scLabel->setOpacity(0);
    scLabel->setTextColor(Color4B::RED);
    this->addChild(scLabel);
    clog("%f,%f",scLabel->getPositionX(),scLabel->getPositionY());
//    scLabel->setPosition(this->getPosition());
    ActionInterval*  actionFadeTo = FadeTo::create(0.6, 255);
    ActionInterval*  actionMoveTo = MoveTo::create(1, Point(scLabel->getPositionX(),scLabel->getPositionY()+50));
    scLabel->runAction(Sequence::create(actionFadeTo, NULL));
    
    CallFunc *callFunc = CallFunc::create(CC_CALLBACK_0(numSprite::removeScore,this));
    scLabel->runAction(Sequence::create(actionMoveTo,callFunc, NULL));
    
    auto  ppp = (newGameScene *)this->getParent()->getParent();
    ppp->addScore(m_num);
}

void numSprite::removeScore(){
    this->removeChildByTag(111);
}

void numSprite::SpriteColor(int num){
    
    auto bk = this->getChildByTag(110);
    Label *label = (Label *)bk->getChildByTag(10);
    label->setTextColor(Color4B::WHITE);

    switch (m_num) {
        case 2:
            label->setTextColor(Color4B(65,63,66,255));
            if(gameStyle == HISTORY){
                label->setString("  夏\n商周");
                bk->setColor(Color3B(155,202,168));
            }
            else{
                bk->setColor(cocos2d::Color3B(240,230,220));
                
            }
            break;
        case 4:
            label->setTextColor(Color4B(65,63,66,255));
            if(gameStyle == HISTORY){
                label->setString("秦");
                bk->setColor(Color3B(222,162,33));
            }else{
                bk->setColor(cocos2d::Color3B(240,220,200));
                
            }
            break;
        case 8:
            if(gameStyle == HISTORY){
                label->setString("汉");
                bk->setColor(Color3B(119,170,52));
            }else{
                bk->setColor(cocos2d::Color3B(240,180,120));

            }
            break;
        case 16:
            if(gameStyle == HISTORY){
                label->setString("  魏晋\n南北朝");
                bk->setColor(Color3B(230,120,80));
            }
            else{
                bk->setColor(cocos2d::Color3B(240,140,90));
            }
            break;
        case 32:
            if(gameStyle == HISTORY){
                label->setString("隋");
                bk->setColor(Color3B(0,73,179));
            }else{
                bk->setColor(cocos2d::Color3B(240,120,90));

            }
            break;
        case 64:
            if(gameStyle == HISTORY){
                label->setString("唐");
                bk->setColor(Color3B(230,70,60));
            }
            else{
                bk->setColor(cocos2d::Color3B(240,90,60));
                
            }
            break;
        case 128:
            if(gameStyle == HISTORY){
                label->setString("宋");
                bk->setColor(Color3B(230,190,60));
            }else{
                bk->setColor(cocos2d::Color3B(240,90,60));
            }
            break;
        case 256:
            if(gameStyle == HISTORY){
                label->setString("元");
                bk->setColor(Color3B(250,190,70));
            }
            else{
                bk->setColor(cocos2d::Color3B(240,200,70));

            }
            break;
        case 512:
            if(gameStyle == HISTORY){
                label->setString("明");
                bk->setColor(Color3B(230,190,60));
            }
            else{
                bk->setColor(cocos2d::Color3B(240,200,80));

            }
            break;
        case 1024:
            if(gameStyle == HISTORY){
                label->setString("清");
                bk->setColor(Color3B(32,178,170));

            }
            else{
                bk->setColor(cocos2d::Color3B(0,130,0));
            }
            break;

        case 2048:
            if(gameStyle == HISTORY){
                bk->setColor(Color3B(210,180,30));
            }
            else{
                bk->setColor(cocos2d::Color3B(10,130,0));
            }
              break;
       default:
//            label->setScale(0.5);
            bk->setColor(Color3B(210,180,30));
            label->setColor(Color3B(255,255,255));
            if(gameStyle == HISTORY){
                label->setString("当代");
            }
            break;
    }
    
    if(gameStyle == DAT){
       label->setString(StringUtils::format("%d",m_num));
    }
}