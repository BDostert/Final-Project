// Final Project.cpp : 

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

void Introduction(char c, string message)
{
    //Display header
    cout << setfill(c) << setw(40) << c << endl;
    cout << setfill(c) << " " << setw(2) << c << message << setfill(c) << setw(2) << c << endl;
    cout << setfill(c) << setw(40) << c << endl;
    cout << endl;

    //Display output to the user
    cout << "Enter \'?\' to call \'??????????\'" << endl;
    cout << "Enter \'?\' to call \'??????????\'" << endl;
    cout << "Enter \'?\' to call \'??????????\'" << endl;
    cout << "Enter \'q\' to exit the program" << endl;

}

bool ReadFile(string fileName)
{
    return(0);
}


int main(int argc, char* argv[1])
{
    //Declare variables
    ifstream inFile;
    ofstream outFile;
    bool fileOpened = false;

    string message = " ITCS 2350 Group 4: Final Project ";
    char c = '*';
    char userInput = ' ';

    // Open file Presidents.txt
    inFile.open(argv[1]);

    // Function allows user to enter choice
    Introduction('*', message);

    // Function that takes a file name and reads in data and returns true on success or false on failure.
    fileOpened = ReadFile(argv[1]);

    if (fileOpened == true)
    {


        //Decide which function to call
        while (userInput != 'q' && userInput != 'Q')
        {

            // Add space for next prompt
            cout << endl;
            cout << endl;

            //Receive users input
            cout << "Please enter an operation to perform:";
            cin >> userInput;

            if (userInput == '?' || userInput == '?')
            {


            }
            else if (userInput == '?' || userInput == '?')
            {


            }
            else if (userInput == '?' || userInput == '?')
            {


            }
            else
            {
                cout << "Invalid selection please choose \'?\', \'?\', \'?\', \'q\'. Try again." << endl;
            }
        }




        // Return 0 to indicate success.
        return (0);
    }

    else
    {
        return(-1);
    }

    return(0);
}
