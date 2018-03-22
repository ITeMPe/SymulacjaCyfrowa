#ifndef SYMULACJA_CYFROWA_PROCESS_H
#define SYMULACJA_CYFROWA_PROCESS_H
#include "symulation.h"
class Event;
class Medium;
class Event_list;
class Transmitter;

class Process 
{
private:
	Event *my_event_;
	
public:
	void virtual execute( Event_list *list, double clock, Medium *med, Transmitter *ptr, Symulation *sym_ptr, double begin_phase_lengt) {};
	
	void activate(double time, Event_list *list, double clock);
	int phase;
	bool terminated;
	Process();
	~Process();

	
};
#endif // SYMULACJA CYFROWA Process H
