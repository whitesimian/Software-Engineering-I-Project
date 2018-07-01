#pragma once

#include "Model.h"
#include <string>

class System;

class Flow {

public:
	virtual ~Flow() {};

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* new_flow(System*, System*, const std::string&);

	virtual std::string get_name() = 0;
	virtual System* get_source() = 0;
	virtual System* get_target() = 0;
	virtual double flow_funct() = 0;
};