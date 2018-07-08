#include "Model.h"
#include "ModelImpl.h"
#include <string>

Model * Model::new_model(int time)
{
	return ModelHandle::new_model(time);
}

System * Model::add_system(const string & name, int stock)
{
	return ModelImpl::add_system(name, stock);
}

Model * Model::get_instance()
{
	return ModelHandle::get_instance();
}
