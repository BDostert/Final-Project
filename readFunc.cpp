#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void readDates (int userDate[], int startDate[], int endDate[], string& presidentName, string& termsServed);

int robert()
{
    //dummy main for testing

    string presidentName;
    string termsServed;
    int startDate[3], endDate[3];
    int userDate[3] = {2013,2,20}; //assigning a test variable to simulate user input

    readDates(userDate, startDate, endDate, presidentName, termsServed);

    cout << endl;
    cout << presidentName << " was president ";
    for (int i = 0; i < 3; i++)
    {
        cout << startDate[i] << '/';
    }
    cout << " - ";
    for (int i = 0; i < 3; i++)
    {
        cout << endDate[i] << '/';
    }
    if (termsServed ==  "currently serving")
        cout << endl << "he is " << termsServed;
    else
        cout << endl << "he served " << termsServed;

    return 0;
}

void readDates (int userDate[], int startDate[], int endDate[], string& presidentName, string& termsServed)
{
    //Variables
    ifstream inFile;
    bool matchFound = false;

    //open input file
    inFile.open("Presidents.txt");

    //loop continues until a matching date range is found or the input file ends
    while (!matchFound && !inFile.eof())
    {
        //skips to a start date and inputs it into an array
        inFile.ignore(100, '@'); 
        for (int i = 0 ; i<3 ; i++)
        {
            inFile >> startDate[i];
            inFile.ignore(100, ' ');
        }

        //skips to an end date and inputs it into an arrray
        inFile.ignore(100, '#');
        for (int i = 0 ; i<3 ; i++)
        {
            inFile >> endDate[i];
            inFile.ignore(100, ' ');
        }

        //If structure to compare dates

        if (userDate[0] > startDate[0] && userDate[0] < endDate[0])    //compares user date year against year range
            matchFound = true;

        else if (userDate[0] == startDate[0])   // if same as start year, compare months
        {
            if (userDate[1] > startDate[1])
                matchFound = true;

            else if (userDate[1] == startDate[1])   // if same months, compare days
                if (userDate[2] >= startDate[2])    
                    matchFound = true;
        }

        else if (userDate[0] == endDate[0]) // if same as end year, compare months
        {
            if (userDate[1] < endDate[1])
                matchFound = true;
            else if (userDate[1] == startDate[1]) // if same month, compare days
                if (userDate[2] <= endDate[2])
                    matchFound = true;
        }
    } // end of While loop
    
    if (!matchFound)
        cout << "Date out of bounds.";
    else
    {
        inFile.ignore(100, '*');
        getline(inFile, presidentName, '*');
        inFile.ignore(100, '$');
        getline(inFile, termsServed);
    }

    //Closing the inpute file
    inFile.close();
}