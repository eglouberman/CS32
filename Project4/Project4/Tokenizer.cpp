#include "provided.h"
#include <string>
#include <vector>
#include <queue>
using namespace std;

class TokenizerImpl
{
public:
    TokenizerImpl(string separators);
    vector<string> tokenize(const std::string& s) const;
private:
    string m_separators;
};

TokenizerImpl::TokenizerImpl(string separators)
{
    m_separators = separators;
}

vector<string> TokenizerImpl::tokenize(const std::string& s) const
{
    vector<string> my_vec;
    std::queue<char> token_queue;
    for (int i = 0; i < s.length(); i++)
    {
       if(m_separators.find(s[i])< m_separators.length()) //if the current char is a separator //m_separators.find(s[i])>=0 &&
       {
           if (!token_queue.empty())
           {
               string word ="";
               while (!token_queue.empty())
               {
                   char popped = token_queue.front();
                   word += popped;
                   token_queue.pop();
               }
               my_vec.push_back(word);
           }
           
       }
       else {
           token_queue.push(s[i]);
       }
    }
    
    if (!token_queue.empty()) // in the case that we don't end on a punctuation
    {
        string word ="";
        while (!token_queue.empty())
        {
            char popped = token_queue.front();
            word += popped;
            token_queue.pop();
        }
        my_vec.push_back(word);
    }
    
    return my_vec;
}

//******************** Tokenizer functions ************************************

// These functions simply delegate to TokenizerImpl's functions.
// You probably don't want to change any of this code.

Tokenizer::Tokenizer(string separators)
{
    m_impl = new TokenizerImpl(separators);
}

Tokenizer::~Tokenizer()
{
    delete m_impl;
}

vector<string> Tokenizer::tokenize(const std::string& s) const
{
    return m_impl->tokenize(s);
}
