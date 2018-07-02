#include "ModelImpl.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

Model* ModelImpl::instance = nullptr; // Singleton

ModelImpl::ModelImpl(int initial_time = 0, bool flag = false) : time(initial_time), print(flag)
{
}

ModelImpl::~ModelImpl()
{
	for (Flow* elem : flowSet)
		if (elem != nullptr)
			delete elem;
	for (System* elem : systemSet)
		if (elem != nullptr)
			delete elem;
}

vector<System*>* ModelImpl::system_vector()
{
	return &systemSet;
}

vector<Flow*>* ModelImpl::flow_vector()
{
	return &flowSet;
}

Model * ModelImpl::new_model(int time = 0, bool print = false)
{
	if (instance == nullptr)
		instance = new ModelImpl(time, print);
	return instance;
}

vector<System*>::iterator ModelImpl::systemBegin()
{
	return systemSet.begin();
}

vector<System*>::iterator ModelImpl::systemEnd()
{
	return systemSet.end();
}

vector<Flow*>::iterator ModelImpl::flowBegin()
{
	return flowSet.begin();
}

vector<Flow*>::iterator ModelImpl::flowEnd()
{
	return flowSet.end();
}

System* ModelImpl::add_system(const string& name, int stock)
{
	System *to_add = System::new_system(name, stock);
	try {
		Model::get_instance()->system_vector()->push_back(to_add);
	}
	catch (...) {
		if (to_add != nullptr)
			delete to_add;
		return nullptr;
	}
	return to_add;
}

/*template<typename __FLOW_FUNCT_OBJ>
Flow* ModelImpl::add_flow(System *f1, System *f2, const std::string& name)
{
	Flow *to_add = Flow::new_flow<__FLOW_FUNCT_OBJ>(f1, f2, name);
	try {
		Model::get_instance()->flow_vector().push_back(to_add);
	}
	catch (...) {
		if(to_add != nullptr)
			delete to_add;
		return nullptr;
	}
	return to_add;
}*/

Model * ModelImpl::get_instance()
{
	return ModelImpl::instance;
}

bool ModelImpl::erase_system(const string& name)
{
	vector<System *>::iterator it = systemBegin();
	while (it != systemEnd()) {
		if ((*it)->get_name() == name) {
			delete *it;
			systemSet.erase(it);
			return true;
		}
		advance(it, 1);
	}
	return false;
}

bool ModelImpl::erase_flow(const string& name)
{
	vector<Flow *>::iterator it = flowBegin();
	while (it != flowEnd()) {
		if ((*it)->get_name() == name) {
			delete *it;
			flowSet.erase(it);
			return true;
		}
		advance(it, 1);
	}
	return false;
}

void ModelImpl::set_print_status(bool flag)
{
	print = flag;
}

bool ModelImpl::get_print_status()
{
	return print;
}

bool ModelImpl::set_time(int time)
{
	this->time = time;
	return true;
}

int ModelImpl::get_cur_time()
{
	return time;
}

bool ModelImpl::clear()
{
	for (auto elem : flowSet)
		if (elem != nullptr)
			delete elem;
	for (auto elem : systemSet)
		if (elem != nullptr)
			delete elem;
	systemSet.clear();
	flowSet.clear();
	time = 0;
	print = false;

	return true;
}

System* ModelImpl::system_exists(const string& name)
{
	for (System* elem : *Model::get_instance()->system_vector()) {
		if (elem->get_name() == name)
			return elem;
	}
	return nullptr;
}

Flow* ModelImpl::flow_exists(const string & name)
{
	for (Flow* elem : *Model::get_instance()->flow_vector()) {
		if (elem->get_name() == name)
			return elem;
	}
	return nullptr;
}

bool ModelImpl::run(int end_time)
{
	/*if (this->print) {
		cout << setw(15) << time;
		for (System* sys : systemSet) {
			cout << setw(15) << sys->get_name();
		}
		cout << "\n";
	}*/

	while (time < end_time) {
		for (Flow* flux : flowSet) {
			double package = flux->flow_funct();
			flux->get_source()->set_stock(flux->get_source()->get_stock() - package);
			flux->get_target()->set_stock(flux->get_target()->get_stock() + package);
		}

		for (System* sistema : systemSet) {
			sistema->set_last_stock(sistema->get_stock());
		}

		/*if (this->print) {
			cout << time << "\t";
			for (System* sys : systemSet) {
				cout << sys->get_stock() << "\t";
			}
			cout << "\n";
		}*/
		++time;
	}

	return true;
}
