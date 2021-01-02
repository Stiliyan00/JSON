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
    string temp;
    temp.push_back('"');
    int counter = 0;
    while(counter < str.size())
    {
        temp.push_back(str[counter]);
        counter++;
    }
    temp.push_back('"');

    if(validString(temp))
    {
        return pairs[str];
       ///else cout << "NOT FOUND" << endl;
    }
    else cerr << "INVALID INPUTTED STRING" << endl;
}

void JSON::printPairs() const
{
    for (auto pair: pairs) {
        std::cout << pair.first << ": " << pair.second << "\n";
    }
}

void JSON::inputPairs(const string& input)
{
    if(validObject(input))
    {
        int counter = 3;
        string str;
        string temp;

        while(input[counter] != '"' && input[counter] != '\\')
        {
            str.push_back(input[counter]);
            counter++;
        }

        if(input[counter] == '\\')
        {
            str.push_back(input[counter]);
            counter++;
            str.push_back(input[counter]);
            counter++;
        }
        else
        {
            counter++;
            counter++;
            counter++;
            counter++;

            while(counter < input.size() - 1)
            {
                temp.push_back(input[counter]);
                counter++;
            }
        }
            pairs[str] = temp;
    }
    else cerr << "WRONG INPUT!" << endl;
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
