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

class JSON
{
private:
    list<pair<string, string>> pairs;
    vector<string> arr;

public:
    void inputArray(string& str);
    void getValues(string &str);

    void printArr()const;
    void printPairs()const;

    void removeNullsFromArray();

    void takePairsFromArray();
    void inputPairs(const string& str);

    string* search_key(const string& str);
    void Replace(const string& str, const string& value, const string& newStr);

    void createObject(const string& str, const string& value, const string& newObject);
    void sortValue( string& str,  string& value);

    void deleteElement(const string& str, const string& value);
    void Move(const string& str, const string& value, const string& secondStr, const string& secondValue);

    void save(const string& str, bool isTrue);
    void saveElement(const string& str, const string& value, const string& fileName);
};

void JSON::saveElement(const string& str, const string& value, const string& fileName)
{
    ofstream oFile(fileName);
    oFile << str << " : " << value << endl;
}

void JSON::save(const string& str, bool isTrue)
{
    if(isTrue)
    {
        ofstream oFile(str);
        oFile << "Array: " << endl;
        for(int i = 0; i < arr.size(); i++)
        {
            oFile << arr[i] << endl;
        }
        oFile << endl;
        oFile << "Objects: " << endl;
        for(auto it = pairs.begin(); it != pairs.end(); ++it)
        {
            oFile << it->first << " " << it->second << endl;
        }
    }
    else
    {
        ofstream oFile(str);
        oFile << "Array: ";
        for(int i = 0; i < arr.size(); i++)
        {
            oFile << arr[i];
        }
        oFile << "Objects: ";
        for(auto it = pairs.begin(); it != pairs.end(); ++it)
        {
            oFile << it->first<< it->second;
        }
    }
}


void JSON::sortValue( string& str,  string& value)
{
    if(validArr(value))
    {
        bool isFound = false;
            string value1 = value;
            sortArr(value1);

            for(auto it = pairs.begin(); it != pairs.end(); ++it)
            {
                if(it->first == str && it->second == value)
                {
                    it->second = value1;
                    isFound = true;
                }
            }
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

            for(int i = 0; i < value1.size(); i++)
            {
                newTemp.push_back(value1[i]);

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
    else cerr <<"INPOSSIBLE TO SORT" << endl;
}


void JSON::removeNullsFromArray()
{
    vector<string> arr1;
    for(int i = 0; i < arr.size(); i++)
    {
        if(arr[i] != "")
        {
            arr1.push_back(arr[i]);
        }
    }
    arr.clear();
    for(int i = 0; i < arr1.size(); i++)
    {
        arr.push_back(arr1[i]);
    }
}


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
/**
void JSON::Move(const string& str, const string& value, const string& secondStr, const string& secondValue)
{
    bool isFound1 = false;
    bool isFound2 = false;
    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {
        if(it->first == str && it->second == value)
        {
            it->second.erase();
            it->second = secondValue;
            isFound1 = true;
        }

        if(it->first == secondStr && it->second == secondValue)
        {
            it->second.erase();
            it->second = value;
            isFound2 = true;
        }
    }
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
*/

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

        vector<string> arrTemp;

        for(int i = 0; i < arr.size(); i++)
        {
            if(arr[i] != temp)
            {
                arrTemp.push_back(arr[i]);
            }
        }
        arr.clear();
        for(int i = 0; i < arrTemp.size(); i++)
        {
            arr.push_back(arrTemp[i]);
        }
    }
}

void JSON::Replace(const string& str, const string& value, const string& newStr)
{
    bool isFound = false;
    for(auto it = pairs.begin(); it != pairs.end(); ++it)
    {
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

        int numberArrayBrackets = 0;

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
            if(input[counter] == '[') numberArrayBrackets++;

                while(input[counter] != ',' && input[counter] != '}')
                {
                    if(input[counter] == '[') numberArrayBrackets++;
                    if(input[counter] == ']') numberArrayBrackets--;
                    if(input[counter] == '{') bracketCount++;
                    if(input[counter] == ' ' && input[counter + 1] == ',') break;
                    temp.push_back(input[counter]);
                    counter++;
                    if(input[counter] == ',' && numberArrayBrackets > 0)
                    {
                        temp.push_back(input[counter]);
                        counter++;
                    }
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

void JSON::getValues(string& str)
{
    if(validArr(str))
    {
        int counter = 1;
        int bracketCounter = 1;
        string value;
        int valueCounter = 0;
        while(bracketCounter  > 0)
        {
            if(str[counter] == '[')
            {
                value.push_back(str[counter]);
                counter++;
                bracketCounter++;
            }
            if(str[counter] == ']' && bracketCounter > 1)
            {
                value.push_back(str[counter]);
                counter++;
                bracketCounter--;
            }

            if(str[counter] == ']' && bracketCounter == 1)
            {
                break;
            }

            if(str[counter] == ',' && bracketCounter == 1)
            {
                arr.push_back(value);
                value.erase();
                counter++;
            }

            if(str[counter] == ',' && bracketCounter > 1)
            {
                value.push_back(str[counter]);
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

void JSON::inputArray( string& str)
{
    if(validArr(str))
    {
        getValues(str);
        return;
    }
    cerr << "INVALID ARRAY INPUT : " << endl;
}

#endif // _JSON_H
