#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}
void HelloWorld::SetPhysicsWorld(PhysicsWorld *world) {
	sceneWorld = world;
	sceneWorld->setGravity(Vec2(0, -98.0f));
}
void HelloWorld::setupTouchListener() {
	//Create a the listener object
	this->touchEventListener = EventListenerTouchOneByOne::create();
	//Attach the touch events from the listener to our callback functions
	this->touchEventListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
	this->touchEventListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
	this->touchEventListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
	this->touchEventListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(this->touchEventListener, this);
}
bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event){
	//This function will fire as soon as you touch the screen	
	//Get a reference to the scene that is currently running
	auto scene = Director::getInstance()->getRunningScene();
	//We want to create an instance of sprite a and position it where the touch has occured within the scene
	auto sprite = Sprite::create("sprite_a.png");
	sprite->setName("sprite_a");
	//Get the Point that represents the location of the touch in the scene into a variable
	Point touchLocation = scene->convertToNodeSpace(touch->getLocation());
	//Assign the position of the sprite to that Point
	sprite->setPosition(touchLocation);
	//Add the sprite to the scene
	scene->addChild(sprite);
	return true;
}
void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event){
	//This function will fire as soon as your finger stops touching the screen
	auto scene = Director::getInstance()->getRunningScene();
	Point touchLocation = scene->convertToNodeSpace(touch->getLocation());
	//auto sprite = utils::findChild(scene, "sprite_a");
	auto sprites = utils::findChildren(*scene, "sprite_a");
	for (auto spr : sprites) {
		if (spr) {
			//Create a rectangle which will hold all posible points that are contained in the sprite
			Rect spriteRectangle = spr->getBoundingBox();
			//If our the point where the touch ended is contained in the rectangle
			if (spriteRectangle.containsPoint(touchLocation)) {
				//Release the sprite by adding a PhysicsBody object to it and letting the PhysicsWorld take over
				PhysicsBody *sprite_body = PhysicsBody::createBox(spriteRectangle.size, PHYSICSBODY_MATERIAL_DEFAULT);
				//Make sure you actually attach the PhysicsBody object to the sprite
				spr->setPhysicsBody(sprite_body);
			}
		}
	}
}
void HelloWorld::onTouchMoved(cocos2d::Touch*, cocos2d::Event*){
	//This function will continuously fire as you swipe your finger across the screen
}
void HelloWorld::onTouchCancelled(cocos2d::Touch*, cocos2d::Event*) {
	//This function will fire if the phone switches apps such as when you recieve a call and the phone app appears
}
// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

	this->setupTouchListener(); //Call the setup function
    
    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
