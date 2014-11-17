//
//  GameScene.cpp
//  PanBox
//
//  Created by adi on 14-7-31.
//
//

#include "GameScene.h"

USING_NS_CC;

Scene *GameScene::creatScene(){
    auto sence = Scene::create();
    auto layer = GameScene::create();
    sence->addChild(layer);
    return sence;
}

bool GameScene::init(){
    if ( !Layer::init() )
    {
        return false;
    }
    auto touchLister = EventListenerTouchOneByOne::create();
    touchLister->onTouchBegan =CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchLister->onTouchEnded =CC_CALLBACK_2(GameScene::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchLister,this);
    
    //加入游戏的背景颜色
    auto layerColorBG = cocos2d::LayerColor::create(cocos2d::Color4B(180,170,160,255));
    this->addChild(layerColorBG);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    //创建卡片
    createCardSprite(visibleSize);
    
//    //创建2张自动生成卡片
    autoCreateCardNumber();
    autoCreateCardNumber();
    //加入“分数”label
    auto labelTTFCardNumberName = LabelTTF::create("SCORE","HiraKakuProN-W6",80);
    labelTTFCardNumberName->setPosition(Point(visibleSize.width/3,visibleSize.height-40));
    addChild(labelTTFCardNumberName);
    
    //加入具体的分数
    labelTTFCardNumber = LabelTTF::create("0","HiraKakuProN-w6",80);
    labelTTFCardNumber->setPosition(Point(visibleSize.width-400,visibleSize.height-50));
    addChild(labelTTFCardNumber);
    
    return true;
}

bool GameScene::onTouchBegan(cocos2d::Touch *touch,cocos2d::Event *unused_event)
{
    log("ddddddd");
    Point touchPoint = touch->getLocation();
    touch->getLocationInView();
    firstX = touchPoint.x;
    firstY = touchPoint.y;
    return true;
}

void GameScene::onTouchEnded(cocos2d::Touch *touch,cocos2d::Event *unused_event){
     log("kkkkkkkkk");
    //获取X轴和Y轴的移动范围
    Point touchPoint=touch->getLocation(); //获取OpenGL坐标（即cocos2d-x坐标，原点在左下角）
    endX=firstX - touchPoint.x;
    endY=firstY - touchPoint.y;
    
    //判断X轴和Y轴的移动距离，如果X轴的绝对值大，则向左右滑动，如果Y轴的绝对值大，则向上下滑动
    if(abs(endX) > abs(endY))
    {
        //手势向左右
        //判断向左还是向右
        if(endX+5>0)
        {
            //向左
            doLeft();
            //判断游戏是否还能继续
            doCheckGameOver();
        }
        else
        {
            //向右
            doRight();
            //判断游戏是否还能继续
            doCheckGameOver();
        }
    }
    else
    {
        //手势向上下
        //判断手势向上还是向下
        if(endY+5>0)
        {
            //向下
            doDown();
            //判断游戏是否还能继续
            doCheckGameOver();
        }
        else
        {
            //向上
            doUp();
            //判断游戏是否还能继续
            doCheckGameOver();
        }
    }
}

