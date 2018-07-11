// MyHash.h

// Skeleton for the MyHash class template.  You must implement the first seven
// member functions; we have implemented the eighth.
#include <iostream>
using namespace std;

template<typename KeyType, typename ValueType>
class MyHash
{
public:
    MyHash(double maxLoadFactor = 0.5);
    ~MyHash();
    void reset();
    void associate(const KeyType& key, const ValueType& value);
    int getNumItems() const;
    double getLoadFactor() const;

      // for a map that can't be modified, return a pointer to const ValueType
    const ValueType* find(const KeyType& key) const;

      // for a modifiable map, return a pointer to modifiable ValueType
    ValueType* find(const KeyType& key)
    {
        return const_cast<ValueType*>(const_cast<const MyHash*>(this)->find(key));
    }

      // C++11 syntax for preventing copying and assignment
    MyHash(const MyHash&) = delete;
    MyHash& operator=(const MyHash&) = delete;

private:
    
    struct Node
    {
        KeyType   m_key;
        ValueType m_value;
        ~Node() {if (m_next!=nullptr) delete m_next;};
        Node*     m_next = nullptr;
        
    };
    
    int m_size;
    int m_items;
    double m_loadFactor;
    double maxLoadFactor;
    Node* m_array;
    int m_buckets;
    unsigned int getBucketNumber(const KeyType& key, int size) const
    {
        unsigned int hash(const KeyType& k);
        unsigned int h = hash(key);
        return h%size;
    }
    
};

template <typename KeyType,typename ValueType>
MyHash<KeyType,ValueType>::MyHash(double max_LoadFactor):m_size(100)
{
    m_array = new Node[m_size];
    
    for (int i= 0; i< m_size; i++)
    {
        m_array[i].m_next =nullptr;
    }
    
    if (maxLoadFactor<=0)
        maxLoadFactor = 0.5;
    
    if (maxLoadFactor >=2.0)
        maxLoadFactor = 2.0;
    
    maxLoadFactor= max_LoadFactor;
    m_loadFactor =0;
   // cerr<< m_loadFactor << "-->Load";
    
    m_size =100;
    m_items =0;
    m_buckets =0;
}

template <typename KeyType,typename ValueType>
MyHash<KeyType,ValueType>::~MyHash()
{
    delete [] m_array;
}

