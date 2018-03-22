#ifndef SYMULACJA_CYFROWA_MEDIUM_H
#define SYMULACJA_CYFROWA_MEDIUM_H
class Packet;

class Medium
{
	bool medium_access;	// dostep do lacza		
	double medium_time_busy; // czas zajetosci medium;


public:
	Medium();
	~Medium();

	Packet *tab_transmitted_packets[10];  // tablica przesylanych paietow   
										 // jesli jest wiecej niz jeden element -->  KOLIZJA MOZLIWA
	int iterator;						//pomocny do w/w tablicy 
	bool collision;

	bool medium_free();
	bool set_medium_access(bool data);
	double set_medium_time_busy(double busy_time,double clk);
	double show_medium_time_busy();
 
	bool show_medium_access();
	//double difs;
};
#endif // SYMULACJA CYFROWA Medium H
