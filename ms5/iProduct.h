/*****************************
Harsh Tuwar
version 2.0
SenecaEmail: htuwar@myseneca.ca
SenecaID: 154-156-160
NOTE: Whole milestone is completed again. Help taken from stackoverflow.
****************************/
#ifndef AMA_IPRODUCT_H_
#define AMA_IPRODUCT_H_

#include <fstream>
#include<iostream>

#include "ErrorState.h"

namespace AMA {

	class iProduct {
	public:
		virtual std::fstream &store(std::fstream &, bool /*new_line*/ = true) const = 0;
		virtual std::fstream &load(std::fstream &) = 0;
		virtual std::ostream &write(std::ostream &, bool ) const = 0;
		virtual std::istream &read(std::istream &) = 0;
		virtual bool operator==(const char * ) const = 0;
		virtual double total_cost() const = 0;
		virtual const char *name() const = 0;
		virtual void quantity(int) = 0;
		virtual int qtyNeeded() const = 0;
		virtual int quantity() const = 0;
		virtual int operator+=(int ) = 0;
		virtual bool operator>(const iProduct &) const = 0;
		virtual const char *sku() const = 0;
		virtual ErrorState &error() = 0;
	};

	std::ostream &operator<<(std::ostream &, iProduct &);
	std::istream &operator>>(std::istream &, iProduct &);
	double operator+=(double &, const iProduct &);
	iProduct *CreateProduct();
	iProduct *CreatePerishable();

}
#endif
