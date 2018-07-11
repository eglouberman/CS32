//
//  CarMap.cpp
//  CS31_HW1
//
//  Created by Elon Glouberman on 1/21/18.
//  Copyright (c) 2018 Elon Glouberman PIC10b. All rights reserved.
//

#include "CarMap.h"
#include <iostream>

CarMap:: CarMap(){
}

// If a car with the given license plate is not currently in the map,
// and there is room in the map, add an entry for that car recording
// that it has 0 gallons of gas in it, and return true.  Otherwise,
// make no change to the map and return false.
bool CarMap:: addCar(std::string license){
    if (m_carMap.insert(license, 0)){
        return true;
    }
    else return false;
}


// If a car with the given license plate is in the map, return the
// number of gallons of gas in its tank; otherwise, return -1.
double CarMap:: gas(std::string license) const{
    double gas = -1.0;
    if (m_carMap.contains(license)){
        m_carMap.get(license, gas);
    }
    return gas;
}


// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, increase the number of gallons of gas in the
// indicated car by the gallons parameter and return true.
bool CarMap:: addGas(std::string license, double gallons){
    double gals = gallons;
    
    if (!m_carMap.contains(license) || gallons < 0){
        return false;
    }
    else {
        m_carMap.get(license, gallons);
        gals += gallons;
        m_carMap.update(license, gals);
        return true;
    }
    
}


// If no car with the given license plate is in the map or if
// gallons is negative, make no change to the map and return
// false.  Otherwise, decrease the number of gallons of gas in the
// indicated car by the gallons parameter and return true.
bool CarMap:: useGas(std::string license, double gallons){
    if (!m_carMap.contains(license) || gallons < 0)
        return false;
    double gals = 0.0;
    m_carMap.get(license,gals);
    gals -= gallons;
    if (gals<0){
        gals = gallons;
        return false;
    }
    m_carMap.update(license, gals);
    return true;
    
}

// Return the number of cars in the CarMap.
int CarMap:: fleetSize() const{
    return m_carMap.size();
    
}

// Write to cout one line for every car in the map.  Each line
// consists of the car's license plate, followed by one space,
// followed by the number of gallons in that car's tank.  Write
// no other text.
void CarMap:: print() const{
    for (int i = 0; i< m_carMap.size(); i++)
    {
        std::string k;
        double v;
        m_carMap.get(i, k, v);
        std::cout << k +  " " << v << std::endl;
    }
}

