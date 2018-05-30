/*****************************
Harsh Tuwar
version 2.0
SenecaEmail: htuwar@myseneca.ca
SenecaID: 154-156-160
NOTE: Whole milestone is completed again. Help taken from stackoverflow.
****************************/
#include<iostream>
#include<cstring>
#include<cstdio>
#include<string>

#include"ErrorState.h"

namespace AMA {

	ErrorState::ErrorState(const char *errorMessage){
		err= nullptr;
		message(errorMessage); //call the message function and pass the pointer
	}

	ErrorState::~ErrorState() {
	       /* if(this != 0){
		delete[] this;
		}*/
	       clear();
	}

	void ErrorState::clear() { //deallocates the memory, hence clearing the message
		if (err != nullptr) {
			delete[] err;
			err = nullptr;
		}
	}

	bool ErrorState::isClear() const {

		bool flag = false;
		if (err==nullptr) {
			flag = true;
		}
		return flag;
	}

	

	void ErrorState::message(const char *str) {
		if (str == nullptr) {
			return;
		}
		clear();
		const int sizelength = strlen(str);
		if (sizelength != 0) {
			err = new char[sizelength+1];
			strncpy(err, str, sizelength+1);
		}
	}

	const char *ErrorState::message() const {
		return err;
	}

	std::ostream &operator<<(std::ostream &os, const ErrorState &erst) {
		if (erst.isClear()) {
			return os;
		}
		return os << erst.message();
	}

}
