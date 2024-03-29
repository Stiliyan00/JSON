#include <iostream>
#include "JSON.hpp"
#include <stack>
#include "valid_value.hpp"
#include <fstream>
#include <sstream>

using namespace std;

void printString(const string str[])
{
    for(int i = 0; i < str->size(); i++)
    {
        cout << str[i] << " ";
    }
    cout << endl;
}

void printStringIndex(const string str[], int index)
{
    cout << str[index] << endl;
}

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
        if(str == "Create a new object") commandHelp = 'C';
        if(str == "Erase") commandHelp = 'D';
        if(str == "Sort values in:") commandHelp = 'S';
        if(str == "Save in file with whitespace:") commandHelp = 'F';
        if(str == "Save in file without whitespace:") commandHelp = 'B';
        if(str == "Save element:") commandHelp = 's';
        if(str == "Delete element:") commandHelp = 'd';
        if(str[0] == '[') commandHelp = 'A';
        if(str[0] == '{') commandHelp = 'O';
        switch (commandHelp) {
            case 'A':
            {
                if(validArr(str))
                {
                    m.inputArray(str);
                    m.removeNullsFromArray();
                    m.takePairsFromArray();
                }
                else
                {
                    cerr << "WRONG INPUTTED ARRAY!" << endl;
                 return 0;
                }
            }; break;
            case 'O':
                {
                    if(validObject(str))
                    {
                        m.inputPairs(str);
                    }
                    else cerr << "INVALID INPUT FOR OBJECT! " << endl;
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
                    if(s == "and print all values")
                    {
                        string s1;
                        getline(iFile, s1);
                        cout << s1 << endl;
                        printString(m.search_key(s1));
                    }
                    else if(s == "and print the value on index:")
                    {
                        string s1;
                        getline(iFile, s1);
                        cout << s1 << endl;
                        string s2;
                        getline(iFile, s2);
                        cout << s2 << endl;

                        stringstream geek(s1);
                        int x = 0;
                        geek >> x;

                        printStringIndex(m.search_key(s2), x);
                    }

                    else m.search_key(s);

                }; break;

            case 'R' :
                {
                    string str, str1;
                    getline(iFile, str);
                    getline(iFile, str1);
                    string temp;
                    string temp1;
                    string value;
                    getline(iFile, temp);
                    getline(iFile, temp1);
                    int counter = 0;
                    while(temp1 == "->")
                    {
                        counter++;
                        value.push_back('{');
                        value.push_back(' ');
                        for(int i = 0; i < temp.size(); i++)
                        {
                            value.push_back(temp[i]);
                        }
                        value.push_back(' ');
                        value.push_back(':');
                        value.push_back(' ');
                        getline(iFile, temp);
                        getline(iFile, temp1);

                    }

                    string newString = temp1;

                    string newStr= value;

                    for(int i = 0; i < temp.size(); i++)
                    {
                        value.push_back(temp[i]);
                    }

                    for(int i = 0; i < newString.size(); i++)
                    {
                        newStr.push_back(newString[i]);
                    }
                    for(int i = 0; i < counter; i++)
                    {
                        newStr.push_back('}');
                        value.push_back('}');
                    }

                    m.Replace(str, value, newStr);

                };break;

            case 'S' :
                {
                    string str, str1;
                    getline(iFile, str);
                    getline(iFile, str1);
                    string temp;
                    string temp1;
                    string value;
                    getline(iFile, temp);
                    getline(iFile, temp1);
                    int counter = 0;
                    while(temp1 == "->")
                    {
                        counter++;
                        value.push_back('{');
                        value.push_back(' ');
                        for(int i = 0; i < temp.size(); i++)
                        {
                            value.push_back(temp[i]);
                        }
                        value.push_back(' ');
                        value.push_back(':');
                        value.push_back(' ');
                        getline(iFile, temp);
                        getline(iFile, temp1);

                    }

                    for(int i = 0; i < temp.size(); i++)
                    {
                        value.push_back(temp[i]);
                    }

                    for(int i = 0; i < counter; i++)
                    {
                        value.push_back('}');
                    }

                    m.sortValue(str, value);

                };break;
            case 'D' :
                {
                    string str, str1;
                    getline(iFile, str);
                    getline(iFile, str1);
                    string temp;
                    string temp1;
                    string value;
                    getline(iFile, temp);
                    getline(iFile, temp1);
                    int counter = 0;
                    while(temp1 == "->")
                    {
                        counter++;
                        value.push_back('{');
                        value.push_back(' ');
                        for(int i = 0; i < temp.size(); i++)
                        {
                            value.push_back(temp[i]);
                        }
                        value.push_back(' ');
                        value.push_back(':');
                        value.push_back(' ');
                        getline(iFile, temp);
                        getline(iFile, temp1);

                    }

                    for(int i = 0; i < temp.size(); i++)
                    {
                        value.push_back(temp[i]);
                    }

                    for(int i = 0; i < counter; i++)
                    {
                        value.push_back('}');
                    }

                    m.deleteElement(str, value);

                };break;


             case 'd' :
                {

                    string str;
                    getline(iFile, str);


                    m.deleteElementInArray(str);

                };break;

            case 'C' :
                {
                    string str, str1;
                    getline(iFile, str);
                    getline(iFile, str1);
                    string temp;
                    string temp1;
                    string value;
                    getline(iFile, temp);
                    getline(iFile, temp1);
                    int counter = 0;
                    while(temp1 == "->")
                    {
                        counter++;
                        value.push_back('{');
                        value.push_back(' ');
                        for(int i = 0; i < temp.size(); i++)
                        {
                            value.push_back(temp[i]);
                        }
                        value.push_back(' ');
                        value.push_back(':');
                        value.push_back(' ');
                        getline(iFile, temp);
                        getline(iFile, temp1);

                    }

                    for(int i = 0; i < temp.size(); i++)
                    {
                        value.push_back(temp[i]);
                    }

                    for(int i = 0; i < counter; i++)
                    {
                        value.push_back('}');
                    }

                    m.createObject(str, value, temp1);

                };break;


            case 'F' :
                {
                    string s;
                    getline(iFile, s);

                    m.save(s, true);
                };break;
            case 'B' :
                {
                    string s;
                    getline(iFile, s);

                    m.save(s, false);
                };break;

            case 's' :
                {
                    string str, str1;
                    getline(iFile, str);
                    getline(iFile, str1);
                    string temp;
                    string temp1;
                    string value;
                    getline(iFile, temp);
                    getline(iFile, temp1);
                    int counter = 0;
                    while(temp1 == "->")
                    {
                        counter++;
                        value.push_back('{');
                        value.push_back(' ');
                        for(int i = 0; i < temp.size(); i++)
                        {
                            value.push_back(temp[i]);
                        }
                        value.push_back(' ');
                        value.push_back(':');
                        value.push_back(' ');
                        getline(iFile, temp);
                        getline(iFile, temp1);

                    }

                    for(int i = 0; i < temp.size(); i++)
                    {
                        value.push_back(temp[i]);
                    }

                    for(int i = 0; i < counter; i++)
                    {
                        value.push_back('}');
                    }

                    cout << str << " " << value << endl;
                    string fileName;
                    getline(iFile, fileName);
                    cout << "In file: " << endl;
                    cout << fileName << endl;

                    m.saveElement(str, value, fileName);

                };break;

            case 'E': exit = true; break;

            default: cout<<"Invalid command! Try again!\n";
        }
    } while (!exit);

    return 0;
}
