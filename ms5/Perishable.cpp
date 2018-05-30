/*****************************
Harsh Tuwar
version 2.0
SenecaEmail: htuwar@myseneca.ca
SenecaID: 154-156-160
NOTE: Whole milestone is completed again from start. Help taken from stackoverflow.
****************************/

#include "Product.h"
#include "Perishable.h"
#include"Date.h"
#include"iProduct.h"

#include <string>
#include <fstream>
#include <iomanip>
#include <cstring>
#include<iostream>
#include<cstdio>

namespace AMA {

	Perishable::Perishable() : Product('P') {}

	std::fstream &Perishable::store(std::fstream &file, bool newLine) const {
		Product::store(file, false) << ',' << m_exp_date; //calls its base class store function, inserts a comma after each record and appends the expiry date at the end
		if (newLine) {
			file << "\n";
		}
		return file;
	}
	
	std::fstream &Perishable::load(std::fstream &file) {
		Product::load(file); 
		file >> m_exp_date;
		return file;
	}
	
	std::ostream &Perishable::write(std::ostream &os, bool linear) const {
		Product::write(os, linear); 
		if (isEmpty()) { 
			return os;
		}
		if (linear) { 
			os << m_exp_date;
		}
		else {
			os << std::endl << " Expiry date: " << m_exp_date;
		}
		return os;
	}
	
	std::istream &Perishable::read(std::istream &is) {
		Product::read(is); //same phenomenon as above
		if (is.fail()) {
			return is; //fail is a default istream member function that checks if the procedure will fail or not
		}
		std::cout << " Expiry date (YYYY/MM/DD): ";
		is >> m_exp_date;
		if (m_exp_date.bad()) { //default istream function that checks if the data is corrupted or not
			switch (m_exp_date.errCode()) {
			case CIN_FAILED:  //this can also be done using if else
				message("Invalid Date Entry");
				break;
			case YEAR_ERROR:
				message("Invalid Year in Date Entry");
				break;
			case MON_ERROR:
				message("Invalid Month in Date Entry");
				break;
			case DAY_ERROR:
				message("Invalid Day in Date Entry");
				break;
			}
		}
		else {
			error().clear(); //set the data to a valid(good) state
		}
		return is;
	}
	const Date &Perishable::expiry() const {
		return m_exp_date;
	}

}
