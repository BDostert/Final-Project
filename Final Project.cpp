//Title: ITCS 2350 Final Project.cpp
//Authors: Brandon Dostert, Robert Fox, Robert Kern
//Date: 12/11/2022
//Description: A program that will take a users input of year/month/day
//and return the President along with the terms they served.  Then create an output file.


#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int DATE_ARRAY_SIZE = 3; //constant for array sizes - (Robert Kern)

//struct to store results of the readData() function - (Robert Kern)
struct resultsType {
    int startDate[DATE_ARRAY_SIZE];
    int endDate[DATE_ARRAY_SIZE];
    string name;
    string terms;
};

// displays the header along with the help menu (Robert Fox)
void Introduction(char c, string message) 
{
    //Display header
    cout << setfill(c) << setw(40) << c << endl;
    cout << setfill(c) << " " << setw(2) << c << message << setfill(c) << setw(2) << c << endl;
    cout << setfill(c) << setw(40) << c << endl;
    cout << endl;

    //Display menu options to the user
    cout << "Enter \'m\' to show the Menu" << endl;
    cout << "Enter \'y\' to get President for given date" << endl;
    cout << "Enter \'q\' to exit the program" << endl;

}

//function that reads dates from the input file, compares them to a date input by a user
//and adds data for a corresponding president to a results struct.
//returns true if successful, or false if it couldn't find a matching range of dates - (Robert Kern)
bool readDates(string fileName, int userDate[], resultsType& results)
{
    //Variables
    ifstream inFile;
    bool matchFound = false;

    //open input file
    inFile.open(fileName);

    //loop continues until a matching date range is found or the input file ends
    while (!matchFound && !inFile.eof())
    {
        //skips to a start date and inputs it into an array
        inFile.ignore(100, '@');
        for (int i = 0; i < DATE_ARRAY_SIZE; i++)
        {
            inFile >> results.startDate[i];
            inFile.ignore(100, ' ');
        }

        //skips to an end date and inputs it into an arrray
        inFile.ignore(100, '#');
        for (int i = 0; i < DATE_ARRAY_SIZE; i++)
        {
            inFile >> results.endDate[i];
            inFile.ignore(100, ' ');
        }

        //If structure to compare dates
        if (userDate[0] > results.startDate[0] && userDate[0] < results.endDate[0])    //compares user date year against year range
            matchFound = true;

        else if (userDate[0] == results.startDate[0])   // if same as start year, compare months
        {
            if (userDate[1] > results.startDate[1])
                matchFound = true;

            else if (userDate[1] == results.startDate[1])   // if same months, compare days
                if (userDate[2] >= results.startDate[2])
                    matchFound = true;
        }

        else if (userDate[0] == results.endDate[0]) // if same as end year, compare months
        {
            if (userDate[1] < results.endDate[1])
                matchFound = true;
            else if (userDate[1] == results.startDate[1]) // if same month, compare days
                if (userDate[2] <= results.endDate[2])
                    matchFound = true;
        }
    } // end of While loop

    if (!matchFound)
        return false;
    else
    {
        inFile.ignore(100, '*');
        getline(inFile, results.name, '*');
        inFile.ignore(100, '$');
        getline(inFile, results.terms);
    }

    //Closing the input file
    inFile.close();

    return true;
}


void Output(int userDate[], resultsType results) {

    static ofstream fsOut;

    if (!fsOut.is_open()) //should only open the output file once, so previous results don't get overwritten --(R Kern)
        fsOut.open("results.txt");

    if (fsOut.is_open()) {
        // outputs results to screen 
        cout << "On " << userDate[1] << "/" << userDate[2] << "/" << userDate[0] << " "
            << results.name << " was president and served " << results.terms
            << " from " << results.startDate[1] << "/" << results.startDate[2] << "/" << results.startDate[0]
            << " to " << results.endDate[1] << "/" << results.endDate[2] << "/" << results.endDate[0] << "." << endl;
        // outputs results to results.txt file
        fsOut << "On " << userDate[1] << "/" << userDate[2] << "/" << userDate[0] << " "
            << results.name << " was president and served " << results.terms
            << " from " << results.startDate[1] << "/" << results.startDate[2] << "/" << results.startDate[0]
            << " to " << results.endDate[1] << "/" << results.endDate[2] << "/" << results.endDate[0] << "." << endl;
    }

}

// Brings in file and calls all functions to execute user inputs (Robert Fox)
int main(int argc, char* argv[1]) 
{
    //Declare variables
    string message = " ITCS 2350 Group 4: Final Project ";
    char c = '*';
    char userInput = ' ';
    int dateInput[DATE_ARRAY_SIZE];
    resultsType results;


    // Function allows user to enter choice
    Introduction('*', message);



        //Decide which function to call
        while (userInput != 'q' && userInput != 'Q')
        {

            // Add space for next prompt
            cout << endl;
            cout << endl;

            //Receive users input
            cout << "Please enter an operation to perform:";
            cin >> userInput;
            cin.ignore(100,'\n'); // this is to clear the buffer for first hundred characters or new line
            cout << "\n"; //adds a new line

            //Execute option based on user input
            if (userInput == 'm' || userInput == 'M')
            {
                // Function displays header and choice for user to enter
                Introduction('*', message);

            }
            else if (userInput == 'y' || userInput == 'Y')
            {
                cout << "Please enter a year: ";
                cin >> dateInput[0];  // Populate index [0] of dateInput array

                cout << "Please enter a month: ";
                cin >> dateInput[1];  // Populate index [1] of dateInput array

                cout << "Please enter a day: ";
                cin >> dateInput[2];  // Populate index [2] of dateInput array
                cout << "\n";

                // Call readDates function and take in the file along with user information
                if (readDates(argv[1], dateInput, results)) //only calls the Output() function if a matching date is found --(R Kern)
                {
                    // Call Output function to create results text file and output to the display
                    Output(dateInput, results);
                }
                else
                    cout << "Date out of bounds." << endl;
            }
            // Quit program based on user input
            else if (userInput == 'q' || userInput == 'Q')
            {
                cout << "Program ending." << endl;
                cout << "Good Bye!" << endl;

                system("pause");
            }
            // Display choices based on invalid entry
            else
            {
                cout << "\nInvalid selection please choose \'m\', \'y\', \'q\'. try again." << endl;
            }
        }

        // return 0 to indicate success.
        return (0);

    }

