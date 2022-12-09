#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

using namespace std;

const int DATE_ARRAY_SIZE = 3;

struct resultsType {
	int startDate[DATE_ARRAY_SIZE];
	int endDate[DATE_ARRAY_SIZE];
	string name;
	string terms;
};



void Output(int userDate[DATE_ARRAY_SIZE], resultsType results) {
	ofstream fsOut;
	fsOut.open("results.txt");
	if (fsOut.is_open()) {
		cout << "On " << userDate[1] << "/" << userDate[2] << "/" << userDate[0] << " "
			<< results.name << " was president and served " << results.terms
			<< " from " << results.startDate[1] << "/" << results.startDate[2] << "/" << results.startDate[0]
			<< " to " << results.endDate[1] << "/" << results.endDate[2] << "/" << results.endDate[0] << ".\n";

		fsOut << "On " << userDate[1] << "/" << userDate[2] << "/" << userDate[0] << " "
			<< results.name << " was president and served " << results.terms
			<< " from " << results.startDate[1] << "/" << results.startDate[2] << "/" << results.startDate[0]
			<< " to " << results.endDate[1] << "/" << results.endDate[2] << "/" << results.endDate[0] << ".\n";
	}
}



int main() {    

	resultsType results{   // filled struct for testing Output
		{1789,4,30}, {1797,3,3}, "George Washington", "2 full terms"
	};

	int inputDate[DATE_ARRAY_SIZE] = { 1792, 1, 1 };

	Output(inputDate, results);
}





