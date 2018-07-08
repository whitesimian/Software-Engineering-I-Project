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

SystemImpl & SystemImpl::operator=(SystemImpl * obj)
{
	if (obj == this)
		return *this;
	set_name(obj->get_name());
	set_stock(obj->get_stock());
	set_last_stock(obj->get_last_stock());
	return *this;
}

bool SystemImpl::operator==(SystemImpl * obj)
{
	return (this->name == obj->get_name() && this-> stock == obj->get_stock() && this->last_stock == obj->get_last_stock());
}

bool SystemImpl::operator!=(SystemImpl * obj)
{
	return (this->name != obj->get_name() || this->stock != obj->get_stock() || this->last_stock != obj->get_last_stock());
}

// ===================================================================================

SystemHandle::SystemHandle(const string & name, double stock)
{
	pImpl_->set_name(name);
	pImpl_->set_stock(stock);
	pImpl_->set_last_stock(stock);
}

string SystemHandle::get_name()
{
	return pImpl_->get_name();
}

void SystemHandle::set_name(const string & name)
{
	pImpl_->set_name(name);
}

void SystemHandle::set_stock(double stock)
{
	pImpl_->set_stock(stock);
}

double SystemHandle::get_stock()
{
	return pImpl_->get_stock();
}

double SystemHandle::get_last_stock()
{
	return pImpl_->get_last_stock();
}

bool SystemHandle::set_last_stock(double stock)
{
	return pImpl_->set_last_stock(stock);
}

System& SystemHandle::operator=(System * obj)
{
	if (obj == this)
		return *this;
	this->set_name(obj->get_name());
	this->set_stock(obj->get_stock());
	this->set_last_stock(obj->get_last_stock());
	return *this;
}

bool SystemHandle::operator==(System * obj)
{
	return (this->get_name() == obj->get_name() && this->get_stock() == obj->get_stock() && this->get_last_stock() == obj->get_last_stock());
}

bool SystemHandle::operator!=(System * obj)
{
	return (this->get_name() != obj->get_name() || this->get_stock() != obj->get_stock() || this->get_last_stock() != obj->get_last_stock());
}

