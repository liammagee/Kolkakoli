//
//  GameViewScene.cpp
//  Kolkakoli
//
//  Created by Liam Magee on 30/08/2016.
//
//

#include "GameViewScene.hpp"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* GameViewScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameViewScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameViewScene::init()
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
                                           CC_CALLBACK_1(GameViewScene::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);
    
    /////////////////////////////
    // 3. add your codes below...
    
    // add a label shows "Hello World"
    // create and initialize a label
    
    /*
     auto label = Label::createWithTTF("Kolkakoli", "fonts/Marker Felt.ttf", 24);
     
     // position the label on the center of the screen
     label->setPosition(Vec2(origin.x + visibleSize.width/2,
     origin.y + visibleSize.height - label->getContentSize().height));
     
     // add the label as a child to this layer
     this->addChild(label, 1);
     */
    
    
    targetLabelText = Label::createWithTTF("Target:", "fonts/Marker Felt.ttf", 14);
    movesLabelText = Label::createWithTTF("Moves:", "fonts/Marker Felt.ttf", 14);
    scoreLabelText = Label::createWithTTF("Score:", "fonts/Marker Felt.ttf", 14);
    targetLabel = Label::createWithTTF("999999", "fonts/Marker Felt.ttf", 20);
    movesLabel = Label::createWithTTF("999999", "fonts/Marker Felt.ttf", 20);
    scoreLabel = Label::createWithTTF("999999", "fonts/Marker Felt.ttf", 20);
    
    targetLabelText->setColor(Color3B::BLACK);
    movesLabelText->setColor(Color3B::BLACK);
    scoreLabelText->setColor(Color3B::BLACK);
    targetLabel->setColor(Color3B::BLACK);
    movesLabel->setColor(Color3B::BLACK);
    scoreLabel->setColor(Color3B::BLACK);
    
    targetLabelText->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
                                      origin.y + visibleSize.height - targetLabelText->getContentSize().height));
    movesLabelText->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
                                     origin.y + visibleSize.height - movesLabelText->getContentSize().height));
    scoreLabelText->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
                                     origin.y + visibleSize.height - scoreLabelText->getContentSize().height));
    targetLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.2,
                                  origin.y + visibleSize.height - targetLabelText->getContentSize().height - targetLabel->getContentSize().height));
    movesLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.5,
                                 origin.y + visibleSize.height - movesLabelText->getContentSize().height - movesLabel->getContentSize().height));
    scoreLabel->setPosition(Vec2(origin.x + visibleSize.width * 0.8,
                                 origin.y + visibleSize.height - scoreLabelText->getContentSize().height - movesLabel->getContentSize().height));
    
    this->addChild(targetLabelText, 1);
    this->addChild(movesLabelText, 1);
    this->addChild(scoreLabelText, 1);
    this->addChild(targetLabel, 1);
    this->addChild(movesLabel, 1);
    this->addChild(scoreLabel, 1);
    
    // add "HelloWorld" splash screen"
    //auto spriteLattu = Sprite::create("lattu.png");
    //auto spritePinu = Sprite::create("pinu.png");
    
    // position the sprite on the center of the screen
    //    sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    //spriteLattu->setPosition(Vec2(visibleSize.width/4 + origin.x, visibleSize.height/2 + origin.y));
    //spritePinu->setPosition(Vec2(visibleSize.width/4*3 + origin.x, visibleSize.height/2 + origin.y));
    
    // add the sprite as a child to this layer
    //this->addChild(spriteLattu, 0);
    //this->addChild(spritePinu, 1); // In case they overlap
    
    auto sprite = Sprite::create("Images/Background-hd.png");
    //sprite->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    sprite->setScaleX(visibleSize.width / sprite->getBoundingBox().size.width);
    sprite->setScaleY(visibleSize.height / sprite->getBoundingBox().size.height);
    sprite->setAnchorPoint(Vec2(0, 0));
    this->addChild(sprite, 0);
    
    selectionSprite = Sprite::create("Images/Background-hd.png");
    selectionSprite->retain();
    selectionSprite->setOpacity(0);
    this->addChild(selectionSprite);
    
    gameLayer = new cocos2d::Node();
    gameLayer->setVisible(false);
    gameLayer->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    this->addChild(gameLayer, 0);

    cocos2d::Point layerPosition = cocos2d::Point(-TileWidth * Level::NumColumns / 2, -TileHeight * Level::NumRows / 2);
    
    tilesLayer = new cocos2d::Node();
    tilesLayer->setPosition(layerPosition);
    gameLayer->addChild(tilesLayer);
    
    cropLayer = new cocos2d::ClippingNode();
    gameLayer->addChild(cropLayer);
    
    maskLayer = new cocos2d::Node();
    maskLayer->setPosition(layerPosition);
    cropLayer->setStencil(maskLayer);
    
    cookiesLayer = new cocos2d::Node();
    cookiesLayer->setPosition(layerPosition);
    cropLayer->addChild(cookiesLayer);
    
    preloadResources();
    
    return true;
}


