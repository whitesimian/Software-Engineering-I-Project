#pragma once

#include <string>
#include "System.h"

using namespace std;

class SystemImpl : public System{
private:
	string name;
	double stock;

public:
	SystemImpl(string, double);

	string get_name();
	void set_name(const string&);
	void set_stock(double);
	double get_stock();

};