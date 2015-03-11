/*
 * main.cc
 *
 *  Created on: Apr 17, 2012
 *      Author: jonathan
 */

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cmath>

using namespace std;

/*******************************************************************************
 *
 *
 *
 * 				Helper Functions
 *
 *
 *
 *******************************************************************************/

/**
 * Function that validates the mayan date to make sure the values
 * don't go above or below the bounds.
 */
string validateMayanDate(unsigned int baktun, unsigned int katun, unsigned tun, unsigned int uinal, unsigned int kin) {
	while(1) {
		if (baktun > 19) {
			cout << "date out of bounds.\n";
			exit(1);
		}

		if (katun >= 20) {
			katun -= 20;
			baktun++;
		}

		if (tun >= 20) {
			tun -= 20;
			katun++;
		}

		if (uinal >= 18) {
			uinal -= 18;
			tun++;
		}

		if (kin >= 20) {
			kin -= 20;
			uinal++;
		}

		if (baktun < 0 || katun < 0 || tun < 0 || uinal < 0 || kin < 0) {
			cout << "date out of bounds.\n";
			exit(1);
		}

		if (kin < 20 && uinal < 18 && tun < 20 &&  katun < 20 && baktun < 20) {
			std::ostringstream oss;
			oss << "" << baktun;
			oss << "." << katun;
			oss << "." << tun;
			oss << "." << uinal;
			oss << "." << kin;
			return oss.str();
		}
	}

	return "error validating date.\n";
}

/**
 * Function that validates the gregorian date to make sure the values
 * don't go above or below the bounds.
 */
void validateGregorianDate(unsigned int month, unsigned int day, int year) {
	if (year > 4772 || year < -3113) {
		cout << "date out of bounds.\n";
		exit(1);
	}

	if (year == 4772) {
		if (month == 10) {
			if (day >= 13) {
				cout << "date out of bounds.\n";
				exit(1);
			}
		} else if (month > 10) {
			cout << "date out of bounds.\n";
			exit(1);
		}
	}

	if (year == -3113) {
		if (month == 8) {
			if (day <= 10) {
				cout << "date out of bounds.\n";
				exit(1);
			}
		} else if (month < 8) {
			cout << "date out of bounds.\n";
			exit(1);
		}
	}
}


/**
 * Converts the Gregorian Date into a number of days
 * Returns the number of days that correspond to the gregorian date
 */
unsigned int convertToDays(unsigned int month, unsigned int day, int year) {
	unsigned int days = 0;
	int base = -3113;
	int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	validateGregorianDate(month, day, year);

	if (year > base)
		days+= 142;

	if (year == base) {
		if (month <= 8 && day < 11) {
			cout << "Not a valid mayan date.";
		} else {
			if (month == 8) {
				days += day;
				days -= 11;
			} else {
				for (unsigned int i = 8; i < month; i++) {
					days += monthDays[i];
				}
				days += day;
			}
			return days;
		}
	} else {
		for (;;) {
			if ((base % 4 == 0 && !(base % 100 == 0)) || (base % 400 == 0))
				days++;
			base++;
			if (base == year)
				break;
			days += 365;
		}

		if ((year % 4 == 0 && !(year % 100 == 0)) || (year % 400 == 0))
			monthDays[2] = 29;

		for (unsigned int i = 1; i < month; i++) {
			days += monthDays[i];
		}

		days += day;

		return days;
	}

	return 0;
}

/**
 * Converts the Mayan Date into a number of days
 * Returns the number of days that correspond to the mayan date
 */
unsigned int convertToDays(unsigned int baktun, unsigned int katun, unsigned tun, unsigned int uinal, unsigned int kin) {
	unsigned int a, b, c, d, e;
	a = 144000 * baktun;
	b = 7200 * katun;
	c = 360 * tun;
	d = 20 * uinal;
	e = kin;

	string result = validateMayanDate(baktun, katun, tun, uinal, kin);

	unsigned int days = a + b + c + d + e;
	return days;
}

/**
 * Converts the specified days into a mayan date
 */
string convertToMayan(unsigned int dayArg) {
	unsigned int days = dayArg;
	unsigned int baktun = 0, katun = 0, tun = 0, uinal = 0, kin = 0;

	while (days > 0) {

		if (days >= 144000) {
			baktun++;
			days -= 144000;
		}

		if (days >= 7200) {
			days -= 7200;
			katun++;
		}

		if (days >= 360) {
			days -= 360;
			tun++;
		}

		if (days >= 20) {
			days -= 20;
			uinal++;
		}

		if (days <= 20) {
			kin += days;
			days = 0;
		}
	}

	string result = validateMayanDate(baktun, katun, tun, uinal, kin);
	return result;
}

/**
 * Converts the specified days into a gregorian date
 */
