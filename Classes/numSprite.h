//
//  numSprite.h
//  PanBox
//
//  Created by adi on 14-8-28.
//
//

#ifndef __PanBox__numSprite__
#define __PanBox__numSprite__

enum Sprite_Dir{
    UP=100,
    DOWN,
    LEFT,
    RIGHT
};

enum GameStyle{
    DAT,
    HISTORY
};

#include "cocos2d.h"

USING_NS_CC;

class numSprite:public Sprite{
public:
    virtual bool init();
    CREATE_FUNC(numSprite);
    
    int m_r;
    int m_c;
    int m_num;
    
    int m_n; ///移动格数
    
    GameStyle gameStyle;
    
    void moveTo(int r,int c); /// 动画move

    void doubleNumber();
    
    
    void setPoint(float xx,float yy);
    void SpriteColor(int num);

private:
    
    void removeScore();

    
};

#endif /* defined(__PanBox__numSprite__) */
