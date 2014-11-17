//
//  GameOverScene.h
//  PanBox
//
//  Created by adi on 14-9-3.
//
//

#ifndef __PanBox__GameOverScene__
#define __PanBox__GameOverScene__

#include "cocos2d.h"
//共有继承 与 私有继承？？？
USING_NS_CC;

class GameOverScene :public Layer{
public:
    virtual bool init();
//    static Scene *createScene();
    CREATE_FUNC(GameOverScene);
    void setCutImage(RenderTexture *texture);
    
    int _GameStyle;

    void shareCallbac(int platform, int stCode, std::string& errorMsg);
private:
//    void initTouchEvent();
    void changeScen(int style);
};

#endif /* defined(__PanBox__GameOverScene__) */
