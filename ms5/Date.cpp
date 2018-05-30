/*****************************
Harsh Tuwar
version 2.0
SenecaEmail: htuwar@myseneca.ca
SenecaID: 154-156-160
NOTE: Whole milestone is completed again. Help taken from stackoverflow.
****************************/


#define _CRT_SECURE_NO_WARNINGS

#include "Date.h"
#include <iostream>
#include <cstdio>
#include <cstring>

namespace AMA {

int Date::mdays(int month_, int year_) const {
	int days[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, -1};
	int month_tmp = month_ >= 1 && month_ <= 12 ? month_ : 13;
	month_tmp--;
	return days[month_tmp] +
		int((month_tmp == 1) * ((year_ % 4 == 0) && (year_ % 100 != 0)) ||
			(year_ % 400 == 0));
}

void Date::errCode(int errorCode) {
	m_err_state = errorCode;
}

Date::Date() {
	m_year = 0;
	m_day = 0;
	m_month = 0;
	m_comp_val = 0;
	errCode(NO_ERROR);
}

Date::Date(int year, int month, int day) : m_err_state(NO_ERROR) {
	if (year < min_year || year > max_year) {
		Date();
		errCode(YEAR_ERROR);
		return;
	}
	m_year = year;
	if (month < 1 || month > 12) {
		Date();
		errCode(MON_ERROR);
		return;
	}
	m_month = month;
	int days_in_month = mdays(m_month, m_year);
	if (day < 1 || day > days_in_month) {
		Date();
		errCode(DAY_ERROR);
		return;
	}
	m_day = day;
	m_comp_val = m_year * 372 + m_month * 13 + m_day;
}

bool Date::operator==(const Date &rhs) const {
	return m_comp_val == rhs.m_comp_val;
}

bool Date::operator!=(const Date &rhs) const {
	return !(*this == rhs); 
}

bool Date::operator<(const Date &rhs) const {
	return m_comp_val < rhs.m_comp_val;
}

bool Date::operator>(const Date &rhs) const {
	return m_comp_val > rhs.m_comp_val;
}

bool Date::operator<=(const Date &rhs) const {
	return *this < rhs || *this == rhs;
}

bool Date::operator>=(const Date &rhs) const {
	return *this > rhs || *this == rhs;
}

int Date::errCode() const {
	return m_err_state;
}

bool Date::bad() const {
	bool flag;
	flag = (m_err_state != NO_ERROR);
	return flag;
}

std::istream &Date::read(std::istream &is) {
	char date_in[0004 + 1 + 02 + 1 + 02 + 1] = {'\0'};
	is >> date_in;
	int year_ = 0, month_ = 0, day_ = 0;

	if (is.fail() ||
		(sscanf(date_in, "%4d/%2d/%2d", &year_, &month_, &day_) < 3 &&
		 sscanf(date_in, "%4d-%2d-%2d", &year_, &month_, &day_) < 3)) {
		is.setstate(std::ios::failbit);
		errCode(CIN_FAILED);
		return is;
	}
	if (year_ < min_year || year_ > max_year) {
		is.setstate(std::ios::failbit);
		errCode(YEAR_ERROR);
		return is;
	}
	m_year = year_;
	if (month_ < 1 || month_ > 12) {
		is.setstate(std::ios::failbit);
		errCode(MON_ERROR);
		return is;
	}
	m_month = month_;
	int days_in_month = mdays(m_month, m_year);
	if (day_ < 1 || day_ > days_in_month) {
		is.setstate(std::ios::failbit);
		errCode(DAY_ERROR);
		return is;
	}
	m_day = day_;
	m_comp_val = m_year * 372 + m_month * 13 + m_day;
	errCode(NO_ERROR);
	return is;
}

std::ostream &Date::write(std::ostream &ostr) const {

	ostr << m_year << "/";
	if (m_month < 10)
		ostr << "0" << m_month << "/";
	else
		ostr << m_month << "/";
	if (m_day < 10)
		ostr << "0" << m_day;
	else
		ostr << m_day;

	return ostr;

}

std::istream &operator>>(std::istream &lhs, Date &rhs) {
	return rhs.read(lhs);
}

std::ostream &operator<<(std::ostream &lhs, const Date &rhs) {
	return rhs.write(lhs);
}

}
