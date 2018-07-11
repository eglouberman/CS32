#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
#include "GameConstants.h"
#include <iostream>
class Projectile;
class Cabbage;
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp

class Actor: public GraphObject
{
public:
    Actor(StudentWorld* g, int id, int x, int y, int dir, double size, int dep): GraphObject(id,x,y, dir, size,dep) {
        isAlive = true;
        collided = false;
        torpHit = false;
        m_gw = g;
    };
    StudentWorld* getGw() {return m_gw;};
    virtual void doSomething() = 0;
    virtual ~Actor(){};
    void setAlive(bool val) {isAlive = val;};
    bool getAlive() {return isAlive; };
    virtual bool isAlien() { return false; };
    bool hasBeenHitByCabbageOrTurnip() {return collided; };
    bool hasBeenHitByTorpedo() {return torpHit;};
    void setTorpedoHit(bool x) {torpHit = x;};
    void setCabbageHit(bool x) {collided = x;};
    virtual void collision(){};

    virtual bool isDamageableObject() const {return false;};

private:
    bool isAlive;
    bool collided;
    bool torpHit;
    StudentWorld* m_gw;
    
};

class DamageableObject : public Actor
{
public:
    DamageableObject(double hitPoints, StudentWorld* g, int imageID, int startX, int startY,int dir, double size, int dep): Actor(g,imageID, startX, startY, dir, size, dep)
    {
        hitP = hitPoints;
    };
    
    // How many hit points does this actor have left?
    double hitPoints() const {return hitP;};
    
    virtual bool isDamageableObject() const {return true;};
    
    // Increase this actor's hit points by amt.
    void increaseHitPoints(double amt) {hitP =amt; };
    
    // This actor suffers an amount of damage caused by being hit by either
    // a ship or a projectile (see constants above).
    virtual void sufferDamage(double amt){
        if (amt <= hitP)
            hitP -= amt;
        else if (amt >hitP)
            hitP = 0;
        
        if (hitP <=0)
        {
            setAlive(false);
        }
    };
private:
    double hitP;
};


//NACHENBLASTER CLASS
class NachenBlaster: public DamageableObject
{
public:
    NachenBlaster( StudentWorld* g,int id = IID_NACHENBLASTER , double hitPoints =50,int x = 0, int y =128, int dir = 0, double size = 1.0, int depth =0): DamageableObject(hitPoints,g,id,x,y,dir,size, depth)
    {
        cabbageInventory =30;
        flatulanceTorps = 0;
    };
    virtual void doSomething();
    int get_cabbageInt() {return cabbageInventory;};
    void setCabbages(int x) {if (x<=30 && x>0) cabbageInventory = x;}
    int getTorps() {return flatulanceTorps;};
    void setTorps(int x) {flatulanceTorps = x;};
private:
    int cabbageInventory;
    int flatulanceTorps;
};

//STAR CLASS
class Star: public Actor
{
public:
    Star(StudentWorld* g,int x, int y,double size, int id = IID_STAR, int dir =0 , int depth =3): Actor(g,id,x,y,dir,size,depth){};
    virtual void doSomething(); //should move one pixel to the left
    virtual ~Star(){};
};
//EXPLOSION CLASS
class Explosion: public Actor{
public:
    Explosion(StudentWorld* g, int x, int y, int id = IID_EXPLOSION, int dir = 0, double size = 1, int dep = 0):Actor (g,id,x,y,dir,size,dep){};
    virtual void doSomething(){
        if (getAlive() == false)
            return;
        double s = getSize();
        if (s >= 3.370)
        {
            setAlive(false);
            return;
        }
        else setSize(s*1.5);
    };

};
//PROJECTILE CLASS
class Projectile: public Actor
{
public:
    Projectile(StudentWorld*g, int x, int y, int id, int dir =0, double size =0.5, int depth=1):Actor(g,id, x,y, dir, size, depth)
    {};
    virtual void rotate(){
        int x = getDirection();
        setDirection(x+20);
    };
    virtual void collision(){};
    virtual void doSomething();
private:
    virtual void doOtherStuff() = 0;

};

//CABBAGE CLASS
class Cabbage: public Projectile
{
public:
    Cabbage(StudentWorld* g, int x, int y,int id = IID_CABBAGE):Projectile(g,x,y,id)
    {
//        std::cerr<< "created Cabbage";
//        std::cerr<< getX() << " " << getY(); 
    };
    virtual void collision();
private:
    virtual void doOtherStuff(); 
};


//TURNIP CLASS
class Turnip: public Projectile
{
public:
    Turnip(StudentWorld* g, int x, int y, int id = IID_TURNIP):Projectile(g,x,y,id)
    {};
    virtual void collision();
private:
    virtual void doOtherStuff();
};

//TORPEDO CLASS
class Torpedo: public Projectile
{
public:
    Torpedo(StudentWorld* g, bool isN, int x, int y,int id = IID_TORPEDO):Projectile(g,x,y,id)
    {
        moveTo(getX()+14, getY()); // we assume its a NachenBlaster's torpedo
    if (isN)
        isNachen = true;
    else
    {
        isNachen = false;
        setDirection(180);
        moveTo(getX()-28, getY());  // we move it to the left of the ship that is firing it.
    }
    };
    virtual void collision(); 
    bool isNB() {return isNachen;};
    virtual void rotate() {return;};
private:
    virtual void doOtherStuff();
    bool isNachen;
};

