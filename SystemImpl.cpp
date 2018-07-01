#include "SystemImpl.h"

SystemImpl::SystemImpl(string n, double e) : name(n), stock(e)
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
