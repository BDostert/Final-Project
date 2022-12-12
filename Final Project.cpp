// Final Project.cpp : 

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

void Introduction(char c, string message)
{
    //Display header
    cout << setfill(c) << setw(40) << c << endl;
    cout << setfill(c) << " " << setw(2) << c << message << setfill(c) << setw(2) << c << endl;
    cout << setfill(c) << setw(40) << c << endl;
    cout << endl;

    //Display output to the user
    cout << "Enter \'m\' to show Menu" << endl;
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

    ofstream fsOut;
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



        //decide which function to call
        while (userInput != 'q' && userInput != 'Q')
        {

            // add space for next prompt
            cout << endl;
            cout << endl;

            //receive users input
            cout << "Please enter an operation to perform:";
            cin >> userInput;
            cin.ignore(100,'\n'); // this is to clear the buffer for first hundred characters or new line
            cout << "\n";

            if (userInput == 'm' || userInput == 'M')
            {
                // Function allows user to enter choice
                Introduction('*', message);

            }
            else if (userInput == 'y' || userInput == 'Y')
            {
                cout << "Please enter the year:";
                cin >> dateInput[0];


                cout << "Please enter the month:";
                cin >> dateInput[1];

                cout << "Please enter the day:";
                cin >> dateInput[2];
                cout << "\n";

                readDates(argv[1], dateInput, results);

                Output(dateInput, results);

            }
            else
            {
                cout << "\nInvalid selection please choose \'m\', \'y\', \'q\'. try again." << endl;
            }
        }
        cout << "Program ending.\n" << endl;

        cout << "Good Bye" << endl;



        // return 0 to indicate success.
        return (0);

    }

