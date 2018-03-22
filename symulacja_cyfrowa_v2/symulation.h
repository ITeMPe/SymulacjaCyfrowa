#ifndef SYMULACJA_CYFROWA_SYMULATION_H
#define SYMULACJA_CYFROWA_SYMULATION_H
#include  "event_list.h"
#include <queue>
using namespace  std;
class Event_list;
class Process;
class Generator;

class Symulation
{
	int all_packets_;
	int all_retransmissions_;
	int all_positive_transmission_;
	double all_negative_transmission_;
	double all_delay_packet_time_;
	double all_waiting_packet_time;
	double average_delay_packet_time_;
	double average_waiting_packet_time;
public:
	Symulation();
	~Symulation();
	double all_positive_delivery_retransmition_;
	Generator ** generators;
	Process *current;
	Event_list *agenda;
	Symulation *symul_ptr;
	double clock;
	queue<double> my_packets_queue;
	double average_packet_error_level;

	void start_symulation(double required_simulation_time_,int work_step_by_step, bool show_messages,double begin_phase_length, int sym_numb);
	void all_packets_increment();
	void all_retrensmissions_increment();
	void all_positive_transmission_increment();
	void all_negative_transmission_increment();
	void set_all_delay_packet_time(double time);
	void set_all_waiting_packet_time(double time);
	double show_all_delay_packet_time();
	int show_all_positive_transmissions();
	double show_all_waiting_time();
	void set_averag_delay_time(double time1, int deliver_packets);
	void set_average_waiting_packet_time(double time1, int deliver_packets);
	double show_average_delay_time();
	double show_average_waiting_packet_time();
	void set_all_packets(int x);
	void set_all_retransmission(int x);
	void set_all_positive_transmission(int x);
	void set_all_negative_transmission(int x);
};
#endif // SYMULACJA CYFROWA Symulation H

