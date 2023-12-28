#include <iostream>
#include <string>

#include "Dictionary_class.hpp"

using namespace std;


int main(){

    string command{""};
    string parameter{""};
    cin >> command; //first command is always M
    cin >> parameter; //first pararmeter is always m, the size of the table
    cout << "success\n";
    Dictionary word_dictionary(stoi(parameter)); //stoi = string to integer

    cin >> command;
    while (command != "EXIT"){
        try{

        if (command == "INSERT"){
            cin >> parameter;
            cout << word_dictionary.insertWord(parameter) << "\n";
        }
        else if (command == "READ"){
            cin >> parameter;
            fstream fin(parameter.c_str());
            cout << word_dictionary.readFile(fin) << "\n";
        }
        else if (command == "TOKENIZE"){
            cin >> parameter;
            cout << word_dictionary.getToken(parameter) << "\n";
        }
        else if (command == "RETRIEVE"){
            cin >> parameter;
            cout << word_dictionary.getWord(stoi(parameter)) << "\n";
        }
        else if (command == "STOK"){
            cin >> parameter;
            while (parameter != "_DONE_"){
                cout << word_dictionary.getToken(parameter) << " ";
                cin >> parameter;
            }
            cout << "\n";
        }
        else if (command == "TOKS"){
            cin >> parameter;
            while (parameter != "-1"){
                cout << word_dictionary.getWord(stoi(parameter)) << " ";
                cin >> parameter;
            }
            cout << "\n";
        }
        else if (command == "PRINT"){
            cin >> parameter;
            cout << word_dictionary.getKeys(stoi(parameter)) << "\n";
        }
        else{
            cout << "Invalid command, try again\n";
        }
        
        }//end of the try block
        catch(...){
            cout << "an exception occurred, check input and try again\n";
        }

        cin >> command;
    }


    return 0;
}