string convertToGregorian(unsigned int dayArg) {
	unsigned int days = dayArg;
	unsigned int month = 1, day = 1;
	unsigned int monthDays[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	string monthNames[13] = {"", "January", "February", "March", "April", "May", "June", 
		"July", "August", "September", "October", "November", "December"};
	string dayOfTheWeek[7] = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday",
			"Saturday", "Sunday"};
	int year = -3113;

	if (days < 142) {
		for (month = 8; days > monthDays[month]; month++) {
			days -= monthDays[month];
		}
		days += 11;
		if (days > monthDays[month]) {
			days -= monthDays[month];
			month++;
		}
		day = days;
	} else {
		days -= 142;
		for (;;) {
			year++;
			if ((year % 4 == 0 && !(year % 100 == 0)) || (year % 400 == 0))
				days--;
			if (days < 365)
				break;
			days -= 365;
		}

		for (month = 1; days > monthDays[month]; month++) {
			days -= monthDays[month];
		}

		day = days;
	}

	validateGregorianDate(month, day, year);

	std::ostringstream oss;
	oss << dayOfTheWeek[dayArg % 7] << " ";
	oss << monthNames[month] << " ";
	oss << day << ", ";

	if (year < 0) {
		oss << abs (year-1) << " B.C.\n";
	} else {
		oss << year << " A.D.\n";	
	}
	return oss.str();
}


/*******************************************************************************
 *
 *
 *
 * 				Main Functions
 *
 *
 *
 *******************************************************************************/


/*
 * Adds a number of days to a mayan date
 * Returns the mayan date with the # of days added
 */
void MayanPlus(char* dateArg, char* daysArg) {
	unsigned int days, baktun, katun, tun, uinal, kin;

	if (sscanf(dateArg, "%u.%u.%u.%u.%u", &baktun, &katun, &tun, &uinal, &kin) != 5) {
		cout << "invalid argument for mayan date or days.\n";
		exit(1);
	}

	if (sscanf(daysArg, "%u", &days) != 1) {
		cout << "invalid argument for days.\n";
		exit(1);
	}

	unsigned int mayanDays = convertToDays(baktun, katun, tun, uinal, kin);
	mayanDays += days;

	string result = convertToMayan(mayanDays);
	std::cout << result << "\n";
}

/**
 * Subtracts a number of days from a mayan date
 * Returns the mayan date with the # of days subtracted
 */
void MayanMinus(char* dateArg, char* daysArg) {
	unsigned int days, baktun, katun, tun, uinal, kin;

	if (sscanf(dateArg, "%u.%u.%u.%u.%u", &baktun, &katun, &tun, &uinal, &kin) != 5) {
		cout << "invalid argument for days or mayan date.\n";
		exit(1);
	}

	if (sscanf(daysArg, "%u", &days) != 1) {
		cout << "invalid argument for days.\n";
		exit(1);
	}

	unsigned int mayanDays = convertToDays(baktun, katun, tun, uinal, kin);
	mayanDays -= days;

	string result = convertToMayan(mayanDays);
	std::cout << result << "\n";
}

/**
 * Compares two mayan dates and
 * Returns the number of days in between them.
 */
void MayanCompare(char* dateOne, char* dateTwo) {
	unsigned int baktun, katun, tun, uinal, kin;
	unsigned int daysOne = 0, daysTwo = 0;

	if( sscanf(dateOne, "%u.%u.%u.%u.%u", &baktun, &katun, &tun, &uinal, &kin) != 5) {
		cout << "invalid mayan date for second or third argument\n";
		exit(1);
	} else {
		daysOne = convertToDays(baktun, katun, tun, uinal, kin);
	}

	if( sscanf(dateTwo, "%u.%u.%u.%u.%u", &baktun, &katun, &tun, &uinal, &kin) != 5) {
		cout << "invalid mayan date for third argument\n";
		exit(1);
	} else {
		daysTwo = convertToDays(baktun, katun, tun, uinal, kin);
	}

	int days = daysOne-daysTwo;

	if (days >= 0) {
		cout << "Day Difference: " << days << "   ";
		string result = convertToGregorian(days);
		std::cout << "\nDate Conversion: " << result << "\n";
	} else {
		days = daysTwo - daysOne;
		cout << "Day Difference: " << days << "   ";
		string result = convertToGregorian(days);
		std::cout << "\nDate Conversion: " << result << "\n";
	}
}

/*
 * Adds a number of days to a gregoran date
 * Returns the gregorian date with the # of days added
 */
void GregorianPlus(char* dateArg, char* daysArg) {
	unsigned int days, month, day, year;

	if (sscanf(dateArg, "%u/%u/%d", &month, &day, &year) != 3) {
		cout << "invalid gregorian date entered.\n";
		exit(1);

	}

	if (sscanf(daysArg, "%u", &days) != 1) {
		cout << "invalid argument for days.\n";
		exit(1);
	}

	unsigned int gregorianDays = convertToDays(month, day, year);
	gregorianDays += days;

	string result = convertToGregorian(gregorianDays);
	std::cout << result << "\n";
}

/*
 * Subtracts a number of days from a gregoran date
 * Returns the gregorian date with the # of days subtracted
 */
