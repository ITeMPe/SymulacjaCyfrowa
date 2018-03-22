#include "link.h"
Link::Link()
{
}
Link::Link(Event* ptr)
{
	data = ptr;
	next = prev = this;
}
Link::~Link()
{
}

void Link::add(Link* item)	// funkcja wstawia obiekt na liste za elementem wskazywanym przez parametr 
{
	prev = item;
	next = item->next;
	item->next = next->prev = this;
}

void Link::remove() // funkcja usuwajaca obiekt z listy
{
	prev->next = next;
	next->prev = prev;
	delete this;
}
