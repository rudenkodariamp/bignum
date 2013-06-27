#include <string>
#include <cstdio>
#include "bignumcpp.h"


Long::Long(const char* s) {
	num = bigread(s);
}



Long::~Long() {
	if (num.d)
		freemem(num);
}
const bignum &Long::getnum() const {
	return num;
}

Long::Long(const bignum &a) {
	num = a;
}

Long::Long(const Long &a) {
	num = bigcopy(a.getnum());
}

Long &Long::operator =(const Long &a) {
	if (this == &a)
		return *this;
	freemem(num);
	num = bigcopy(a.getnum());
	return *this;
}


const Long Long::operator +(Long &a) {
	return Long(bigaddz(num, a.getnum()));
}

const Long Long::operator -(Long &a) {
	return Long(bigsubz(num, a.getnum()));
} 
Long Long::operator -() {
	return Long(bigneg(bigcopy(num)));
}

const Long Long::operator *(Long &a) {
	return Long(bigmul(num, a.getnum()));
}

const Long Long::operator /(Long &a) {
	return Long(bigdiv(num, a.getnum()));
}

const Long Long::operator %(Long &a) {
	return Long(bigmod(num, a.getnum()));
}


bool Long::operator ==(const Long &b) {
	if (bigcompare(b.getnum(), num) == 0) 
		return true;
	else
		return false;
}

bool Long::operator >(const Long &b) {
	if (bigcompare(num, b.getnum()) == 1) 
		return true;
	else
		return false;
}

bool Long::operator <(const Long &b) {
	if (bigcompare(num, b.getnum()) == -1) 
		return true;
	else
		return false;
}
bool Long::operator <=(const Long &b) {
	if (bigcompare(num, b.getnum()) <= 0) 
		return true;
	else
		return false;
}
bool Long::operator >=(const Long &b) {
	if (bigcompare(num, b.getnum()) >= 0) 
		return true;
	else
		return false;
}

void Long::outf(const char * s) {
	bigwrite(num, s);
}

void Long::out() {
	bigout(num);
}
