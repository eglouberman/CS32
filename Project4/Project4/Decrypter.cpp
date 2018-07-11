#include "provided.h"
#include <string>
#include <vector>
#include <iostream>
#include <map>
#include <set>
using namespace std;

class DecrypterImpl
{
public:
    DecrypterImpl():m_tokenizer(" -,.!?;"){
        m_called =1;
    };
    bool load(string filename);
    vector<string> crack(const string& ciphertext);
private:
    WordList m_wordlist;
    Translator m_translator;
    Tokenizer m_tokenizer;
    bool isTranslated(string word);
    vector<string> tryCandidate(vector<string> candidates, string w, vector<string> cipherWords);
    vector<vector<string>> m_validSolutions;
    void detokenize(const string& word, vector<string> &vec);
    int m_called;
    string m_cipherCopy;
};

void DecrypterImpl::detokenize(const string &word, vector<string>& vec)
{
    string tokens = "-,.!?;";
    string vec_words ="";
    map<int, string> token_map;
    for (int j =0; j< vec.size(); j++)
    {
        vec_words +=vec[j] + " ";
    }
    
    for (int i =0; i < word.length(); i++)
    {
        if (tokens.find(word[i])< word.length())
        {
            token_map[i]= word[i];
        }
    }
    bool hasNoSeparators = true;
    for (int i =0; i< tokens.size();i++)
    {
        if (vec_words.find(tokens[i])< vec_words.size())
            hasNoSeparators = false;
    }
    if (hasNoSeparators)
    {
    map<int,string> :: iterator it;
    it = token_map.begin();
    while(it!=token_map.end())
    {
        vec_words.insert(it->first, it->second);
        it++;
    }
    }

    for (int i =0; i < word.length(); i++)
    {
        if ((word[i]<= 'Z' && word[i] >='A') && (vec_words[i]>='a' && vec_words[i]<='z')) //takes care of case
            vec_words[i]-=char(32);
    }
    vec.clear();
    vec.push_back(vec_words);
    return;
}
vector<string> DecrypterImpl:: tryCandidate(vector<string> candidates, string w, vector<string> cipherWords)
{
    int countPushes =0;
    
    for (int i =0; i< candidates.size(); i++)
    {
        bool doesntWork = false;
        bool completelyTranslated = true;
        for (int j =0; j< w.size(); j++)
        {
            string a = "";
            string b = "";
            a+=w[j];
            b+=candidates[i][j];
            if (m_translator.getTranslation(a) == "?")
                {
                    if(!m_translator.pushMapping(a,b))// we update temporary mapping, but if we try to add duplicates,
                    {
                        //cerr<< "sorry you tried duplicating"<< endl;
                        while(countPushes!=0)
                        {
                            m_translator.popMapping(); // we undo all the previous pushing we did.
                            countPushes--;
                        }
                        if (countPushes==0)
                        {
                            j +=w.size();
                            doesntWork =true;
                        }
                    }
                    else countPushes++;
                }
            else if(m_translator.getTranslation(a)!= b)
            {
                //we have to move on to the next candidate
                while(countPushes!=0)
                {
                    m_translator.popMapping(); // we undo all the previous pushing we did.
                    countPushes--;
                }
                j +=w.size();
                doesntWork =true; // maybe set a bool over here.
            }
        }
        vector<string> checkString;
        if (!doesntWork)
        { // check for words that are fully translated and are not in the dictionary
            for (int x =0; x< cipherWords.size(); x++)
            {
                string check=  m_translator.getTranslation(cipherWords[x]);
                if (check.find('?') > cipherWords[x].size()) // if it is fully translated
                {
                    if ((m_wordlist.findCandidates(cipherWords[x], check).empty())) // temporary mapping doesn't translate well!
                    {
                        while (countPushes!=0)
                        {
                            m_translator.popMapping();
                            countPushes--;
                        }
                        doesntWork = true;
                        x += cipherWords.size();
                        checkString.clear();
                        continue;
                    }
                }
                else if (m_wordlist.findCandidates(cipherWords[x], check).empty())
                {
                    while (countPushes!=0)
                    {
                        m_translator.popMapping();
                        countPushes--;
                    }
                    doesntWork = true;
                    x += cipherWords.size();
                    checkString.clear();
                    continue;
                }
                if (check.find('?') < cipherWords[x].size())
                    completelyTranslated = false;
                checkString.push_back(check);
            }
        }
        
        if (!doesntWork)
        {   // solution seems promising!
//            for (int z =0; z< checkString.size(); z++)
//                cerr<< checkString[z]<< endl;
            if(!completelyTranslated)
            {
                string cipher_string ="";
                for (int l =0; l< cipherWords.size(); l++)
                    cipher_string += cipherWords[l] +" ";
                crack(cipher_string);
                while (countPushes!=0){
                    m_translator.popMapping();
                    countPushes--;
                }
            }
            
            else
            { //all translations are perfect!
                m_validSolutions.push_back(checkString);
//                for (int z =0; z< checkString.size(); z++)
//                    cerr<< checkString[z]<< endl;
                while (countPushes!=0)
                {
                    m_translator.popMapping();
                    countPushes--;
                }
                checkString.clear(); // look for more mappings!
                doesntWork = false;
                completelyTranslated = true;
                continue;
            }
        }
    }
    
    while (countPushes!=0){
        m_translator.popMapping();
        countPushes--;
    }
    //return empty vector if we didn't find anything
    cipherWords.clear();
    return cipherWords;

    
}
bool DecrypterImpl::load(string filename)
{
    return m_wordlist.loadWordList(filename);
}
bool DecrypterImpl::isTranslated(string word)
{
    word=  m_translator.getTranslation(word);
    if (word.find('?') < word.length())
        return false;
    else return true;
}
vector<string> DecrypterImpl::crack(const string& ciphertext)
{
    m_called++;
    m_cipherCopy =ciphertext; 
    for (int i =0; i< m_cipherCopy.length(); i++)
    {
        if (m_cipherCopy[i]>= 'A' && m_cipherCopy[i]<='Z')
            m_cipherCopy[i]+=32;
    }
    vector<string> my_vec;
    my_vec = m_tokenizer.tokenize(m_cipherCopy); //2
    string chosen = "";
    int minQM =0;
    //choose word that has not yet been chosen and has the most ciphertext letters
    for (int i =0; i< my_vec.size(); i++)
    {
        int countQM =0;
        string trans = m_translator.getTranslation(my_vec[i]);
        for (int j= 0; j< trans.length(); j++)
        {
            if (trans[j] =='?')
                countQM++;
        }
        if (!isTranslated(my_vec[i]) && countQM >= minQM && my_vec[i].length()>chosen.length())
        {
            chosen = my_vec[i];
            minQM= countQM;
        }
    }
    
    string currTranslation = m_translator.getTranslation(chosen);
    
    vector<string> candidates; // finding candidates with the chosen pattern given the current translation
    candidates = m_wordlist.findCandidates(chosen, currTranslation); //3
    
    if (candidates.empty() == true)
    {
        while(!m_translator.popMapping())
            m_translator.popMapping(); 
        return candidates;
    }
    
//    for (int i =0; i< candidates.size(); i++)
//    {
//        cerr<< candidates[i]<<endl;
//    }
//    cerr<< "END OF CANDIDATES!!!!!!!!!!!!!!!!" << endl;
    tryCandidate(candidates,chosen, my_vec); //6
    
    
    set<string> ordered; // this enables us to alphebatize
    for(int i=0; i<m_validSolutions.size(); i++)
    {
        detokenize(ciphertext, m_validSolutions[i]);
        string individual ="";
        for (int z= 0; z< m_validSolutions[i].size(); z++)
        {
            individual+= m_validSolutions[i][z];
        }

        ordered.insert(individual);
    }
    
    vector<string> final;
    
    std::copy(ordered.begin(), ordered.end(), std::back_inserter(final));
    
    for (int i =0; i< final.size(); i++)
    {
        while(final[i].length() > ciphertext.length())
            final[i].pop_back(); 
    }
    
    m_cipherCopy ="";
    m_called--;
    if (m_called ==1)
    {
        m_called = 1;
        m_validSolutions.clear();
    }
    return final;
    
}

//******************** Decrypter functions ************************************

// These functions simply delegate to DecrypterImpl's functions.
// You probably don't want to change any of this code.

Decrypter::Decrypter()
{
    m_impl = new DecrypterImpl;
}

Decrypter::~Decrypter()
{
    delete m_impl;
}

bool Decrypter::load(string filename)
{
    return m_impl->load(filename);
}

vector<string> Decrypter::crack(const string& ciphertext)
{
   return m_impl->crack(ciphertext);
}
