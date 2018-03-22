#ifndef SYMULACJA_CYFROWA_EVENT_LIST_H
#define SYMULACJA_CYFROWA_EVENT_LIST_H
class Event;
class Link;


class Event_list
{
	Link *head;
	int number_elements;
public:
	Event_list();
	~Event_list();

	Event *first();
	Event *remove_first(bool show_messages);
	void schedule(Event*e);
	bool empty();

	void show_agenda();
	int show_number_elements();

};
#endif // SYMULACJA CYFROWA Event_list H
