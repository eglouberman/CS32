#include "Actor.h"
#include "StudentWorld.h"

// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp


void NachenBlaster:: doSomething()
{
    if(getAlive() == false)
        return;
    int val;
    int x = getX();
    int y = getY();
    if (getGw() ->getKey(val))
    {
        
        if ((val == KEY_PRESS_UP ||val == 'w' || val == '8') && y < 250)
            moveTo(x,y+6);
        if ((val == KEY_PRESS_DOWN||val == 's' || val == '2')  && y >6)
            moveTo(x, y-6);
        if ((val == KEY_PRESS_RIGHT||val == 'd' || val == '6')  && x<256)
            moveTo(x+6,y);
        if ((val == KEY_PRESS_LEFT||val == 'a' || val == '4')  && x!=0)
            moveTo(x-6,y);
        
        if (val == KEY_PRESS_SPACE) // fire a cabbage
        {
            if (cabbageInventory <=0){
                cabbageInventory=0;
                return;
            }
            
            if (cabbageInventory >=5){
                setCabbages(cabbageInventory-=5);
//                std::cerr<< getX() << " " << getY();
                getGw()->addObject(new Cabbage(getGw(), getX() +12, getY()));
                getGw()->playSound(SOUND_PLAYER_SHOOT);
            }
            else setCabbages(0);
            
        }
        //FIRE A TORPEDO
        if (val == KEY_PRESS_TAB)
        {
            if (flatulanceTorps>0)
            {
                flatulanceTorps--;
                getGw()->addObject(new Torpedo(getGw(),true, getX(), getY()));
                getGw()->playSound(SOUND_TORPEDO);
            }
        }
    }
}


void Star:: doSomething()
{
    

    int x = getX();
    int y = getY();
    
    moveTo(x-1, y);
    
    if (getX() < 0)
    {
        setAlive(false);
        return;
    }
}

void Projectile:: doSomething()
{
    if ((getX() >= VIEW_WIDTH) || getX() < 0)
    {
        setAlive(false);
        return;
    }
    
    collision();
    
    if (getAlive() == false)
        return;
    
    doOtherStuff();
    rotate();

    collision();
    
}


void Cabbage:: doOtherStuff()
{

    moveTo(getX()+8, getY());
    
}

void Cabbage:: collision(){
    Actor* a= getGw()-> getOneCollidingAlien(this);
    if (a!=nullptr)
    {
        a->setCabbageHit(true);
        //cerr << "HITPOINTS OF ALIEN" << a->hitPoints();
        setAlive(false);
        getGw()->playSound(SOUND_BLAST);
    }

}

void Turnip:: collision()
{
    NachenBlaster* a= getGw()-> getCollidingPlayer(this);
    if (a!=nullptr)
    {
        a->sufferDamage(2);
        //cerr << "HITPOINTS OF NB" <<a->hitPoints();
        setAlive(false);
        getGw()->playSound(SOUND_BLAST);
    }
}

void Turnip:: doOtherStuff()
{
    
    moveTo(getX()-6, getY());
    
}

void Torpedo::collision()
{
    if (isNachen)
    {
        Actor* a= getGw()-> getOneCollidingAlien(this);
        if (a!=nullptr)
        {
            a->setTorpedoHit(true);
            setAlive(false);
            getGw()->playSound(SOUND_BLAST);
        }
    }
    
    NachenBlaster* a= getGw()-> getCollidingPlayer(this);
    if (a!=nullptr)
    {
        a->sufferDamage(8);
        setAlive(false);
        getGw()->playSound(SOUND_BLAST);
    }
    return;
}
void Torpedo:: doOtherStuff()
{
    if (isNB())
    {
        moveTo(getX()+8, getY());
    }
    else
    {
        moveTo(getX()-8, getY());
    }
    
}
void Goodie:: collision()
{
    NachenBlaster* a= getGw()-> getCollidingPlayer(this);
    if (a !=nullptr)// if collided with NB!!!!!!
    {
        getGw()->increaseScore(100);
        cerr << "INCREASED SCORE BY " << 100 << " BC goodie:" << getGw()->getScore() << endl;
        setAlive(false);
        getGw()->playSound(SOUND_GOODIE);
        doOtherStuff(a);
        return;
    }
}

void Goodie:: doSomething()
{
    if (getAlive() == false)
        return;
    
    collision();
    if (getAlive()==false)
        return;
    
    moveTo(getX()-0.75, getY()-0.75);
    
    collision();
    return;
}

void ExtraLifeGoodie:: doOtherStuff(NachenBlaster* a)
{
    getGw()->incLives();
}

void RepairGoodie:: doOtherStuff(NachenBlaster* a)
{
     int x = a->hitPoints();
     if (x>40)
         a->increaseHitPoints(50);
     else a->increaseHitPoints(x+10);
}

void TorpedoGoodie:: doOtherStuff(NachenBlaster* a)
{
    int x = a->getTorps();
    a->setTorps(x+5);
}


void Alien:: checkFlightPlan()
{
    if (flight_plan ==0)
    {
        int j = randInt(1,3);
        if (j ==1) // due left
        {
            setDeltaX(-getSpeed());
            setDeltaY(0);
        }
        else if (j ==2) //up and left
        {
            setDeltaX(-getSpeed());
            setDeltaY(getSpeed());
        }
        else if (j ==3) // down and left
        {
            setDeltaX(-getSpeed());
            setDeltaY(-getSpeed());
        }
        int x  = randInt(1,32);
        flight_plan = x;
    }
    
    if (getY()>= VIEW_HEIGHT-1) // WE SET TRAVEL DIRECTION TO DOWN AND TO THE LEFT
    {
        setDeltaX(-getSpeed());
        setDeltaY(-getSpeed());
        return;
    }
    if (getY() <=0)
    {
        setDeltaX(-getSpeed());
        setDeltaY(getSpeed());
        return;
    }
}

