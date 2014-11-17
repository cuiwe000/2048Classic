//
//  GameOverScene.cpp
//  PanBox
//
//  Created by adi on 14-9-3.
//
//

#include "GameOverScene.h"
#include "newGameScene.h"

#if UM_COCOS2DX_SOCIAL
#include "CCUMTypeDef.h"
#endif

#include "OpenUrl.h"

#define SCALE 2
bool GameOverScene::init(){
    if (!Layer::init()) {
        return false;
    }
//    
//    Color4B color = Color4B(254,236,198,255);
//    LayerColor *layerColor =LayerColor::create(color) ;
//    this->addChild(layerColor,-2);
//    
    auto restart = MenuItemImage::create("restart.png", "restart.png", CC_CALLBACK_0(GameOverScene::changeScen, this,100));///图片
    restart->setAnchorPoint(Vec2(0,0));
    restart->setScale(SCALE);
    restart->setPosition(40,20);
    
    auto fengxiang = MenuItemImage::create("fengxiang.png", "fengxiang.png", CC_CALLBACK_0(GameOverScene::changeScen, this,101));///图片
    fengxiang->setAnchorPoint(Vec2(0,0));
    fengxiang->setScale(SCALE);
    fengxiang->setPosition(320,restart->getPositionY());
    
    Menu *mu=Menu::create(restart,fengxiang, NULL);
    mu->setPosition(Point::ZERO);
    this->addChild(mu);
    return true;
}

void GameOverScene::setCutImage(RenderTexture *texture){
    Sprite * sprite = Sprite::createWithTexture(texture->getSprite()->getTexture());///背景图片
//    sprite->setAnchorPoint(Vec2(0,0));
    sprite->setPosition(DEVICE_WIDTH/2,DEVICE_HEIGHT/2);
    sprite->setFlippedY(true);

//    sprite->setScale(0.6);
    texture->saveToFile("cutImage.png", Image::Format::PNG);

    this->addChild(sprite,-1);
//    CC_SAFE_DELETE(texture);

}

void GameOverScene::changeScen(int style){
    if(style == 100){
        /**
         *  重新开始
         */
        Scene * scene = newGameScene::createScene((GameStyle)_GameStyle);
        TransitionCrossFade *reScene = TransitionCrossFade::create(0.3,scene);
        Director::getInstance()->replaceScene(reScene);
        
        OpenUrl::sharedOpenUrl()->showADWO(false);
    }
    else{
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
        
#if UMSOCIAL
        OpenUrl::sharedOpenUrl()->showSocial();
#endif
        
    }
}

/*
 * 分享回调, 该回调不是某个类的成员函数， 而是一个普通的函数, 具体使用参考HelloWorldScene的例子
 * @param platform 要分享到的目标平台
 * @param stCode 返回码, 200代表分享成功, 100代表开始分享
 * @param errorMsg 分享失败时的错误信息,android平台没有错误信息
 */
void shareCallbac(int platform, int stCode, std::string& errorMsg)
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