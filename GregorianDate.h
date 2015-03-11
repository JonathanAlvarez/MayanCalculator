/*
 * GregorianDate.h
 *
 *  Created on: Apr 17, 2012
 *      Author: jonathan
 */

#ifndef GREGORIANDATE_H_
#define GREGORIANDATE_H_

class GregorianDate {
	unsigned int month, day;
	int year; //since years can go into negative B.C. range

public:
	GregorianDate();
	GregorianDate(unsigned int, unsigned int, int);
	void set(unsigned int, unsigned int, int);
	GregorianDate& operator++();
	bool operator==(const GregorianDate&) const;
	bool operator!=(const GregorianDate&) const;
	int operator-(const GregorianDate&) const;
	GregorianDate operator-(unsigned int) const;
	GregorianDate operator+(unsigned int) const;
	void get_string(char*, unsigned int) const;
};

#endif /* GREGORIANDATE_H_ */
