#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "valid_value.hpp"

///tuka raboti sys string kato "name", a ne s name prosto
bool validObject(string input)
{
    if(removeSpaces(input) == "{}") return true;
    if(getFirstSymbol(input) == '{')
    {
        int counter = 1;
        string str;
        while(input[counter] != '}')
        {
            if(input[counter] == ':')
            {
                if(validString(str))
                {
                    str.erase();
                    counter++;
                }
                else return false;
            }
            if(input[counter] == ',')
            {
                if(isValidValue(str))
                {
                    str.erase();
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






#endif // _OBJECT_H_