bool Alien :: determineToShoot()
{
    if (getGw()->isOnLeft(getX(), getY()))
    {
        //1 in ((20/CurrentLevelNumber)+5)
        int currentLevel = getGw()->getLevel();
        double denom = (20/currentLevel) + 5;
        double prob= (1/denom)*100;
        int ran = randInt(1,100);
        if (prob >= ran)
        {
            getGw()->addObject(new Turnip(getGw(), getX()-14, getY()));
            getGw()->playSound(SOUND_ALIEN_SHOOT);
            return true;
        }
    }
    return false;
        
}

void Alien::collision()
{
    if (hasBeenHitByCabbageOrTurnip())
    {
        //cerr<< "THE AMOUNT OF HITPOINTS OF THIS SHIP IS: " << hitPoints() << endl;
        sufferDamage(2.0);
        //cerr<< "NOW IT HAS : " << hitPoints() << endl;
        if (hitPoints()==0)
        {
            setAlive(false);
            getGw()->addShipDestroyed();
            getGw()->increaseScore(incScoreVal);
            //cerr << "INCREASED SCORE BY " << incScoreVal << " BC CABBAGE OR TURNIP DESTROYED" << getGw()->getScore() << endl;
            getGw()->playSound(SOUND_DEATH);
            getGw()->addObject(new Explosion(getGw(), getX(),getY()));
        }
        setCabbageHit(false);
        getGw()->playSound(SOUND_BLAST);
    }
    if (hasBeenHitByTorpedo())
    {
        sufferDamage(8);
        if (hitPoints()==0)
        {
            setAlive(false);
            getGw()->addShipDestroyed();
            getGw()->increaseScore(incScoreVal);
            cerr << "INCREASED SCORE BY " << incScoreVal << " BC Torpedo:" << getGw()->getScore() << endl;
            getGw()->playSound(SOUND_DEATH);
            getGw()->addObject(new Explosion(getGw(), getX(),getY()));
        }
        setTorpedoHit(false);
        getGw()->playSound(SOUND_BLAST);
        
    }
    
    NachenBlaster* player = nullptr; // in charge of whether it collides with a player or not
    player = getGw()->getCollidingPlayer(this);
    if (player!= nullptr)
    {
        //NB suffers damage from current alien
        player->sufferDamage(m_scoreVal);
        setAlive(false);
        getGw()->addShipDestroyed();
        getGw()->increaseScore(incScoreVal);
        cerr << "INCREASED SCORE BY " << incScoreVal << " Bc collision!:" << getGw()->getScore() << endl;
        getGw()->playSound(SOUND_DEATH);
        getGw()->addObject(new Explosion(getGw(), getX(),getY()));
    }
    
    if (getAlive() ==false)
    {
        possiblyDropGoodie();
    }

}


void Alien:: doSomething()
{

    if (getAlive() == false)
        return;
    
    if (getX()<=0)
        setAlive(false);
    
    //collision function here.
    collision();
    if (getAlive()==false)
        return;
    
    checkFlightPlan();
    if (determineToShoot())
        return;
   
    move();
    flight_plan--;
    
    collision(); 
    //another collision function here. 
    
}


bool Smoregon:: determineToShoot()
{
    if (Alien::determineToShoot()) return true;
    
    if (getSpeed() == 5)
        return false;
    
    if (getGw()->isOnLeft(getX(), getY())) // if nachenblaster is on the left of the smoregon
    {
    int currentLevel = getGw()->getLevel();
    double denom = (20/currentLevel) + 5;
    double prob= (1/denom)*100;
    int ran = randInt(1,100);
    if (prob>=ran)
    {
        setSpeed(5.0);
        setDeltaX(-getSpeed());
        setDeltaY(0);
        setFlightPlan(256);
        return false;
    }
    }
    
    return false;
    
    
}

bool Snagglegon:: determineToShoot()
{
    if (getGw()->isOnLeft(getX(), getY()))
    {
        int currentLevel = getGw()->getLevel();
        double denom = (15/currentLevel) + 10;
        double prob= (1/denom)*100;
        int ran = randInt(1,100);
        if (prob >= ran)
        {
            getGw()->addObject(new Torpedo(getGw(), false, getX(), getY()));
            getGw()->playSound(SOUND_TORPEDO);
            return true;
        }
    }
    return false;
}

void Snagglegon:: possiblyDropGoodie()
{
    int prob = randInt(1,3);
    
    if (prob ==1)
    {
        int prob2 =randInt(1,2);
        if (prob2 ==1)
        {
            getGw()->addObject(new RepairGoodie(getGw(), getX(), getY()));
            return;
        }
        if (prob2 ==2)
        {
            getGw()->addObject(new TorpedoGoodie(getGw(), getX(), getY()));
            return;
        }
        
    }
}

void Smoregon:: possiblyDropGoodie()
{
    int prob = randInt(1,6);
    
    if (prob ==1)
    {
        getGw()->addObject(new ExtraLifeGoodie(getGw(),getX(),getY()));
    }
}





