#pragma warning(disable:4996)

#include <iostream>
#include <cassert>
#include <cstdlib>
#include "_model.h"

/* 
* FELIPE C�SAR LOPES MACHADO - 16.2.5890
* UFOP - UNIVERSIDADE FEDERAL DE OURO PRETO
* JUL/2018
*/

using namespace std;

class Exp : public FlowImpl {
public:
	double flow_funct() {
		return get_source()->get_last_stock() * 0.01;
	}
};

class Logistic : public FlowImpl {
public:
	double flow_funct() {
		return 0.01 * get_target()->get_last_stock() * (1 - get_target()->get_last_stock() / 70);
	}
};

int main() {

	// TESTES UNIT�RIOS
	cout << "Iniciando testes unitarios...\n";
	// ======== SYSTEM
	{
		cout << "Iniciando testes para System...\n";
		System* sistema = new SystemHandle("test1", 1000);
		assert(sistema->get_name() == "test1");
		assert(sistema->get_stock() == 1000);

		sistema->set_name("testONE");
		assert(sistema->get_name() == "testONE");

		sistema->set_stock(1010);
		assert(sistema->get_stock() == 1010);
		assert(sistema->get_last_stock() == 1000);

		sistema->set_last_stock(30);
		assert(sistema->get_last_stock() == 30);
		cout << "Concluido.\n";
	}

	// ======== FLOW

	{
		cout << "Iniciando testes para Flow...\n";
		System* sistema1 = new SystemHandle("source", 1000);
		System* sistema2 = new SystemHandle("target", 0);

		Flow* fluxo = new FlowHandle<Exp>(sistema1, sistema2, "fluxo teste");
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


		Flow* fluxo2 = new FlowHandle<Logistic>(sistema1, sistema2, "fluxo teste");

		double logistic_stock_test = fluxo2->flow_funct();
		assert(logistic_stock_test == 0.01 * fluxo2->get_target()->get_stock() * (1 - fluxo2->get_source()->get_stock() / 70));
		cout << "Concluido.\n";
	}

	// MODEL E SINGLETON
	{
		cout << "Iniciando testes para Model...\n";
		Model* modelo = ModelHandle::new_model(5);
		Model* modelo_teste_singleton = ModelHandle::new_model(2);

		assert(modelo == modelo_teste_singleton); // Testa singleton -> mesmo objeto

		assert(modelo->get_cur_time() == 5);

		assert(modelo->systemBegin() == modelo->systemEnd()); // Vazio
		assert(modelo->flowBegin() == modelo->flowEnd()); // Vazio

		assert(ModelHandle::add_system("sistema1", 1) != nullptr);
		assert((*modelo->systemBegin())->get_name() == "sistema1"); // Modelo adicionado corresponde ao anterior
		assert((*modelo->systemBegin())->get_stock() == 1);
		
		assert(modelo->erase_system("sistema1") && modelo->systemBegin() == modelo->systemEnd());
		assert(!modelo->erase_system("sistema nao existente"));

		System* sistema1 = new SystemHandle("source", 1000);
		System* sistema2 = new SystemHandle("target", 0);

		assert(ModelHandle::add_flow<Logistic>(sistema1, sistema2, "fluxo teste") != nullptr); // "source" e "target" adicionados ao modelo

		assert(ModelHandle::get_instance()->system_exists("source") != nullptr);
		assert(ModelHandle::get_instance()->system_exists("target") != nullptr);
		assert(ModelHandle::get_instance()->flow_exists("fluxo teste") != nullptr);

		assert(ModelHandle::add_flow<Exp>("source", "target", "novo_fluxo") != nullptr);

		assert(ModelHandle::get_instance()->system_amount() == 2);
		assert(ModelHandle::get_instance()->flow_amount() == 2);
	
		assert(ModelHandle::get_instance()->system_resize_one_more());
		assert(ModelHandle::get_instance()->flow_resize_one_more());

		modelo->clear();
		assert(modelo->get_cur_time() == 0);
		cout << "Concluido.\n";
	}

	// TESTES FUNCIONAIS
	{
		ModelHandle::new_model();
		cout << "\nIniciando testes funcionais...\n";
		// TESTE 1
		{
			cout << "Iniciando teste funcional 1...\n";
			ModelHandle::get_instance()->set_time(0);
			ModelHandle::add_system("pop1", 100.0);
			ModelHandle::add_system("pop2", 0.0);
			ModelHandle::add_flow<Exp>("pop1", "pop2", "exponencial");
			ModelHandle::get_instance()->run(100);

			assert(ModelHandle::get_instance()->system_exists("pop1")->get_stock() - 36.6032 < 1e-04);
			assert(ModelHandle::get_instance()->system_exists("pop2")->get_stock() - 63.3968 < 1e-04);
			cout << "Concluido.\n";
		}
		
		// TESTE 2
		{
			cout << "Iniciando teste funcional 2...\n";
			ModelHandle::get_instance()->set_time(0);
			ModelHandle::add_system("p1", 100.0);
			ModelHandle::add_system("p2", 10.0);
			ModelHandle::add_flow<Logistic>("p1", "p2", "logistica");
			ModelHandle::get_instance()->run(100);

			assert(ModelHandle::get_instance()->system_exists("p1")->get_stock() - 88.2167 < 1e-04);
			assert(ModelHandle::get_instance()->system_exists("p2")->get_stock() - 21.7834 < 1e-04);
			cout << "Concluido.\n";
		}

		//TESTE 3
		{
			cout << "Iniciando teste funcional 3...\n";
			ModelHandle::get_instance()->set_time(0);
			ModelHandle::add_system("S1", 100.0);
			ModelHandle::add_system("S2", 0.0);
			ModelHandle::add_system("S3", 100.0);
			ModelHandle::add_system("S4", 0.0);
			ModelHandle::add_system("S5", 0.0);
			ModelHandle::add_flow<Exp>("S1", "S2", "exponencial1");
			ModelHandle::add_flow<Exp>("S1", "S3", "exponencial2");
			ModelHandle::add_flow<Exp>("S2", "S3", "exponencial3");
			ModelHandle::add_flow<Exp>("S2", "S5", "exponencial4");
			ModelHandle::add_flow<Exp>("S3", "S4", "exponencial5");
			ModelHandle::add_flow<Exp>("S4", "S1", "exponencial6");
			ModelHandle::get_instance()->run(100);

			assert(ModelHandle::get_instance()->system_exists("S1")->get_stock() - 31.8513 < 1e-04);
			assert(ModelHandle::get_instance()->system_exists("S2")->get_stock() - 18.4003 < 1e-04);
			assert(ModelHandle::get_instance()->system_exists("S3")->get_stock() - 77.1143 < 1e-04);
			assert(ModelHandle::get_instance()->system_exists("S4")->get_stock() - 56.1728 < 1e-04);
			assert(ModelHandle::get_instance()->system_exists("S5")->get_stock() - 16.4612 < 1e-04);
			cout << "Concluido.\n";
		}
	}

	// ==========================================
	
	cout << "\n\tOs testes finalizaram com sucesso.\n\n";
	system("pause");

	exit(EXIT_SUCCESS);
}