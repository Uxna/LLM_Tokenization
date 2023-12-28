#ifndef Word_class_hpp
#define Word_class_hpp

#include <string>

/*
Node of the linked list to resolve collision in the hash table
Each object stores the token of the word, the ASCII key, and the word itself
*/
class Word{
    public:
        std::string getWord_W();
        unsigned int getToken_W();
        unsigned int getKey_W();
        Word* getPNext_W();
        void setPNext_W(Word* p_new);

        Word(unsigned int tok, unsigned int key, std::string word);
        ~Word();

    private:
        unsigned int token;
        unsigned int key;
        std::string word;
        Word* p_next_word;
};


Word::Word(unsigned int tok, unsigned int k, std::string w): token{tok}, key{k}, word{w}, p_next_word{nullptr} {}
Word::~Word() {}

std::string Word::getWord_W(){
    return word;
}

unsigned int Word::getToken_W(){
    return token;
}

unsigned int Word::getKey_W(){
    return key;
}

Word* Word::getPNext_W(){
    return p_next_word;
}

void Word::setPNext_W(Word* p_new){
    p_next_word = p_new;
}

#endif