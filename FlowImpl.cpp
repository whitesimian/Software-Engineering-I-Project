#include "FlowImpl.h"
#include <string>

FlowImpl::FlowImpl(System *source = nullptr, System *target = nullptr, const string & n = "") : from(source), to(target), name(n)
{
}

FlowImpl::FlowImpl()
{
	name = "";
	from = nullptr;
	to = nullptr;
}

FlowImpl::~FlowImpl()
{
	if (from == nullptr)
		delete from;
	if (to == nullptr)
		delete to;
	from = nullptr;
	to = nullptr;
}

string FlowImpl::get_name()
{
	return name;
}

System* FlowImpl::get_source()
{
	return from;
}

System* FlowImpl::get_target()
{
	return to;
}

bool FlowImpl::set_name(const std::string & name)
{
	this->name = name;
	return true;
}

bool FlowImpl::set_source_system(System * source)
{
	this->from = source;
	return true;
}

bool FlowImpl::set_target_system(System * target)
{
	this->to = target;
	return true;
}

Flow & FlowImpl::operator=(Flow * obj)
{
	if (this == obj)
		return *this;
	this->name = obj->get_name();
	this->from = obj->get_source();
	this->to = obj->get_target();
	return *this;
}

bool FlowImpl::operator==(Flow * obj)
{
	return (this->name == obj->get_name() && this->from == obj->get_source() && this->to == obj->get_target());
}

bool FlowImpl::operator!=(Flow * obj)
{
	return (this->name != obj->get_name() || this->from != obj->get_source() || this->to != obj->get_target());
}