bool GameScene::doUp(){
    log("doUp");
    bool isdo = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 3; y >= 0; y--) {
            
            for (int y1 = y - 1; y1 >= 0; y1--) {
                if (cardArr[x][y1]->getNumber() > 0) {
                    if (cardArr[x][y]->getNumber() <= 0) {
                        cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
                        cardArr[x][y1]->setNumber(0);
                        
                        y++;
                        isdo = true;
                    }else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()){
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        cardArr[x][y1]->setNumber(0);
                        
                        isdo = true;
                    }
                    break;
                }
            }
            
        }
    }
    return isdo;
}
bool GameScene::doDown(){
    log("doDown");
    bool isdo = false;
    for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            
            for (int y1 = y + 1; y1 < 4; y1++) {
                if (cardArr[x][y1]->getNumber() > 0) {
                    if (cardArr[x][y]->getNumber() <= 0) {
                        cardArr[x][y]->setNumber(cardArr[x][y1]->getNumber());
                        cardArr[x][y1]->setNumber(0);
                        
                        y--;
                        isdo = true;
                    }else if(cardArr[x][y]->getNumber() == cardArr[x][y1]->getNumber()){
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        cardArr[x][y1]->setNumber(0);
                        
                        isdo = true;
                    }
                    break;
                }
            }
            
        }
    }
    return isdo;
}
bool GameScene::doLeft(){
    log("doLeft");
    bool isdo = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            
            for (int x1 = x + 1; x1 < 4; x1++) {
                if (cardArr[x1][y]->getNumber() > 0) {
                    if (cardArr[x][y]->getNumber() <= 0) {
                        cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
                        cardArr[x1][y]->setNumber(0);
                        x--;
                        isdo = true;
                    }else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        cardArr[x1][y]->setNumber(0);
                        
                        isdo = true;
                    }
                    break;
                }
            }
            
        }
    }
    return isdo;
}
bool GameScene::doRight(){
    log("doRight");
    bool isdo = false;
    for (int y = 0; y < 4; y++) {
        for (int x = 3; x >= 0; x--) {
            
            for (int x1 = x - 1; x1 >= 0; x1--) {
                if (cardArr[x1][y]->getNumber() > 0) {
                    if (cardArr[x][y]->getNumber() <= 0) {
                        cardArr[x][y]->setNumber(cardArr[x1][y]->getNumber());
                        cardArr[x1][y]->setNumber(0);
                        
                        x++;
                        isdo = true;
                    }else if(cardArr[x][y]->getNumber() == cardArr[x1][y]->getNumber()){
                        cardArr[x][y]->setNumber(cardArr[x][y]->getNumber()*2);
                        cardArr[x1][y]->setNumber(0);
                        
                        isdo = true;
                    }
                    break;
                }
            }
            
        }
    }
    return isdo;
}

//创建卡片
void GameScene::createCardSprite(cocos2d::Size size)
{
    //求出单元格的宽度和高度
    int unitSize = (size.width-28)/4;
    
    //4*4的单元格
    for(int i=0; i<4; i++)
    {
        for(int j=0; j<4; j++)
        {
            CardSprite* card = CardSprite::createCardSprite(0, unitSize, unitSize, unitSize*i+0, unitSize*j+20);
            addChild(card);
            //把卡片加入到数组中
            cardArr[i][j] = card;
        }
    }
}
//自动生成卡片
void GameScene::autoCreateCardNumber()
{
    int i = CCRANDOM_0_1()*4;
    int j = CCRANDOM_0_1()*4;
    
    //判断是否这个位置已存在卡片
    if(cardArr[i][j]->getNumber() > 0)
    {
        autoCreateCardNumber();
    }
    else
    {
        cardArr[i][j]->setNumber(CCRANDOM_0_1()*10 < 1 ? 2: 4);
    }
}

//判断游戏是否还能继续
void GameScene::doCheckGameOver(){
    bool isGameOver = true;
    
    for (int y = 0; y < 4; y++) {
        for (int x = 0; x < 4; x++) {
            if (cardArr[x][y]->getNumber() == 0||
                (x>0&&(cardArr[x][y]->getNumber() == cardArr[x-1][y]->getNumber()))||
                (x<3&&(cardArr[x][y]->getNumber() == cardArr[x+1][y]->getNumber()))||
                (y>0&&(cardArr[x][y]->getNumber() == cardArr[x][y-1]->getNumber()))||
                (y<3&&(cardArr[x][y]->getNumber() == cardArr[x][y+1]->getNumber()))) {
                isGameOver = false;
            }
        }
    }
    
    if (isGameOver) {
        //游戏结束，重新开始游戏
        log("游戏结束");
        Director::getInstance()->replaceScene(TransitionFade::create(1, GameScene::creatScene()));
    }
    else{
        autoCreateCardNumber();
    }
}

