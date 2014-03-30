#include "ScrollViewEx.h"

USING_NS_CC;
USING_NS_CC_EXT;

bool MenuEx::ccTouchBegan(CCTouch *touch, CCEvent *event) {
    if (!validTouchRectInWorldSpace.size.width || !validTouchRectInWorldSpace.size.height) {
        return CCMenu::ccTouchBegan(touch, event);
    }
    
    CCPoint touchLocation = touch->getLocation();
    if (!validTouchRectInWorldSpace.containsPoint(touchLocation)) {
        return false;
    }
    
    return CCMenu::ccTouchBegan(touch, event);
}

// ------------------------------------------------------------------------

const float ScrollViewEx::MIN_DISTANCE = 10;

void ScrollViewEx::registerWithTouchDispatcher() {
    CCTouchDispatcher *dispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
    dispatcher->addTargetedDelegate(this, kScrollViewExPriority, true);
}

bool ScrollViewEx::ccTouchBegan(CCTouch *touch, CCEvent *event) {
    pressPoint = touch->getLocationInView();
    if (menu && !waitingTouchEnd) {
        waitingTouchEnd = menu->ccTouchBegan(touch, event);
    }
    return CCScrollView::ccTouchBegan(touch, event);
}

void ScrollViewEx::ccTouchMoved(CCTouch *touch, CCEvent *event) {
    if (menu && waitingTouchEnd) {
        CCPoint endPoint = touch->getLocationInView();
        float distance = ccpDistance(endPoint, pressPoint);
        
        if(distance < MIN_DISTANCE) {
            menu->ccTouchMoved(touch, event);
        } else {
            menu->ccTouchCancelled(touch, event);
            waitingTouchEnd = false;
        }
    }
    CCScrollView::ccTouchMoved(touch, event);
}

void ScrollViewEx::ccTouchEnded(CCTouch *touch, CCEvent *event) {
    if (menu && waitingTouchEnd) {
        CCPoint endPoint = touch->getLocationInView();
        float distance = ccpDistance(endPoint, pressPoint);
        
        if(distance < MIN_DISTANCE) {
            menu->ccTouchEnded(touch, event);
        } else {
            menu->ccTouchCancelled(touch, event);
        }
        waitingTouchEnd = false;
    }
    CCScrollView::ccTouchEnded(touch, event);
}

void ScrollViewEx::ccTouchCancelled(CCTouch *touch, CCEvent *event) {
    if (menu && waitingTouchEnd) {
        menu->ccTouchCancelled(touch, event);
        waitingTouchEnd = false;
    }
    CCScrollView::ccTouchCancelled(touch, event);
}

void ScrollViewEx::setMenu(CCMenu *menu) {
    this->menu = menu;
    MenuEx *ex = dynamic_cast<MenuEx *>(menu);
    if (ex) {
        ex->setValidTouchRectInWorldSpace(getViewRect());
    }
}
