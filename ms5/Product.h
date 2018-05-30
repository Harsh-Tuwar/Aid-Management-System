/*****************************
Harsh Tuwar
version 2.0
SenecaEmail: htuwar@myseneca.ca
SenecaID: 154-156-160
NOTE: Whole milestone is completed again. Help taken from stackoverflow.
****************************/
#ifndef AMA_PRODUCT_H_
#define AMA_PRODUCT_H_

#include "ErrorState.h"
#include"iProduct.h"
namespace AMA {

	const int max_sku_length = 7;
	const int max_unit_length = 10;
	const int max_name_length = 75;
	const double TAX= 0.13;

	class Product:public iProduct {
		char m_type;
		char m_sku[max_sku_length + 1]; 
		char m_unit[max_unit_length + 1];
		char *m_pro_name;
		int m_qnty_on_hand;
		int m_qnty_needed;
		double m_price;
		bool m_isTaxable;

	protected:
		ErrorState err;
		void name(const char *);
		const char *name() const;
		double cost() const;
		void message(const char *);
		bool isClear() const;
		const char *sku() const;
		const char *unit() const;
		bool taxed() const;
		double price() const;
		ErrorState &error();//extra

	public:
		Product(char = 'N');
		Product(const char * , const char * , const char * , int  = 0, bool = true, double = 0.00, int  = 0);
		Product(const Product &);
		~Product();
		Product &operator=(const Product &);
		std::istream &read(std::istream &is);
		bool operator==(const char *) const;
		std::fstream &store(std::fstream &, bool newline = true) const;
		std::fstream &load(std::fstream &file);
		double total_cost() const;
		void quantity(int);
		bool isEmpty() const;
		int qtyNeeded() const;
		int quantity() const;
		bool operator>(const char *) const;
		bool operator>(const iProduct &) const;
		int operator+=(int);
		std::ostream &write(std::ostream &os, bool linear) const;
	};



	std::ostream &operator<<(std::ostream &, const iProduct &);
	std::istream &operator>>(std::istream &, iProduct &);
	double operator+=(double &, const iProduct &);

}
#endif
