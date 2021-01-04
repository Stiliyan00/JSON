#ifndef _JSON_H
#define _JSON_H

#include <iostream>
#include <string.h>
#include <hashtable.h>
#include <vector>
#include<unordered_map>
#include "valid_value.hpp"
#include <list>
#include <iterator>
#include <fstream>

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

    void takePairsFromArray();
    void inputPairs(const string& str);

    string* search_key(const string& str);
    void Replace(const string& str, const string& value, const string& newStr);

    void createObject(const string& str, const string& value, const string& newObject);

    void deleteElement(const string& str, const string& value);
    void Move(const string& str, const string& value, const string& secondStr, const string& secondValue);
};

void JSON::takePairsFromArray()
{
    for(int i = 0; i < arr.size(); i++)
    {
        if(validObject(arr[i]))
        {
            inputPairs(arr[i]);
        }
    }
}

void JSON::createObject(const string& str, const string& value, const string& newObject)
{
    bool isFound = false;
    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        if(it->first == str && it->second == value)
        {
            pairs.erase(it);
            isFound = true;
            break;
        }
    }
    if(isFound)
    {
        string temp;
        temp.push_back('{');
        temp.push_back(' ');
        for(int i = 0; i < newObject.size(); i++)
        {
            temp.push_back(newObject[i]);
        }
        temp.push_back(' ');
        temp.push_back(':');
        temp.push_back(' ');
        for(int i = 0; i < value.size(); i++)
        {
            temp.push_back(value[i]);
        }
        temp.push_back('}');
        inputPairs(temp);
    }
}


///i tuka nqmam proverka dali sa namereni i syshtestvuvat it1 i it2
void JSON::Move(const string& str, const string& value, const string& secondStr, const string& secondValue)
{
    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        if(it->first == str && it->second == value)
        {
            it->second.erase();
            it->second = secondValue;
            break;
        }

        if(it->first == secondStr && it->second == secondValue)
        {
            it->second.erase();
            it->second = value;
        }
    }

}

void JSON::deleteElement(const string& str, const string& value)
{
    bool isFound = false;
    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        if(it->first == str && it->second == value)
        {
            pairs.erase(it);
            isFound = true;
            break;
        }
    }
    if(isFound)
    {
        string temp;
        temp.push_back('{');
        temp.push_back(' ');
        temp.push_back('"');

        for(int i = 0; i < str.size(); i++)
        {
            temp.push_back(str[i]);
        }
        temp.push_back('"');
        temp.push_back(' ');
        temp.push_back(':');
        temp.push_back(' ');

        for(int i = 0; i < value.size(); i++)
        {
            temp.push_back(value[i]);
        }

        temp.push_back('}');


        for(int i = 0; i < arr.size(); i++)
        {
            if(arr[i] == temp)
            {
                arr[i].erase();
            }
        }

    }
}

void JSON::Replace(const string& str, const string& value, const string& newStr)
{
    bool isFound = false;
    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {

      ///  cout << str << " " << it->first << "|" << it->second << " " << value << endl;
        if(it->first == str && it->second == value)
        {
            it->second.replace(0, value.size(), newStr);
            isFound = true;
        }
    }
    ///tova e da promenim i dannite v arr
    if(isFound)
    {
        string temp;
        string newTemp;
        temp.push_back('{');
        temp.push_back(' ');
        temp.push_back('"');
        newTemp.push_back('{');
        newTemp.push_back(' ');
        newTemp.push_back('"');

        for(int i = 0; i < str.size(); i++)
        {
            temp.push_back(str[i]);
            newTemp.push_back(str[i]);
        }
        temp.push_back('"');
        temp.push_back(' ');
        temp.push_back(':');
        temp.push_back(' ');
        newTemp.push_back('"');
        newTemp.push_back(' ');
        newTemp.push_back(':');
        newTemp.push_back(' ');

        for(int i = 0; i < value.size(); i++)
        {
            temp.push_back(value[i]);
        }

        for(int i = 0; i < newStr.size(); i++)
        {
            newTemp.push_back(newStr[i]);

        }
        temp.push_back('}');
        newTemp.push_back('}');

        for(int i = 0; i < arr.size(); i++)
        {
            if(arr[i] == temp)
            {
                arr[i] = newTemp;
            }
        }

    }
}
string* JSON::search_key(const string& str)
{
   if(validString(str))
    { string temp;

    int counter = 1;
    while(counter < str.size() - 1)
    {
        temp.push_back(str[counter]);
        counter++;
    }

    string* res = new string[1024];
    int i = 0;

        for(auto it = pairs.begin(); it != pairs.end(); ++it)
        {
            if(it->first == temp)
            {
                res[i] = it->second;
                i++;
            }
        }
        return res;
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
        int bracketCount = 1;

        while(counter < input.size() - 1)
        {
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
            }
                while(input[counter] != ',' && input[counter] != '}')
                {
                    if(input[counter] == '{') bracketCount++;
                    if(input[counter] == ' ' && input[counter + 1] == ',') break;
                    temp.push_back(input[counter]);
                    counter++;
                }
                if(input[counter] == '}' && counter < input.size() - 1)
                {
                    for(int i = 1; i < bracketCount; i++)
                    {
                        temp.push_back('}');
                    }
                }
                if((input[counter + 1] == ',' ) || (input[counter] == '}' && counter < input.size() - 1)) counter += 3;

            pair<string, string> p1(str, temp);
            pairs.push_back(p1);
        }
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
