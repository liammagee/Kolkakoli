//
//  GameScene.hpp
//  Kolkakoli
//
//  Created by Liam Magee on 31/08/2016.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>

class GameScene : cocos2d::Layer {
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
};

#endif /* GameScene_hpp */
