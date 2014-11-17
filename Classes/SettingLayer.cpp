//
//  SettingLayer.cpp
//  PanBox
//
//  Created by adi on 14-9-17.
//
//

#include "SettingLayer.h"
#include "GameDefine.h"

#include "SplashScene.h"

#include "OpenUrl.h"

#define SPACE_ 130

bool SettingLayer::init(){
    if (!Layer::init()) {
        return false;
    }
//    this->setVisible(true);
    this->initTouchEvent();
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("pic_cn-hd.plist","pic_cn-hd.pvr.ccz");
    backgroundMusic = UserDefault::getInstance()->getBoolForKey("backgroundMusic", true);
    musicEffect =  UserDefault::getInstance()->getBoolForKey("musicEffect", true);

    this->setContentSize(Size(320, 300));
    
    Color4B color = Color4B(254,236,198,0);
    layerColor =LayerColor::create(color,400,300) ;
    layerColor->setPosition(Vec2((DEVICE_WIDTH-400)/2, (DEVICE_HEIGHT-300)/2));
    layerColor->setScale(0.2);
    this->addChild(layerColor);

    Sprite * sprite = Sprite::create("wqAlertBg.png");///背景图片
    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setPosition(0,0);
    sprite->setScale(0.6);
    layerColor->addChild(sprite,0);
    
    Label *labeltitle = Label::createWithSystemFont("菜单设置", "YuppySC-Regular.otf", 30);
    labeltitle->setTextColor(Color4B::ORANGE);
    labeltitle->setPosition(190 , 240);
    layerColor->addChild(labeltitle);

    std::string str;
    if (backgroundMusic) {
        str ="button_musicon.png";
    }
    else{
        str ="button_musicoff.png";
    }
    Sprite * sprite2 = Sprite::createWithSpriteFrame(LoadSpriteFameByName(str));
    MenuItemSprite *menuSprite = MenuItemSprite::create(sprite2, sprite2,CC_CALLBACK_0(SettingLayer::doingSome, this,10001));
    menuSprite->setTag(10001);
    menuSprite->setPosition(60, 180);
    
    if (musicEffect) {
        str ="pl_lbtn_sound_on.png";
    }
    else{
        str ="pl_lbtn_sound_off.png";
    }
    Sprite * sprite3 = Sprite::createWithSpriteFrame(LoadSpriteFameByName(str));
    MenuItemSprite *menuSprite1 = MenuItemSprite::create(sprite3, sprite3,CC_CALLBACK_0(SettingLayer::doingSome, this,10002));
    menuSprite1->setPosition(menuSprite->getPositionX()+SPACE_, menuSprite->getPositionY());
    menuSprite1->setTag(10002);
  
    Sprite * commentImg = Sprite::createWithSpriteFrame(LoadSpriteFameByName("button_rate.png"));
    MenuItemSprite *commentSprite1 = MenuItemSprite::create(commentImg, commentImg,CC_CALLBACK_0(SettingLayer::doingSome, this,10003));
    commentSprite1->setPosition(menuSprite1->getPositionX()+SPACE_, menuSprite1->getPositionY());
    commentSprite1->setTag(10003);
    
    Sprite * helpImg = Sprite::createWithSpriteFrame(LoadSpriteFameByName("button_help.png"));
    MenuItemSprite *helpSprite1 = MenuItemSprite::create(helpImg, helpImg,CC_CALLBACK_0(SettingLayer::doingSome, this,10004));
    helpSprite1->setPosition(menuSprite->getPositionX(), 80);
    helpSprite1->setTag(10004);
    
    Sprite * shareImg = Sprite::createWithSpriteFrame(LoadSpriteFameByName("pl_lbtn_share.png"));
    MenuItemSprite *shareSprite1 = MenuItemSprite::create(shareImg, shareImg,CC_CALLBACK_0(SettingLayer::doingSome, this,10005));
    shareSprite1->setPosition(helpSprite1->getPositionX()+SPACE_, helpSprite1->getPositionY());
    shareSprite1->setTag(10005);

    MenuItemImage *menuImage = MenuItemImage::create("adsmogo_close.png","adsmogo_close.png",CC_CALLBACK_0(SettingLayer::dismisSettingLayer, this));
    menuImage->setPosition(350, 250);
    menuImage->setTag(10010);
    
    mu = Menu::create(menuSprite, menuSprite1,menuImage,commentSprite1,helpSprite1,shareSprite1,NULL);
    mu->setPosition(0, 0);
    layerColor->addChild(mu);
    
    ActionInterval*  actionTo = ScaleTo::create(0.0f, 0.2f);
    ActionInterval*  actionTo1 = ScaleTo::create(0.3f, 1.0f);
    //    ActionInterval*  actionTo2 = ScaleTo::create(0.2f, 1.0f);
    layerColor->runAction(Sequence::create(actionTo,actionTo1, NULL));
    return true;
}

