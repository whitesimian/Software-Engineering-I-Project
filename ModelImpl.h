#pragma once

#include <vector>
#include "Model.h"
#include <stdexcept>

using namespace std;

class ModelImpl : public Model {

private:
	vector<Flow *> flowSet;
	vector<System *> systemSet;
	int time;

	static Model* instance; // Singleton

	ModelImpl(int);
	~ModelImpl();

public:

	static Model* new_model(int);

	vector<System * >::iterator systemBegin();
	vector<System * >::iterator systemEnd();
	bool system_resize_one_more();
	size_t system_amount();
	vector<Flow * >::iterator flowBegin();
	vector<Flow * >::iterator flowEnd();
	bool flow_resize_one_more();
	size_t flow_amount();

	static System* add_system(const string&, int);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(System *, System *, const string&);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(const string&, const string&, const string&);

	static Model* get_instance();
	bool erase_system(const string&);
	bool erase_flow(const string&);
	bool set_time(int);
	int get_cur_time();
	bool clear();
	System* system_exists(const string&);
	Flow* flow_exists(const string&);

	void * operator new(size_t);

	bool run(int);

};

template<typename __FLOW_FUNCT_OBJ>
inline Flow* ModelImpl::add_flow(System* s1, System* s2, const std::string& name)
{
	Flow *to_add = Flow::new_flow<__FLOW_FUNCT_OBJ>(s1, s2, name);
	try {
		Model* ins = Model::get_instance();
		ins->flow_resize_one_more();
		*(--ins->flowEnd()) = to_add;

		if (Model::get_instance()->system_exists(s1->get_name()) == nullptr) { // Se o sistema não existe, adicione-o
			ins->system_resize_one_more();
			*(--ins->systemEnd()) = s1;
		}

		if (Model::get_instance()->system_exists(s2->get_name()) == nullptr) {
			ins->system_resize_one_more();
			*(--ins->systemEnd()) = s2;
		}
	}
	catch (...) {
		if (to_add != nullptr)
			delete to_add;
		return nullptr;
	}
	return to_add;
}

template<typename __FLOW_FUNCT_OBJ>
inline Flow * ModelImpl::add_flow(const string & s1, const string & s2, const string & name)
{
	if (Model::get_instance() == nullptr) // Modelo inexistente
		return nullptr;

	System* system_one = Model::get_instance()->system_exists(s1); // nullptr se não existir
	System* system_two = Model::get_instance()->system_exists(s2);

	if (system_one == nullptr || system_two == nullptr)
		return nullptr;

	Flow *to_add = Flow::new_flow<__FLOW_FUNCT_OBJ>(system_one, system_two, name); // Cria o fluxo

	try {
		Model* ins = Model::get_instance();
		ins->flow_resize_one_more();
		*(--ins->flowEnd()) = to_add;
	}
	catch (...) {
		if (to_add != nullptr)
			delete to_add;
		return nullptr;
	}
	return to_add;
}

template<typename __FLOW_FUNCT_OBJ>
static Flow* Model::add_flow(System * s1, System * s2, const string& name) {
	return ModelImpl::add_flow<__FLOW_FUNCT_OBJ>(s1, s2, name);
}

template<typename __FLOW_FUNCT_OBJ>
inline Flow * Model::add_flow(const string & s1, const string & s2, const string & name)
{
	return ModelImpl::add_flow<__FLOW_FUNCT_OBJ>(s1, s2, name);
}
