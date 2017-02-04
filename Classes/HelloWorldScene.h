#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(Ref* pSender);
	void setupTouchListener();
	virtual bool onTouchBegan(Touch*, cocos2d::Event*) override;
	virtual void onTouchEnded(Touch*, cocos2d::Event*) override;
	virtual void onTouchMoved(Touch*, cocos2d::Event*) override;
	virtual void onTouchCancelled(Touch*, cocos2d::Event*) override;
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	EventListenerTouchOneByOne *touchEventListener;
	PhysicsWorld *sceneWorld;
	void SetPhysicsWorld(PhysicsWorld *world);
};

#endif // __HELLOWORLD_SCENE_H__
