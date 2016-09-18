#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "SimpleAudioEngine.h"

#include "Level.hpp"
#include "Swap.hpp"
#include "Cookie.hpp"
#include "GameViewScene.hpp"


class GameControllerScene : public cocos2d::Layer
{
public:
    bool playMusic = true;
    Level level;
    Swap swap;
    GameViewScene *myScene;

    cocos2d::ui::ImageView* gameOverPanel;
    cocos2d::ui::Button* btnShuffle;
    cocos2d::EventListenerTouchOneByOne* gameOverListener;
    
    

    static cocos2d::Scene* createScene();

    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameControllerScene);

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
