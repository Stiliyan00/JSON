#ifndef _JSON_H
#define _JSON_H

#include <iostream>
#include <string.h>
#include <hashtable.h>
#include <vector>
#include<unordered_map>
#include "valid_value.hpp"
#include "object.hpp"

using namespace std;

///zasega shte rabotim samo s string za ime i int za value:

class JSON
{
private:
    unordered_map<string, string> pairs;
    vector<string> arr;

public:
    void inputArray(const string& str);
    void getValues(string str);

    void printArr()const;
    void printPairs()const;
    ///----------------------------///

    void getPairs(const string& str);
    void inputPairs(const string& str);

    string& search_key(const string& str);
};

string& JSON::search_key(const string& str)
{
    return pairs[str];
}

void JSON::printPairs() const
{
    for (auto pair: pairs) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}


void JSON::getPairs(const string& input)
{
    if(getFirstSymbol(input) == '{')
    {
        int counter = 1;
        string str;
        string temp;
        while(input[counter] != '}')
        {

            if(input[counter] == ':')
            {
                if(validString(str))
                {
                    temp = str;
                    str.erase();
                    counter++;
                }
                else cout << "error!" << endl; return;
            }
            if(input[counter] == ',')
            {
                if(isValidValue(str))
                {
                    pairs[temp] = str;
                    str.erase();
                    temp.erase();
                    counter++;
                }
                else cout << "error!" << endl; return;
            }
            else
            {
                str.push_back(input[counter]);
                counter++;
            }
        }
        if(isValidValue(str))
            {
                    pairs[temp] = str;

                    cout << pairs[temp] << endl;
                    str.erase();
                    temp.erase();
                }

        return;
    }
    else cout << "ERROR!" << endl;

}

void JSON::inputPairs(const string& str)
{

}


void JSON::printArr() const
{
        for(int i = 0; i < arr.size(); i++)
        {
            cout << arr[i]<< endl;
        }
}

void JSON::getValues(string str)
{
    if(validArr(str))
    {
        int counter = 1;
        string value;
        int valueCounter = 0;
        while(str[counter] != ']')
        {

            if(str[counter] == ',')
            {
                arr.push_back(value);
                value.erase();
                counter++;

            }

            else
            {
                value.push_back(str[counter]);
                counter++;

            }
        }
        arr.push_back(value);
    }
    else cout << "INVALID ARR INPUT" << endl;

}

void JSON::inputArray(const string& str)
{
    if(validArr(str))
    {
        getValues(str);
        return;
    }
    cout << "MOllqqq" << endl;


}

#endif // _JSON_H
