//
//  SettingLayer.h
//  PanBox
//
//  Created by adi on 14-9-17.
//
//

#ifndef __PanBox__SettingLayer__
#define __PanBox__SettingLayer__

#define SETTINGNotification "SETTINGNotification"

#include "cocos2d.h"

USING_NS_CC;


class SettingLayer :public Layer{
private:
    bool backgroundMusic;
    bool musicEffect;
    
    void dismisSettingLayer();
    LayerColor *layerColor;
public:
    virtual bool init();
    ~SettingLayer();
    
    CREATE_FUNC(SettingLayer);
    
    void doingSome(int tag);
    
    Menu *mu;
    
    void initTouchEvent();
    
};

#endif /* defined(__PanBox__SettingLayer__) */