//GOODIE
class Goodie: public Actor
{
public:
    Goodie(StudentWorld* g,int x, int y, int id, int dir =0, double size =0.5, int dep =1):Actor(g,id,x,y,dir,size,dep){
        setSize(0.5);
    };
    virtual void doSomething();
    virtual void collision();
    
private:
    virtual void doOtherStuff(NachenBlaster* b)=0;
};

//EXTRA LIFE GOODIE
class ExtraLifeGoodie: public Goodie
{
public:
    ExtraLifeGoodie(StudentWorld* g, int x, int y, int id = IID_LIFE_GOODIE): Goodie(g,x,y,id){};
private:
    virtual void doOtherStuff(NachenBlaster* a);
};

//REPAIR LIFE GOODIE
class RepairGoodie: public Goodie
{
public:
    RepairGoodie(StudentWorld* g, int x, int y, int id = IID_REPAIR_GOODIE): Goodie(g,x,y,id){};
private:
    virtual void doOtherStuff(NachenBlaster* a);
};

//FLATULANCE TORPEDO GOODIE
class TorpedoGoodie: public Goodie
{
public:
    TorpedoGoodie(StudentWorld* g, int x, int y, int id = IID_TORPEDO_GOODIE): Goodie(g,x,y,id){};
private:
    virtual void doOtherStuff(NachenBlaster* a);
};

//ALIEN CLASS
/////
///


class Alien: public DamageableObject
{
public:
    Alien(double speed, unsigned int scoreVal, double hitPoints,StudentWorld* g,int id, int x, int y,int dir =0, double size =1.5, int depth=1):DamageableObject(hitPoints,g,id,x,y,dir, size, depth)
    {
        m_speed = speed;
        m_scoreVal = 5;
        m_deltaX = speed;
        m_deltaY = speed;
        flight_plan = 0;
        incScoreVal =250;
        
       // std::cerr<< "ALIEN OBJECT DEPTH:" << depth << std::endl;
    };
    virtual void doSomething();
    //virtual void collisionAction()= 0;
    //virtual void sufferDamage(double amt, int cause);
    bool isAlien() {return true; };
    virtual void collision(); 
    void setDeltaY(double dy) {m_deltaY = dy; };
    void setDeltaX(double dx){m_deltaX = dx;};
    double getDeltaX() {return m_deltaX;};
    double getDeltaY() {return m_deltaY;};
    void setSpeed(double speed) {m_speed = speed;};
    double getSpeed() {return m_speed;};
    void setScoreVal(int n) {m_scoreVal =n;};
    void setIncVal(int n) {incScoreVal =n;};
    void move() {moveTo(getX()+ m_deltaX, getY()+ m_deltaY);};
    
    // If this alien collided with the player, damage the player and return
    // true; otherwise, return false.
    //virtual bool damageCollidingPlayer(double amt);
    virtual void possiblyDropGoodie(){};
    virtual bool determineToShoot();
    virtual void checkFlightPlan();
    void setFlightPlan(int x) {flight_plan = x; };
    int getFlightPlan() {return flight_plan;};
private:
    double m_speed;
    unsigned int m_scoreVal;
    double m_deltaY;
    double m_deltaX;
    unsigned int incScoreVal;
    int flight_plan;
    
};

class Smallgon: public Alien
{
public:
    Smallgon(double hitPoints, StudentWorld*g, int x, int y, int id = IID_SMALLGON,unsigned int scoreVal=0,double speed = 2.0,double dx = 2.0, double dy =2.0): Alien(speed,scoreVal,hitPoints,g,id,x,y)
    {
        //std:: cerr << x <<" "<< y << id << std::endl;
    };
    //virtual void checkFlightPlan();
    
    
    
private:
    
};

class Smoregon: public Alien
{
public:
    Smoregon(double hitPoints, StudentWorld*g, int x, int y, int id = IID_SMOREGON,unsigned int scoreVal=0,double speed = 2.0,double dx = 2.0, double dy =2.0): Alien(speed,scoreVal,hitPoints,g,id,x,y)
    {};
    virtual bool determineToShoot();
    virtual void possiblyDropGoodie();
    
};


class Snagglegon: public Alien
{
public:
    Snagglegon(double hitPoints, StudentWorld*g, int x, int y, int id = IID_SNAGGLEGON,unsigned int scoreVal=0,double speed = 1.75,double dx = 2.0, double dy =2.0): Alien(speed,scoreVal,hitPoints,g,id,x,y)
    {
        setDeltaX(-getSpeed());
        setDeltaY(-getSpeed());
        setScoreVal(15);
        setIncVal(1000);
    }
    virtual void checkFlightPlan()
    {
       
        if (getY()>= VIEW_HEIGHT-1) // WE SET TRAVEL DIRECTION TO DOWN AND TO THE LEFT
        {
            setDeltaX(-getSpeed());
            setDeltaY(-getSpeed());
        }
        else if (getY() <=0)
        {
            setDeltaX(-getSpeed());
            setDeltaY(getSpeed());
        }

    };
    virtual bool determineToShoot();
    virtual void possiblyDropGoodie(); 
    
private:

    
    
};




#endif // ACTOR_H_
