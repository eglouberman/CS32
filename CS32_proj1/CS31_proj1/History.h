//
//  History.h
//  CS31_proj1
//
//  Created by Elon Glouberman on 1/11/18.
//  Copyright (c) 2018 Elon Glouberman PIC10b. All rights reserved.
//

#ifndef __CS31_proj1__History__
#define __CS31_proj1__History__

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;

private:
    int m_rows;
    int m_cols;
    int coordinatesToMark[MAXROWS][MAXCOLS];
};

#endif /* defined(__CS31_proj1__History__) */
