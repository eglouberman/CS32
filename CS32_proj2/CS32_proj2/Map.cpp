//
//  Map.cpp
//  CS32_proj2
//
//  Created by Elon Glouberman on 1/25/18.
//  Copyright (c) 2018 Elon Glouberman. All rights reserved.
//

#include "Map.h"
#include <iostream>
using namespace std;

Map::Map()
{
    head = nullptr;
    m_size = 0;
    
}

Map::Map(const Map& src)
{
    m_size = src.m_size;
    head = nullptr;
    for (int i =0 ;i < src.m_size; i++)
    {
        KeyType k;
        ValueType v;
        src.get(i,k,v);
        this->insert(k,v);
    }
    
}

Map& Map:: operator= (const Map &m)
{
    if (&m == this)
        return *this;
    
    //we need to delete the current Map.
    Node* p = head;
    while (p != nullptr){
        Node* n = p->next;
        delete p;
        p=n;
    }
    p = nullptr; //good style to have this.
    
    m_size= m.m_size; // set size = to m's
    head = nullptr;
    for (int i =0 ;i < m.m_size; i++)
    {
        KeyType k;
        ValueType v;
        m.get(i,k,v);
        this->insert(k,v);
    }

    return (*this);
    
}

bool Map:: empty() const
{
    return (m_size ==0);
}

int Map:: size() const
{
    return m_size;
}

bool Map::insert(const KeyType& key, const ValueType& value)
{
    //if head is nullptr, list is empty. So we add a node to the front and link it to head (nullptr)
    if (head == nullptr){
        Node* p = new Node;
        p->key = key;
        p->value =value;
        p->next = nullptr;
        p->prev = head;
        head = p;
        m_size = 1;
        return true;
    }
    
    Node* p = head;
    while (p != nullptr){
        if (p->key == key)
            return false;
        p = p->next;
    }
    
    //At this point, if its not empty, and if it is not in the list already, we can add it to the end
   
    Node* j = head;
    while (j->next != nullptr)
    {
        j = j->next;
    }
    // we now have j at the last index. This is where we want to insert our new node.
    Node* n = new Node;
    n->key = key;
    n->value = value;
    n->next = nullptr;
    n->prev = j;
    j->next = n;
    m_size++;
    return true;
}

bool Map:: update(const KeyType& key, const ValueType& value)
{
    //only enters this loop if the list contains the current key
    if (this->contains(key))
    {
        Node* p = head;
        while (p != nullptr){
            if (p->key == key){
                p->value = value;
                return true;
            }
            p = p->next;
        }
        return true;
    }
    else return false; //otherwise we return falses
}
bool Map:: insertOrUpdate(const KeyType& key, const ValueType& value){
    //function is always going to return true
    
    // if it is currently in the map, then we update the value
    if (this->contains(key))
    {
        return this->update(key,value);
    }
    else{// else we insert it in the front
        return this->insert(key, value);
    }
}

bool Map:: erase(const KeyType& key){
    if (this -> contains(key))
    {
        Node* p = head;
        //if we are trying to erase the first object, we delete it and allocate the second object as the head
        
       
        if (p->key == key){
            if (size() ==1)
            {
                head = nullptr;
                p->prev = nullptr;
                delete p;
                p = nullptr;
                m_size--;
                return true;
            }
            p->next->prev = nullptr;
            head = p->next;
            delete p;
            p=nullptr;
            
            m_size--;
            return true;
        }
        while (p != nullptr){
            if(p != nullptr && p->next->key == key)
                break;
            p = p->next;
        }
        //if we found it!
        if (p!= nullptr)
        {
            Node* killme = p->next;
            p->next = killme->next;
            //if the item we are deleting is not the last element in the list, we update the next's previous
           if(killme->next != nullptr){
                killme->next->prev = p;
            }
           
            killme->prev = nullptr;
            killme->next = nullptr;
            delete killme;
            killme= nullptr;
            m_size--;
            return true;
        }
    }
    return false;
}

