//
//  newGameScene.cpp
//  PanBox
//
//  Created by adi on 14-8-25.
//
//

#include "newGameScene.h"
#include "SimpleAudioEngine.h"
#include "GameOverScene.h"

//Inheritance diagram for ControlButton:

//#include <time.h>
#include <stdlib.h>

//#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
////#include "AppController.h"
//#endif

#include "OpenUrl.h"

USING_NS_CC;
using namespace CocosDenshion;

Scene* newGameScene::createScene(GameStyle gStyle){
    auto sence = Scene::create();
    auto layer = newGameScene::create();
    layer->gameStyle = gStyle;
    
    layer->newMoveSprite();
    layer-> newMoveSprite();

    sence->addChild(layer);
    return sence;
}

bool newGameScene::init(){
//    CC_BREAK_IF(!LayerColor::(ccc4(255, 255, 255, 255)));

    if(!Layer::init())
    {
        return false;
    }
    
    Color4B color = Color4B(254,236,198,255);
    LayerColor *layerColor =LayerColor::create(color) ;
    this->addChild(layerColor);
    
//    Color4B color2 = Color4B(254,236,198,255);
    LayerColor *layerColor2 =LayerColor::create(Color4B::ORANGE, DEVICE_WIDTH,100) ;
    layerColor2->setPosition(0,DEVICE_HEIGHT - 150);
    this->addChild(layerColor2);
    
    Score = 0;
    scoreLabel = Label::createWithSystemFont(StringUtils::format("%d",Score), "宋体", 40);
    scoreLabel->setPosition(Point(layerColor2->getContentSize().width/2,layerColor2->getContentSize().height/2+5));
    layerColor2->addChild(scoreLabel);

    layerbgColor = LayerColor::create(Color4B::GRAY, layerBg,layerBg);
//    layerbgColor->setAnchorPoint(Vec2(0.5, 0.5));
    clog("%d,%f",layerBg,DEVICE_WIDTH);
    layerbgColor->setPosition(Vec2((DEVICE_WIDTH-layerBg)/2, (DEVICE_HEIGHT-layerBg)/2));
    this->addChild(layerbgColor);
    
    for (int i=0; i<G_R; i++) {
        for (int j= 0; j<G_C; j++) {
            LayerColor *lay = LayerColor::create(Color4B(200,190,180,255), SpriteWH, SpriteWH);
            lay->setPosition(SPACE+j*(SpriteWH+SPACE), SPACE+i*(SpriteWH+SPACE));
            layerbgColor->addChild(lay);
            map[i][j]=0;
        }
    }
    
//    setTouchEnabled(true);//开启事件侦听
    this->setSwallowsTouches(false);

    /**
     *  开启事件监听
     */
    auto listener = EventListenerTouchOneByOne::create();
    listener ->setSwallowTouches(false);
//    _eventDispatcher->addTargetedDelegate(this, 0, true)
    /**
     *   '&' ????
     */
    listener->onTouchBegan=[&](Touch *touch, Event* event){
        clog("");
        m_x = touch->getLocation().x;
        m_y = touch->getLocation().y;
        m_startMove = false;
        return true;
    };
    
    listener->onTouchMoved = [&](Touch *touch,Event *event){
        m_startMove = true;

    };
    
    listener->onTouchEnded = [&](Touch *touch, Event* event){
        clog("");
        Point touchEndPoint = touch->getLocation();
        int endx = m_x- touchEndPoint.x;
        int endy = m_y- touchEndPoint.y;
        
        if (m_startMove) {
            if (abs(endx)>abs(endy)) {
                if (endx+15>0) {
                    moveLeft();
//                    moveDir = moveDir::
                }
                else{
                    moveRight();
                }
            }
            else{
                if (endy+15>0) {
                    moveDown();

                }
                else{
                    moveUp();
                }
            }
            newMoveSprite();
        }
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    MenuItemImage *backMenu = MenuItemImage::create("UMS_nav_button_back.png", "UMS_nav_button_back.png",CC_CALLBACK_0(newGameScene::backMenu,this));
    backMenu->setPosition(50, layerColor2->getContentSize().height/2);
    
    MenuItemImage *setMenu = MenuItemImage::create("shezhi.png", "shezhi.png",CC_CALLBACK_0(newGameScene::showSetting,this));
    setMenu->setPosition(layerColor2->getContentSize().width-50, layerColor2->getContentSize().height/2);

    Menu *mune = Menu::create(backMenu,setMenu,NULL);
    mune->setPosition(Point::ZERO);

    layerColor2->addChild(mune);
    
    g_score = UserDefault::getInstance()->getIntegerForKey("SCORE", 0);

//    __String *ss = __String::createWithFormat("最高分:%s",g.c_str());
    Label *label = Label::createWithSystemFont(StringUtils::format("最高分:%d",g_score), "YuppySC-Regular.otf", 30);
    label->setTag(111111);
    label->setAnchorPoint(Vec2(0, 0));
    label->setPosition(Vec2(0, DEVICE_HEIGHT-60));
    label->setWidth(DEVICE_WIDTH);
    label->setTextColor(Color4B::BLACK);
    label->setAlignment(TextHAlignment::RIGHT);
    this->addChild(label);
//
    bool backgroundMusic = UserDefault::getInstance()->getBoolForKey("backgroundMusic", true);
    SimpleAudioEngine::getInstance()->preloadBackgroundMusic("music_bk3.mp3");
    if (backgroundMusic) {
        SimpleAudioEngine::getInstance()->playBackgroundMusic("music_bk3.mp3",true);
    }
    
    NotificationCenter::getInstance()->addObserver(this, callfuncO_selector(newGameScene::SetLayerNotification), SETTINGNotification, NULL);
    return true;
}

void newGameScene::SetLayerNotification(Ref* obj)
{
    clog("Notification achieved. ID:%d",(bool)obj);
    if(obj){
        SimpleAudioEngine::getInstance()->playBackgroundMusic("music_bk3.mp3",true);

//        SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    }else{
        SimpleAudioEngine::getInstance()->stopBackgroundMusic();
    }
}

void newGameScene::backMenu(){
    clog("dddddddddddddddd");
//    TransitionMoveInL* transitions = TransitionMoveInL::create(0.2f, getScene());
    Director::getInstance()->popSceneWithTransition<TransitionMoveInL>(0.3);
}

#if 0
/*
 * 分享回调, 该回调不是某个类的成员函数， 而是一个普通的函数, 具体使用参考HelloWorldScene的例子
 * @param platform 要分享到的目标平台
 * @param stCode 返回码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 分享失败时的错误信息,android平台没有错误信息
 */
void newGameScene::shareCallback(int platform, int stCode, std::string& errorMsg)
{
    if ( stCode == 100 )
    {
        clog("#### HelloWorld 开始分享");
    }
    else if ( stCode == 200 )
    {
        clog("#### HelloWorld 分享成功");
    }
    else
    {
        clog("#### HelloWorld 分享出错");
    }
    
    clog("platform num is : %d.", platform);
}
#endif

void newGameScene::moveUp(){
    clog("");
//    MoveTo
    bool moveDismis = false;
    for (int c=0; c<G_C; c++) {
        for (int r =G_R-1; r>=0; r--) {
            if (map[r][c]>0) {
                for (int row1=r; row1<G_R-1; row1++) {
                    if (map[row1+1][c]==0) {
                        //
                        map[row1+1][c] =map[row1][c];
                        map[row1][c] =0;
                        v_numSprite.at(map[row1+1][c]-1)->moveTo(row1+1, c);
                    }
                    else{
                        //xiaochu
                        int numObj = v_numSprite.at(map[row1+1][c]-1)->m_num;
                        int numNew = v_numSprite.at(map[row1][c]-1)->m_num;
                        if (numNew == numObj) {
                            v_numSprite.at(map[row1+1][c]-1)->doubleNumber();
                            v_numSprite.at(map[row1][c]-1)->removeFromParent();
                            
                            int index = map[row1][c];
                            v_numSprite.erase(index-1);
                            for (int rr =0; rr<G_R; rr++) {
                                for (int cc=0; cc<G_C; cc++) {
                                    if (map[rr][cc]>index) {
                                        map[rr][cc]--;
                                    }
                                }
                            }
                            map[row1][c] = 0;
                            moveDismis = true;
                        }
                        break;
                    }
                    
                }
            }
        }
    }
    
    makeSound(moveDismis);

}
void newGameScene::moveDown(){
    clog("");
    bool moveDismis = false;
    
    for (int c=0; c<G_C; c++) {
        for (int r =0; r<G_R; r++) {
            if (map[r][c]>0) {
                for (int row1=r; row1>0; row1--) {
                    if (map[row1-1][c]==0) {
                        //
                        map[row1-1][c] =map[row1][c];
                        map[row1][c] =0;
                        v_numSprite.at(map[row1-1][c]-1)->moveTo(row1-1, c);
                    }
                    else{
                        //xiaochu
                        int numObj = v_numSprite.at(map[row1-1][c]-1)->m_num;
                        int numNew = v_numSprite.at(map[row1][c]-1)->m_num;
                        if (numNew == numObj) {
                            v_numSprite.at(map[row1-1][c]-1)->doubleNumber();
                            v_numSprite.at(map[row1][c]-1)->removeFromParent();
                            int index = map[row1][c];
                            v_numSprite.erase(index-1);
                            for (int rr =0; rr<G_R; rr++) {
                                for (int cc=0; cc<G_C; cc++) {
                                    if (map[rr][cc]>index) {
                                        map[rr][cc]--;
                                    }
                                }
                            }
                            map[row1][c] = 0;
                            moveDismis = true;
                        }
                        break;
                    }
                }
            }
        }
    }
    makeSound(moveDismis);

}
void newGameScene::moveLeft(){
    clog("");
    bool moveDismis = false;
    for (int r =0; r<G_R; r++) {
        for (int c=0; c<G_C; c++) {
            if (map[r][c]>0) {
                for (int col1=c; col1>0; col1--) {
                    if (map[r][col1-1]==0) {
                        //
                        map[r][col1-1] =map[r][col1];
                        map[r][col1] =0;
                        v_numSprite.at(map[r][col1-1]-1)->moveTo(r, col1-1);
                    }
                    else{
                        //xiaochu
                        int numObj = v_numSprite.at(map[r][col1-1]-1)->m_num;
                        int numNew = v_numSprite.at(map[r][col1]-1)->m_num;
                        if (numNew == numObj) {
                            v_numSprite.at(map[r][col1-1]-1)->doubleNumber();
                            v_numSprite.at(map[r][col1]-1)->removeFromParent();
                            int index = map[r][col1];
                            v_numSprite.erase(index-1);
                            for (int rr =0; rr<G_R; rr++) {
                                for (int cc=0; cc<G_C; cc++) {
                                    if (map[rr][cc]>index) {
                                        map[rr][cc]--;
                                    }
                                }
                            }
                            map[r][col1] = 0;
                            moveDismis = true;
                        }
                        break;
                    }
                }
            }
        }
    }
    makeSound(moveDismis);
}
void newGameScene::moveRight(){
    clog("");
    bool moveDismis = false;
    for (int r =0; r<G_R; r++) {
        for (int c=G_C-1; c>=0; c--) {
            if (map[r][c]>0) {
                for (int col1=c; col1<G_C-1; col1++) {
                    if (map[r][col1+1]==0) {
                        //
                        map[r][col1+1] =map[r][col1];
                        map[r][col1] =0;
                        v_numSprite.at(map[r][col1+1]-1)->moveTo(r, col1+1);
                    }
                    else{
                        //xiaochu
                        int numObj = v_numSprite.at(map[r][col1+1]-1)->m_num;
                        int numNew = v_numSprite.at(map[r][col1]-1)->m_num;
                        if (numNew == numObj) {
                            v_numSprite.at(map[r][col1+1]-1)->doubleNumber();
                            v_numSprite.at(map[r][col1]-1)->removeFromParent();
                            int index = map[r][col1];
                            v_numSprite.erase(index-1);
                            for (int rr =0; rr<G_R; rr++) {
                                for (int cc=0; cc<G_C; cc++) {
                                    if (map[rr][cc]>index) {
                                        map[rr][cc]--;
                                    }
                                }
                            }
                            map[r][col1] = 0;
                            moveDismis = true;
                        }
                        break;
                    }
                }
            }
        }
    }
    
    makeSound(moveDismis);
}

void newGameScene::newMoveSprite(){
    
    int lose =16-v_numSprite.size();
    clog("lose=%d",lose);
    if(lose == 0){
        // game over
        
        return;
    };
    
    int rand_num = arc4random()%lose;
    clog("rand_num=%d",rand_num);

    int index=0;
    bool find = false;
    int l_r,l_c;
    for (int row=0; row<G_R; row++) {
        for (int col=0; col<G_C; col++) {
            if (map[row][col]==0) {
                if (index==rand_num) {
                    l_r= row;
                    l_c = col;
                    find= true;
                    break;
                }
                index++;
            }
        }
        if (find) {
            break;
        }
    }
    clog("%d,%d",l_r,l_c);

    auto numsprite = numSprite::create();
    numsprite->gameStyle = gameStyle;
    numsprite->SpriteColor(numsprite->m_num);
    layerbgColor->addChild(numsprite);
    numsprite->setPoint(l_r, l_c);
    v_numSprite.pushBack(numsprite);
    map[l_r][l_c]=v_numSprite.getIndex(numsprite)+1;///!!!!
   
    if (v_numSprite.size() == G_R*G_C) {
      bool gameOver1 = gameOver();
        if(gameOver1){
            
        }
    }
}

bool newGameScene::gameOver(){
    for (int row =0 ; row<G_R; row++) {
        for (int col = 0; col<G_C; col++) {
            int numObj = v_numSprite.at(map[row][col]-1)->m_num;
            
            clog("row = %d,col= %d,numObj = %d",row,col,numObj);
//            clog("-----%d，%d",map[row][col]-1,numObj);
            if (col ==G_C-1 && row == G_R-1) {
                clog("do nothing");
            }
            else if(col == G_C-1){
                int numRow_1 = v_numSprite.at(map[row+1][col]-1)->m_num;
                if (numObj == numRow_1) {
                    clog("game continue");
                    return false;
                }
            }
            else if(row == G_R-1){
                int numCol_1 = v_numSprite.at(map[row][col+1]-1)->m_num;
                if (numObj == numCol_1) {
                    clog("game continue");
                    return false;
                }
            }
            else{
                int numRow_1 = v_numSprite.at(map[row][col+1]-1)->m_num;
                int numCol_1 = v_numSprite.at(map[row+1][col]-1)->m_num;
                if (numObj == numRow_1 || numObj == numCol_1) {
                    clog("game continue");
//                    return false;
                }
            }
        }
    }
    clog("game over");
    
    OpenUrl::sharedOpenUrl()->showADWO(true);
    
    RenderTexture *texture = cutScreen();
    auto sence = Scene::create();
    auto layer = GameOverScene::create();
    layer->setCutImage(texture);
    layer->_GameStyle = gameStyle;
    sence->addChild(layer);
    
    TransitionCrossFade *reScene = TransitionCrossFade::create(0.3,sence);
    Director::getInstance()->replaceScene(reScene);

    return true;
}

void newGameScene::addScore(int score){
    clog("%s","addscore");
    Score+=score;
    if (Score > g_score) {
        g_score=Score;
        Label *la = (Label*)this->getChildByTag(111111);
        la->setString( StringUtils::format("最高分:%d",g_score));
        UserDefault::getInstance()->setIntegerForKey("SCORE", g_score);

    }
    scoreLabel->setString(StringUtils::format("%d",Score));

}

void newGameScene::showSetting(){
    
  SettingLayer*  setLayer = SettingLayer::create();
//    this->setDelegate(setLayer);
//    this->setDelegator(setLayer);
    this->addChild(setLayer);
}

//截图
RenderTexture* newGameScene::cutScreen(){
    Size size = Director::getInstance()->getWinSize();
    //定义一个屏幕大小的渲染纹理
    RenderTexture* pScreen = RenderTexture::create(size.width,size.height);
    //获得当前的场景指针
    Scene* pCurScene = Director::getInstance()->getRunningScene();
    //渲染纹理开始捕捉
    pScreen->begin();
    //当前场景参与绘制
    pCurScene->visit();
    //结束捕捉
    pScreen->end();
    //保存为png(经过裁切的)
//    pScreen->saveToFile("Print.png", Image::Format::PNG);
   return  pScreen;
//    //得到该渲染纹理，将该纹理转为精灵经过裁切显示出来
//    CCSprite* pTempImage = CCSprite::spriteWithTexture(
//                                                       (pScreen->getSprite())->getTexture(),
//                                                       m_kRect );
//    pTempImage->setPosition(ccp(0,0));
//    //Y翻转  
//    pTempImage->setFlipY(true);  
//    addChild(pTempImage,1);  
//    //结束且释放  
//    CC_SAFE_DELETE(pScreen);
}

void newGameScene::makeSound(bool mis){
  bool  musicEffect =  UserDefault::getInstance()->getBoolForKey("musicEffect", true);
    if (musicEffect) {
        
        if (mis) {
            SimpleAudioEngine::getInstance()->playEffect("merge.wav");
        }
        else{
            SimpleAudioEngine::getInstance()->playEffect("move.wav");
        }
    }
}
void newGameScene::removeADWO(){
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    //iOS代码
//    [HSpriteOC testLog];
//    [HSpriteOC testLogWithStr:@"wahaha"];
//    [HSpriteOC hMessageBox:@"cocos2dx调用oc函数" title:@"Himi"];
#else
    //Android代码
#endif
    
}
newGameScene::~newGameScene()
{
    clog("~~~~~~~~~~");
    SimpleAudioEngine::getInstance()->end();
    NotificationCenter::getInstance()->removeObserver(this, SETTINGNotification);
    //    CCNotificationCenter::sharedNotificationCenter()->removeAllObservers(this);
}