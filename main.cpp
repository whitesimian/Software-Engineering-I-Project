#pragma warning(disable:4996)

#include <iostream>
#include <cassert>
#include "_model.h"

using namespace std;

class Exp : FlowImpl {
public:
	double flow_funct() {
		return get_source_stock() * 0.05;
	}
};

class Logistic : public FlowImpl {
public:
	double flow_funct() override {
		return 0.01 * get_target_stock() * (1 - get_source_stock() / 70);
	}
};

int main() {


	
}