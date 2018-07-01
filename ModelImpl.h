#pragma once

#include <vector>
#include "Model.h"
#include <iterator>

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

	System* add_system(string, int);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* add_flow(System *, System *, const string&);

	bool erase_system(const string&);
	bool erase_flow(const string&);
	void print_status(bool);
	int get_cur_time();
	bool clear();

	bool run(int);

};

template<typename __FLOW_FUNCT_OBJ>
static Flow* Model::add_flow(System * s1, System * s2, const string& name) {
	return ModelImpl::add_flow(s1, s2, name);
}