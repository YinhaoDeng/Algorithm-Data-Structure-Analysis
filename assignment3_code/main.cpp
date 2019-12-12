#include <iostream>
#include <string>
using namespace std;

class HashTable
{
    private:
        string key; //store keys
        string hash_table[2][26]; //first row status, second row keys
    public:
        HashTable();  //constructor
        int get_hash_value(string key);
        bool search(string key);
        void insert_key(string key);
        void delete_key(string key);
        void print_hash_table();
};

HashTable::HashTable()
{
    for(int i=0; i<26; i++)
    {
        hash_table[0][i]="never used"; //status
        hash_table[1][i]="NULL"; //result
    }
}

int HashTable::get_hash_value(string key)
{
    //key must be lower case
    //we use ASCII to locate the position of hash value 
    char last_char_of_key = key[key.size()-1];
    return last_char_of_key-'a';
}

bool HashTable::search(string key)
{
    int hash_value =get_hash_value(key);

    if(hash_table[1][hash_value]==key)
        return true; //yeah I find the key!
    else if(hash_table[0][hash_value]=="never used")
        return false;
    else if(hash_table[1][hash_value]!=key&&(hash_table[0][hash_value]=="occupied"||hash_table[0][hash_value]=="tombstone"))
        {
            while(hash_table[0][hash_value]!="never used")
            {
                hash_value += 1;
                if(hash_value==26)
                    hash_value = 0; //loop back to the beginning
                if(hash_value==get_hash_value(key))
                    return false;
                if(hash_table[1][hash_value]==key)
                    return true;
            }
        }
    else
        return false;
}

void HashTable::insert_key(string key)
{
    int hash_value=get_hash_value(key);
    
    if(search(key)==false) //if slot empty
    {
        if(hash_table[0][hash_value]=="never used"
        ||hash_table[0][hash_value]=="tombstone") //sucessfully insert_key the key
        {
            hash_table[0][hash_value]="occupied";
            hash_table[1][hash_value]=key;
        }
        else //if the slot is occupied
        {
            while(hash_table[0][hash_value]=="occupied")
            {
                hash_value += 1;
                if(hash_value==26)
                    hash_value=0;
            }
            if(hash_table[0][hash_value]!="occupied")
            {
                hash_table[0][hash_value]="occupied";
                hash_table[1][hash_value]=key;
            }
        }
    }
}

void HashTable::delete_key(string key)
{
    //fist find the index
    int hash_index =-1;
    for(int i=0; i<26; i++)
    {
        if(hash_table[1][i]==key)
        hash_index = i;
    }
    if(search(key)==true)
    {
        hash_table[0][hash_index]="tombstone";
        hash_table[1][hash_index]="NULL";
    }
}

void HashTable::print_hash_table()
{
    for(int i=0; i<26; i++)
    {
        if(hash_table[1][i]!="NULL")
            cout<<hash_table[1][i]<<" ";
    }
}

int main()
{
    string input="";
    getline(cin,input);
    int input_size = input.length();
    string temp="";

    HashTable hash_table_obj;
    for(int i=0;i<input_size;i++)
    {
        if(input[i]==' ')
        {
            if(temp[0]=='A')
            {    
                temp.erase(0,1);
                hash_table_obj.insert_key(temp);
            }
            else if(temp[0]=='D')
            {
                temp.erase(0,1);
                hash_table_obj.delete_key(temp);
            }
            temp="";
        }else
            temp.push_back(input[i]);
    }
    if(temp[0]=='A')
    {
        temp.erase(0,1);
        hash_table_obj.insert_key(temp);
    }else if(temp[0]=='D')
    {
        temp.erase(0,1);
        hash_table_obj.delete_key(temp);
    }
    hash_table_obj.print_hash_table();

    return 0;
}