void GameViewScene::preloadResources() {

}


void GameViewScene::menuCloseCallback(Ref* pSender)
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

bool GameViewScene::convertPoint(Vec2 point, int* col, int* row) {
    if (point.x >= 0 && point.x < Level::NumColumns*TileWidth &&
        point.y >= 0 && point.y < Level::NumRows*TileHeight) {
        *col = (int)(point.x / TileWidth);
        *row = (int)(point.y / TileHeight);
        return true;
    }
    else {
        *col = -1;
        *row = -1;
        return false;
    }
}

void GameViewScene::showSelectionIndicatorForCookie(Cookie* cookie) {
    if (selectionSprite->getParent() != nullptr) {
        selectionSprite->removeFromParent();
    }
    auto sprite = Sprite::create(cookie->highlightedSpriteName());
    sprite->setPosition(Vec2(TileWidth / 2, TileHeight / 2));
    selectionSprite = sprite;
    selectionSprite->setOpacity(255);
    cookie->sprite->addChild(selectionSprite);
}
void GameViewScene::trySwapHorizontal(int horzDelta, int vertDelta) {
    int toColumn = swipeFromColumn + horzDelta;
    int toRow = swipeFromRow + vertDelta;
     
    if (toColumn < 0 || toColumn >= Level::NumColumns) return;
    if (toRow < 0 || toRow >= Level::NumRows) return;
    
    Cookie* toCookie = level->cookieAtColumn(toColumn, toRow);
    if (toCookie == NULL) return;
    
    Cookie* fromCookie = level->cookieAtColumn(swipeFromColumn, swipeFromRow);

    if (swapHandler != NULL) {
        Swap *swap = new Swap();
        swap->cookieA = fromCookie;
        swap->cookieB = toCookie;
        swapHandler(swap);
    }
}
void GameViewScene::addSpriteForCookies(std::vector< Cookie* > cookies) {
        //Create a "one by one" touch event listener (processes one touch at a time)
        auto listener1 = EventListenerTouchOneByOne::create();
        // When "swallow touches" is true, then returning 'true' from the onTouchBegan method will "swallow" the touch event, preventing other listeners from using it.
        listener1->setSwallowTouches(true);
        
        // Example of using a lambda expression to implement onTouchBegan event callback function
        listener1->onTouchBegan = [this](Touch* touch, Event* event){
            // event->getCurrentTarget() returns the *listener's* sceneGraphPriority node.
            auto target = static_cast<Sprite*>(event->getCurrentTarget());

            
            //Get the position of the current point relative to the button
            Point locationInNode = target->convertToNodeSpace(touch->getLocation());
            Size s = target->getContentSize();
            Rect rect = Rect(0, 0, s.width, s.height);
            
            //Check the click area
            if (rect.containsPoint(locationInNode))
            {
                target->setOpacity(180);
                
                // Detect the column and row of the cookie
                Point p = cookiesLayer->convertToNodeSpace(touch->getLocation());
                int col, row;
                this->convertPoint(p, &col, &row);
                Cookie* cookie = this->level->cookieAtColumn(col, row);
                
                if (cookie != NULL) {
                    this->showSelectionIndicatorForCookie(cookie);
                    this->swipeFromColumn = col;
                    this->swipeFromRow = row;
                    
                }
                return true;
            }

            return false;
        };
        
        //Trigger when moving touch
        listener1->onTouchMoved = [this](Touch* touch, Event* event){
            if (this->swipeFromColumn == -1 || this->swipeFromRow == -1) return;

            Point p = cookiesLayer->convertToNodeSpace(touch->getLocation());
            int col, row;
            bool converted = this->convertPoint(p, &col, &row);
            
            if (converted) {
                int horzDelta = 0, vertDelta = 0;
                if (col < swipeFromColumn) {
                    horzDelta = -1;
                } else if (col > swipeFromColumn){
                    horzDelta = 1;
                } else if (row < swipeFromRow){
                    vertDelta = -1;
                } else if (row > swipeFromRow){
                    vertDelta = 1;
                }
                if (horzDelta != 0 || vertDelta != 0) {
                    trySwapHorizontal(horzDelta, vertDelta);
                    hideSelectionIndicator();
                    swipeFromColumn = -1;
                }

            }

            //auto target = static_cast<Sprite*>(event->getCurrentTarget());
            //Move the position of current button sprite
            //target->setPosition(target->getPosition() + touch->getDelta());
        };
 
        //Process the touch end event
        listener1->onTouchEnded = [this](Touch* touch, Event* event){
            //auto target = static_cast<Sprite*>(event->getCurrentTarget());
            log("sprite onTouchesEnded.. ");
            if (swipeFromColumn != -1) {
                hideSelectionIndicator();
            }
            swipeFromColumn = -1;
            swipeFromRow = -1;
        };

    for (Cookie* cookie : cookies) {
        auto sprite = Sprite::create(cookie->spriteName());
        sprite->retain();
        sprite->setPosition(pointForColumn(cookie->col, cookie->row));
        cookiesLayer->addChild(sprite);
        cookie->sprite = sprite;
        cookie->sprite->setOpacity(0);
        cookie->sprite->setScaleX(0.5);
        cookie->sprite->setScaleX(0.5);
        auto waitFor = DelayTime::create(0.25 + rand_0_1() * 0.25);
        auto group = Spawn::createWithTwoActions(FadeIn::create(0.25), ScaleTo::create(0.25, 1.0));
        auto runAction = Sequence::create(waitFor, group, nullptr);
        cookie->sprite->runAction(runAction);
    }
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    // Prevent illegal access to a garbage-collected sprite
    selectionSprite = Sprite::create("Images/Background-hd.png");
    selectionSprite->retain();
    selectionSprite->setOpacity(0);
    this->addChild(selectionSprite);
}

