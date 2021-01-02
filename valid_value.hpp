#ifndef _VALID_VALUE_H_
#define _VALID_VALUE_H_

#include <iostream>
#include <string.h>
#include <stack>
#include <iterator>

using namespace std;

void print(string a)
{
    for(int i = 0; i < a.size(); i++)
    {
        cout << a[i];
    }
}

bool isNumber(const char& str)
{
    if(str >='0' && str <= '9') return true;
    return false;
}

bool isWhiteSpace(const char& ch)
{
    if(ch == ' ') return true;
    return false;
}

char getFirstSymbol(const string str, int i = 0)
{
    if(str[i] == ' ')
        getFirstSymbol(str, i + 1);
    else
    {
        return str[i];
    }
}

bool validString(string str);
bool validBoolen(string str);
bool validNumber(string str);
bool validArr(string str);

bool isValidValue(const string str)
{
    if(getFirstSymbol(str) == '"' && validString(str)) return true;
    if(getFirstSymbol(str) == '(' && validBoolen(str)) return true;
    if(isNumber(getFirstSymbol(str) ) && validNumber(str)) return true;
    if(getFirstSymbol(str) == '[' && validArr(str)) return true;

    else return false;
}

static std::string removeSpaces(std::string str)
{
    str. erase(remove(str. begin(), str. end(), ' '), str. end());
    return str;
}


bool validBoolen(string str)
{
    if(getFirstSymbol(str) == '(')
    {
        if(removeSpaces(str) == "(true)" || removeSpaces(str) == "(false)")
        {
            return true;
        }
    }
    return false;
}

bool validNumber(string str)
{

    if(isNumber(getFirstSymbol(str)) )
    {
        int i = 0;
        while(isNumber(str[i]) )
        {
            i++;
        }
        if(i == str.size()) return true;
    }
    return false;
}

bool validString(string str)
{
    if(getFirstSymbol(str) == '"')
    {
        int i = 0;
        int number_of_quotes = 0;
        while(i < str.size())
        {
            if(str[i] == '"')
            {
                number_of_quotes++;
            }
            i++;
        }
        if(number_of_quotes == 2) return true;
    }
    return false;
}


bool validArr(string str)
{
    ///str = removeSpaces(str);
    if(getFirstSymbol(str) == '[' && str[str.size() - 1] == ']')
    {

        if(str == "[]") return true;
        int counter = 1;
        string value;
        int number_brackets = 1;

        while(number_brackets > 0 && counter < str.size())
        {

            if(str[counter] == '[')
            {
                value.push_back(str[counter]);
                counter++;
                number_brackets++;
            }

            else if(str[counter] == ']' && number_brackets > 1)
            {
                value.push_back(str[counter]);
                counter++;
                number_brackets--;
            }

            else if(str[counter] == ']' && number_brackets == 1)
            {
                number_brackets--;
            }


            else if(str[counter] == ',')
            {
                if(!isValidValue(value))
                {
                    return false;
                }
                else {
                        value.erase();
                        counter++;
                }
            }

            else
            {
                value.push_back(str[counter]);
                counter++;
            }
        }
        if(!isValidValue(value) || number_brackets != 0 || counter < str.size()-1)
        {
            return false;
        }
        return true;
    }
    else return false;
}



#endif // _VALID_VALUE_H_
