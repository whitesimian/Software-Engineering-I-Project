#pragma once

#include "Model.h"
#include <string>

using namespace std;

class System {

public:
	static System* new_system(string, double);

	virtual string get_name()				= 0;
	virtual void set_name(const string&)	= 0;
	virtual void set_stock(double)			= 0;
	virtual double get_stock()				= 0;
	virtual double get_last_stock()			= 0;
	virtual bool set_last_stock(double)		= 0;

	virtual System& operator=(System *)		= 0;
	virtual bool operator==(System *)		= 0;
	virtual bool operator!=(System *)		= 0;
};