#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "configs/models/CardResConfig.h"
#include "views/CardView.h"
#include "models/GameModel.h"
#include "views/GameView.h"
#include "services/GameModelFromLevelGenerator.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// 错误处理函数
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// 在这里初始化你的场景
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. 添加菜单项
    //    你可以修改下面的代码来创建更多的菜单项

    // 添加关闭按钮
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + visibleSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // 创建菜单，并将菜单项添加到菜单中
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. 添加其他初始化代码

    // 增加背景颜色
    // 创建两个彩色图层作为背景：上半区为棕色，下半区为紫色


    // ========== 1. 上半区：棕色背景 ==========
    float topHeight = visibleSize.height * 2.0f / 3.0f; // 上半区高度占 2/3 屏幕
    Color4B topColor(165, 42, 42, 255); // 棕色（RGB：165,42,42；alpha：255）
    auto topLayer = LayerColor::create(topColor, visibleSize.width, topHeight);
    // 位置：底部对齐下半区顶部（y = 下半区高度 = visibleSize.height - topHeight）
    topLayer->setPosition(Vec2(0, visibleSize.height - topHeight));
    addChild(topLayer, 0); // zOrder=0，确保在最底层

    // ========== 2. 下半区：紫色背景 ==========
    float bottomHeight = visibleSize.height - topHeight; // 下半区高度占 1/3 屏幕
    Color4B bottomColor(128, 0, 128, 255); // 紫色（RGB：128,0,128；alpha：255）
    auto bottomLayer = LayerColor::create(bottomColor, visibleSize.width, bottomHeight);
    bottomLayer->setPosition(Vec2(0, 0)); // 位置：左下角对齐
    addChild(bottomLayer, 0);

    // 使用 GameModelFromLevelGenerator 生成 GameModel 和 GameView
    auto gameModel = GameModelFromLevelGenerator::generateGameModel("level_1.json");
    GameModelFromLevelGenerator::generateGameView(gameModel, this);
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //关闭应用程序
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif


    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
