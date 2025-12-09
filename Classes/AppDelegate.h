#ifndef  _APP_DELEGATE_H_
#define  _APP_DELEGATE_H_

#include "cocos2d.h"

/**
@brief 这个类是应用程序的委托类

私有继承自cocos2d
*/
class  AppDelegate : private cocos2d::Application
{
public:
    AppDelegate();
    virtual ~AppDelegate();

    virtual void initGLContextAttrs();

    /**
    @brief    这个函数将在应用程序启动后立即调用
    @return true   初始化成功
    @return false   初始化失败
    */
    virtual bool applicationDidFinishLaunching();

    /**
    @brief  唤起应用程序进入后台
    @param  这个应用程序的指针
    */
    virtual void applicationDidEnterBackground();

    /**
    @brief  唤起应用程序进入前台
    @param  这个应用程序的指针
    */
    virtual void applicationWillEnterForeground();
};

#endif // _APP_DELEGATE_H_

