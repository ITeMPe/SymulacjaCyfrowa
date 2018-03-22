#include "source.h"
#include "packet.h"
#include <ctime>
#include "transmitter.h"
#include "symulation.h"
#include "generator.h"
#include <iostream>
Source::Source()
{
}
Source::Source(Transmitter* ptr, Symulation* sym_ptr, int index)
{
	transmiter_ptr = ptr;
	symulation_ptr = sym_ptr;
	index_ = index;
}
Source::~Source()
{
}
void Source::execute(Event_list *list, double clock, Medium *med, Transmitter *ptr, Symulation *sym_ptr, double begin_phase_lengt)
{
	int time1 = symulation_ptr->generators[index_+1]->generator_rownomierny() *10 +1;  // CTP [1,2,...10]
	int temp = symulation_ptr->generators[index_]->generator_wykladniczy(0.004);	   	 // CGP rozklad wykladniczy
	double time2 = temp / 10.0;														// CGP rozklad wykladniczy cd.																	
	Packet *temp_ptr;
	(temp_ptr = new Packet(transmiter_ptr, symulation_ptr,this,time1));  // wygenerowanie nowego pakietu
	temp_ptr->activate(0.0, list, clock);			// umieszczenie na agendziehtd
	transmiter_ptr->generate_packet_(temp_ptr, clock);	// wrzucenie do bufora
	activate(time2,list, clock);		// zaplanowanie stworzenia nowego pakietu
}
void Source::start_source(Event_list *list, double clk)
{
	double time = symulation_ptr->generators[index_]->generator_wykladniczy(0.75);  // tu moze byc co chce bo to i tak tylko raz sie wykonuje na starcie -- faza poczatkowa
	int temp_time = time * 10;
	time = temp_time / 10.0;
	activate(time, list, clk);	// umieszczenie na agendzie 
	cout <<"czas w start source  "<<this->transmiter_ptr->transmiter_id_<<"\t"<< time << endl;
}
