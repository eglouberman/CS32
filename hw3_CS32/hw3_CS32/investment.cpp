//
//  main.cpp
//  hw3_CS32
//
//  Created by Elon Glouberman on 2/8/18.
//  Copyright (c) 2018 Elon Glouberman. All rights reserved.
//

#include <iostream>
#include <string> 
using namespace std;


//class Investment. This is the base class for all our inheritance
class Investment
{
public:
    Investment(string name, int value) {m_name =name, m_value =value;};
    virtual bool fungible() const {return false;}// makes sure that this class cannot be allocated and instantiated
    string name() const {return m_name;};
    int purchasePrice() const {return m_value;};
    virtual string description() const = 0; // pure virtual
    virtual ~Investment(){};
    
private:
    string m_name;
    int m_value;
    
};

//class painting, a subclass of investment.
class Painting: public Investment
{
public:
    Painting(string name, int value): Investment(name,value){};
    virtual string description() const {return "painting"; };
    virtual ~Painting() {cout<< "Destroying " + name() + ", a painting" << endl;};
};

//class stock, a subclass of investment

class Stock: public Investment
{
public:
    Stock(string name, int value, string ticker): Investment(name,value) { m_ticker = ticker;};
    virtual string description() const {return "stock trading as " + m_ticker; };
    virtual bool fungible() const {return true; };
    virtual ~Stock() {cout<< "Destroying " + name() + ", a stock holding" << endl;};
private:
    string m_ticker;
};

//class House, a subclass of Investment
class House: public Investment
{
public:
    House(string name, int value): Investment(name, value) {};
    virtual string description() const {return "house"; };
    virtual ~House() {cout<< "Destroying the house " + name() << endl;};

};

//void display(const Investment* inv)
//{
//    cout << inv->name();
//    if (inv->fungible())
//        cout << " (fungible)";
//    cout << ": " << inv->description() << " bought for $" << inv->purchasePrice() << endl;
//}
//
//int main()
//{
//    Investment* portfolio[4];
//    portfolio[0] = new Painting("Salvator Mundi", 450300000);
//    // Stock holdings have a name, value, and ticker symbol
//    portfolio[1] = new Stock("Alphabet", 100000, "GOOGL");
//    portfolio[2] = new Stock("Symantec", 50000, "SYMC");
//    portfolio[3] = new House("4 Privet Drive", 660000);
//    
//    for (int k = 0; k < 4; k++)
//        display(portfolio[k]);
//    
//    // Clean up the investments before exiting
//    cout << "Cleaning up" << endl;
//    for (int k = 0; k < 4; k++)
//        delete portfolio[k];
//}

