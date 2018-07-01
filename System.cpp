#include "System.h"
#include "SystemImpl.h"

System* System::new_system(string name, double stock)
{
	System* novo = new SystemImpl(name, stock);
	return novo;
}
