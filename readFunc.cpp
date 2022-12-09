#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const int DATE_ARRAY_SIZE = 3;

struct resultsType {
    int startDate[DATE_ARRAY_SIZE];
    int endDate[DATE_ARRAY_SIZE];
    string name;
    string terms;
};


bool readDates (int userDate[], resultsType &results);

int main()
{
    //dummy main for testing

    resultsType results;

    int userDate[DATE_ARRAY_SIZE] = {2013,1,21}; //assigning a test variable to simulate user input

    if (!readDates(userDate, results))
    {
        cout << "Error, date out of bounds." << endl;
        return -1;
    }

    else
    {
        cout << endl;
        cout << results.name << " was president ";
        for (int i = 0; i < DATE_ARRAY_SIZE; i++)
        {
            cout << results.startDate[i] << '/';
        }
        cout << " - ";
        for (int i = 0; i < DATE_ARRAY_SIZE; i++)
        {
            cout << results.endDate[i] << '/';
        }
        if (results.terms ==  "currently serving")
            cout << endl << "he is " << results.terms;
        else
            cout << endl << "he served " << results.terms;
    }

    return 0;
}

bool readDates (int userDate[], resultsType &results)
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
        for (int i = 0 ; i < DATE_ARRAY_SIZE ; i++)
        {
            inFile >> results.startDate[i];
            inFile.ignore(100, ' ');
        }

        //skips to an end date and inputs it into an arrray
        inFile.ignore(100, '#');
        for (int i = 0 ; i < DATE_ARRAY_SIZE; i++)
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