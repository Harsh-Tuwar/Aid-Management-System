/*****************************
Harsh Tuwar
version 2.0
SenecaEmail: htuwar@myseneca.ca
SenecaID: 154-156-160
NOTE: Whole milestone is completed again. Help taken from stackoverflow.
****************************/
#include "Product.h"

#include <cstring>
#include <fstream>
#include <iomanip>
#include <string>

namespace AMA {

	static constexpr char kFieldDelim = ',';

	// Creates an empty Product object with safe-state values.
	Product::Product(char TYPE)
		: m_type(TYPE),
		m_sku{ '\0' },
		m_unit{ '\0' },
		m_pro_name(nullptr),
		m_qnty_on_hand(0),
		m_qnty_needed(0),
		m_price(0.00),
		m_isTaxable(false),
		err() {
	}
	// data members set to a safe empty state
	Product::Product(
		const char *SKU,
		const char *NAME,
		const char *UNIT,
		int ON_HAND,
		bool STATUS,
		double pRICE,
		int NEED)
		: m_pro_name(nullptr),
		m_qnty_on_hand(ON_HAND),
		m_qnty_needed(NEED),
		m_price(pRICE),
		m_isTaxable(STATUS),
		err() {
		name(NAME);

		if (SKU != nullptr) {
			strncpy(m_sku, SKU, sizeof(m_sku));
		}

		if (m_unit != nullptr) {
			strncpy(m_unit, UNIT, sizeof(m_unit));
		}
	}

	Product::Product(const Product &pr) {

		  // assigning the parameter to the current object
		m_type = pr.m_type;
		strncpy(m_sku, pr.m_sku, strlen(pr.m_sku));
		m_sku[strlen(pr.m_sku)] = '\0';
		strncpy(m_unit, pr.m_unit, strlen(pr.m_unit));
		m_unit[strlen(pr.m_unit)] = '\0';
		m_qnty_on_hand = pr.m_qnty_on_hand;
		m_qnty_needed = pr.m_qnty_needed;
		m_price = pr.m_price;
		m_isTaxable = pr.m_isTaxable;
		m_pro_name = nullptr;
		name(pr.m_pro_name);
	}

	Product::~Product() {
		name(nullptr); // calls the name function below
	}

	void Product::name(const char *p_name) {
		if (p_name == nullptr && m_pro_name != nullptr) {
			delete[] m_pro_name;
			m_pro_name = nullptr;
		}

		else if (p_name != nullptr) {
			if (m_pro_name != nullptr) {
				delete[] m_pro_name;
				m_pro_name = nullptr;
			}
			size_t size = strlen(p_name) + 1;
			m_pro_name = new char[size];
			strncpy(m_pro_name, p_name, size);
		}
	}

	const char *Product::name() const {
		if (m_pro_name[0] == '\0') {
			return nullptr;
		}
		return m_pro_name;
	}

	double Product::cost() const {
		double total = m_price;
		if (m_isTaxable) {
			total *= 0.13;
		}
		return total;
	}

	void Product::message(const char *msg) {
		err.message(msg);
	}

	bool Product::isClear() const {
		return err.isClear();
	}
	const char *Product::sku() const {
		return m_sku;
	}
	const char *Product::unit() const {
		return m_unit;
	}
	bool Product::taxed() const {
		return m_isTaxable;
	}
	double Product::price() const {
		return m_price;
	}

	Product &Product::operator=(const Product &pr) {
		m_type = pr.m_type;
		strncpy(m_sku, pr.m_sku, sizeof(m_sku));
		strncpy(m_unit, pr.m_unit, sizeof(m_unit));
		name(pr.m_pro_name);
		m_qnty_on_hand = pr.m_qnty_on_hand;
		m_qnty_needed = pr.m_qnty_needed;
		m_price = pr.m_price;
		m_isTaxable = pr.m_isTaxable;
		message(pr.err.message());
		return *this;
	}

	std::istream &Product::read(std::istream &is) {
		std::cout << " Sku: ";
		std::string value_tmp;
		is >> value_tmp;
		strncpy(m_sku, value_tmp.c_str(), sizeof(m_sku));

		std::cout << " Name (no spaces): ";
		is >> value_tmp;
		name(value_tmp.c_str());

		std::cout << " Unit: ";
		is >> value_tmp;
		strncpy(m_unit, value_tmp.c_str(), sizeof(m_unit));

		std::cout << " Taxed? (y/n): ";
		is.get();						  
		char value_ch = toupper(is.get()); 
		if (value_ch != 'Y' && value_ch != 'N') {
			is.setstate(std::ios::failbit);
			message("Only (Y)es or (N)o are acceptable");
			return is;
		}
		m_isTaxable = value_ch != 'N';

		std::cout << " Price: ";
		double value_d;
		is >> value_d;
		if (is.fail()) {
			message("Invalid Price Entry");
			return is;
		}
		m_price = value_d;

		std::cout << " Quantity on hand: ";
		int value_i;
		is >> value_i;
		if (is.fail()) {
			message("Invalid Quantity Entry");
			return is;
		}
		m_qnty_on_hand = value_i;

		std::cout << " Quantity needed: ";
		is >> value_i;
		if (is.fail()) { 
			message("Invalid Quantity Needed Entry");
			return is;
		}
		m_qnty_needed = value_i;
		err.clear();
		is.get();
		return is;
	}
	std::fstream &Product::store(std::fstream &file, bool insert_newline) const {
		file.put(m_type) << ',' << m_sku << ',' << m_pro_name << ',' << m_unit
			<< ',' << m_isTaxable << ',' << m_price << ',' << m_qnty_on_hand << ','
			<< m_qnty_needed;
		if (insert_newline) {
			file << std::endl;
		}
		return file;
	}

