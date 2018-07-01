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

/*System* ModelImpl::systemAt(unsigned pos)
{
	return systemSet.at(pos);
}*/

vector<Flow*>::iterator ModelImpl::flowBegin()
{
	return flowSet.begin();
}

vector<Flow*>::iterator ModelImpl::flowEnd()
{
	return flowSet.end();
}

System* ModelImpl::add_system(string name, int stock)
{
	System *to_add = System::new_system(name, stock);
	try {
		systemSet.push_back(to_add);
	}
	catch (...) {
		if (to_add != nullptr)
			delete to_add;
		return nullptr;
	}
	return to_add;
}

template<typename __FLOW_FUNCT_OBJ>
Flow* ModelImpl::add_flow(System *f1, System *f2, const string& name)
{
	Flow *to_add = Flow::new_flow<__FLOW_FUNCT_OBJ>(f1, f2, name);
	try {
		flowSet.push_back(to_add);
	}
	catch (...) {
		if(to_add != nullptr)
			delete to_add;
		return nullptr;
	}
	return to_add;
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

void ModelImpl::print_status(bool flag)
{
	print = flag;
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

bool ModelImpl::run(int end_time)
{
	if (print) {
		cout << setw(15) << time;
		for (System* sys : systemSet) {
			cout << setw(15) << sys->get_name();
		}
		cout << "\n";
	}

	while (time < end_time) {
		for (Flow* flux : flowSet) {
			double package = flux->flow_funct();
			flux->get_source()->set_stock(flux->get_source()->get_stock() - package);
			flux->get_target()->set_stock(flux->get_target()->get_stock() + package);
		}

		if (print) {
			cout << time << "\t";
			for (System* sys : systemSet) {
				cout << sys->get_stock() << "\t";
			}
			cout << "\n";
		}
		++time;
	}

	return true;
}

/*Flow * ModelImpl::flowAt(unsigned pos)
{
	return flowSet.at(pos);
}*/
