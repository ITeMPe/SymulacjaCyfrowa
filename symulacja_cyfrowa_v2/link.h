#ifndef SYMULACJA_CYFROWA_LINK_H
#define SYMULACJA_CYFROWA_LINK_H
class Event;
class Event_list;

class Link
{
	Link *next, *prev;
	Event *data;
	friend class Event_list;
public:
	Link();
	Link(Event *ptr);
	~Link();
	
	void add(Link *item);
	void remove();

	 
};
#endif // SYMULACJA CYFROWA Link H
