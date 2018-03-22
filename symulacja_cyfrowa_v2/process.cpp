#include "process.h"
#include  "event.h"
#include "packet.h"
#include "event_list.h"

Process::Process()
{
	phase = 0;
	terminated = false;
	my_event_ = new Event(this);
	
}

Process::~Process()
{
}

void Process::activate(double time, Event_list *list, double clock)
{
	my_event_->event_time_ =  clock + time;
	list->schedule(my_event_);  
}


