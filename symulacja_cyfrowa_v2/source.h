#ifndef SYMULACJA_CYFROWA_SOURCE_H
#define SYMULACJA_CYFROWA_SOURCE_H
#include "process.h"

class Generator;

class Source:public Process
{
public:
	Source();
	~Source();
	Source(Transmitter *ptr, Symulation *sym_ptr,int index);


	Transmitter  *transmiter_ptr;
	Symulation   *symulation_ptr;
	Generator    *generator_ptr;
	int index_;  //  numer indeksu w tablicy do ziarna
	void execute(Event_list *list, double clock, Medium *med, Transmitter *ptr, Symulation *sym_ptr, double begin_phase_lengt);
	void start_source(Event_list *list, double clk);


};
#endif // SYMULACJA CYFROWA Source H
