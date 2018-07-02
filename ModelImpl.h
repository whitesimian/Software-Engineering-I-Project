#pragma once

#include <vector>
#include "Model.h"
#include <stdexcept>

using namespace std;

class ModelImpl : public Model{

private:
	vector<Flow *> flowSet;
	vector<System *> systemSet;
	int time;
	bool print;

	static Model* instance; // Singleton

	ModelImpl(int, bool);
	~ModelImpl();
	
public:

	static Model* new_model(int, bool);

	vector<System * >::iterator systemBegin();
	vector<System * >::iterator systemEnd();
	vector<Flow * >::iterator flowBegin();
	vector<Flow * >::iterator flowEnd();

	vector<System *> * system_vector();
	vector<Flow *> * flow_vector();

	static System* add_system(const string&, int);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(System *, System *, const string&);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(const string&, const string&, const string&);

	static Model* get_instance();
	bool erase_system(const string&);
	bool erase_flow(const string&);
	void set_print_status(bool);
	bool get_print_status();
	bool set_time(int);
	int get_cur_time();
	bool clear();
	System* system_exists(const string&);
	Flow* flow_exists(const string&);

	bool run(int);

};

template<typename __FLOW_FUNCT_OBJ>
inline Flow* ModelImpl::add_flow(System* s1, System* s2, const std::string& name)
{
	Flow *to_add = Flow::new_flow<__FLOW_FUNCT_OBJ>(s1, s2, name);
	try {
		Model::get_instance()->flow_vector()->push_back(to_add);

		if (Model::get_instance()->system_exists(s1->get_name()) == nullptr) // Se o sistema não existe, adicione-o
			Model::get_instance()->system_vector()->push_back(s1);

		if (Model::get_instance()->system_exists(s2->get_name()) == nullptr)
			Model::get_instance()->system_vector()->push_back(s2);
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
		Model::get_instance()->flow_vector()->push_back(to_add);
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
