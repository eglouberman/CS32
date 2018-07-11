#include "provided.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <functional>
#include "MyHash.h"
#include <cmath>
#include <list>
using namespace std;

class WordListImpl
{
public:
    WordListImpl() {};
    bool loadWordList(string filename);
    bool contains(string word) const;
    vector<string> findCandidates(string cipherWord, string currTranslation) const;
private:
    MyHash<int, list<string>> m_hash;
    unsigned int getPattern(string word) const;  // makes a pattern for a specfic word.
};


unsigned int WordListImpl:: getPattern(string word) const
{
    vector<unsigned int> arr;
    
    for (int i = 0; i< word.size();i++)
        arr.push_back(0);
    
    int count = 1;
    for (int i =0; i< word.size(); i++){
        if (arr[i] ==0)
        {
            arr[i] = count;
            for (int j = 0; j<word.size(); j++)
            {
                if (word[j]== word[i] || (word[i]-word[j] == 32) || (word[i]-word[j] == -32))
                    arr[j] = count;
            }
            count++;
        }
    }
    unsigned int final =0;
    for (int i = 0; i< word.size(); i++)
    {
        arr[i] *= pow(10,(word.size()-i-1));
        final += arr[i];
    }
    
    return final;
}
bool WordListImpl::loadWordList(string filename)
{
    if (m_hash.getNumItems()>0) // if we have loaded a previous file
        m_hash.reset();
    ifstream ifs;
    ifs.open(filename); // file we want to open
    
    if (!ifs)
        return false;
    
    string word;
    
    while (getline(ifs, word))
    {
        bool foundNonLetter = false;
        for (int i =0; i< word.size(); i++)
        {
            if (word[i]<= 'Z' && word[i]>= 'A')
                word[i] +=32; // we convert to lower.
            if(word[i] != char(39) && (word[i]<'a' || word[i] >'z'))
            {
                foundNonLetter = true;
                break;
            }
        }
        if (foundNonLetter)
            continue;
        unsigned int code = getPattern(word);

        //find if the pattern is already in the hashmap.
        if (m_hash.find(code)!= nullptr)
        {
            list<string> *current_list = m_hash.find(code);
            list<string>:: iterator it = current_list->begin();
            while (it != current_list->end())
            {
                if (*it == word)
                    break;
                
//                if (code == 123443)
//                {
//                    cerr<<  *it << endl;
//                }
                it++;
            }

            if (it == current_list->end())
            {
                current_list->push_back(word);
//                if (code == 123443)
//                {
//                    cerr<< "Just appended " + word << endl;
//                }
                
            }
            
//            else
//                cerr<< "FAILED TO APPEND " << word << " SINCE ALREADY EXISTS" << endl;
        }
        //if pattern isnt in the hashmap, then we make a new linked list.
        else
        {
            //cerr<< "VALUE: " << word << "-->";
            list<string> string_list;
            string_list.push_back(word);
            m_hash.associate(code, string_list); // if code is already in map, then we automatically update it with the string_list that we found in the map plus the new word.
//            if (code == 123443)
//            {
//                cerr<< "Just REALLY inserted " + word << endl;
//            }
        }
    }
//
//    list<string> *cur=  m_hash.find(123443);
//    list <string> :: iterator it;
//    it = cur->begin();
//    while (it != cur->end())
//    {
//        cerr<< *it<< endl; // we copy all the words that are in the list.
//        it++;
//    }
 //  cerr<< m_hash.getNumItems();
    
    ifs.close();
    return true;
}

bool WordListImpl::contains(string word) const
{
    // or convert word to pattern and find(pattern)
    unsigned int p = getPattern(word);
    const list<string>* found=  m_hash.find(p);
    list <string> :: const_iterator it;
    if (found != nullptr)
    {
    it = found->cbegin();
    while(it!= found->cend())
    {
        if (*it == word)
            return true;
        it++;
    }
    }
    return false;
}

vector<string> WordListImpl::findCandidates(string cipherWord, string currTranslation) const
{
    for (int i =0; i< currTranslation.length(); i++)
    {
        if (currTranslation[i]>= 'A' && currTranslation[i]<='Z')
            currTranslation[i]+=32; 
    }
    vector<string> my_vec;
    if (currTranslation.size()!= cipherWord.size()) // we check if both sizes are the same.
        return my_vec;

    if (m_hash.find(getPattern(cipherWord)))
    {
        unsigned int code = getPattern(cipherWord);
        const list<string> *cur=  m_hash.find(code); // pointer to the value of the cipherWord
        list <string> :: const_iterator it;
        if (cur!= nullptr)
        {
        it = cur->cbegin();
        while (it != cur->cend())
        {
            string current_word = *it;
            bool isMatch = true;
            for (int i = 0; i< it->size(); i++)
            {
                if (currTranslation[i] != '?' && currTranslation[i] != current_word[i])
                {
                    isMatch = false;
                    break;
                }
            }
            if (isMatch)
                my_vec.push_back(current_word);
            it++;
        }
        }
    }
    return my_vec;
}

//***** hash functions for string, int, and char *****

unsigned int hash(const std::string& s)
{
    return std::hash<std::string>()(s);
}

unsigned int hash(const int& i)
{
    return std::hash<int>()(i);
}

unsigned int hash(const char& c)
{
    return std::hash<char>()(c);
}

//******************** WordList functions ************************************

// These functions simply delegate to WordListImpl's functions.
// You probably don't want to change any of this code.

WordList::WordList()
{
    m_impl = new WordListImpl;
}

WordList::~WordList()
{
    delete m_impl;
}

bool WordList::loadWordList(string filename)
{
    return m_impl->loadWordList(filename);
}

bool WordList::contains(string word) const
{
    return m_impl->contains(word);
}

vector<string> WordList::findCandidates(string cipherWord, string currTranslation) const
{
   return m_impl->findCandidates(cipherWord, currTranslation);
}

