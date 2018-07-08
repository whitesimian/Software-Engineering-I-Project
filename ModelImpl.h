#pragma once

#include <vector>
#include "Model.h"
#include "HandleBody.h"
#include <stdexcept>

using namespace std;

class ModelImpl : public Body { /// Model Body

private:
	vector<Flow *> flowSet;
	vector<System *> systemSet;
	int time;

	static ModelImpl* instance;

public:

	ModelImpl(int); /// Not singleton, although the idea is to securely use ModelImpl::new_model().
	~ModelImpl();

	static ModelImpl* new_model(int);

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

	static ModelImpl* get_instance();
	bool erase_system(const string&);
	bool erase_flow(const string&);
	bool set_time(int);
	int get_cur_time();
	bool clear();
	System* system_exists(const string&);
	Flow* flow_exists(const string&);

	void * operator new(size_t);						  /// Returns the same unique object.
	ModelImpl(const ModelImpl&)					= delete; /// No copy allowed.
	ModelImpl& operator=(const ModelImpl&)		= delete;

	bool run(int);

};

template<typename __FLOW_FUNCT_OBJ>
inline Flow* ModelImpl::add_flow(System* s1, System* s2, const std::string& name)
{
	Flow *to_add = new FlowHandle<__FLOW_FUNCT_OBJ>(s1, s2, name);
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

	Flow *to_add = new FlowHandle<__FLOW_FUNCT_OBJ>(system_one, system_two, name); // Cria o fluxo

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
inline static Flow* Model::add_flow(System * s1, System * s2, const string& name) {
	return ModelImpl::add_flow<__FLOW_FUNCT_OBJ>(s1, s2, name);
}

template<typename __FLOW_FUNCT_OBJ>
inline Flow * Model::add_flow(const string & s1, const string & s2, const string & name)
{
	return ModelImpl::add_flow<__FLOW_FUNCT_OBJ>(s1, s2, name);
}

/// Model handle below

/// Handle's pImpl_ will point to the same object regardless of new attemps of allocation of ModelHandle.

class ModelHandle : public Model, public Handle<ModelImpl> { 

private:
	static Model * instance;

	ModelHandle(int); /// Singleton

public:
	static Model* new_model(int time = 0);

	vector<Flow *>::iterator flowEnd();
	vector<Flow *>::iterator flowBegin();
	vector<System *>::iterator systemEnd();
	vector<System *>::iterator systemBegin();

	size_t flow_amount();
	size_t system_amount();
	bool flow_resize_one_more();
	bool system_resize_one_more();

	static System* add_system(const std::string&, int);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(System *, System *, const string&);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(const string&, const string&, const string&);

	static Model* get_instance();
	bool erase_system(const string&);
	bool erase_flow(const string&);
	bool set_time(int);
	int get_cur_time();
	System* system_exists(const string&);
	Flow* flow_exists(const string&);
	bool clear();

	ModelHandle(const ModelHandle&)					= delete; /// No copy allowed.
	ModelHandle& operator=(const ModelHandle&)		= delete;

	bool run(int);
};

template<typename __FLOW_FUNCT_OBJ>
inline static Flow* ModelHandle::add_flow(System * s1, System * s2, const string& name) {
	return ModelImpl::add_flow<__FLOW_FUNCT_OBJ>(s1, s2, name);
}

template<typename __FLOW_FUNCT_OBJ>
inline static Flow* ModelHandle::add_flow(const string& n1, const string& n2, const string& n3) {
	return ModelImpl::add_flow<__FLOW_FUNCT_OBJ>(n1, n2, n3);
}