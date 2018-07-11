//
//  History.cpp
//  CS31_proj1
//
//  Created by Elon Glouberman on 1/11/18.
//  Copyright (c) 2018 Elon Glouberman PIC10b. All rights reserved.
//

#include "History.h"
using namespace std; 

History:: History (int nRows, int nCols){
    m_rows = nRows;
    m_cols = nCols;
    for (int i =0; i< m_rows; i ++){
        for(int j= 0; j< m_cols; j++){
            coordinatesToMark[i][j] = 64;
        }
    }
    
}

bool History:: record(int r, int c){
    if (r> m_rows || c > m_cols){
        return false;
    }
    else {
        coordinatesToMark[r-1][c-1] +=1;
        return true;
    }
}

void History:: display() const{
    clearScreen();
    // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill the grid with dots
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
        {
            if(coordinatesToMark[r][c] > 64 && coordinatesToMark[r][c] < 'Z'){
                grid[r][c] = char(coordinatesToMark[r][c]);
            }
            else if(coordinatesToMark[r][c] >= 'Z'){
                grid[r][c] = 'Z';
            }
            else{
                grid[r][c] = '.';
            }
        }
    }
    
    for (r = 0; r < m_rows; r++)
    {
        for (c = 0; c < m_cols; c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

    
}
