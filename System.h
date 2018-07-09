/*
* FELIPE CÉSAR LOPES MACHADO - 16.2.5890
* UFOP - UNIVERSIDADE FEDERAL DE OURO PRETO
* JUL/2018
*/

#pragma once

#include "Model.h"
#include <string>

using namespace std;

class System {

public:
	virtual ~System() {};
	
	virtual string get_name()			= 0;
	virtual void set_name(const string&)		= 0;
	virtual void set_stock(double)			= 0;
	virtual double get_stock()			= 0;
	virtual double get_last_stock()			= 0;
	virtual bool set_last_stock(double)		= 0;

	virtual System& operator=(System *)		= 0;
	virtual bool operator==(System *)		= 0;
	virtual bool operator!=(System *)		= 0;
};
