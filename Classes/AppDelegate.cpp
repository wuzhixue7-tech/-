#include "AppDelegate.h"
#include "HelloWorldScene.h"

// #define USE_AUDIO_ENGINE 1
// #define USE_SIMPLE_AUDIO_ENGINE 1

#if USE_AUDIO_ENGINE && USE_SIMPLE_AUDIO_ENGINE
#error "Don't use AudioEngine and SimpleAudioEngine at the same time. Please just select one in your game!"
#endif

#if USE_AUDIO_ENGINE
#include "audio/include/AudioEngine.h"
using namespace cocos2d::experimental;
#elif USE_SIMPLE_AUDIO_ENGINE
#include "audio/include/SimpleAudioEngine.h"
using namespace CocosDenshion;
#endif

USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1080, 2080);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate() 
{
#if USE_AUDIO_ENGINE
    AudioEngine::end();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::end();
#endif
}

//  修改glContextAttrs的值以获得不同的上下文（影响所有平台）
void AppDelegate::initGLContextAttrs()
{
	// 设置OpenGL的上下文属性：红色、绿色、蓝色、alpha、深度、模板、多重采样数量
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8, 0};

    GLView::setGLContextAttrs(glContextAttrs);
}

// 如果想要使用packages manager进行扩展，可以在这里注册
static int register_all_packages()
{
    return 0; //包管理器的标志
}

bool AppDelegate::applicationDidFinishLaunching() {
    // 初始化导演器
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
        glview = GLViewImpl::createWithRect("card_game", cocos2d::Rect(0, 0, designResolutionSize.width, designResolutionSize.height), 0.5);
#else
        glview = GLViewImpl::create("card_game");
#endif
        director->setOpenGLView(glview);
    }

    // 开启显示帧率
    director->setDisplayStats(true);

    //设置帧数，默认值是1.0/60，如需要修改在此处改
    director->setAnimationInterval(1.0f / 60);

    // 设定设计分辨率
    glview->setDesignResolutionSize(designResolutionSize.width, designResolutionSize.height, ResolutionPolicy::FIXED_WIDTH);
#if  0
    auto frameSize = glview->getFrameSize();
    //如果帧的高度大于大尺寸的高度
    if (frameSize.height > mediumResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(largeResolutionSize.height/designResolutionSize.height, largeResolutionSize.width/designResolutionSize.width));
    }
    // 如果帧的高度介于中等和大尺寸之间
    else if (frameSize.height > smallResolutionSize.height)
    {        
        director->setContentScaleFactor(MIN(mediumResolutionSize.height/designResolutionSize.height, mediumResolutionSize.width/designResolutionSize.width));
    }
    // 如果帧的高度小于等于小尺寸的高度
    else
    {        
        director->setContentScaleFactor(MIN(smallResolutionSize.height/designResolutionSize.height, smallResolutionSize.width/designResolutionSize.width));
    }
#endif //  0
    register_all_packages();

    // 创建一个场景并运行
    auto scene = HelloWorld::createScene();

    // 运行场景
    director->runWithScene(scene);

    return true;
}

// 这个函数将在应用程序进入后台时调用
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::pauseAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
    SimpleAudioEngine::getInstance()->pauseAllEffects();
#endif
}

// 这个函数将在应用程序进入前台时调用
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

#if USE_AUDIO_ENGINE
    AudioEngine::resumeAll();
#elif USE_SIMPLE_AUDIO_ENGINE
    SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
    SimpleAudioEngine::getInstance()->resumeAllEffects();
#endif
}
