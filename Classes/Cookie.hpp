//
//  Cookie.hpp
//  Kolkakoli
//
//  Created by Liam Magee on 30/08/2016.
//
//

#ifndef Cookie_hpp
#define Cookie_hpp

#include "cocos2d.h"
#include <stdio.h>

class Cookie {
public:
    static const unsigned int NumCookieTypes = 6;
    cocos2d::Sprite* sprite;
    int col;
    int row;
    int cookieType;
    
    std::string spriteName();
    std::string highlightedSpriteName();
    std::string description();
};

#endif /* Cookie_hpp */
