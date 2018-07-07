#pragma once

#include "Model.h"
#include <string>

class System;

class Flow {

public:
	virtual ~Flow() {};

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* new_flow(System*, System*, const std::string&);

	virtual std::string get_name()				= 0;
	virtual System* get_source()				= 0;
	virtual System* get_target()				= 0;
	virtual bool set_name(const std::string&)	= 0;
	virtual bool set_source_system(System *)	= 0;
	virtual bool set_target_system(System *)	= 0;

	virtual Flow& operator=(Flow *)				= 0;
	virtual bool operator==(Flow *)				= 0;
	virtual bool operator!=(Flow *)				= 0;

	virtual double flow_funct()					= 0;
};