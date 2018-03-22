#ifndef SYMULACJA_CYFROWA_EVENT_H
#define SYMULACJA_CYFROWA_EVENT_H
class Process;

class Event
{
public:
	double event_time_;
	Process *proc_;
	Event();
	Event(Process *ptr);
	~Event();
};
#endif // SYMULACJA CYFROWA Event H
