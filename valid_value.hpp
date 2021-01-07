#ifndef _VALID_VALUE_H_
#define _VALID_VALUE_H_

#include <iostream>
#include <string.h>
#include <stack>
#include <iterator>
#include <sstream>

using namespace std;

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
bool validArr( string& str);
bool validObject(string str);

bool isValidValue( string& str)
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

bool validArr(string& str)
{
    int numberOfValidValues = 0;
    ///str = removeSpaces(str);
    if(getFirstSymbol(str) == '[' && str[str.size() - 1] == ']')
    {

        bool isInArray = false;

        if(str == "[]") return true;
        int counter = 1;
        string value;
        int number_brackets = 1;

        while(number_brackets > 0 && counter < str.size())
        {
            if(str[counter] == '[')
            {
                isInArray = true;
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
                if(isValidValue(value)) number_brackets--;
                else
                {
                    if(value != "") cerr << "THE GIVEN VALUE: " << value << " IS INVALID!" << endl;
                        int indx = counter - 1;
                        int res = 0;
                        while(str[indx] != ',' && str[indx] != '[')
                        {
                            res++;
                            indx--;
                        }

                        str.replace(indx, res,"");
                        value.erase();
                        counter++;

                }
            }

            else if(str[counter] == ',' && isInArray == false)
            {
                if(!isValidValue(value))
                {
                    if(value != "") cerr << "THE GIVEN VALUE: " << value << " IS INVALID!" << endl;
                        int indx = counter - 1;
                        int res = 0;
                        while(str[indx] != ',' && str[indx] != '[')
                        {
                            res++;
                            indx--;
                        }

                        str.replace(indx, res,"");
                        value.erase();
                        counter++;
                }
                else {
                        numberOfValidValues++;
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
        if(numberOfValidValues == 0 || number_brackets != 0 || counter < str.size()-1)
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
    if(removeSpaces(input) == "{ }") return true;
    if(input[0] == '{')
    {
        int counter = 1;
        string str;

        if(input[counter] == ' ') counter++;
        else
        {
            return false;
        }

        int number_of_brackets = 1;

        bool isArray = false;

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

            else if(input[counter] == ' ' && input[counter + 1] == ':' && input[counter + 2] == ' ')
            {
                if(validString(str))
                {
                    str.erase();
                    counter++;
                    counter++;
                    counter++;
                }
                else return false;
            }
            else if(input[counter] == '[')
            {
                isArray = true;
                while(input[counter] != ']')
                {
                    str.push_back(input[counter]);
                    counter++;
                }
                str.push_back(input[counter]);

                if(validArr(str))
                {
                    counter++;
                    isArray = false;
                }
                else return false;
            }

            else if(input[counter] == ',' && isArray == false)
            {
                if(isValidValue(str) && input[counter + 1] == ' ')
                {
                    str.erase();
                    counter++;
                    counter++;
                }
                else
                {
                    return false;
                }
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
    else
    {
        return false;
    }
}

bool canBeSorted(string& str)
{
    if(validArr(str))
    {
        vector<string> arr;
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

        bool isCorrect = true;
        for(int i = 1; i < arr.size(); i++)
        {
            if(validString(arr[i - 1]) && validString(arr[i]) && isCorrect)
            {
                isCorrect = true;
            }
            else if(validNumber(arr[i - 1]) && validNumber(arr[i]) && isCorrect)
            {
                isCorrect = true;
            }
            else isCorrect = false;

        }
        if(isCorrect) return true;
        return false;
    }
    else cerr << "THE GIVEN VALUE: " << str << "IS NOT A VALID ARRAY!" << endl;
}

void sortArr(string& str)
{
    if(canBeSorted(str))
    {
        vector<string> arr;
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
        if(validNumber(arr[0]))
        {
            vector<int> arrHelp;
            for(int i = 0; i < arr.size(); i++)
            {

                stringstream geek(arr[i]);
                int x = 0;
                geek >> x;
                arrHelp.push_back(x);
            }
            arr.clear();
            sort(arrHelp.begin(), arrHelp.end());
            for(int i = 0; i < arrHelp.size(); i++)
            {
                stringstream ss;
                ss<<arrHelp[i];
                string s;
                ss>>s;
                arr.push_back(s);
            }
        }
        else
        {
            sort(arr.begin(), arr.end());
        }
        str.erase();
        str.push_back('[');
        for(int i = 0; i < arr.size() - 1; i++)
        {
            for(int j = 0; j < arr[i].size(); j++)
            {
                str.push_back(arr[i][j]);
            }
            str.push_back(',');
        }
        for(int j = 0; j < arr[arr.size() - 1].size(); j++)
        {
            str.push_back(arr[arr.size() - 1][j]);
        }
        str.push_back(']');

    }
    else cerr << "CANNOT BE SORTED!" << endl;

}

#endif // _VALID_VALUE_H_
