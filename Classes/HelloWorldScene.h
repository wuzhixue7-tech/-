#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    // 一个关闭菜单的回调函数
    void menuCloseCallback(cocos2d::Ref* pSender);

    // 方法宏，自动生成create()函数
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
