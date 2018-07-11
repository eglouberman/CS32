#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include <string>
#include <vector>
#include <list>
#include "Actor.h"
using namespace std;
class Actor;
class NachenBlaster; 

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetDir);
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    void setText();
    void setDefaults();
    bool completedLevel() const; 
    void makeRandomStar(int x);
    void addObject(Actor* p);
    void deleteDeadActors(); 
    void addShipDestroyed() {
        shipsDestroyed++;
    };
    bool checkCollision(const Actor* a, const Actor* b) const;
    double euclidean_dist(int x1, int y1, int x2, int y2) const; 
    void addNewShip();
    bool isOnLeft(int x, int y);
    
    // If there's at least one alien that's collided with a, return
    // a pointer to one of them; otherwise, return a null pointer.
    Actor* getOneCollidingAlien(const Actor* a) const;
    
    // If the player has collided with a, return a pointer to the player;
    // otherwise, return a null pointer.
    NachenBlaster* getCollidingPlayer(const Actor* a) const;
    

    virtual ~StudentWorld();

private:
    vector<Actor*> actor_vector;
    NachenBlaster* NB;
    int shipsDestroyed;
    int aliensOnBoard;
    
};

#endif // STUDENTWORLD_H_
