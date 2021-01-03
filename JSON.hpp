#ifndef _JSON_H
#define _JSON_H

#include <iostream>
#include <string.h>
#include <hashtable.h>
#include <vector>
#include<unordered_map>
#include "valid_value.hpp"
#include "object.hpp"
#include <list>
#include <iterator>

using namespace std;

///zasega shte rabotim samo s string za ime i int za value:

class JSON
{
private:
    list<pair<string, string>> pairs;
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
    void Replace(const string& str, const string& value, const string newStr);

    void deleteElement(const string& str, const string& value);
    void Move(const string& str, const string& value, const string& secondStr, const string& secondValue);
};


///i tuka nqmam proverka dali sa namereni i syshtestvuvat it1 i it2
void JSON::Move(const string& str, const string& value, const string& secondStr, const string& secondValue)
{
    list<pair<string , string> >::iterator it1;
    list<pair<string , string> >::iterator it2;

    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        if(it->first == str && it->second == value)
        {
            it1 = it;
        }
        if(it->first == secondStr && it->second == secondValue)
        {
            it2 = it;
        }
    }

        swap(*it1, *it2);

}

void JSON::deleteElement(const string& str, const string& value)
{
    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        if(it->first == str && it->second == value)
        {
            pairs.erase(it);
            break;
        }
    }
}


void JSON::Replace(const string& str, const string& value, const string newStr)
{
    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        if(it->first == str && it->second == value)
        {

            it->second.replace(0, value.size(), newStr);
        }
    }
}

string& JSON::search_key(const string& str)
{
   if(validString(str))
    { string temp;

    int counter = 1;
    while(counter < str.size() - 1)
    {
        temp.push_back(str[counter]);
        counter++;
    }

        for(auto it = pairs.begin(); it != pairs.end(); ++it)
        {
            if(it->first == temp) cout << it->second << endl;
        }
    }
    else cerr << "INVALID INPUTTED STRING" << endl;
}

void JSON::printPairs() const
{
    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        cout << it->first << ": " << it->second <<endl;
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
        pair<string, string> p1(str, temp);
        pairs.push_back(p1);
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
