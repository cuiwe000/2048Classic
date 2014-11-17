//
//  GameDefine.h
//  PanBox
//
//  Created by adi on 14-8-27.
//
//

#ifndef PanBox_GameDefine_h
#define PanBox_GameDefine_h

#define DEBUG 0

#define APPLEID "922797710"

#define UMSOCIAL 0
#define UM_COCOS2DX_SOCIAL 1
#define UMANALISIS 1
#define ADWO 1

//#define ISLOG true
#define ISLOG false

#define APPSTORE_ADDR "https://itunes.apple.com/cn/app/id922797710"

#define ADWO_PID "2d311b90cdb643258f3cbdafe1ab21f0" ///!!!!!!!

#define UMAPPKEY "5402eb36fd98c53f48005778"
#define UMSOCIAL_CONTENT "推荐个游戏#2048经典#，朋友看我总玩，他们也下了个，也入迷了，这个需要动脑，大家可以试试看"

#define QQAPPID "1103155141"
#define QQAppKey "LJ6b58FA25dajIKp"

#define WEIXINAPPID "wx55595c7272fe2686"
#define WEIXINAPPKEY "9bc61c03bb41f34c2e2667decb844cba"

#define DEVICE_WIDTH  Director::getInstance()->getVisibleSize().width
#define DEVICE_HEIGHT Director::getInstance()->getVisibleSize().height

#define LoadSpriteFameByName(__PNG__) SpriteFrameCache::getInstance()->getSpriteFrameByName(__PNG__)

#define SPACE 18
#define SpriteWH 128
#define layerBg 600


#define G_R 4
#define G_C 4

//#define clog(s, ...) \
        log("%s(%d): %s", __PRETTY_FUNCTION__, __LINE__, CCString::createWithFormat(s, ##__VA_ARGS__)->getCString())
#define clog(xx, ...)  ((void)0)

enum class MOVE_DIR { moveUp, moveDown, moveLeft, moveRight };

#endif
