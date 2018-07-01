#include "Model.h"
#include "ModelImpl.h"

Model * Model::new_model(int time = 0, bool print = false)
{
	return ModelImpl::new_model(time, print);
}
