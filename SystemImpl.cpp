#include "SystemImpl.h"

SystemImpl::SystemImpl(string n, double e) : name(n), stock(e), last_stock(e)
{
}

string SystemImpl::get_name()
{
	return name;
}

void SystemImpl::set_name(const string & name)
{
	this->name = name;
}

void SystemImpl::set_stock(double s)
{
	stock = s;
}

double SystemImpl::get_stock()
{
	return stock;
}

double SystemImpl::get_last_stock()
{
	return last_stock;
}

bool SystemImpl::set_last_stock(double value)
{
	this->last_stock = value;
	return true;
}

System & SystemImpl::operator=(System * obj)
{
	if (obj == this)
		return *this;
	set_name(obj->get_name());
	set_stock(obj->get_stock());
	set_last_stock(obj->get_last_stock());
	return *this;
}

bool SystemImpl::operator==(System * obj)
{
	return (this->name == obj->get_name() && this-> stock == obj->get_stock() && this->last_stock == obj->get_last_stock());
}

bool SystemImpl::operator!=(System * obj)
{
	return (this->name != obj->get_name() || this->stock != obj->get_stock() || this->last_stock != obj->get_last_stock());
}
