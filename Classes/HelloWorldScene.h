#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

#include "Level.hpp"
#include "Swap.hpp"
#include "Cookie.hpp"
#include "MyScene.hpp"


class HelloWorld : public cocos2d::Layer
{
public:
    Level level;
    Swap swap;
    MyScene *myScene;

    cocos2d::ui::ImageView* gameOverPanel;
    cocos2d::ui::Button* btnShuffle;
    cocos2d::EventListenerTouchOneByOne* gameOverListener;
    
    

    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

    void addSpriteForCookies(std::vector< Cookie > cookies);
    void addTiles();
    void animateSwap(Swap swap);
    void animateInvalidSwap(Swap swap);
    void beginGame();
    void shuffle();
    void handleMatches();
    void beginNextTurn();
    void decrementMoves();
    void showGameOver();
    void hideGameOver();
};

#endif // __HELLOWORLD_SCENE_H__
