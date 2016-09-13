//
//  Cookie.cpp
//  Kolkakoli
//
//  Created by Liam Magee on 30/08/2016.
//
//

#include "Cookie.hpp"

namespace std {
    template <> struct hash<Cookie> {
        std::size_t operator()(const Cookie& o) const {
            std::size_t h = o.row * 1000000 + o.col;
            return h;
        }
    };
}

std::string Cookie::spriteName(){
    std::vector<std::string> spriteNames = {
        "Sprites/Croissant.png",
        "Sprites/Cupcake.png",
        "Sprites/Danish.png",
        "Sprites/Donut.png",
        "Sprites/Macaroon.png",
        "Sprites/SugarCookie.png",
    };
    
    return spriteNames[cookieType - 1];
};

std::string Cookie::highlightedSpriteName() {
    std::vector<std::string>  highlightedSpriteNames = {
        "Sprites/Croissant-Highlighted.png",
        "Sprites/Cupcake-Highlighted.png",
        "Sprites/Danish-Highlighted.png",
        "Sprites/Donut-Highlighted.png",
        "Sprites/Macaroon-Highlighted.png",
        "Sprites/SugarCookie-Highlighted.png",
    };
    
    return highlightedSpriteNames[cookieType - 1];
};

std::string Cookie::description() {
    return "";
    //return [NSString stringWithFormat:@"type:%ld square:(%ld,%ld)", (long)self.cookieType, (long)self.column, (long)self.row];
};