cocos2d::Point GameViewScene::pointForColumn(int col, int row) {
    Point p = Point(col * TileWidth + TileWidth / 2,row * TileHeight + TileHeight / 2);
    return p;
}
void GameViewScene::addTiles() {
    for (int i = 0; i < Level::NumRows; i++) {
        for (int j = 0; j < Level::NumColumns; j++) {
            if (level->tileAtColumn(j, i) != NULL) {
                //auto tile = Sprite::create("Sprites/Tile.png");
                auto tile = Sprite::create("Grid/MaskTile.png");
                tile->setPosition(pointForColumn(j, i));
                //tilesLayer->addChild(tile);
                maskLayer->addChild(tile);
            }
        }
    }
    
    for (int i = 0; i <= Level::NumRows; i++) {
        for (int j = 0; j <= Level::NumColumns; j++) {
            bool topLeft = (j > 0) && (i < Level::NumRows) && (level->tileAtColumn(j - 1, i) != NULL);
            bool bottomLeft = (j > 0) && (i > 0) && (level->tileAtColumn(j - 1, i - 1) != NULL);
            bool topRight = (j < Level::NumColumns) && (i < Level::NumRows) && (level->tileAtColumn(j, i) != NULL);
            bool bottomRight = (j < Level::NumColumns) && (i > 0) && (level->tileAtColumn(j, i - 1) != NULL);
            int value = topLeft | topRight << 1 | bottomLeft << 2 | bottomRight << 3;
            
            if (value != 0 && value != 6 && value != 9) {
                std::string fileName = "Grid/Tile_" + std::to_string(value) + ".png";
                auto tile = Sprite::create(fileName);
                Point p = Vec2(pointForColumn(j, i));
                p.x -= TileWidth / 2;
                p.y -= TileHeight / 2;
                tile->setPosition(p);
                tilesLayer->addChild(tile);
            }
        }
    }
}
void GameViewScene::animateSwap(Swap* swap, std::function< void ()>* block){
    swap->cookieA->sprite->setLocalZOrder(100);
    swap->cookieB->sprite->setLocalZOrder(90);
 
    const float duration = 0.3;
    auto moveToB = MoveTo::create(duration, swap->cookieB->sprite->getPosition());
    auto moveAEaseOut = EaseOut::create(moveToB, 1.0);
    auto seqA = Sequence::create(moveAEaseOut, nullptr);
    swap->cookieA->sprite->runAction(seqA);
    
    auto moveToA = MoveTo::create(duration, swap->cookieA->sprite->getPosition());
    auto moveBEaseOut = EaseOut::create(moveToA, 1.0);
    auto funcB = CallFunc::create(*block);
    auto seqB = Sequence::create(moveBEaseOut, funcB, nullptr);
    swap->cookieB->sprite->runAction(seqB);
    

    std::function<void()> ssF = [this](){
        if (this->playSounds) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Chomp.wav");
        }
    };
    auto cb = CallFunc::create(ssF);
    this->runAction(cb);
}
void GameViewScene::animateInvalidSwap(Swap* swap) {
    swap->cookieA->sprite->setLocalZOrder(100);
    swap->cookieB->sprite->setLocalZOrder(90);
    
    const float duration = 0.2;
    auto moveToB = MoveTo::create(duration, swap->cookieB->sprite->getPosition());
    auto moveAEaseOut = EaseOut::create(moveToB, 1.0);
    auto moveBackA = MoveTo::create(duration, swap->cookieA->sprite->getPosition());
    auto moveBackAEaseOut = EaseOut::create(moveBackA, 1.0);
    auto seqA = Sequence::create(moveAEaseOut, moveBackAEaseOut, nullptr);
    swap->cookieA->sprite->runAction(seqA);
    
    auto moveToA = MoveTo::create(duration, swap->cookieA->sprite->getPosition());
    auto moveBEaseOut = EaseOut::create(moveToA, 1.0);
    auto moveBackB = MoveTo::create(duration, swap->cookieB->sprite->getPosition());
    auto moveBackBEaseOut = EaseOut::create(moveBackB, 1.0);
    auto seqB = Sequence::create(moveBEaseOut, moveBackBEaseOut, nullptr);
    swap->cookieB->sprite->runAction(seqB);
    
    std::function<void()> ssF = [this](){
        if (this->playSounds) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Error.wav");
        }
    };
    auto cb = CallFunc::create(ssF);
    this->runAction(cb);
}
void GameViewScene::hideSelectionIndicator() {
    const float duration = 0.3;
    auto fadeOut = FadeOut::create(duration);
    //selectionSprite->removeFromParent();
    selectionSprite->getParent()->setOpacity(255);
    selectionSprite->setParent(this);
    auto seq = Sequence::create(fadeOut, nullptr);
    selectionSprite->runAction(seq);
}
void GameViewScene::animateMatchedCookies(std::vector< Chain* > chains, std::function< void ()>* block) {
    for (Chain* chain : chains) {
        animateScoreForCookies(chain);
        for (Cookie* cookie : chain->cookies) {
            if (cookie->sprite != NULL) {
                auto scaleAction = ScaleTo::create(0.3, 0.0);
                auto scaleEaseOut = EaseOut::create(scaleAction, 1.0);
                auto seq = Sequence::create(scaleEaseOut, nullptr);
                cookie->sprite->runAction(seq);
                cookie->sprite->setOpacity(0);
                //cookie->sprite->removeFromParent();
                //cookie->sprite = NULL;
            }
        }
    }
    // Play sound
    std::function<void()> ssF = [this](){
        if (this->playSounds) {
            CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Ka-Ching.wav");
        }
    };
    auto cb = CallFunc::create(ssF);
    this->runAction(cb);
    // Run block to continue
    auto fun = CallFunc::create(*block);
    auto seq = Sequence::create(fun, nullptr);
    this->runAction(seq);
}
void GameViewScene::animateFallingCookies(std::vector< std::vector< Cookie* > > cookies, std::function< void ()>* block) {
    float longestDuration = 0;
    int counter = 0;
    for (std::vector< Cookie* > row : cookies) {
        for (Cookie* cookie : row) {
            Point p = pointForColumn(cookie->col, cookie->row);

            float delay = 0.05 + 0.15 * counter;
            
            float duration = (cookie->sprite->getPosition().y - p.y) / TileHeight * 0.1;
            
            longestDuration = MAX(longestDuration, duration + delay);
            
            auto waitAction = DelayTime::create(delay);
            auto moveAction = MoveTo::create(duration, p);
            
            std::function<void()> ssF = [this](){
                if (this->playSounds) {
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Scrape.wav");
                }
            };
            auto cb = CallFunc::create(ssF);
            auto group = Spawn::createWithTwoActions(moveAction, cb);
            auto seq = Sequence::create(waitAction, group, nullptr);
            cookie->sprite->runAction(seq);
        }
        counter++;
    }
    // Run block at longestDuration
    auto waitAction2 = DelayTime::create(longestDuration);
    auto fun = CallFunc::create(*block);
    auto seq = Sequence::create(waitAction2, fun, nullptr);
    this->runAction(seq);
}
void GameViewScene::animateNewCookies(std::vector< std::vector< Cookie* > > cookies, std::function< void ()>* block) {
    float longestDuration = 0;
    int colCounter = 0;
    for (std::vector< Cookie* > row : cookies) {
        int rowCounter = 0;
        int startRow = row.front()->row;
        for (Cookie* cookie : row) {
            auto sprite = Sprite::create(cookie->spriteName());
            sprite->setPosition(pointForColumn(cookie->col, startRow));
            cookiesLayer->addChild(sprite);
            cookie->sprite = sprite;
            
            float delay = 0.1 + 0.2 * (row.size() - rowCounter - 1);
            
            float duration = (startRow - cookie->row) * 0.1;
            
            longestDuration = MAX(longestDuration, duration + delay);
            
            Point p = pointForColumn(cookie->col, cookie->row);
            
            cookie->sprite->setOpacity(0);
            auto waitAction = DelayTime::create(delay);
            auto moveAction = MoveTo::create(duration, p);
            auto fadeInAction = FadeIn::create(0.05);
            std::function<void()> ssF = [this](){
                if (this->playSounds) {
                    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("Sounds/Drip.wav");
                }
            };
            auto cb = CallFunc::create(ssF);
            auto group = Spawn::create(fadeInAction, moveAction, cb, nullptr);
            auto seq = Sequence::create(waitAction, group, nullptr);
            cookie->sprite->runAction(seq);
            rowCounter++;
        }
        colCounter++;
    }
    // Run block at longestDuration
    auto waitAction2 = DelayTime::create(longestDuration);
    auto fun = CallFunc::create(*block);
    auto seq = Sequence::create(waitAction2, fun, nullptr);
    this->runAction(seq);
}
void GameViewScene::animateScoreForCookies(Chain* chain) {
    Cookie* firstCookie = chain->cookies[0];
    Cookie* lastCookie = chain->cookies[chain->cookies.size() - 1];
        Point p = Vec2((firstCookie->sprite->getPositionX() + lastCookie->sprite->getPositionX()) / 2,
                       (firstCookie->sprite->getPositionY() + lastCookie->sprite->getPositionY()) / 2  - 8);
        cocos2d::Label* label = cocos2d::Label::createWithTTF( std::to_string(chain->score), "fonts/Marker Felt.ttf", 20);
        label->setColor(Color3B::WHITE);
        label->setPosition(p);
        label->setGlobalZOrder(300);
        cookiesLayer->addChild(label, 1);
        
        auto moveAction = MoveBy::create(0.7, Vec2(0, 20));
        auto easeOutAction = EaseOut::create(moveAction, 1.0);
        std::function<void ()> f = [label](){
            label->removeFromParent();
        };
        auto seq = Sequence::createWithTwoActions(easeOutAction, CallFunc::create(f));
        label->runAction(seq);
}
void GameViewScene::updateLabels() {
    targetLabel->setString(std::to_string((long)level->targetScore));
    movesLabel->setString(std::to_string((long)movesLeft));
    scoreLabel->setString(std::to_string((long)score));
}
void GameViewScene::removeAllCookieSprites() {
    cookiesLayer->removeAllChildren();
}
void GameViewScene::animateGameOver() {
    auto moveBy = MoveBy::create(0.3, Vec2(0, -this->getPositionY()));
    auto easeIn = EaseIn::create(moveBy, 1.0);
    gameLayer->runAction(easeIn);
}
void GameViewScene::animateBeginGame() {
    gameLayer->setVisible(true);

    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    gameLayer->setPosition(Vec2(visibleSize.width/2 + origin.x, -(visibleSize.height/2 + origin.y)));
    auto moveTo = MoveTo::create(0.3, Vec2(visibleSize.width/2 + origin.x, (visibleSize.height/2 + origin.y)));
    auto easeIn = EaseIn::create(moveTo, 1.0);
    gameLayer->runAction(easeIn);
}