void GregorianMinus(char* dateArg, char* daysArg) {
	unsigned int days, month, day, year;

	if (sscanf(dateArg, "%u/%u/%d", &month, &day, &year) != 3) {
		cout << "invalid gregorian date entered.\n";
		exit(1);

	}

	if (sscanf(daysArg, "%u", &days) != 1) {
		cout << "invalid argument for days.\n";
		exit(1);
	}

	unsigned int gregorianDays = convertToDays(month, day, year);
	gregorianDays -= days;

	string result = convertToGregorian(gregorianDays);
	std::cout << result << "\n";
}

/**
 * Compares two gregorian dates and
 * Returns the number of days in between them in gregorian form.
 */
void GregorianCompare(char* dateOne, char* dateTwo) {
	unsigned int month, day, year;
	unsigned int daysOne = 0, daysTwo = 0;

	if (sscanf(dateOne, "%u/%u/%d", &month, &day, &year) != 3) {
			cout << "invalid gregorian date for second or third argument.\n";
			exit(1);
	} else {
		daysOne = convertToDays(month, day, year);
	}

	if (sscanf(dateTwo, "%u/%u/%d", &month, &day, &year) != 3) {
		cout << "invalid gregorian date for third argument.\n";
		exit(1);
	} else {
		daysTwo = convertToDays(month, day, year);
	}

	int days = daysOne-daysTwo;

	if (days >= 0) {
		cout << "Day Difference: " << days << "   ";
		string result = convertToGregorian(days);
		std::cout << "\nDate Conversion: " << result << "\n";
	} else {
		days = daysTwo - daysOne;
		cout << "Day Difference: " << days << "   ";
		string result = convertToGregorian(days);
		std::cout << "\nDate Conversion: " << result << "\n";
	}
}

/**
 * Used for testing multiple test cases for gregorian input.
 */
void testFunction(unsigned int month, unsigned int day, int year) {
	unsigned int days = convertToDays(month, day, year);
	string result = convertToMayan(days);
	std::cout << result << "\n";
}

/**
 * Used for testing multiple test cases for mayan input.
 */
void testFunction(unsigned int baktun, unsigned int katun, unsigned int tun, unsigned int uinal, unsigned int kin) {
	unsigned int days = convertToDays(baktun, katun, tun, uinal, kin);
	string result = convertToGregorian(days);
	std::cout << result << "\n";
}

/**
 * Takes a gregorian date, outputs a mayan date
 */
void GregorianConvert(char* gDate) {
	unsigned int month, day;
	int year;
	if (sscanf(gDate, "%u/%u/%d", &month, &day, &year) != 3)
		cout << "invalid gregorian date entered.\n";
	else
		testFunction(month, day, year);
}

/**
 * Takes a mayan date, outputs a gregorian date
 */
void MayanConvert(char* mDate) {
	unsigned int baktun, katun, tun, uinal, kin;
	if (sscanf(mDate, "%u.%u.%u.%u.%u", &baktun, &katun, &tun, &uinal, &kin) != 5)
		cout << "invalid mayan date entered.\n";
	else
		testFunction(baktun, katun, tun, uinal, kin);
}

/*******************************************************************************
 *
 *
 *
 * 				Start Function
 *
 *
 *
 *******************************************************************************/


/*
* main function that checks the arguments and calls the corresponding main function
*/
int main(int argc, char** argv) {

	if (argv[1] == NULL) {
		cout << "no arguments entered.\n";
		exit(1);
	}

	if (strcmp(argv[1],"m+d") == 0) {
		if (argv[2] == NULL || argv[3] == NULL) {
			cout << "second or third argument is null\n";
			exit(1);
		}
		MayanPlus(argv[2], argv[3]);
	} else if (strcmp(argv[1],"m-d") == 0) {
		if (argv[2] == NULL || argv[3] == NULL) {
			cout << "second or third argument is null\n";
			exit(1);
		}
		MayanMinus(argv[2], argv[3]);
	} else if (strcmp(argv[1],"m-m") == 0) {
		if (argv[2] == NULL || argv[3] == NULL) {
			cout << "second or third argument is null\n";
			exit(1);
		}
		MayanCompare(argv[2], argv[3]);
	} else if (strcmp(argv[1],"g+d") == 0) {
		if (argv[2] == NULL || argv[3] == NULL) {
			cout << "second or third argument is null\n";
			exit(1);
		}
		GregorianPlus(argv[2], argv[3]);
	} else if (strcmp(argv[1],"g-d") == 0) {
		if (argv[2] == NULL || argv[3] == NULL) {
			cout << "second or third argument is null\n";
			exit(1);
		}
		GregorianMinus(argv[2], argv[3]);
	} else if (strcmp(argv[1],"g-g") == 0) {
		if (argv[2] == NULL || argv[3] == NULL) {
			cout << "second or third argument is null\n";
			exit(1);
		}
		GregorianCompare(argv[2], argv[3]);
	} else if (strcmp(argv[1],"g=") == 0) {
		if (argv[2] == NULL) {
			cout << "second argument is null\n";
			exit(1);
		}
		GregorianConvert(argv[2]);
	} else if (strcmp(argv[1],"m=") == 0) {
		if (argv[2] == NULL) {
			cout << "second argument is null\n";
			exit(1);
		}
		MayanConvert(argv[2]);
	} else {
		cout << "invalid 1st argument.\n";
	}

	return 0;
}
