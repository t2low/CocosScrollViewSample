#include "HelloWorldScene.h"
#include "ScrollViewEx.h"

USING_NS_CC;
USING_NS_CC_EXT;

CCScene* HelloWorld::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    HelloWorld *layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    if ( !CCLayer::init() ) {
        return false;
    }
    
    CCSize size = getContentSize();
    const float width = size.width;
    const float height = size.height;
    
    const float scale = 1.5;
    
    // メニューを画面の1.5倍の高さで作成
    MenuEx *menu = MenuEx::create();
    menu->setContentSize(CCSizeMake(width, height * scale));
    menu->setPosition(CCPointZero);
    
    // １つ目のボタンをメニューの左下の方に設置
    CCMenuItemImage *item1 = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HelloWorld::menuCloseCallback));
    item1->setPosition(ccp(item1->getContentSize().width, item1->getContentSize().height));
    menu->addChild(item1);
    
    // ２つ目のボタンをメニューの上の方に設置
    CCMenuItemImage *item2 = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HelloWorld::menuCloseCallback));
    item2->setPosition(ccp(width - item2->getContentSize().width, height * scale - item2->getContentSize().height));
    menu->addChild(item2);
    
    // ３つ目のボタンをメニューの真ん中に設置
    CCMenuItemImage *item3 = CCMenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HelloWorld::menuCloseCallback));
    item3->setPosition(ccp(width / 2, height * scale / 2));
    menu->addChild(item3);
    
    // スクロールビューを設置
    ScrollViewEx *scroll = ScrollViewEx::create();
    scroll->setPosition(CCPointZero);
    scroll->setContentSize(CCSizeMake(width, height * scale));
    scroll->setViewSize(size);
    scroll->setDirection(kCCScrollViewDirectionVertical);
    scroll->setBounceable(false);
    addChild(scroll);
    
    // メニューをスクロールビューの中に設置
    scroll->addChild(menu);
    scroll->setMenu(menu);
    
    return true;
}


void HelloWorld::menuCloseCallback(CCObject* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT) || (CC_TARGET_PLATFORM == CC_PLATFORM_WP8)
	CCMessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
#else
    CCDirector::sharedDirector()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
#endif
}
