//
//  Chain.hpp
//  Kolkakoli
//
//  Created by Liam Magee on 11/09/2016.
//
//

#ifndef Chain_hpp
#define Chain_hpp

#include <stdio.h>
#include "Cookie.hpp"

enum ChainType {
    ChainTypeHorizontal = 0,
    ChainTypeVertical = 1
};

class Chain {
public:
    std::vector<Cookie*> cookies;
    ChainType chainType;
    int score;
    
    void addCookie(Cookie* cookie);
};

#endif /* Chain_hpp */
