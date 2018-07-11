#include "provided.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cctype>
#include <random>
#include <algorithm>
#include <numeric>
using namespace std;

//const string WORDLIST_FILE = "wordlist.txt";
//
//string encrypt(string plaintext)
//{
//      // Generate a to z
//    char plaintextAlphabet[26+1];
//    iota(plaintextAlphabet, plaintextAlphabet+26, 'a');
//    plaintextAlphabet[26] = '\0';
//
//      // Generate permutation
//    string ciphertextAlphabet(plaintextAlphabet);
//    default_random_engine e((random_device()()));
//    shuffle(ciphertextAlphabet.begin(), ciphertextAlphabet.end(), e);
//
//      // Run translator (opposite to the intended direction)
//    Translator t;
//    t.pushMapping(plaintextAlphabet, ciphertextAlphabet);
//    return t.getTranslation(plaintext);
//}
//
//bool decrypt(string ciphertext)
//{
//    Decrypter d;
//    if ( !d.load(WORDLIST_FILE))
//    {
//        cout << "Unable to load word list file " << WORDLIST_FILE << endl;
//        return false;
//    }
//    for (const auto& s : d.crack(ciphertext))
//        cout << s << endl;
//    return true;
//}
//
//int main(int argc, char* argv[])
//{
//    if (argc == 3  &&  argv[1][0] == '-')
//    {
//        switch (tolower(argv[1][1]))
//        {
//          case 'e':
//            cout << encrypt(argv[2]) << endl;
//            return 0;
//          case 'd':
//            if (decrypt(argv[2]))
//                return 0;
//            return 1;
//        }
//    }
//
//    cout << "Usage to encrypt:  " << argv[0] << " -e \"Your message here.\"" << endl;
//    cout << "Usage to decrypt:  " << argv[0] << " -d \"Uwey tirrboi miyi.\"" << endl;
//    return 1;
//}
unsigned int pattern(string word)
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

int main()
{
//    Tokenizer t(" ,.!");
//    vector<string> kk = t.tokenize("This,, is a test! It's the... best! ever");
//
//    for (int i =0; i< v.size(); i++)
//        cout<< v[i];


//    unsigned int in = pattern("abbreviating");
//    cout << in;

//    WordList k;
//
//    k.loadWordList("wordlist.txt");
//
//    vector<string> boob;
//
//    boob = k.findCandidates("xyqbbq", "??????");
//
//    if ( k.contains("piazza"))
//        cerr<< "hell";
//
//    for (int i =0; i< boob.size(); i++)
//        cerr<< boob[i] << endl;
//    WordList wl;
//    if ( ! wl.loadWordList("wordlist.txt"))
//    {
//        cout << "Unable to load word list" << endl;
//    }
//    if (wl.contains("onomatopoeia"))
//        cout << "I found onomatopoeia!" << endl;
//    else
//        cout << "Onomatopoeia is not in the word list!" << endl;
//    string cipher = "xyqbbq";
//    string decodedSoFar = "?r????";
//    vector<string> v = wl.findCandidates(cipher, decodedSoFar);
//    if (v.empty())
//        cout << "No matches found" << endl;
//    else
//    {
//        cout << "Found these matches:" << endl;
//        for (size_t k = 0; k < v.size(); k++)
//            cout << v[k] << endl; // writes grotto and troppo
//    }

//    Translator t;
//    t.pushMapping("DHL", "ERD"); // DàE, HàR, LàD
//    if ( ! t.pushMapping("QX", "RY")) // QàR, XàY
//        cout << "Both H and Q would map to R!" << endl;
//    // The current mapping is still DàE, HàR, LàD with no
//    // mapping for Q or X
//    cout << t.getTranslation("HDX") << endl; // writes RE?
//    if ( !t.pushMapping("H", "S")) // HàS
//        cout << "H would map to both R and S!" << endl;
    Decrypter d;
    d.load("wordlist.txt");

    vector<string> v = d.crack("Xjzwq gjz cuvq xz huri arwqvudiy fuk ufjrqoq svquxiy. -Lzjk Nqkkqcy");

    for (int i =0; i< v.size(); i++)
        cout<< v[i]<< endl;

//    WordList w;
//    w.loadWordList("wordlist.txt");
//    if (w.contains("i"))
//        cout<< "contains i";
//
//

}






