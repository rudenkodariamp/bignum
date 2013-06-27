%module bignumcpp

%{
#define SWIG_FILE_WITH_INIT
#include "bignumcpp.h"
%}

class Long {
private:
	bignum num;
public:
	Long(const char *);
	~Long();
	Long(const Long &);
	Long &operator =(const Long&); 
	const Long operator +(Long&);
	const Long operator -(Long&);
	Long operator -();
	const Long operator *(Long&);
	const Long operator /(Long&);
	const Long operator %(Long&);

	bool operator ==(const Long&);
	bool operator <(const Long&);
	bool operator >(const Long&);
	bool operator <=(const Long&);
	bool operator >=(const Long&);

	Long(const bignum&);
	const bignum& getnum() const;
	void outf(const char *);
	void out();
};
