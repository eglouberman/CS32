//
//  Map.h
//  CS32_proj2
//
//  Created by Elon Glouberman on 1/25/18.
//  Copyright (c) 2018 Elon Glouberman. All rights reserved.
//

#ifndef __CS32_proj2__Map__
#define __CS32_proj2__Map__

#include <stdio.h>
#include <string>
using KeyType = std::string;
using ValueType = double;

class Map
{
public:
    Map();
    ~Map();
    Map(const Map& src);
    Map& operator= (const Map &m);
    bool empty() const;
    int size() const;
    bool insert(const KeyType& key, const ValueType& value);
    bool update(const KeyType& key, const ValueType& value);
    bool insertOrUpdate(const KeyType& key, const ValueType& value);
    bool erase(const KeyType& key);
    bool contains(const KeyType& key) const;
    bool get(const KeyType& key, ValueType& value) const;
    bool get(int i, KeyType& key, ValueType& value) const;
    void swap(Map& other);
    void dump() const; 

private:
    struct Node{
        KeyType key;
        ValueType value;
        Node* next;
        Node* prev;
    };
    
    Node* head;
    int m_size;
};

bool combine(const Map& m1, const Map& m2, Map& result);
void subtract(const Map& m1, const Map& m2, Map& result);



#endif /* defined(__CS32_proj2__Map__) */
