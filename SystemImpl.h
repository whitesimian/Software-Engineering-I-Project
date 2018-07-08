#pragma once

#include <string>
#include "System.h"
#include "HandleBody.h"

using namespace std;

class SystemImpl : public Body{ /// System Body
private:
	string name;
	double stock;
	double last_stock;

public:
	SystemImpl(string n = "Dummy", double e = 0.0);

	string get_name();
	void set_name(const string&);
	void set_stock(double);
	double get_stock();
	double get_last_stock();
	bool set_last_stock(double);
	
	SystemImpl& operator=(SystemImpl *);
	bool operator==(SystemImpl *);
	bool operator!=(SystemImpl *);
};

class SystemHandle : public System, public Handle<SystemImpl> {

public:
	SystemHandle(const string&, double);

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