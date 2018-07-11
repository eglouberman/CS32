//
//  main.cpp
//  CS32_proj2
//
//  Created by Elon Glouberman on 1/25/18.
//  Copyright (c) 2018 Elon Glouberman. All rights reserved.
//

#include <iostream>
#include "Map.h"
#include <cassert>

int main() {
    // default constructor
    Map m;
    // For an empty map:
    assert(m.size() == 0);      // test size
    assert(m.empty());          // test empty
    assert(!m.erase("Ricky"));  // nothing to erase
    
    //default constructor
    Map k;
    
    assert(k.insert("Fred", 123.3)); //we insert Fred
    assert(k.erase("Fred"));//erases a map with only one item
    assert(k.insert("Fred", 123.3));
    assert(k.insert("Ethel", 456.1)); // we insert Ethel
    assert(k.size()==2); // make sure size is == 2
    assert(!k.insert("Fred", 456.1)); //Fred already exists, so this should return false
    assert(k.erase("Ethel"));  // we erase Ethel
    assert(k.size()==1); // only one element in our map
    
    // we insert two pairs
    k.insert("Lucy", 789);
    k.insert("george", 34.2);
    
    //erase first element
    assert(k.erase("Fred")); //erases "Fred", element 1
    assert(k.insert("Fred", 123.3)); // we put it back
    //erase middle element
    assert(k.erase("Lucy")); //erases "Lucy", element 2
    assert(k.insert("Lucy", 789)); // we put it back
    //erase last element
    assert(k.erase("george")); //erases "george", element 3 (last element)
    assert(k.insert("george", 34.2)); //we put it back
    
    //check contains function
    assert(k.contains("Lucy") && !k.contains("Ethel"));// make sure Lucy is in the map and Ethel doesn't exist
    
    //check update function
    assert(k.update("george", 45.7));// we change george's value from 34.2 to 45.7
    double k2; // we initialize k2 as a double
    //check if updated using "get" function
    assert(k.get("george",k2) && k2 == 45.7); // we check if george's value is changed to 45.7
    //insertOrUpdate always returns true
    assert(k.insertOrUpdate("", 45));
    assert(k.contains(""));
    assert(k.size() ==4); //size shoud be 4
    assert(k.insertOrUpdate("george", 3)); //should call the update function
    assert(k.size() ==4); //size shoud still be 4
    
    //Map m has size of 0, with no elements
    //Map k has a size of 4
    //testing swap function
    k.swap(m);
    //k should have size of 0 now
    assert(k.size() ==0);
    assert(m.size() == 4 && m.contains("george") && m.contains("Lucy") && m.contains("Fred") && m.contains(""));
    
    //testing = operator
    Map equals;
    equals = m; // we assign Map eqauls to m
    assert(equals.size() == 4 && equals.contains("george") && equals.contains("Lucy") && equals.contains("Fred") && equals.contains(""));
    
    //testing combine and subtract functions
    
    //default constructor for map c
    Map c; // initialize c with Lucy, Fred, and Ethel
    c.insert("Lucy", 789);
    c.insert("Fred", 123);
    c.insert("Ethel", 456);

    Map j; // initializing j with Lucy and Ricky
    j.insert("Lucy", 789);
    j.insert("Ricky", 321);
    
    
    assert(combine(j,c,m)); // combining should get us Fred 123, Lucy 789, Ricky 321, Ethel 456
    assert(m.size() == 4);
    assert(m.contains("Fred") && m.contains("Lucy") && m.contains("Ricky") && m.contains("Ethel"));
    
    j.update("Lucy",654);  // we update Lucy to have a different value.
    
    //m is not empty here when we pass it through combine
    assert(!combine(j,c,m) && !m.contains("Lucy")); // should return false, and Lucy should be excluded
    
    //testing the subtract function
    assert(j.update("Lucy",789));
    assert(j.insert("Ethel", 654));

    subtract(c,j,m); // this should return m with only one pair of Fred 123
    assert(m.size()==1 && m.contains("Fred")); // size is 1, with Fred being the only element in it
    
    std::cout<< "Passed all tests!" << std::endl;
    
    return 0;
}



