//
//  MyScene.hpp
//  Kolkakoli
//
//  Created by Liam Magee on 30/08/2016.
//
//

#ifndef MyScene_hpp
#define MyScene_hpp

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

#include "Level.hpp"
#include "Swap.hpp"
#include "Cookie.hpp"


class MyScene : public cocos2d::Layer {
public:
    static constexpr float TileWidth = 32.0f;
    static constexpr float TileHeight = 36.0f;
    Level* level;
    Swap swap;
    cocos2d::Scene scene;
    cocos2d::Node *gameLayer;
    cocos2d::Node *cookiesLayer;
    cocos2d::Node *tilesLayer;
    cocos2d::Sprite *selectionSprite;
    

    int movesLeft;
    int score;
    
    cocos2d::Label* targetLabelText;
    cocos2d::Label* movesLabelText;
    cocos2d::Label* scoreLabelText;
    cocos2d::Label* targetLabel;
    cocos2d::Label* movesLabel;
    cocos2d::Label* scoreLabel;
    
    int swipeFromColumn = -1;
    int swipeFromRow = -1;
    
    std::function<void(Swap*)> swapHandler;
    
    
    cocos2d::Point pointForColumn(int col, int row);
    bool convertPoint(cocos2d::Vec2 point, int* col, int* row);
    void showSelectionIndicatorForCookie(Cookie* cookie);
    
    void trySwapHorizontal(int horzDelta, int vertDelta);
    void hideSelectionIndicator();
    
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MyScene);

    void preloadResources();

    void addSpriteForCookies(std::vector< Cookie* > cookies);
    void addTiles();
    void animateSwap(Swap* swap, std::function< void ()>* block);
    void animateInvalidSwap(Swap* swap);
    void animateMatchedCookies(std::vector< Chain* > chains, std::function< void ()>* block);
    void animateFallingCookies(std::vector< std::vector< Cookie* > > cookies, std::function< void ()>* block);
    void animateNewCookies(std::vector< std::vector< Cookie* > > cookies, std::function< void ()>* block);
    void updateLabels();
    void removeAllCookieSprites();
};


#endif /* MyScene_hpp */
