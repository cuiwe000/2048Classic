#import <UIKit/UIKit.h>

@class RootViewController;

@interface AppController : NSObject <UIApplicationDelegate> {
    UIWindow *window;

}
//void createADWO(bool isCreated);
@property(nonatomic,retain)    UIView *mAdView;
@property(nonatomic, readonly) RootViewController* viewController;

-(void)showOCSocial;
@end


