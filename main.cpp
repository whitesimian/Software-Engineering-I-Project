#pragma warning(disable:4996)

#include <iostream>
#include <cassert>
#include <cstdlib>
#include "_model.h"

using namespace std;

class Exp : public FlowImpl {
public:
	double flow_funct() {
		return get_source()->get_stock() * 0.01;
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
		assert(fluxo->get_name() == "fluxo teste");
		assert(fluxo->get_source() == sistema1); // Mesmos objetos
		assert(fluxo->get_target() == sistema2);

		fluxo->set_name("novo fluxo teste");
		assert(fluxo->get_name() == "novo fluxo teste");

		fluxo->set_source_system(sistema2);
		assert(fluxo->get_source() == sistema2);

		fluxo->set_target_system(sistema1);
		assert(fluxo->get_target() == sistema1);

		double exp_stock_test = fluxo->flow_funct();
		assert(exp_stock_test == 0.01 * fluxo->get_source()->get_stock());


		Flow* fluxo2 = Flow::new_flow<Logistic>(sistema1, sistema2, "fluxo teste");

		double logistic_stock_test = fluxo2->flow_funct();
		assert(logistic_stock_test == 0.01 * fluxo2->get_target()->get_stock() * (1 - fluxo2->get_source()->get_stock() / 70));

	}

	// MODEL E SINGLETON
	{
		Model* modelo = Model::new_model(5, false);
		Model* modelo_teste_singleton = Model::new_model(2, true);

		assert(modelo == modelo_teste_singleton); // Testa singleton -> mesmo objeto

		assert(modelo->get_cur_time() == 5);

		modelo->set_print_status(true);
		assert(modelo->get_print_status());

		assert(modelo->systemBegin() == modelo->systemEnd()); // Vazio
		assert(modelo->flowBegin() == modelo->flowEnd()); // Vazio

		assert(Model::add_system("sistema1", 1) != nullptr);
		assert((*modelo->systemBegin())->get_name() == "sistema1"); // Modelo adicionado corresponde ao anterior
		assert((*modelo->systemBegin())->get_stock() == 1);
		
		assert(modelo->erase_system("sistema1") && modelo->systemBegin() == modelo->systemEnd());
		assert(!modelo->erase_system("sistema nao existente"));

		System* sistema1 = System::new_system("source", 1000);
		System* sistema2 = System::new_system("target", 0);

		assert(Model::add_flow<Logistic>(sistema1, sistema2, "fluxo teste") != nullptr);

		assert(modelo->system_vector() != nullptr);
		assert(modelo->flow_vector() != nullptr);

		modelo->clear();
		assert(modelo->get_cur_time() == 0);
		assert(!modelo->get_print_status());
	}

	// ==========================================
	
	cout << "\n\tOs testes finalizaram com sucesso.\n\n";
	system("pause");

	exit(EXIT_SUCCESS);
}