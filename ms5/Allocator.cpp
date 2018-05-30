/*****************************
Harsh Tuwar
version 2.0
SenecaEmail: htuwar@myseneca.ca
SenecaID: 154-156-160
NOTE: Whole milestone is completed again. Help taken from stackoverflow.
****************************/
#include "Product.h"
#include "Perishable.h"

namespace AMA {

	// creates an empty product
	//
	iProduct* CreateProduct() {
		return new Product();
	}

	// creates an empty perishable product
	//
	iProduct* CreatePerishable() {
		return new Perishable();
	}
}
