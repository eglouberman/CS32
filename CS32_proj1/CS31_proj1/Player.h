//
//  Player.h
//  CS31_proj1
//
//  Created by Elon Glouberman on 1/11/18.
//  Copyright (c) 2018 Elon Glouberman PIC10b. All rights reserved.
//

#ifndef __CS31_proj1__Player__
#define __CS31_proj1__Player__

#include <stdio.h>

#include "globals.h"
class City;

class Player
{
public:
    // Constructor
    Player(City *cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    int  health() const;
    bool isPassedOut() const;
    
    // Mutators
    void  preach();
    void  move(int dir);
    void  getGassed();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
    int   m_health;
    int   m_age;
};

#endif /* defined(__CS31_proj1__Player__) */
