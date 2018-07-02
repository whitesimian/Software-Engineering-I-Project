#include "Model.h"
#include "ModelImpl.h"
#include <string>

Model * Model::new_model(int time = 0, bool print = false)
{
	return ModelImpl::new_model(time, print);
}

System * Model::add_system(const string & name, int stock)
{
	return ModelImpl::add_system(name, stock);
}

Model * Model::get_instance()
{
	return ModelImpl::get_instance();
}

/*template<typename __FLOW_FUNCT_OBJ>
Flow* Model::add_flow(System * s1, System * s2, const std::string& name) {
	return ModelImpl::add_flow<__FLOW_FUNCT_OBJ>(s1, s2, name);
}*/