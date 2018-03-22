#include "event_list.h"
#include  "link.h"
#include "event.h"
#include <iostream>
#include <windows.h>
using namespace std;


Event_list::Event_list()
{
	head = new Link (new Event());
	number_elements = 0;
}


Event_list::~Event_list()
{
}

void Event_list::schedule(Event*e)		// przeszukiwanie odpowiedniego miejsca na liscie do wstawienia nowego zdarzeia
{

		Link *k;
		for (k = head->prev; k->data->event_time_ > e->event_time_; k = k->prev);
		(new Link(e))->add(k);
		++number_elements;

}
void Event_list::show_agenda()
{

	Link *p= head->next;
	 while(p  != head)
	 {
		 cout <<endl<< "\t \t event_time: " << p->data->event_time_ << endl << "\t \t *proces : " << p->data->proc_ <<endl<<"\t \t liczba elementow w agendzie: "<<number_elements<< endl;
		 cout << "\t \t proces nastepny: " << p->next->data->proc_ << "\t\t event time nastepnego procesu: " << p->next->data->event_time_ << endl;
		 cout << "\t \t proces poprzedni: " << p->prev->data->proc_ << "\t\t event time poprzedniego procesu: " << p->prev->data->event_time_ << endl<<endl;
		 
	 	p = p->next;
	 }
}


bool Event_list::empty()
{
	return head->next == head;
}

Event* Event_list::first()	// pokazuje pierwszy element z listy, poza "sztucznym" zdarzeniem
{
	
	return head->next->data;
}

Event* Event_list::remove_first(bool show_messages) //usuwanie pierwszego elementu z listy
{
	Event *current = first();
if (show_messages)	cout <<"current = "<<current<< "\t Usuwany jest pakiet: " << head->next->data<< endl;
	head->next->remove();
	--number_elements;
	current = first();
if (show_messages)	cout << "zwracam current: " << current << endl;
	return current;
}

int Event_list::show_number_elements()
{
	return number_elements;
}
