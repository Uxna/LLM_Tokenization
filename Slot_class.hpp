#ifndef Slot_class_hpp
#define Slot_class_hpp

#include "Word_class.hpp"

#include <string>
/*
Each object is a linked list representing a slot in the hash table
*/
class Slot {
    public:
        void insertWord_S(Word* word);
        Word* getPHead_S();
        void setPHead_S(Word* p_new);
        unsigned int getToken_S(std::string word);

        Slot();
        ~Slot();

    private:
        Word* p_head_word;
};

Word* Slot::getPHead_S(){
    return p_head_word;
}

void Slot::setPHead_S(Word* p_new){
    p_head_word = p_new;
    return;
}

void Slot::insertWord_S(Word* word){
    Word* p_old_head{getPHead_S()};
    setPHead_S(word);
    word->setPNext_W(p_old_head);
    return;
}

unsigned int Slot::getToken_S(std::string word){
    unsigned int token{0}; //return 0 if stored in the linked list
    Word* p_current_word{getPHead_S()};
    while (p_current_word != nullptr){
        if (p_current_word->getWord_W() == word){
            token = p_current_word->getToken_W();
            break;
        }
        p_current_word = p_current_word->getPNext_W();
    }
    return token;
}

//Destructor should delete all dynamically allocated memory
Slot::Slot(): p_head_word{nullptr} {}
Slot::~Slot(){
    while (p_head_word != nullptr){
        Word* p_old{p_head_word};
        p_head_word = p_head_word->getPNext_W();
        delete p_old;
        p_old = nullptr;
    }
}

#endif