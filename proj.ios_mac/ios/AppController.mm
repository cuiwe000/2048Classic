/****************************************************************************
 Copyright (c) 2010 cocos2d-x.org

 http://www.cocos2d-x.org

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#import "AppController.h"
#import "CCEAGLView.h"
#import "cocos2d.h"
#import "AppDelegate.h"
#import "RootViewController.h"

#include <string.h>


#if 1
#import "UMSocial.h"
//#import "UMSocialWechatHandler.h"
//#import "UMSocialQQHandler.h"
#endif

#if ADWO
#import "AdwoAdSDK.h"
ADWO_SDK_WITHOUT_PASSKIT_FRAMEWORK()
ADWO_SDK_WITHOUT_CORE_LOCATION_FRAMEWORK()
#endif

@interface AppController()<AWAdViewDelegate>
{
    //    unity3DGetAd *unityAd;
    
}
@end

@implementation AppController

#pragma mark -
#pragma mark Application lifecycle

// cocos2d application instance
static AppDelegate s_sharedApplication;

- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {    

    // Override point for customization after application launch.

    // Add the view controller's view to the window and display.
    window = [[UIWindow alloc] initWithFrame: [[UIScreen mainScreen] bounds]];

    // Init the CCEAGLView
    CCEAGLView *eaglView = [CCEAGLView viewWithFrame: [window bounds]
                                     pixelFormat: kEAGLColorFormatRGBA8
                                     depthFormat: GL_DEPTH24_STENCIL8_OES
                              preserveBackbuffer: NO
                                      sharegroup: nil
                                   multiSampling: NO
                                 numberOfSamples: 0];

    // Use RootViewController manage CCEAGLView 
    _viewController = [[RootViewController alloc] initWithNibName:nil bundle:nil];
    _viewController.wantsFullScreenLayout = YES;
    _viewController.view = eaglView;

#if ADWO
    // 创建广告banner
    std::string  kkkk = ADWO_PID;
    NSString *adwopid =[NSString stringWithCString: kkkk.c_str()   encoding:NSUTF8StringEncoding];
    _mAdView = AdwoAdCreateBanner(adwopid, YES, self);
    
    if(_mAdView == nil)
    {
        NSLog(@"Banner广告创建失败");
    }
    // 设置放置Banner的位置
    _mAdView.frame = CGRectMake(0, [[UIScreen mainScreen]bounds].size.height-50, 0.0f, 0.0f);
    
    // 将当前的广告Banner放到父视图上
    AdwoAdAddBannerToSuperView(_mAdView, eaglView);
    
    // 加载广告banner
    AdwoAdLoadBannerAd(_mAdView, ADWO_ADSDK_BANNER_SIZE_NORMAL_BANNER, NULL);
    
#endif
    
#if UM_COCOS2DX_SOCIAL
//    std::string  umappkey_s = UMAPPKEY;
//    NSString *umappkey =[NSString stringWithCString: umappkey_s.c_str()   encoding:NSUTF8StringEncoding];
//    [UMSocialData setAppKey:umappkey];
//    
////    std::string  wxappid_s = WEIXINAPPID;
////    NSString *wxappid =[NSString stringWithCString: wxappid_s.c_str()   encoding:NSUTF8StringEncoding];
////    std::string  wxappkey_s = WEIXINAPPKEY;
////    NSString *wxappkey =[NSString stringWithCString: wxappkey_s.c_str()   encoding:NSUTF8StringEncoding];
////    std::string  url_s = APPSTORE_ADDR;
////    NSString *url =[NSString stringWithCString: url_s.c_str()   encoding:NSUTF8StringEncoding];
////    [UMSocialWechatHandler setWXAppId:wxappid url:url];
//  
//    [UMSocialData openLog:YES];

#endif
    
#if UMSOCIAL
    [UMSocialData setAppKey:@UMAPPKEY];
    [UMSocialData openLog:YES];
    //如果你要支持不同的屏幕方向，需要这样设置，否则在iPhone只支持一个竖屏方向
    [UMSocialConfig setSupportedInterfaceOrientations:UIInterfaceOrientationMaskAll];
    
    //设置微信AppId，设置分享url，默认使用友盟的网址
    [UMSocialWechatHandler setWXAppId:@WEIXINAPPID appSecret:@WEIXINAPPKEY url:@APPSTORE_ADDR];
    [UMSocialQQHandler setQQWithAppId:@QQAPPID appKey:@QQAppKey url:@APPSTORE_ADDR];
    [UMSocialQQHandler setSupportWebView:YES];
#endif
    
    // Set RootViewController to window
    if ( [[UIDevice currentDevice].systemVersion floatValue] < 6.0)
    {
        // warning: addSubView doesn't work on iOS6
        [window addSubview: _viewController.view];
    }
    else
    {
        // use this method on ios6
        [window setRootViewController:_viewController];
    }

    [window makeKeyAndVisible];

    [[UIApplication sharedApplication] setStatusBarHidden:true];

    // IMPORTANT: Setting the GLView should be done after creating the RootViewController
    cocos2d::GLView *glview = cocos2d::GLView::createWithEAGLView(eaglView);
    cocos2d::Director::getInstance()->setOpenGLView(glview);

    cocos2d::Application::getInstance()->run();

    return YES;
}

- (void)applicationWillResignActive:(UIApplication *)application {
    /*
     Sent when the application is about to move from active to inactive state. This can occur for certain types of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the application and it begins the transition to the background state.
     Use this method to pause ongoing tasks, disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->pause(); */
}

