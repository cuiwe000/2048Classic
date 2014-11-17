//
//  OpenUrl.h
//  PanBox
//
//  Created by adi on 14-9-19.
//
//

#ifndef __OpenUrl__OpenUrl__
#define __OpenUrl__OpenUrl__

#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class OpenUrl
{
public:
    static OpenUrl* sharedOpenUrl();
    void openUrlFunc(std::string Str_Url);
    
    void showADWO(bool isShowed);
    void showSocial();
};

#endif /* defined(__OpenUrl__OpenUrl__) */
