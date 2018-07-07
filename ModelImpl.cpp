#include "ModelImpl.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <stdexcept>

Model* ModelImpl::instance = nullptr; // Singleton

ModelImpl::ModelImpl(int initial_time = 0) : time(initial_time)
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

void * ModelImpl::operator new(size_t tam)
{
	if (instance == nullptr) {
		tam = sizeof(ModelImpl);
		return (instance = (ModelImpl*)malloc(tam));
	}
	return instance;
}

Model * ModelImpl::new_model(int time = 0)
{
	if (instance == nullptr)
		instance = new ModelImpl(time);
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

bool ModelImpl::system_resize_one_more()
{
	try {
		this->systemSet.resize(systemSet.size() + 1);
	}
	catch (...) {
		return false;
	}
	return true;
}

size_t ModelImpl::system_amount()
{
	return this->systemSet.size();
}

vector<Flow*>::iterator ModelImpl::flowBegin()
{
	return flowSet.begin();
}

vector<Flow*>::iterator ModelImpl::flowEnd()
{
	return flowSet.end();
}

bool ModelImpl::flow_resize_one_more()
{
	try {
		this->flowSet.resize(flowSet.size() + 1);
	}
	catch (...) {
		return false;
	}
	return true;
}

size_t ModelImpl::flow_amount()
{
	return this->flowSet.size();
}

System* ModelImpl::add_system(const string& name, int stock)
{
	System *to_add = System::new_system(name, stock);
	try {
		Model* ins = Model::get_instance();
		ins->system_resize_one_more();
		*(--ins->systemEnd()) = to_add;
	}
	catch (...) {
		if (to_add != nullptr)
			delete to_add;
		return nullptr;
	}
	return to_add;
}

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

	return true;
}

System* ModelImpl::system_exists(const string& name)
{
	vector<System *>::iterator it = Model::get_instance()->systemBegin();
	while (it != Model::get_instance()->systemEnd()) {
		if ((*it)->get_name() == name)
			return (*it);
		advance(it, 1);
	}
	return nullptr;
}

Flow* ModelImpl::flow_exists(const string & name)
{
	vector<Flow *>::iterator it = Model::get_instance()->flowBegin();
	while (it != Model::get_instance()->flowEnd()) {
		if ((*it)->get_name() == name)
			return (*it);
		advance(it, 1);
	}
	return nullptr;
}

bool ModelImpl::run(int end_time)
{
	while (time < end_time) {
		for (Flow* flux : flowSet) {
			double package = flux->flow_funct();
			flux->get_source()->set_stock(flux->get_source()->get_stock() - package);
			flux->get_target()->set_stock(flux->get_target()->get_stock() + package);
		}

		for (System* sistema : systemSet) {
			sistema->set_last_stock(sistema->get_stock());
		}
		++time;
	}

	return true;
}