bool Map:: contains(const KeyType& key) const
{
    Node* p = head;
    while (p != nullptr){
        if (p->key == key)
            return true;
        p = p->next;
    }
    return false;
}

bool Map:: get(const KeyType& key, ValueType& value) const
{
    if (this->contains(key)){
        Node* p = head;
        while (p != nullptr){
            if (p->key == key){
                value = p->value;
                return true;
            }
            p = p->next;
        }

    }
    return false;
}

bool Map:: get(int i, KeyType& key, ValueType& value) const
{
    int count = 0;
    if (0<= i && i< this->size()){
        Node* p = head;
        while (p != nullptr){
            if (i == count){
                value = p->value;
                key = p->key;
                return true;
            }
            count++;
            p = p->next;
        }
    }
    return false;
}

void Map:: swap(Map& other)
{
    //just switch the heads!
    //also switch the sizes
    Node* temp  = head;
    head = other.head;
    other.head = temp;
    temp  = nullptr;
    
    int t = m_size;
    m_size = other.m_size;
    other.m_size = t;

}

Map::~Map()
{
    Node* p = head;
    while (p != nullptr){
        Node* n = p->next;
        delete p;
        p=n;
    }
}

//prints out the map
void Map:: dump() const{
    Node* p = head;
    while (p!= nullptr){
        std::cerr<< p->key << "->" << p->value << std::endl;
        p = p->next;
    }
}


//
//If a key appears in exactly one of m1 and m2, then result must contain a pair consisting of that key and its corresponding value.
//If a key appears in both m1 and m2, with the same corresponding value in both, then result must contain exactly one pair with that key and value.
//When this function returns, result must contain no pairs other than those required by these rules. (You must not assume result is empty when it is passed in to this function; it might not be.)
//If there exists a key that appears in both m1 and m2, but with different corresponding values, then this function returns false; if there is no key like this, the function returns true. Even if the function returns false, result must be constituted as defined by the above rules.
bool combine(const Map& m1, const Map& m2, Map& result)
{
    bool shouldreturn = true;// the default bool that it should return. 
    
    Map result1;// create a result1 to compare with result at the end of this function
    result = result1; //effectively deletes all of the current contents of result.
    
    //here, we have a double for loop to compare each key-value pair in both maps.
    for (int i = 0; i < m1.size(); i++)
    {
        KeyType k1;
        ValueType v1;
        m1.get(i,k1, v1); // we use the get function at index i to set k1 and v1 to the index of the first map
        
        for(int j = 0; j< m2.size(); j++)
        {
            
            KeyType k2;
            ValueType v2;
            
            m2.get(j,k2,v2);
            
            if (k1 == k2 && v1 != v2)// if the keys are equal, but the values are not
            {
                shouldreturn = false;
            }
            
            else if (k1 == k2 && v1 ==v2) // if both pairs are exactly the same, we add the pair to result
            {
                result.insert(k1,v1);
            }
            
            else if (k1 != k2) // if both pairs are not at all the same, we add both pairs to the new map
            {
                //if only the keys match, we dont want to include it in "result"
                if ((m1.contains(k1) && m2.contains(k1)) || (m2.contains(k2) && m1.contains(k2))){
                    continue;
                }
                result.insert(k1,v1);
                result.insert(k2,v2);
            }
            
        }
    }
        
    
    return shouldreturn;
}

void subtract(const Map& m1, const Map& m2, Map& result)
{
    
    Map result1;// create a result1 to compare with result at the end of this function
    result = result1; //effectively deletes all of the current contents of result.
    
    //Iterate through all of m1 and see if m2 has "i"
    for (int i = 0; i< m1.size(); i++)
    {
        KeyType k1;
        ValueType v1;
        m1.get(i,k1, v1);
        if (!m2.contains(k1))
            result.insert(k1,v1);
    }
    
    return;
}




