#include "FlowImpl.h"
#include <string>

FlowImpl::FlowImpl(System *source, System *target, const string & n) : from(source), to(target), name(n)
{
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

double FlowImpl::get_source_stock()
{
	return from->get_stock();
}

double FlowImpl::get_target_stock()
{
	return to->get_stock();
}
