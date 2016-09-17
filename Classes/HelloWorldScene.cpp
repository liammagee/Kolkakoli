#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
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

    
    // Add Game Over panel
    gameOverPanel = ui::ImageView::create("Images/GameOver-hd.png");
    gameOverPanel->setScaleX(visibleSize.width / gameOverPanel->getBoundingBox().size.width);
    gameOverPanel->setScaleY(visibleSize.height / gameOverPanel->getBoundingBox().size.height * 0.4);
    gameOverPanel->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                    origin.y / 2 + visibleSize.height / 2));
    this->addChild(gameOverPanel, 2);
    gameOverPanel->setVisible(false);

    btnShuffle = ui::Button::create("Images/Button-hd.png");
    btnShuffle->setScaleX(0.5);
    btnShuffle->setScaleY(0.5);
    btnShuffle->setPosition(Vec2(origin.x + visibleSize.width / 2,
                                origin.y + btnShuffle->getContentSize().height / 2));
    btnShuffle->setTitleText("Shuffle");
    btnShuffle->setTitleFontName("fonts/Marker Felt.ttf");
    btnShuffle->setTitleFontSize(20);
    btnShuffle->addTouchEventListener([&](Ref* sender, ui::Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                std::cout << "Button 1 clicked" << std::endl;
                this->shuffle();
                this->decrementMoves();
                break;
            default:
                break;
        }
    });
    this->addChild(btnShuffle, 2);
    
    // Add Level
    auto level = Level::initWithFile("Grid/Level_1.json");

    
    // Initialise actual swap scene
    myScene = MyScene::create();
    myScene->level = level;
    myScene->addTiles();
    
    std::function<void(Swap*)> block = [this](Swap* swap) {
        Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this->myScene);
        if (this->myScene->level->isPossibleSwap(swap)) {
            this->myScene->level->performSwap(swap);
            std::function<void()> postSwap = [this]() {
                this->handleMatches();
            };
            this->myScene->animateSwap(swap, &postSwap);
            Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->myScene);
        }
        else {
            this->myScene->animateInvalidSwap(swap);
            Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->myScene);
        }
    };
    
    myScene->swapHandler = block;
    
    this->beginGame();
    this->addChild(myScene);
    
    // Play music
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic(
                                                                          "Sounds/Mining by Moonlight.mp3", true);
    
    return true;
}

void HelloWorld::beginNextTurn() {
    myScene->level->detectPossibleSwaps();
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
    decrementMoves();
}
void HelloWorld::handleMatches() {
    std::vector< Chain*> chains = this->myScene->level->removeMatches();
    if (chains.size() == 0) {
        beginNextTurn();
        return;
    }
    for (Chain* chain : chains) {
        myScene->score += chain->score;
        myScene->updateLabels();
    }
    std::function<void()> postMatch = [this]() {
        std::vector< std::vector< Cookie* > > cookies = myScene->level->fillHoles();
        std::function<void()> postFall = [this]() {
            std::vector< std::vector< Cookie* > > topUpCookies = myScene->level->topUpCookies();
            std::function<void()> postTopUp = [this]() {
                handleMatches();
            };
            this->myScene->animateNewCookies(topUpCookies, &postTopUp);
        };
        myScene->animateFallingCookies(cookies, &postFall);
    };
    myScene->animateMatchedCookies(chains, &postMatch);
}

void HelloWorld::beginGame() {
    myScene->animateBeginGame();
    myScene->movesLeft = myScene->level->maximumMoves;
    myScene->score = 0;
    myScene->updateLabels();
    this->shuffle();
}

void HelloWorld::shuffle() {
    myScene->removeAllCookieSprites();
    std::vector< Cookie* > cookies = myScene->level->shuffle();
    myScene->addSpriteForCookies(cookies);
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

void HelloWorld::decrementMoves() {
    myScene->movesLeft--;
    myScene->updateLabels();
    if (myScene->score >= myScene->level->targetScore) {
        gameOverPanel->loadTexture("Images/LevelComplete-hd.png");
        showGameOver();
    }
    else if (myScene->movesLeft <= 0) {
        gameOverPanel->loadTexture("Images/GameOver-hd.png");
        showGameOver();
    }
}

void HelloWorld::showGameOver() {
    myScene->animateGameOver();
    gameOverPanel->setVisible(true);
    btnShuffle->setVisible(false);
    Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this->myScene);
    
    //Create a "one by one" touch event listener (processes one touch at a time)
    gameOverListener = EventListenerTouchOneByOne::create();
    // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
    gameOverListener->setSwallowTouches(true);
    
    // Example of using a lambda expression to implement onTouchBegan event callback function
    gameOverListener->onTouchBegan = [this](Touch* touch, Event* event){
        this->hideGameOver();
        return false;
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(gameOverListener, gameOverPanel);
}
void HelloWorld::hideGameOver() {
    _eventDispatcher->removeEventListener(gameOverListener);
    gameOverListener = NULL;
    gameOverPanel->setVisible(false);
    btnShuffle->setVisible(true);
    Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this->myScene);
    beginGame();
}