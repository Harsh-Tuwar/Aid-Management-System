/*****************************
Harsh Tuwar
version 2.0
SenecaEmail: htuwar@myseneca.ca
SenecaID: 154-156-160
NOTE: Whole milestone is completed again. Help taken from stackoverflow.
****************************/
#ifndef AMA_ERROR_STATE_H_
#define AMA_ERROR_STATE_H_

#include <iostream>

namespace AMA {

	class ErrorState {
		char *err;
	public:
		explicit ErrorState(const char *errorMessage = nullptr);
		ErrorState(const ErrorState &) = delete;
		virtual ~ErrorState();//deallocator
		ErrorState &operator=(const ErrorState &) = delete;
		void clear();
		bool isClear() const;
		void message(const char *str);
		const char *message() const;
	};
	std::ostream &operator<<(std::ostream &os, const ErrorState &er);

}
#endif  // AMA_ERROR_STATE_H_
