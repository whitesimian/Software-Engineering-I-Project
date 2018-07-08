/*
* FELIPE CÉSAR LOPES MACHADO - 16.2.5890
* UFOP - UNIVERSIDADE FEDERAL DE OURO PRETO
* JUL/2018
*/

#pragma once

#include "Model.h"
#include <string>

class System;

class Flow {

public:
	virtual ~Flow() {};

	virtual std::string get_name() const		= 0;
	virtual System* get_source()			= 0;
	virtual System* get_target()			= 0;
	virtual bool set_name(const std::string&)	= 0;
	virtual bool set_source_system(System *)	= 0;
	virtual bool set_target_system(System *)	= 0;

	virtual Flow& operator=(Flow *)			= 0;
	virtual bool operator==(Flow *)			= 0;
	virtual bool operator!=(Flow *)			= 0;

	virtual double flow_funct()			= 0;
};
