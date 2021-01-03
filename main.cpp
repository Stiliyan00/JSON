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
        if(str == "Replace") commandHelp = 'R';
        if(str == "Search by key") commandHelp = 'K';
        if(str == "Erase") commandHelp = 'D';
        if(str == "Move") commandHelp = 'M';
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
                    cout << s << endl;
                    m.search_key(s);


                }; break;

            case 'R' :
                {
                    string s;
                    string s1;
                    string newString;
                    getline(iFile, s);
                    getline(iFile, s1);
                    getline(iFile, newString);
                    m.Replace(s, s1, newString);

                };break;

            case 'D' :
                {
                    string str;
                    string value;
                    getline(iFile, str);
                    getline(iFile, value);

                   m.deleteElement(str, value);

                };break;

            case 'M' :
                {
                    string str;
                    string value;
                    string secondStr;
                    string secondValue;

                    getline(iFile, str);
                    getline(iFile, value);
                    getline(iFile, secondStr);
                    getline(iFile, secondValue);

                   m.Move(str, value, secondStr, secondValue);

                };break;

            case 'E': exit = true; break;

            default: cout<<"Invalid command! Try again!\n";
        }
    } while (!exit);

    return 0;
}
