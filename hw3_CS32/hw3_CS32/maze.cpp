
//
// maze.cpp
//  Homework3_CS32
//
//  Created by Elon Glouberman on 2/12/18.
//  Copyright (c) 2018 Elon Glouberman. All rights reserved.
//

#include <iostream>
#include <stack>
#include <string>
#include <cassert>
using namespace std;


class Coord
{
public:
    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
    int r() const { return m_r; }
    int c() const { return m_c; }
private:
    int m_r;
    int m_c;
};


bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
{
    Coord current(sr,sc);
    Coord end(er,ec);
    if (current.r() == end.r() && current.c() == end.c()) return true;
    maze[sr][sc] = '@';

    if (maze[current.r()][current.c()+1] == '.') // if we can go east
        if (pathExists(maze,nRows,nCols, current.r(), current.c() +1, end.r(), end.c()))return true;
    if (maze[current.r()+1][current.c()] == '.') // if we can go south
        if (pathExists(maze,nRows,nCols, current.r() +1, current.c(), end.r(), end.c()))return true;
    if (maze[current.r()][current.c()-1] == '.') // if we can go west
        if (pathExists(maze,nRows,nCols, current.r(), current.c() -1, end.r(), end.c()))return true;
    if (maze[current.r()-1][current.c()] == '.') // if we can go north
        if (pathExists(maze,nRows,nCols, current.r()-1, current.c(), end.r(), end.c()))return true;

    return false;
}
