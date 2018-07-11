#include "StudentWorld.h"
#include "GameConstants.h"
#include "Actor.h"
#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
using namespace std;

GameWorld* createStudentWorld(string assetDir)
{
	return new StudentWorld(assetDir);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h and Actor.cpp

StudentWorld::StudentWorld(string assetDir)
: GameWorld(assetDir)
{
    shipsDestroyed = 0;
    aliensOnBoard =0; 
}

void StudentWorld:: makeRandomStar(int x)
{
    int y = randInt(0,VIEW_HEIGHT-1);
    double size = randInt(5,50);
    size = size/100;
    actor_vector.push_back(new Star(this,x,y,size));
}

void StudentWorld:: setText()
{
    ostringstream oss;
    double health = NB->hitPoints();
    health = (health/50)*100;
    int width =5;
    if (health==100)
        width = 6;
    else if (health <10)
        width = 4;
    double cabbages = NB->get_cabbageInt();
    cabbages = (cabbages/30)*100;
    int width2 = 5;
    if (cabbages ==100)
        width2 = 6;
    else if (cabbages< 10)
        width= 4;

    oss<< "Lives:"<< setw(3) << getLives() << setw(9)<< "Health:" << "  " << health <<"%"<< setw(8)<< "Score:"<<"  "<< getScore() << "  "<< "Level:" << setw(3)<< getLevel() <<setw(11)<< "Cabbages:" << setw(width2-1) << int(cabbages) << "%"<< setw(11)<< "Torpedos:" << "  " << NB->getTorps();
    string text = oss.str();
    setGameStatText(text);
}

void StudentWorld:: setDefaults()
{
    NB->setAlive(true);
    NB->increaseHitPoints(50);
    NB->setTorps(0);
    NB->setCabbages(30);
    shipsDestroyed = 0;
    aliensOnBoard =0;
    
}

bool StudentWorld:: completedLevel() const
{
    int D = shipsDestroyed;
    int T = 6 + (4*getLevel());
    int R = T-D;
    
    if (R<=0)
        return true;
    
    return false;
}

void StudentWorld:: addObject(Actor* p)
{
    actor_vector.push_back(p);
}

double StudentWorld:: euclidean_dist(int x1, int y1, int x2, int y2) const
{
    double distance = 0.0;
    double dist_x = x2-x1;
    double dist_y = y2-y1;
    
    dist_x = dist_x* dist_x;
    dist_y = dist_y*dist_y;
    
    distance = sqrt(dist_x + dist_y);
    
    return distance;
    
}


void StudentWorld:: addNewShip()
{
    int D = shipsDestroyed;
    int T = 6 + (4*getLevel());
    int R = T-D;
    int M = 4 + (.5 * getLevel());

    
    if (aliensOnBoard < min(M,R))
    {
        
        double S1 = 60;
        double S2 = 20 + (getLevel() * 5);
        double S3 = 5 + (getLevel() * 10);
        double S = S1+S2+S3;
        
        double prob = randInt(1,S);
        
//        cerr<< "S1:" << s1prob <<endl;
//        cerr<< "S2: " << s2prob << endl;
//        cerr << "S3:" << s3prob << endl;
        
//        cerr<< prob << endl;
        if (prob<=S1)
        {
            int startx = VIEW_WIDTH-1;
            double health_level = 5 * (1 + (getLevel()- 1) * .1);
            int starty = randInt(1, VIEW_HEIGHT-1);
            addObject(new Smallgon(health_level,this,startx,starty));
            //cerr << "created Smallgon" << endl;
            aliensOnBoard++;
        }
        
            //create smallgon
        else if (prob > S1 && prob <= (S1+S2)){
            double health_level = 5 * (1 + (getLevel()- 1) * .1);
            int startx = VIEW_WIDTH-1;
            int starty = randInt(1, VIEW_HEIGHT-1);
            addObject(new Smoregon(health_level,this,startx,starty));
            //cerr << "created smoregon" <<endl;
            aliensOnBoard++;
        }
            //create smoregon
        else if(prob>(S1+S2)){
            double health_level = 10 * (1 + (getLevel()- 1) * .1);
            int startx = VIEW_WIDTH-1;
            int starty = randInt(1, VIEW_HEIGHT-1);
            addObject(new Snagglegon(health_level,this,startx,starty));
           // cerr << "created snagglegon" <<endl;
            aliensOnBoard++;
        }
            //create snagglegon
    }
}

bool StudentWorld:: isOnLeft(int x, int y)
{
    if (NB->getX()<= x && abs(NB->getY()-y) <=4)
        return true;
    else return false; 
}

bool StudentWorld:: checkCollision(const Actor *a, const Actor *b) const
{
    if ((euclidean_dist(a->getX(), a->getY(), b->getX(), b->getY())) < (0.75 * (a->getRadius()+ b->getRadius())))
    {
        return true;
    }
    
    else return false;
}

NachenBlaster* StudentWorld:: getCollidingPlayer(const Actor* a) const
{
    if (checkCollision(a, NB))
        return NB; 

    return nullptr;
}

Actor* StudentWorld:: getOneCollidingAlien(const Actor* a) const
{
    for (int i= 0; i< actor_vector.size(); i++)
    {
        if (actor_vector[i]->isDamageableObject() && actor_vector[i]->isAlien())
        {
            if (checkCollision(a,actor_vector[i]))
                return actor_vector[i];
        }
    }
    
    return nullptr;
}

void StudentWorld:: deleteDeadActors()
{
    for (int i = 0; i < actor_vector.size(); i++)
    {
        if (actor_vector[i]->getX() <0 || actor_vector[i]->getX()>VIEW_WIDTH || actor_vector[i]->getAlive()==false){
            if (actor_vector[i]->isAlien())
            {
                aliensOnBoard--;
            }
            
            delete actor_vector[i];
            //            cerr<< "deleted";
            actor_vector.erase(actor_vector.begin() +i); // if pos is <0, erase from vector
            i--;
        }
    }

}


int StudentWorld::init()
{
    NB = new NachenBlaster(this);
    for (int i= 0; i<30; i ++)
    {
       makeRandomStar(randInt(0,VIEW_WIDTH-1));
    }
    
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    //asks each actor to do something , move themselves or do behavior. disposes actors that need to dissapear during a given tick. Auto called once during each tick of the game.
    if (NB->hitPoints() ==0)
        setDefaults();

    if (NB->get_cabbageInt()<=0) NB->setCabbages(1);
    else NB->setCabbages(NB->get_cabbageInt()+1);
    NB->doSomething();
    
    int count = 0;
    for (int i= 0; i < actor_vector.size(); i++)
    {

        if (actor_vector[i]->getAlive() == true)
        {
            actor_vector[i]->doSomething();
//            cerr << "just moved!";
            if (actor_vector[i]->isAlien())
                count++;
        }
        
        if (NB->hitPoints() == 0)
        {
            if (getLives()>0)
                decLives();
            //cerr<< NB->hitPoints();
            aliensOnBoard =0;
            shipsDestroyed =0;
            return GWSTATUS_PLAYER_DIED;
        }
        
        
        if (completedLevel()) // if we completed the level
        {
            //increase score appropriately
            
            shipsDestroyed = 0;
            return GWSTATUS_FINISHED_LEVEL;
        }
        
    }
    
    deleteDeadActors();
    
    aliensOnBoard = count;
    
    //remove newly-dead game objects

    
    if (randInt(1,15) ==1)
        makeRandomStar(VIEW_WIDTH-1);
    
    setText();
    addNewShip();
    return GWSTATUS_CONTINUE_GAME;
}

//called when completed a level. Frees all actors and objects that are in the game. 
void StudentWorld::cleanUp()
{
    if (NB!= nullptr)
    {
        delete NB;
        NB = nullptr;
    }
    
    for (int i = 0; i<actor_vector.size(); i++)
    {
        delete actor_vector[i];
        actor_vector.erase(actor_vector.begin() +i); // if pos is <0, erase from vector
        i--;
    }
    
}

 StudentWorld:: ~StudentWorld()
{
    cleanUp();
}
