#ifndef Dictionary_class_hpp
#define Dictionary_class_hpp

#include <string>
#include <fstream>

#include "Slot_class.hpp"

/*
The class will include a hash table and a dynamically allocated array
The hash table will use the ASCII sum as the key and store the token of the words
The array will store the actual string and the tokens will be the index
*/
class Dictionary {
    public:
        std::string getWord(unsigned int token); //return UNKNOWN if the token is not valid
        unsigned int getToken(std::string word); //0 if the word is not yet stored, token of the word otherwise
        std::string insertWord(std::string word); //return "success" or "failure"
        unsigned int calcASCIIsum(std::string word); //calcualte the ASCII key value of the word
        std::string getKeys(unsigned int slot_position); //return all the ASCII key values at this slot in the table
        std::string readFile(std::fstream& fin);

        Dictionary(unsigned int size);
        ~Dictionary();

    private:
        unsigned int table_size;
        unsigned int array_size; //initialized to 100, resize to array_size + 100 when the array is full
        unsigned int current_end_index; //index of the last word in the array
        Slot* hash_table; //use the ASCII sum as the key
        std::string* word_array; //list used to store the words (strings), with token-1 being their index
};

//******************************************************************************
//Definitions
//******************************************************************************

std::string Dictionary::readFile(std::fstream& fin){
    std::string aWord;
    bool success = false;
    while (fin >> aWord){
        if (insertWord(aWord) == "success"){
            success = true;
        }
    }
    if (success){
        return "success";
    }
    else {
        return "failure";
    }
}

std::string Dictionary::insertWord(std::string word){
    unsigned int ASCII_sum = calcASCIIsum(word);
    if (ASCII_sum == 0){ //contains non-alphabetic characters
        return "failure";
    }
    else if (getToken(word) != 0){ //word already stored in the dictionary
        return "failure";
    }
    if (current_end_index+1 == array_size){
        array_size += 100;
        std::string* new_word_array = new std::string[array_size];
        for (unsigned int i{0}; i < array_size-100; ++i){
            new_word_array[i] = word_array[i];
        }
        std::string* p_old_array = word_array;
        word_array = new_word_array;
        delete[] p_old_array;
        p_old_array = nullptr;
    }
    unsigned int slot_position{ASCII_sum % table_size};
    current_end_index += 1;
    Word* new_word{new Word(current_end_index, ASCII_sum, word)};
    word_array[current_end_index] = word;
    hash_table[slot_position].insertWord_S(new_word);
    return "success";
}

unsigned int Dictionary::getToken(std::string word){
    //go into the slot in the hash table the word would be in, check 
    unsigned int ASCII_key = calcASCIIsum(word);
    unsigned int table_index = ASCII_key % table_size;
    unsigned int apparentToken = hash_table[table_index].getToken_S(word);
    return apparentToken;
}

std::string Dictionary::getWord(unsigned int token){
    if (token > current_end_index){
        return "UNKNOWN";
    }
    return word_array[token];
}

std::string Dictionary::getKeys(unsigned int slot_position){
    Word* p_current_word{ hash_table[slot_position].getPHead_S() };
    std::string key_chain{""};
    while (p_current_word != nullptr){
        key_chain = key_chain + std::to_string(p_current_word->getKey_W()) + " ";
        p_current_word = p_current_word->getPNext_W();
    }
    if (key_chain == ""){
        return "chain is empty";
    }
    return key_chain;
}

//Constructors and destructors
Dictionary::Dictionary(unsigned int size): table_size{size}, array_size{100}, current_end_index{0} {
    hash_table = new Slot[table_size];
    word_array = new std::string[array_size];
    word_array[0] = ""; //token of 0 is used to indicate word not in dictionary
}
Dictionary::~Dictionary(){ //need to delete the dynamically allocated memories
    delete[] hash_table;
    hash_table = nullptr;
    delete[] word_array;
    word_array = nullptr;
}
//end of constructors and destructors

//function to calculate the ASCII key value of a word
//return 0 if contains non-alphabetic characters
unsigned int Dictionary::calcASCIIsum(std::string word){
    unsigned int sum{0};
    for (int i{0}; i < word.size(); ++i){
        int value{int(word[i])};
        if ( std::isalpha(word[i]) ){
            sum += value;
            continue;
        }
        return 0; 
    }
    return sum;
}

#endif