////
//
////  Map.cpp
//
////  CS31_HW1
//
////
//
////  Created by Elon Glouberman on 1/17/18.
//
////  Copyright (c) 2018 Elon Glouberman PIC10b. All rights reserved.
//
////
//
//
//
//#include "Map.h"
//
//#include <iostream>
//using namespace std;
//
//
//
//// Create an empty map (i.e., one with no key/value pairs)
//
//Map::Map() {
//
//    m_size =0;
//
//}
//
//
//
//// Return true if the map is empty, otherwise false.
//
//bool Map::empty() const{
//
//    return (m_size == 0);
//
//}
//
//
//// Return the number of key/value pairs in the map.
//
//int Map:: size() const
//
//{
//
//    return m_size;
//
//}
//
//
//
//// If key is not equal to any key currently in the map, and if the
//
//// key/value pair can be added to the map, then do so and return true.
//
//// Otherwise, make no change to the map and return false (indicating
//
//// that either the key is already in the map, or the map has a fixed
//
//// capacity and is full).
//
//bool Map::insert(const KeyType& key, const ValueType& value){
//    if (m_size == 0){
//        m_size = 1;
//        mapArray[0].key = key;
//        mapArray[0].value = value;
//        return true;
//
//    }
//
//    for (int i =0; i< m_size; i++)
//
//    {
//
//        if (key == mapArray[i].key)
//            return false;
//    }
//
//    mapArray[m_size].key = key;
//    mapArray[m_size].value = value;
//
//    m_size++;
//
//    return true;
//}
//
//
//
//
//
//// If key is equal to a key currently in the map, then make that key no
//
//// longer map to the value it currently maps to, but instead map to
//
//// the value of the second parameter; return true in this case.
//
//// Otherwise, make no change to the map and return false.
//
//bool Map::update(const KeyType& key, const ValueType& value){
//
//    for (int i =0; i< m_size; i++)
//
//    {
//
//        if (key == mapArray[i].key){
//
//            mapArray[i].value = value;
//
//            return true;
//
//        }
//
//    }
//
//    return false;
//
//}
//
//
//
//// If key is equal to a key currently in the map, then make that key no
//
//// longer map to the value it currently maps to, but instead map to
//
//// the value of the second parameter; return true in this case.
//
//// If key is not equal to any key currently in the map and if the
//
//// key/value pair can be added to the map, then do so and return true.
//
//// Otherwise, make no change to the map and return false (indicating
//
//// that the key is not already in the map and the map has a fixed
//
//// capacity and is full).
//
//bool Map::insertOrUpdate(const KeyType& key, const ValueType& value)
//
//{
//
//    if (this->contains(key))
//
//    {
//
//        this->update(key, value);
//
//        return true;
//
//    }
//
//    else if (this->size() <250){
//
//        this->insert(key,value);
//
//        return true;
//
//    }
//
//    else
//
//    {
//
//        return false;
//
//    }
//
//}
//
//
//
//void Map::dump() const{
//
//    for (int i = 0; i< m_size; i++){
//
//        std::cerr<< mapArray[i].key;
//
//        std::cerr<< "-> " << mapArray[i].value << std::endl;
//
//    }
//
//}
//
//
//
//// If key is equal to a key currently in the map, remove the key/value
//
//// pair with that key from the map and return true.  Otherwise, make
//
//// no change to the map and return false.
//
//bool Map::erase(const KeyType& key){
//
//
//    int index = 250;
//
//    for (int i = 0; i< m_size; i++)
//
//    {
//
//        if (mapArray[i].key == key){
//
//            index = i;
//
//        }
//
//    }
//
//    for (int j = index; j < m_size; j++){
//
//        mapArray[j]= mapArray[j+1];
//
//    }
//
//
//    m_size--;
//
//    return true;
//
//}
//
//
//
//
//
//// Return true if key is equal to a key currently in the map, otherwise
//
//// false.
//
//bool Map::contains(const KeyType& key) const{
//
//    for (int i =0; i< m_size; i++){
//
//        if (mapArray[i].key == key){
//
//            return true;
//
//        }
//    }
//
//    return false;
//
//}
//
//
//
//// If key is equal to a key currently in the map, set value to the
//
//// value in the map that that key maps to, and return true.  Otherwise,
//
//// make no change to the value parameter of this function and return
//
//// false.
//
//bool Map::get(const KeyType& key, ValueType& value) const{
//
//    for (int i =0; i < m_size; i++){
//
//        if (mapArray[i].key == key){
//
//            value = mapArray[i].value;
//
//            return true;
//
//        }
//
//    }
//
//    return false;
//
//}
//
//
//
//// If 0 <= i < size(), copy into the key and value parameters the
//
//// key and value of one of the key/value pairs in the map and return
//
//// true.  Otherwise, leave the key and value parameters unchanged and
//
//// return false.  (See below for details about this function.)
//
//bool Map:: get(int i, KeyType& key, ValueType& value) const{
//
//    if (0<=i && i < this->size())
//
//    {
//
//        key = mapArray[i].key;
//
//        value = mapArray[i].value;
//
//        return true;
//
//    }
//
//    else return false;
//
//}
//
//
//
//// Exchange the contents of this map with the other one.
//
//void Map::swap(Map& other){
//
//    Map temp = *this;
//    *this = other;
//    other = temp;
//
//}
//
//
//Map::~Map(){
//
//}
//
//
//
//
//
//
//
//
//
