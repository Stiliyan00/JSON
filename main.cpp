#include <iostream>
#include "JSON.hpp"
#include <stack>
#include "valid_value.hpp"
#include "object.hpp"

using namespace std;


int main()
{
    JSON m;

    char str[1024];
    cin.getline(str, 1024, '\n');
    ///cout << str << endl;


   /// cout << validArr(str) << endl;

   cout << validString(str) << endl;


   /// cout << validString(str) << endl;
   /// cout << validNumber(str) << endl;
   /// cout << validBoolen(str) << endl;
    ///if(validString(str)) cout << "mamka mu" << endl;


 /**    string command;
    char commandHelp;
    bool exit = false;
    do {
        cout<<"$";
        cin>>command;

        if(command == "e") commandHelp = 'E';
        if(command[0] == '[') commandHelp = 'A';
        switch (commandHelp) {
            case 'A':
            {
                int newData;
                cin >> newData;
                m.Add_To_Array(newData);

            }; break;
            case 'I':
                {


                }; break;

            case 'B':
                {

                }; break;

            case 'F':
                {


                }; break;

            case 'R':
                {

                }; break;

            case 'P':
                {

                }; break;

            case 'S' :
                {

                };break;

            case 'E': exit = true; break;

            default: cout<<"Invalid command! Try again!\n";
        }
    } while (!exit);

*/



    return 0;
}
