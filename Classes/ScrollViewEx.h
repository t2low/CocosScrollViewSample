#ifndef __SCROLL_VIEW_EX_H_INCLUDED__
#define __SCROLL_VIEW_EX_H_INCLUDED__

#include "cocos2d.h"
#include "cocos-ext.h"

class MenuEx : public cocos2d::CCMenu {
public:
    CREATE_FUNC(MenuEx);
    
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    void setValidTouchRectInWorldSpace(cocos2d::CCRect rect) { this->validTouchRectInWorldSpace = rect; };
private:
    cocos2d::CCRect validTouchRectInWorldSpace;
};


class ScrollViewEx : public cocos2d::extension::CCScrollView {
public:
    CREATE_FUNC(ScrollViewEx);

    virtual void registerWithTouchDispatcher();
    virtual bool ccTouchBegan(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchMoved(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchEnded(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    virtual void ccTouchCancelled(cocos2d::CCTouch *touch, cocos2d::CCEvent *event);
    
    void setMenu(cocos2d::CCMenu *menu);
    
    enum {
        kScrollViewExPriority = (cocos2d::kCCMenuHandlerPriority - 1)
    };
private:
    static const float MIN_DISTANCE;
    cocos2d::CCPoint pressPoint;
    cocos2d::CCMenu *menu;
    bool waitingTouchEnd;
};

#endif /* defined(__SCROLL_VIEW_EX_H_INCLUDED__) */
