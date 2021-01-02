#ifndef _VALID_VALUE_H_
#define _VALID_VALUE_H_

#include <iostream>
#include <string.h>
#include <stack>
#include <iterator>

using namespace std;

///[123,-123,0.e+213,[[[12321]]],null]

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
bool validObject(string str);

bool isValidValue(const string str)
{
        if(getFirstSymbol(str) == '"' && validString(str)) return true;
        if(getFirstSymbol(str) == '(' && validBoolen(str)) return true;
        if(validNumber(str)) return true;
        if(getFirstSymbol(str) == '[' && validArr(str)) return true;
        if(getFirstSymbol(str) == '{' && validObject(str)) return true;
        if(str == "null") return true;

    else return false;
}

static string removeSpaces(string str)
{
    str. erase(remove(str. begin(), str. end(), ' '), str. end());
    return str;
}
/**
static string remove_front_and_back_whitespace(string str)
{
    str.erase(remove_if(str.begin(), str.end(), [](const string& str){if}))
}
*/
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
    int i = 0;
    if(str[i] == '-') i++;

    ///tuk e sluchaq za tova da zapochnem s 0
    if(str[i] == '0')
    {
        if(i == str.size() - 1) return true;

        ///tova e proverka ako e fraction
        else if(str[i+1] == '.')
        {
            i++;
            i++;
            if(str[i] >= 48 && str[i] <= 58)
            {
                while(str[i] >= 48 && str[i] <= 58) i++;
            }

            else if(str[i] == 'E' || str[i] == 'e')
            {
                i++;
                if(str[i] == '+' || str[i] == '-')
                {
                    i++;
                }

                ///tova za da sme sig che ima pone edna cifra
                if(str[i] >= 48 && str[i] <= 58)
                {
                    while(str[i] >= 48 && str[i] <= 58) i++;
                }
            }

            if(i == str.size()) return true;
            return false;

        }

        ///tova e proverka ako e exponent
        else if(str[i+1] == 'E' || str[i+1] == 'e')
        {
            i++;
            i++;
            if(str[i] == '+' || str[i] == '-')
            {
                i++;
            }

            ///tova za da sme sig che ima pone edna cifra
            if(str[i] >= 48 && str[i] <= 58)
            {
                while(str[i] >= 48 && str[i] <= 58)
                    i++;

            }
            if(i == str.size()) return true;
            return false;
        }
        else return false;
    }

    else
    {
        if(str[i] >= 49 && str[i] <= 58)
        {
            i++;
            while(str[i] >= 48 && str[i] <= 58)
            {
                i++;
            }
        }
        else return false;
    }

    if(i == str.size()) return true;
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
            if(str[i] == '\\')
            {
                i++;
                if((str[i] == '"' || str[i] == '/' || str[i] == '\\' || str[i] == 'b' || str[i] == 'f' || str[i] == 'n' || str[i] == 'r' || str[i] == 't') && (str[i+1] == '"') )
                {
                    return true;
                }
                else if(str[i] == 'u' && str[i+5] == '"')
                {
                    i++;
                    while(str[i] != '"')
                    {
                        if(!((str[i]>=48 && str[i]<=57) || (str[i]>=65 && str[i]<=70)) )
                        {
                            return false;
                        }
                        i++;
                    }
                    return true;
                }
                else return false;
            }

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

bool validObject(string input)
{
    ///trqa da se smeni  i da proverqva za { } a ne za {} i proizvolen br whitespace mejdu tqh
    if(removeSpaces(input) == "{}") return true;
    if(input[0] == '{')
    {
        int counter = 1;
        string str;

        if(input[counter] == ' ') counter++;
        else return false;

        int number_of_brackets = 1;

        while(number_of_brackets > 0 && counter < input.size())
        {
            if(input[counter] == '{')
            {
                while(input[counter] != '}')
                {
                    str.push_back(input[counter]);
                    counter++;
                }
                str.push_back(input[counter]);
                counter++;
                if(isValidValue(str)) counter++;
                else return false;
            }

            else if(input[counter] == '}' && number_of_brackets == 1)
            {
                number_of_brackets--;
            }

            else if(input[counter] == ':')
            {
                if(validString(str) && input[counter + 1] == ' ' && input[counter - 1] == ' ')
                {
                    str.erase();
                    counter++;
                    counter++;
                }
                else return false;
            }
            else if(input[counter] == ',')
            {
                if(isValidValue(str) && input[counter + 1] == ' ')
                {
                    str.erase();
                    counter++;
                    counter++;
                }
                else return false;
            }
            else
            {
                str.push_back(input[counter]);
                counter++;
            }
        }
        if(isValidValue(str)) return true;

        return false;
    }
    else return false;
}


#endif // _VALID_VALUE_H_
