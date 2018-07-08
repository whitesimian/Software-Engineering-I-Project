#pragma once

#include <string>
#include "Flow.h"
#include "HandleBody.h"

using namespace std;

class FlowImpl : public Body{ /// Flow Body
	string name;
	System *from, *to;

public:
	FlowImpl();
	FlowImpl(System *, System *, const string&);
	
	virtual ~FlowImpl();

	string get_name();
	System* get_source();
	System* get_target();
	bool set_name(const string&);
	bool set_source_system(System *);
	bool set_target_system(System *);

	FlowImpl& operator=(FlowImpl *);
	bool operator==(FlowImpl *);
	bool operator!=(FlowImpl *);

	virtual double flow_funct() = 0;

};

/// Flow handle below

template<typename __FLOW_FUNCT_OBJ>
class FlowHandle : public Flow, public Handle<__FLOW_FUNCT_OBJ> {

public:
	FlowHandle();
	FlowHandle(System *, System *, const string&);
	~FlowHandle();

	string get_name() const;
	System* get_source();
	System* get_target();
	bool set_name(const string&);
	bool set_source_system(System *);
	bool set_target_system(System *);

	Flow& operator=(Flow *);
	bool operator==(Flow *);
	bool operator!=(Flow *);

	double flow_funct();
};

// ==============================================================================

template<typename __FLOW_FUNCT_OBJ>
inline FlowHandle<__FLOW_FUNCT_OBJ>::FlowHandle(System * s1, System * s2, const string& name) {
	this->pImpl_->set_source_system(s1);
	this->pImpl_->set_target_system(s2);
	this->pImpl_->set_name(name);
}

template<typename __FLOW_FUNCT_OBJ>
inline FlowHandle<__FLOW_FUNCT_OBJ>::~FlowHandle()
{
}

template<typename __FLOW_FUNCT_OBJ>
inline FlowHandle<__FLOW_FUNCT_OBJ>::FlowHandle()
{
}

template<typename __FLOW_FUNCT_OBJ>
inline string FlowHandle<__FLOW_FUNCT_OBJ>::get_name() const
{
	return this->pImpl_->get_name();
}

template<typename __FLOW_FUNCT_OBJ>
inline System * FlowHandle<__FLOW_FUNCT_OBJ>::get_source()
{
	return this->pImpl_->get_source();
}

template<typename __FLOW_FUNCT_OBJ>
inline System * FlowHandle<__FLOW_FUNCT_OBJ>::get_target()
{
	return this->pImpl_->get_target();
}

template<typename __FLOW_FUNCT_OBJ>
inline bool FlowHandle<__FLOW_FUNCT_OBJ>::set_name(const string & name)
{
	return this->pImpl_->set_name(name);
}

template<typename __FLOW_FUNCT_OBJ>
inline bool FlowHandle<__FLOW_FUNCT_OBJ>::set_source_system(System * obj)
{
	return this->pImpl_->set_source_system(obj);
}

template<typename __FLOW_FUNCT_OBJ>
inline bool FlowHandle<__FLOW_FUNCT_OBJ>::set_target_system(System * obj)
{
	return this->pImpl_->set_target_system(obj);
}

template<typename __FLOW_FUNCT_OBJ>
inline Flow & FlowHandle<__FLOW_FUNCT_OBJ>::operator=(Flow * obj)
{
	if (obj == this)
		return *this;
	this->pImpl_->set_name(obj->get_name());
	this->pImpl_->set_source_system(obj->get_source());
	this->pImpl_->set_target_system(obj->get_target());
	return *this;
}

template<typename __FLOW_FUNCT_OBJ>
inline bool FlowHandle<__FLOW_FUNCT_OBJ>::operator==(Flow * obj)
{
	return (this->get_name() == obj->get_name() && this->get_source() == obj->get_source() && this->get_target() == obj->get_target());
}

template<typename __FLOW_FUNCT_OBJ>
inline bool FlowHandle<__FLOW_FUNCT_OBJ>::operator!=(Flow * obj)
{
	return (this->get_name() != obj->get_name() || this->get_source() != obj->get_source() || this->get_target() != obj->get_target());
}

template<typename __FLOW_FUNCT_OBJ>
inline double FlowHandle<__FLOW_FUNCT_OBJ>::flow_funct()
{
	return this->pImpl_->flow_funct();
}