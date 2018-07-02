#pragma once

#include "Flow.h"
#include "System.h"
#include <cstring>
#include <vector>

using namespace std;

class Flow;
class System;

class Model{

public:
	static Model* new_model(int time = 0, bool print = false);

	virtual vector<System *>::iterator systemBegin() = 0;
	virtual vector<System *>::iterator systemEnd() = 0;
	virtual vector<Flow *>::iterator flowBegin() = 0;
	virtual vector<Flow *>::iterator flowEnd() = 0;

	static System* add_system(const std::string&, int);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(System *, System *, const string&);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(const string&, const string&, const string&);

	static Model* get_instance();
	virtual bool erase_system(const string&) = 0;
	virtual bool erase_flow(const string&) = 0;
	virtual void set_print_status(bool) = 0;
	virtual bool get_print_status() = 0;
	virtual bool set_time(int) = 0;
	virtual int get_cur_time() = 0;
	virtual System* system_exists(const string&) = 0;
	virtual Flow* flow_exists(const string&) = 0;
	virtual bool clear() = 0;

	virtual bool run(int) = 0;

	virtual std::vector<System *> * system_vector() = 0; // Para se poder usar add_system e add_flow
	virtual std::vector<Flow *> * flow_vector() = 0;
};