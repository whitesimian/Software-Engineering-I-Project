#pragma once

#include "Flow.h"
#include "System.h"
#include <cstring>
#include <vector>

using namespace std;

class Flow;
class System;

class Model {

public:
	static Model* new_model(int, bool);

	virtual vector<System *>::iterator systemBegin() = 0;
	virtual vector<System *>::iterator systemEnd() = 0;
	virtual vector<Flow *>::iterator flowBegin() = 0;
	virtual vector<Flow *>::iterator flowEnd() = 0;

	virtual bool add_system(string, int) = 0;

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(System *, System *, const string&);

	virtual bool erase_system(const string&) = 0;
	virtual bool erase_flow(const string&) = 0;
	virtual void print_status(bool) = 0;
	virtual int get_cur_time() = 0;
	virtual bool clear() = 0;
	virtual bool run(int) = 0;
};