//
//  Level.hpp
//  Kolkakoli
//
//  Created by Liam Magee on 30/08/2016.
//
//

#ifndef Level_hpp
#define Level_hpp

#include <stdio.h>
#include <iostream>

#include "external/json/document.h"
#include "Cookie.hpp"
#include "Swap.hpp"
#include "Tile.hpp"
#include "Chain.hpp"


class Level {
public:
    
    static const int NumColumns = 9;
    static const int NumRows = 9;
    
    int targetScore;
    int maximumMoves;
    
    std::vector<std::vector<Cookie*> > cookies;
    std::vector<std::vector<Tile*> > tiles;
    std::vector< Swap* > possibleSwaps;
    
    Level();  // This is the constructor
    std::vector< Cookie* > createInitialCookies();
    void detectPossibleSwaps();
    std::vector< Cookie* > shuffle();
    bool hasChainAtColumn(int col, int row);
    Cookie* createCookieAtColumn(int col, int row, int cookieType);
    Cookie* cookieAtColumn(int col, int row);
    
    static void loadJSON(const std::string& filename, Level *level);
    static Level* initWithFile(const std::string& filename);
    ::Tile* tileAtColumn(int col, int row);
    void performSwap(Swap* swap);
    bool isPossibleSwap(Swap* swap);

    std::vector< Chain* > removeMatches();
    void removeCookies(std::vector< Chain* > chains);
    std::vector< Chain* > detectHorizontalMatches();
    std::vector< Chain* > detectVerticalMatches();

    std::vector< std::vector< Cookie* > > fillHoles();
    std::vector< std::vector< Cookie* > > topUpCookies();
    
    void calculateScores(std::vector< Chain* > chains);
};

#endif /* Level_hpp */