	std::ostream &Product::write(std::ostream &os, bool linear) const {
		if (linear) {
			os << std::left << std::setfill(' ') << std::setw(max_sku_length);
			os << m_sku << std::setw(0) << std::right << "|"; 
			os << std::left << std::setw(20) << m_pro_name << std::setw(0)
				<< std::right << "|";
			char cost_str[256] = { '\0' };
			sprintf(cost_str, "%.2lf", m_isTaxable ? m_price * (1.0 + 0.13) : m_price);
			os << std::setw(7) << cost_str << std::setw(0) << "|";
			os << std::setw(4) << m_qnty_on_hand << std::setw(0) << "|";
			os << std::left << std::setw(max_unit_length) << m_unit
				<< std::setw(0) << std::right << "|";
			os << std::setw(4) << m_qnty_needed << std::setw(0) << "|";
		}
		else {
			os << " Sku: " << m_sku << std::endl;
			os << " Name (no spaces): " << m_pro_name << std::endl;
			std::streamsize old_precision = os.precision();
			os << " Price: " << std::fixed << std::setprecision(2) << m_price
				<< std::setprecision(old_precision) << std::endl;
			os.unsetf(std::ios::floatfield);
			os << " Price after tax: ";
			if (m_isTaxable) {
				os << std::fixed << std::setprecision(2) << total_cost()
					<< std::setprecision(old_precision) << std::endl;
				os.unsetf(std::ios::floatfield);
			}
			else {
				os << "N/A" << std::endl;
			}

			os << " Quantity on Hand: " << m_qnty_on_hand << " " << m_unit
				<< std::endl;
			os << " Quantity needed: " << m_qnty_needed;
		}
		return os;
	}

	std::fstream &Product::load(std::fstream &file) {
		Product tmp;
		size_t field_count = 1;
		bool done = false;
		while (!file.eof() && !done) {
			std::string field_tmp;
			std::getline(file, field_tmp, ',');

			switch (field_count++) {
			case 1:
				strncpy(tmp.m_sku, field_tmp.c_str(), sizeof(tmp.m_sku));
				break;
			case 2:
				tmp.name(field_tmp.c_str());
				break;
			case 3:
				strncpy(
					tmp.m_unit, field_tmp.c_str(), sizeof(tmp.m_unit));
				break;
			case 4:
				tmp.m_isTaxable = strtol(field_tmp.c_str(), NULL, 10);
				break;
			case 5:
				tmp.m_price = strtod(field_tmp.c_str(), NULL);
				break;
			case 6:
				tmp.m_qnty_on_hand = strtol(field_tmp.c_str(), NULL, 10);
				break;
			case 7:
				tmp.m_qnty_needed = strtol(field_tmp.c_str(), NULL, 10);
				done = true;
				break;
			}
		}
		*this = tmp;
		return file;
	}


	bool Product::operator==(const char *str) const {
		return !strcmp(m_sku, str); 
	}


	double Product::total_cost() const {
		double total = m_price * m_qnty_on_hand;
		if (m_isTaxable) {
			total *= 1.00 + 0.13;
		}
		return total;
	}

	void Product::quantity(int Received) {
		m_qnty_on_hand = Received;
	}
	bool Product::isEmpty() const {
		bool flag = false;
		if (m_pro_name[0] == '\0') {
			flag = true;
		}
		else {
			flag = false;
		}
		return flag;
	}

	int Product::qtyNeeded() const {
		return m_qnty_needed;
	}
	int Product::quantity() const {
		return m_qnty_on_hand;
	}

	bool Product::operator>(const char *SKU) const {
		return strcmp(m_sku, SKU) > 0;
	}

	bool Product::operator>(const iProduct &pr) const {
		
		int check = strcmp(m_sku, pr.name());
		if (check > 0) {
			return true;
		}
		else {
			return false;
		}
	}

	int Product::operator+=(int ADD) {
		if (ADD > 0) {
			m_qnty_on_hand += ADD;
			;
		}
		return m_qnty_on_hand;
	}

	ErrorState &Product::error() {
		return err;
	}

	std::ostream &operator<<(std::ostream &os, iProduct &product) {
		return product.error().message() == nullptr ||
			strlen(product.error().message()) == 0U
			? product.write(os, true)
			: os << product.error().message();
	} 

	std::istream &operator>>(std::istream &is, iProduct &product) {
		return product.read(is);
	}

	double operator+=(double &cst, const iProduct &product) {
		return cst += product.total_cost();
	}
}
