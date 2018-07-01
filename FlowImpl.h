#pragma once
#include <string>
#include "Flow.h"

using namespace std;

class FlowImpl : public Flow{
	string name;
	System *from, *to;

public:
	FlowImpl(System *, System *, const string&);
	FlowImpl();
	virtual ~FlowImpl();
	string get_name();
	System* get_source();
	System* get_target();
	bool set_name(const string&);
	bool set_source_system(System *);
	bool set_target_system(System *);

	template<typename __FLOW_FUNCT_OBJ>
	static Flow* new_flow(System *, System *, const string&);

	virtual double flow_funct() = 0;

};

template<typename __FLOW_FUNCT_OBJ>
inline Flow* FlowImpl::new_flow(System * from, System * to, const string & n)
{
	Flow* novo = new __FLOW_FUNCT_OBJ;
	novo->set_name(n);
	novo->set_source_system(from);
	novo->set_target_system(to);
	return novo;
}

template<typename __FLOW_FUNCT_OBJ>
static Flow* Flow::new_flow(System* s1, System* s2, const string& name) {
	return FlowImpl::new_flow<__FLOW_FUNCT_OBJ>(s1, s2, name);
}