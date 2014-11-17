//
//  OpenUrl.m
//  PanBox
//
//  Created by adi on 14-9-19.
//
//

#include "OpenUrl.h"
#include "AppController.h"
//#include "GameDefine.h"


static OpenUrl* sharedStatic;
OpenUrl* OpenUrl::sharedOpenUrl()
{
    if(!sharedStatic){
        sharedStatic = new OpenUrl();
    }
    return sharedStatic;
}

void OpenUrl::openUrlFunc(std::string Str_Url)
{
//    ((AppController *)[[UIApplication sharedApplication] delegate]).mAdView.hidden= YES;
    NSString* showTime = [NSString stringWithCString: Str_Url.c_str()   encoding:NSUTF8StringEncoding];
    [[UIApplication sharedApplication] openURL:[NSURL URLWithString:showTime]];
}

void OpenUrl::showADWO(bool isShowed){
    NSLog(@"%d",isShowed);
    ((AppController *)[[UIApplication sharedApplication] delegate]).mAdView.hidden= (BOOL)isShowed;
}

void OpenUrl::showSocial(){
    [(AppController *)[[UIApplication sharedApplication] delegate] showOCSocial];
}