void SettingLayer:: doingSome(int tag){
    MenuItemSprite *menuSprite = (MenuItemSprite*)mu->getChildByTag(tag);
    switch (tag) {
        case 10001:
        {
            backgroundMusic = !backgroundMusic;
            std::string str;
            if (backgroundMusic) {
                str ="button_musicon.png";
            }
            else{
                str ="button_musicoff.png";
            }
            Sprite * sprite1 = Sprite::createWithSpriteFrame(LoadSpriteFameByName(str));
            menuSprite->setNormalImage(sprite1);
            UserDefault::getInstance()->setBoolForKey("backgroundMusic", backgroundMusic);
            
            NotificationCenter::getInstance()->postNotification(SETTINGNotification, (Ref*)backgroundMusic);

        }
            break;
        case 10002:
        {
            musicEffect = !musicEffect;
            std::string str;
            if (musicEffect) {
                str ="pl_lbtn_sound_on.png";
            }
            else{
                str ="pl_lbtn_sound_off.png";
            }
            Sprite * sprite1 = Sprite::createWithSpriteFrame(LoadSpriteFameByName(str));
            menuSprite->setNormalImage(sprite1);
            UserDefault::getInstance()->setBoolForKey("musicEffect", musicEffect);
        }
            break;
        case 10003:
        {
            OpenUrl::sharedOpenUrl()->openUrlFunc(APPSTORE_ADDR);
            break;
        }
        case 10004:
        {
            OpenUrl::sharedOpenUrl()->openUrlFunc("http://blog.sina.com.cn/s/blog_bce003fd0102v3dy.html");
            break;
        }
        case 10005:{
#if UM_COCOS2DX_SOCIAL
            // 获取一个CCUMSocialSDK实例
            CCUMSocialSDK *sdk = CCUMSocialSDK::create(UMAPPKEY);
            // **********************   设置平台信息  ***************************
            sdk->setQQAppIdAndAppKey(QQAPPID, QQAppKey);
            sdk->setWechatAppId(WEIXINAPPID, WEIXINAPPKEY, APPSTORE_ADDR);
            sdk->setLogEnable(ISLOG) ;
            // **********************   END ***************************
            
            // 设置用户点击一条图文分享时用户跳转到的目标页面, 一般为app主页或者下载页面
            sdk->setTargetUrl(APPSTORE_ADDR);
            // 设置友盟分享面板上显示的平台
            vector<int>* platforms = new vector<int>();
            platforms->push_back(SINA);
            platforms->push_back(RENREN) ;
            platforms->push_back(DOUBAN) ;
            platforms->push_back(QZONE) ;
            platforms->push_back(QQ) ;
            platforms->push_back(WEIXIN) ;
            platforms->push_back(WEIXIN_CIRCLE) ;
            platforms->push_back(TENCENT_WEIBO) ;
            //        platforms->push_back(WEIXIN_CIRCLE) ;
            
            // 设置平台, 在调用分享、授权相关的函数前必须设置SDK支持的平台
            sdk->setPlatforms(platforms) ;
            
            // 打开分享面板, 注册分享回调, 参数1为分享面板上的平台, 参数2为要分享的文字内容，
            // 参数3为要分享的图片路径(android和IOS的图片地址格式不一致，因此分平台设置), 参数4为分享回调.
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
            sdk->openShare("要分享的文字内容", "/sdcard/image.png", share_selector(shareCallback));
#elif (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
            std::string documentPath = FileUtils::getInstance()->getWritablePath().c_str();
            std::string  fileName = "cutImage.png";
            std::string  filePath = documentPath + fileName;
            clog("---%s",filePath.c_str());
            sdk->openShare(UMSOCIAL_CONTENT,filePath.c_str(),NULL);
#endif
            
#endif

        }
            break;
        default:
            break;
    }
    UserDefault::getInstance()->flush();
}

void SettingLayer::dismisSettingLayer(){
//    ((SplashScene *)getParent())->mu->setEnabled(true);
//    this->removeFromParent();
//    this->setVisible(false);
//    this->setZOrder(-100);
    removeFromParentAndCleanup(true);
}

SettingLayer::~SettingLayer(){
    clog("~SettingLayer()");
//    layerColor->removeFromParent();
//    layerColor=nullptr;
}

void SettingLayer::initTouchEvent(){
    //
    auto m_pListener =   EventListenerTouchOneByOne::create();
    m_pListener->setSwallowTouches(true);
    m_pListener->onTouchBegan = [](Touch* touch, Event* event) {
        return true;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(m_pListener, this);
}