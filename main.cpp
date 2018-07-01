#pragma warning(disable:4996)

#include <iostream>
#include <cassert>
#include <cstdlib>
#include "_model.h"

using namespace std;

class Exp : public FlowImpl {
public:
	double flow_funct() {
		return get_source()->get_stock() * 0.05;
	}
};

class Logistic : public FlowImpl {
public:
	double flow_funct() {
		return 0.01 * get_target()->get_stock() * (1 - get_source()->get_stock() / 70);
	}
};

int main() {

	// TESTES UNITÁRIOS

	// ======== SYSTEM
	{
		System* sistema = System::new_system("test1", 1000);
		assert(sistema->get_name() == "test1");
		assert(sistema->get_stock() == 1000);

		sistema->set_name("testONE");
		assert(sistema->get_name() == "testONE");

		sistema->set_stock(1010);
		assert(sistema->get_stock() == 1010);
	}

	// ======== FLOW

	{
		System* sistema1 = System::new_system("source", 1000);
		System* sistema2 = System::new_system("target", 0);

		Flow* fluxo = Flow::new_flow<Exp>(sistema1, sistema2, "fluxo teste");
	}

	// ==========================================

	system("pause");

	exit(EXIT_SUCCESS);
}