#ifndef SYMULACJA_CYFROWA_PACKET_H
#define SYMULACJA_CYFROWA_PACKET_H
#include "process.h"
#include "transmitter.h"
class Medium;
class Source;

class Packet:public Process  // klasa Pakiet jest jedynym procesem w tej symulce
{
	double packet_transmission_time_;	// czas transmisji pakietu
	int retransmission_number_;		// liczba retransmisji
	int ack_transmission_time_; // czas transmisji ACK  CTIZ =1ms
	int packet_id;
	double arrival_packet_time; //czas przyjscia pakietu do bufora
	double delivery_time_packet_; //czas dostarczenia pakietu
	double leave_bufor_packet_time;  //czas opuszczenia pakietu z bufora
	double delay_packet_timie_;	 // opoznienie pakietu
	double waiting_packet_time; // czas oczekiwania pakietu
	
	
	Transmitter  *transmiter_ptr;
	Symulation   *symulation_ptr;
	Event_list	 *event_list_ptr;
	Medium       *medium_ptr;
	Source		 *src_ptr_;
public:
	Packet();
	Packet(Transmitter *ptr, Symulation *sym_ptr,Source *source_ptr, double time);

	~Packet();

	double time_in_medium;

	
	void execute(Event_list *list, double clock,Medium *med, Transmitter *ptr, Symulation *sym_ptr, double begin_phase_lengt);
double current_difs;
	 
	void set_ptt(int cgp);
	void inc_ret_number();
	void set_packet_id(int t, int n);
	int show_packet_id();

	void set_arrival_packet_time(double time);
	void set_leave_bufor_packet_time(double time);
	void set_delivery_packet_time(double time);
	void set_delay_packet_time(double time);
	void set_waiting_packet_time(double time);

	double show_leave_bufor_packet_time();
	double show_arrival_packet_time();
	
};
#endif // SYMULACJA CYFROWA Packet H
