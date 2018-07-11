#include <iostream>
#include "Map.h"
#include "CarMap.h"
#include<cassert>
using namespace std;

int main ()
{
    CarMap myCars; //checking with car map class
    
    CarMap ride;
    
    string car1 = "Mercedes";
    string car2 = "Lexus";
    string car3 = "Jag";
    string car4 = "BMW";
    ride.addCar(car1);
    ride.print();
    ride.addGas(car1, 69.0);
    ride.useGas(car1,5);
    //ride.useGas(car1,65.0);
    //cout << ride.fleetSize();
    ride.addCar(car2);
    ride.addCar(car3);
    ride.addCar(car4);
    ride.addGas(car2, 609);
    //cout<< ride.fleetSize();
    ride.print();
    
    myCars.addCar("A");
    myCars.addCar("B");
    myCars.addCar("C");
    myCars.addCar("D");
    assert(myCars.gas("A")==0);
    assert(myCars.gas("B")==0);
    assert(myCars.gas("C")==0);
    assert(myCars.gas("D")==0);
    
    myCars.addGas("A", 1);
    myCars.addGas("B", 2);
    myCars.addGas("C", 3);
    myCars.addGas("d", 2);
    assert(myCars.gas("A")==1);
    assert(myCars.gas("B")==2);
    assert(myCars.gas("C")==3);
    assert(myCars.gas("D")==0);
    
    myCars.useGas("A", 20);
    myCars.useGas("C", 2);
    myCars.useGas("F", 3);
    assert(myCars.gas("A")==1);
    assert(myCars.gas("B")==2);
    assert(myCars.gas("C")==1);
    assert(myCars.gas("D")==0);
    
    assert (myCars.fleetSize()==4);
    
    Map a;
    Map b;
    a.insert("A", 1);
    a.insert("B", 2);
    a.insert("C", 3);
    
    
    b.insert("D", 4);
    b.insert("E", 5);
    
    
    KeyType one;
    ValueType two;
    a.swap(b);
    
    a.get(1, one, two);
    assert(one=="E" && two==5);
    assert (a.size()==2);
    one="K";
    two=5;
    
    b.get(0, one, two);
    assert(one=="A" && two==1);
    b.get(2, one, two);
    assert(one=="C" && two==3);
    
    one="B";
    two=5;
    assert(b.insertOrUpdate(one, two));
    b.get("B", two);
    assert(two==5);

}


