//
//  Flatulan.h
//  CS31_proj1
//
//  Created by Elon Glouberman on 1/11/18.
//  Copyright (c) 2018 Elon Glouberman PIC10b. All rights reserved.
//



#ifndef CS31_proj1_Flatulan_h
#define CS31_proj1_Flatulan_h
#include "globals.h"

class City;  // This is needed to let the compiler know that City is a
// type name, since it's mentioned in the Flatulan declaration.


class Flatulan
{
public:
    // Constructor
    Flatulan(City* cp, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    
    // Mutators
    void move();
    bool possiblyGetConverted();
    
private:
    City* m_city;
    int   m_row;
    int   m_col;
};



#endif