template <typename KeyType, typename ValueType>
int MyHash<KeyType, ValueType>::getNumItems() const
{
    return m_items;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::reset()
{
    delete[] m_array;
    m_buckets =0;
    m_array = new Node[100];
    m_size = 100;
    m_items = 0;
    return;
}

template<typename KeyType, typename ValueType>
void MyHash<KeyType, ValueType>::associate(const KeyType& key, const ValueType &value)
{
    bool inserted = false;
    //check if the key is already in the array
    unsigned int key_index = getBucketNumber(key, m_size);
    Node* temp = m_array[key_index].m_next;
    
    if (temp == nullptr) // if it is a nullptr, we just add it in.
    {
        Node* keyValuePair =new Node;
        keyValuePair->m_key = key;
        keyValuePair->m_value = value;
        m_array[key_index].m_next = keyValuePair;
        inserted = true;
        m_items++;
        m_buckets ++;
//        if (key == 123443)
//        {
//            cerr<< key <<" inserted at: " <<key_index << endl;
//        }
        //cerr<< "NUM BUCKETS: "<< m_buckets << endl;
        
//        cerr<< "------------" << endl;
//        cerr<< "Item, " << key << "inserted at" << key_index << endl;
//        cerr<< "There are currently " << m_items <<  " in the hash." <<endl;
//        cerr<< "------------" << endl;
    }
    

  else {
        
    while (temp != nullptr)
    {
        if (temp->m_key == key) // we have found the key in the array already, so we just update its value!
        {
            temp->m_value = value; // we just updated it.
            inserted = true;
           // m_items++;
            
//            cerr<< "------------" << endl;
//            cerr<< "Item, " << key << "UPDATED at" << key_index << endl;
//            cerr<< "There are currently " << m_items <<  " in the hash." <<endl;
//            cerr<< "------------" << endl;
        }
        temp = temp->m_next;
    }
    //temp's next value is a nullptr
    if (!inserted){
        Node* keyValuePair =new Node;
        keyValuePair->m_key = key;
        keyValuePair->m_value = value;
        keyValuePair->m_next = m_array[key_index].m_next; 
        m_array[key_index].m_next = keyValuePair;
//        if (key == 123443)
//        {
//            cerr<< key <<" updated at: " <<key_index << endl;
//        }
//        cerr<< "------------" << endl;
//        cerr<< "Item, " << key << " APPENDED at " << key_index << endl;
//        cerr<< "There are currently " << m_items <<  " in the hash." <<endl;
//        cerr<< "------------" << endl;
        m_items++;
    }
}
    
    m_loadFactor = double(m_buckets)/double(m_size);
    if (m_loadFactor> maxLoadFactor) // we have exceeded the load factor!
    {
        m_buckets =0;
//        cerr << "REALLOCATING!!!!!!!!!!!!!!!!!!!"<< endl;
        
        Node* new_array = new Node[m_size*2];
        for (int i =0; i< m_size; i++)
        {
            Node* curr = m_array[i].m_next;
            while (curr != nullptr) // first item that we have found that isnt empty
            {
                KeyType keyz = (curr->m_key); // new key
                ValueType valuez = (curr->m_value); // new value
                int size2 = m_size*2;
                unsigned int new_key_index = getBucketNumber(keyz, size2); // finds new index we need to insert at
                Node* temp2 = new_array[new_key_index].m_next; // node pointing to new index
                
                
                if (temp2 == nullptr) // if it is a nullptr, we just add it in.
                {
                    m_buckets++;
                    Node* keyValuePair =new Node;
                    keyValuePair->m_key = keyz;
                    keyValuePair->m_value = valuez;
                    new_array[new_key_index].m_next = keyValuePair;
//                    if (keyz == 123443)
//                    {
//                        cerr<< keyz <<" inserted in an empty bucket at: " <<new_key_index << endl;
//                    }
                    curr = curr->m_next;
                }
                
                
                else {

                    Node* keyValuePair =new Node;
                    keyValuePair->m_key = keyz;
                    keyValuePair->m_value = valuez;
                    keyValuePair->m_next = temp2;
                   // temp2 =nullptr;
                    new_array[new_key_index].m_next = nullptr;
                    new_array[new_key_index].m_next = keyValuePair;
//                    if (keyz == 123443)
//                    {
//                        cerr<< keyz <<" added to another bucket at: " << new_key_index << endl;
//                    }
                    curr = curr->m_next;
                }
            }
        }
        
        delete [] m_array;
        m_size = m_size*2;
        
        m_array = new Node[m_size];
        
       // m_array = new_array; // we should iterate through all the items in new_array so that we explicitly copy every element.
        for (int i =0; i< m_size; i++)
        {
            m_array[i].m_next = nullptr;
            Node* curr = new_array[i].m_next;
            Node* to_be_added = m_array[i].m_next;
            if (curr != nullptr && to_be_added == nullptr) // first item that we have found that isnt empty, we start copying the buckets
            {
                m_array[i].m_next = curr;
                new_array[i].m_next = nullptr;
            }
        }
        
        
        delete [] new_array;
        
       // cerr<< "DONE REALLOCATING"<< endl;
    }
    return;
}


template <typename KeyType, typename ValueType>
double MyHash<KeyType, ValueType>::getLoadFactor() const
{
    return m_loadFactor;
}

template <typename KeyType, typename ValueType>
const ValueType* MyHash<KeyType, ValueType>::find(const KeyType& key) const
{
    ValueType* j = nullptr;
    unsigned int key_index = getBucketNumber(key, m_size);
    
    Node* temp = m_array[key_index].m_next;
    
    while(temp != nullptr)
    {
    //    KeyType t = temp->m_key;
        if (temp->m_key == key)
        {
            j = &(temp->m_value);
            return j;
        }
        temp =temp->m_next;

    }
    return j;
}






