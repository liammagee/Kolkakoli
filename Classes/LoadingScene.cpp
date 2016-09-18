//
//  LoadingScene.cpp
//  Kolkakoli
//
//  Created by Liam Magee on 18/09/2016.
//
//

#include "LoadingScene.hpp"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoadingScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool LoadingScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    
     auto label = Label::createWithTTF("Kolkakoli", "fonts/Marker Felt.ttf", 24);
     
     // position the label on the center of the screen
     label->setPosition(Vec2(origin.x + visibleSize.width/2,
     origin.y + visibleSize.height - label->getContentSize().height));
     
     // add the label as a child to this layer
     this->addChild(label, 1);

    
    // add "HelloWorld" splash screen"
    auto spriteLattu = Sprite::create("lattu.png");
    auto spritePinu = Sprite::create("pinu.png");
    
    // position the sprite on the center of the screen
    spriteLattu->setPosition(Vec2(visibleSize.width/4 + origin.x, visibleSize.height/2 + origin.y));
    spriteLattu->setScale(0.1);
    spritePinu->setPosition(Vec2(visibleSize.width/4*3 + origin.x, visibleSize.height/2 + origin.y));
    spritePinu->setScale(0.1);
    
    // add the sprite as a child to this layer
    this->addChild(spriteLattu, 0);
    this->addChild(spritePinu, 1); // In case they overlap

    
    return true;
}
