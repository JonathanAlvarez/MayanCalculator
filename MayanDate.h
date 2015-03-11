/*
 * MayanDate.h
 *
 *  Created on: Apr 17, 2012
 *      Author: jonathan
 */

#ifndef MAYANDATE_H_
#define MAYANDATE_H_

class MayanDate {
	unsigned int kin, //1 kin = 1 day
	uinal, // 1 uinal = 20 days = 20 kin
	tun, // 1 tun = 360 days = 18 uinal
	katun, // 1 ka'tun = 7200 days = 20 tun
	baktun; // 1 bak'tun = 144000 days = 20 Ka'tun

public:
	MayanDate();
	MayanDate(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	void set(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);
	MayanDate& operator++();
	int operator-(const MayanDate&) const;
	MayanDate operator+(unsigned int) const;
	MayanDate operator-(unsigned int) const;
	bool operator==(const MayanDate&) const;
	bool operator!=(const MayanDate&) const;
	void get_string(char*, unsigned int) const;
};


#endif /* MAYANDATE_H_ */
