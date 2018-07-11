////
////  main.cpp
////  Homework2_CS32
////
////  Created by Elon Glouberman on 2/5/18.
////  Copyright (c) 2018 Elon Glouberman. All rights reserved.
////
//
//#include <iostream>
//#include <queue>
//#include <string>
//using namespace std;
//
//
//class Coord
//{
//public:
//    Coord(int rr, int cc) : m_r(rr), m_c(cc) {}
//    int r() const { return m_r; }
//    int c() const { return m_c; }
//private:
//    int m_r;
//    int m_c;
//};
//
//
//bool pathExists(string maze[], int nRows, int nCols, int sr, int sc, int er, int ec)
//{
//    Coord curr(sr,sc);
//    Coord end(er,ec);
//    queue <Coord> coordQueue; //declare queue of coords that we can explore
//    coordQueue.push(curr);
//    maze[sr][sc] = '@';
//    
//    while (!coordQueue.empty()){ //while queue is not empty
//        Coord current = coordQueue.front();//current location we want to explore
//        coordQueue.pop();
////        cerr<< "("<< current.r() << "," << current.c() << ")" << endl;
//        if (current.r() == end.r() && current.c() == end.c()) return true; // if we are at end, return true
//        if (maze[current.r()][current.c()+1] == '.') { // if east
//            coordQueue.push(Coord(current.r(), current.c()+1));
//            maze[current.r()][current.c()+1] = '@';
//        }
//        if (maze[current.r()+1][current.c()] == '.'){ // if we can go south
//            coordQueue.push(Coord(current.r()+1, current.c()));
//            maze[current.r()+1][current.c()] = '@';
//        }
//        if (maze[current.r()][current.c()-1] == '.'){ // if we can go west
//            coordQueue.push(Coord(current.r(), current.c()-1));
//            maze[current.r()][current.c()-1] = '@';
//        }
//        if (maze[current.r()-1][current.c()] == '.'){ // if we can go north
//            coordQueue.push(Coord(current.r()-1, current.c()));
//            maze[current.r()-1][current.c()] = '@';
//        }
//
//    }
//    
//    return false;
//}
//