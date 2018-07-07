#pragma once

#include <string>
#include "System.h"

using namespace std;

class SystemImpl : public System{
private:
	string name;
	double stock;
	double last_stock;

public:
	SystemImpl(string, double);

	string get_name();
	void set_name(const string&);
	void set_stock(double);
	double get_stock();
	double get_last_stock();
	bool set_last_stock(double);
	
	System& operator=(System *);
	bool operator==(System *);
	bool operator!=(System *);
};