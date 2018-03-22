#include "event.h"
Event::Event()
{
}
Event::Event(Process* ptr)
{
	event_time_ = -1.0;
	proc_ = ptr;
}
Event::~Event()
{
}
