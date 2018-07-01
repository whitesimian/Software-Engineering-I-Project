#pragma once
#include <string>
#include "Flow.h"

using namespace std;

class FlowImpl : public Flow{
	string name;
	System *from, *to;

public:
	FlowImpl(System *, System *, const string&);
	~FlowImpl();
	string get_name();
	double get_source_stock();
	double get_target_stock();

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* new_flow(System *, System *, const string&);

	virtual double flow_funct() = 0;

};

template<typename __FLOW_FUNCT_OBJ>
inline Flow* FlowImpl::new_flow(System * from, System * to, const string & n)
{
	Flow* novo = new __FLOW_FUNCT_OBJ(from, to, n);
	return novo;
}

template<typename __FLOW_FUNCT_OBJ>
static Flow* Flow::new_flow(System* s1, System* s2, const string& name) {
	return FlowImpl::new_flow(s1, s2, name);
}