//
//  LoadingScene.hpp
//  Kolkakoli
//
//  Created by Liam Magee on 18/09/2016.
//
//

#ifndef LoadingScene_hpp
#define LoadingScene_hpp

#include "cocos2d.h"




class LoadingScene : public cocos2d::LayerColor
{
public:
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(LoadingScene);
    
};

#endif /* LoadingScene_hpp */
