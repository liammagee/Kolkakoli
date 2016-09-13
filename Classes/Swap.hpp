//
//  Swap.hpp
//  Kolkakoli
//
//  Created by Liam Magee on 30/08/2016.
//
//

#ifndef Swap_hpp
#define Swap_hpp

#include <stdio.h>
#include "Cookie.hpp"



class Swap {
public:
    Cookie* cookieA;
    Cookie* cookieB;
    
    std::string description();
    bool operator==(const Swap &other) const;
};


#endif /* Swap_hpp */
