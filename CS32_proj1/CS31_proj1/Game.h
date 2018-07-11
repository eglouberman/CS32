//
//  Game.h
//  CS31_proj1
//
//  Created by Elon Glouberman on 1/11/18.
//  Copyright (c) 2018 Elon Glouberman PIC10b. All rights reserved.
//

#ifndef __CS31_proj1__Game__
#define __CS31_proj1__Game__

#include <stdio.h>
#include "globals.h"
#include "City.h"

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nFlatulans);
    ~Game();
    
    // Mutators
    void play();
    
private:
    City* m_city;
};


#endif /* defined(__CS31_proj1__Game__) */