- (void)applicationDidBecomeActive:(UIApplication *)application {
    /*
     Restart any tasks that were paused (or not yet started) while the application was inactive. If the application was previously in the background, optionally refresh the user interface.
     */
     //We don't need to call this method any more. It will interupt user defined game pause&resume logic
    /* cocos2d::Director::getInstance()->resume(); */
}

- (void)applicationDidEnterBackground:(UIApplication *)application {
    /*
     Use this method to release shared resources, save user data, invalidate timers, and store enough application state information to restore your application to its current state in case it is terminated later. 
     If your application supports background execution, called instead of applicationWillTerminate: when the user quits.
     */
    cocos2d::Application::getInstance()->applicationDidEnterBackground();
}

- (void)applicationWillEnterForeground:(UIApplication *)application {
    /*
     Called as part of  transition from the background to the inactive state: here you can undo many of the changes made on entering the background.
     */
    cocos2d::Application::getInstance()->applicationWillEnterForeground();
}

- (void)applicationWillTerminate:(UIApplication *)application {
    /*
     Called when the application is about to terminate.
     See also applicationDidEnterBackground:.
     */
}

#pragma mark - Adwo Ad Delegates
#if ADWO
// 此接口必须被实现，并且不能返回空！
- (UIViewController*)adwoGetBaseViewController
{
    return _viewController;
}
#if DEBUG
- (void)adwoAdViewDidFailToLoadAd:(UIView*)adview
{
    int errCode = AdwoAdGetLatestErrorCode();
    NSLog(@"广告请求失败，由于：%d", errCode);
}

- (void)adwoAdViewDidLoadAd:(UIView*)adview
{
    NSLog(@"广告已加载");
}
#endif
#endif

#pragma mark -
#pragma mark Memory management

- (BOOL)application:(UIApplication *)application openURL:(NSURL *)url sourceApplication:(NSString *)sourceApplication annotation:(id)annotation
{
#if 1
    return [UMSocialSnsService handleOpenURL:url];
#endif
}

- (void)applicationDidReceiveMemoryWarning:(UIApplication *)application {
    /*
     Free up as much memory as possible by purging cached data objects that can be recreated (or reloaded from disk) later.
     */
}


- (void)dealloc {
    [window release];
    [super dealloc];
}

-(void)showOCSocial{
//    NSLog(@"jjjjjjjjjjjj");
#if UMSOCIAL
    //注意：分享到微信好友、微信朋友圈、微信收藏、QQ空间、QQ好友、来往好友、来往朋友圈、易信好友、易信朋友圈、Facebook、Twitter、Instagram等平台需要参考各自的集成方法
    [UMSocialSnsService presentSnsIconSheetView:_viewController
                                         appKey:@UMAPPKEY
                                      shareText:[NSString stringWithFormat: @"  感谢您对鬼吹灯的支持,为了更好的为您服务,分享吧！AppStore地址:%@",@APPSTORE_ADDR]
                                     shareImage:[UIImage imageNamed:@"Icon-120.png"]
                                shareToSnsNames:[NSArray arrayWithObjects:UMShareToSina,UMShareToWechatTimeline,UMShareToWechatSession,UMShareToWechatFavorite,UMShareToRenren,UMShareToQzone,UMShareToQQ,UMShareToDouban,nil]
                                       delegate:nil];
#endif
}

@end

