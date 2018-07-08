/*
* FELIPE CÉSAR LOPES MACHADO - 16.2.5890
* UFOP - UNIVERSIDADE FEDERAL DE OURO PRETO
* JUL/2018
*/

#pragma once

#include "FlowImpl.h"
#include "SystemImpl.h"
#include <cstring>
#include <vector>

using namespace std;

class Flow;
class System;

class Model{

public:
	static Model* new_model(int time = 0);

	virtual vector<Flow *>::iterator flowEnd()			= 0;
	virtual vector<Flow *>::iterator flowBegin()		= 0;
	virtual vector<System *>::iterator systemEnd()		= 0;
	virtual vector<System *>::iterator systemBegin()	= 0;
	
	virtual size_t flow_amount()						= 0;
	virtual size_t system_amount()						= 0;
	virtual bool flow_resize_one_more()					= 0;
	virtual bool system_resize_one_more()				= 0;

	static System* add_system(const std::string&, int);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(System *, System *, const string&);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(const string&, const string&, const string&);

	static Model* get_instance();
	virtual bool erase_system(const string&)			= 0;
	virtual bool erase_flow(const string&)				= 0;
	virtual bool set_time(int)							= 0;
	virtual int get_cur_time()							= 0;
	virtual System* system_exists(const string&)		= 0;
	virtual Flow* flow_exists(const string&)			= 0;
	virtual bool clear()								= 0;

	virtual bool run(int)								= 0;
};