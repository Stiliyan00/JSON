#include <iostream>
#include "JSON.hpp"
#include <stack>
#include "valid_value.hpp"
#include "object.hpp"
#include <fstream>

using namespace std;


int main()
{
    JSON m;

    string str;

    ifstream iFile("JSON.txt");
    if(!iFile){
        cout << "ERROR!\n";
        return 0;
    }

    string command;
    char commandHelp;
    bool exit = false;
    do {
        cout<<"$ ";

        getline(iFile, str);
        cout << str << endl;

        if(str == "e") commandHelp = 'E';
        if(str == "Print array") commandHelp = 'P';
        if(str == "Print object") commandHelp = 'Q';
        if(str == "Print object") commandHelp = 'Q';
        if(str == "Search by key") commandHelp = 'K';
        if(str[0] == '[') commandHelp = 'A';
        if(str[0] == '{') commandHelp = 'O';
        switch (commandHelp) {
            case 'A':
            {
                if(validArr(str))
                {
                    m.inputArray(str);
                }
                else cerr << "HELPPPPP" << endl;

            }; break;
            case 'O':
                {
                    if(validObject(str))
                    {
                        m.inputPairs(str);
                    }
                    else cerr << "HELPPP" << endl;
                }; break;

            case 'P':
                {
                    m.printArr();

                }; break;

            case 'Q':
                {
                    m.printPairs();

                }; break;

            case 'K':
                {
                    string s;
                    getline(iFile, s);

                    cout << m.search_key(s) << endl;
                }; break;

            case 'S' :
                {

                };break;

            case 'E': exit = true; break;

            default: cout<<"Invalid command! Try again!\n";
        }
    } while (!exit);

    return 0;
}
