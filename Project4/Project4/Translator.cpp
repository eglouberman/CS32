#include "provided.h"
#include <string>
#include <list>
#include <map>
#include <iostream>
using namespace std;

class TranslatorImpl
{
public:
    bool pushMapping(string ciphertext, string plaintext);
    bool popMapping();
    string getTranslation(const string& ciphertext) const;
private:
    list<map<char,char>> m_stack;
    map<char, char> cipherToPlain;
    map<char,char> plainToCipher;
    bool findInMapping(map<char,char> &j, char &i) const;
};

bool TranslatorImpl::pushMapping(string ciphertext, string plaintext)
{
    if (ciphertext.size()!= plaintext.size())
        return false;

    for (int i=0; i< plaintext.size(); i++)
    {
        if (findInMapping(cipherToPlain,ciphertext[i]) == false)
            return false;
        if (findInMapping(plainToCipher,plaintext[i]) == false)
            return false;
    }
    
    map<char,char> copy;
    
    for (int i=0; i < plaintext.size(); i++)
    {
        cipherToPlain[ciphertext[i]] = plaintext[i]; // we map the letters with each other.
        plainToCipher[plaintext[i]] = ciphertext[i];
        copy[ciphertext[i]] = plaintext[i];
    }
    
    m_stack.push_front(copy);
    
    
    return true;  // This compiles, but may not be correct
}


bool TranslatorImpl::findInMapping(map<char,char> &j, char &i) const
{
    if (j.find(i) != j.end())
    {
        return false;
    }
    
    if (j.find(i) == j.end())
    {
        if (i>='a' && i <='z') // we check to see if it is upper case or lower case
        {
            if(j.find(i-32) != j.end())
                return false;
        }
        if (i<= 'Z' && i>='A')
        {
            if(j.find(i+32) != j.end())
                return false;
        }
    }
    return true;
}
bool TranslatorImpl::popMapping()
{
    if (m_stack.size() ==0)
        return false;
    
    list<map<char,char>> ::iterator it = m_stack.begin();
    
    map<char,char> copy = *it; // now we should iterate through the copy to undo everything that we've done
    
    map<char,char> ::iterator it2 = copy.begin();
    while(it2!= copy.end()) // we undo the previous actions
    {
        char key = it2->first;
        char value = it2->second;
        cipherToPlain.erase(key); // we erase each of the elements in both maps.
        plainToCipher.erase(value);
        it2++;
    }
    
    m_stack.erase(it);
    
    return true;
    
    
}

string TranslatorImpl::getTranslation(const string& ciphertext) const
{
    string word = "";
    map<char,char>::const_iterator it;
    for (int i =0; i< ciphertext.size(); i++)
    {
        if ((ciphertext[i]>='A' && ciphertext[i] <= 'Z') || (ciphertext[i]>='a' && ciphertext[i] <= 'z'))
        {
            it = cipherToPlain.find(ciphertext[i]);
            if (it==cipherToPlain.cend())
            {
                if (ciphertext[i]>='a'&& ciphertext[i]<='z') // we check to see if it is upper case or lower case
                {
                    if(cipherToPlain.find(ciphertext[i]-32) != cipherToPlain.cend())
                    {
                        it =cipherToPlain.find(ciphertext[i]-32);
                        char trans =(it->second);
                        if (trans >= 'A' && trans <= 'Z')
                            trans += 32;
                        word+= trans;
                    }
                    else word += '?';
                }
                else if (ciphertext[i]<= 'Z'&& ciphertext[i]>='A')
                {
                    if(cipherToPlain.find(ciphertext[i]+32) != cipherToPlain.cend())
                    {
                        it =cipherToPlain.find(ciphertext[i]+32);
                        char trans = it->second;
                        if (trans >= 'a' && trans <= 'z')
                            trans -= 32;
                        word+= trans;
                    }
                    else word += '?';
                }
            }
            else
            {
                char trans =it->second;
                if (ciphertext[i]>='A' && ciphertext[i]<= 'Z')
                {
                    if (trans >= 'a' && trans <= 'z')
                        trans -= 32;
                }
                else if (ciphertext[i]>='a' && ciphertext[i]<= 'z')
                {
                    if (trans >= 'A' && trans <= 'Z')
                        trans += 32;
                }
                word+=trans;
            }
        }
        else{
            word += ciphertext[i];
        }
    }
    
    return word;
}

//******************** Translator functions ************************************

// These functions simply delegate to TranslatorImpl's functions.
// You probably don't want to change any of this code.

Translator::Translator()
{
    m_impl = new TranslatorImpl;
}

Translator::~Translator()
{
    delete m_impl;
}

bool Translator::pushMapping(string ciphertext, string plaintext)
{
    return m_impl->pushMapping(ciphertext, plaintext);
}

bool Translator::popMapping()
{
    return m_impl->popMapping();
}

string Translator::getTranslation(const string& ciphertext) const
{
    return m_impl->getTranslation(ciphertext);
}
