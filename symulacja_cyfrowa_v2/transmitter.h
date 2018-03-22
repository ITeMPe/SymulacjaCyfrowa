#ifndef SYMULACJA_CYFROWA_TRANSMITTER_H
#define SYMULACJA_CYFROWA_TRANSMITTER_H
#include <queue>
class Packet;
using namespace  std;

class Transmitter
{
	double negative_transmission_number_;  // liczba odrzuconych pakietow
	double positive_transmission_number_;  //liczba dostarczonych pakietow
	double packet_error_level_;
public:

	Transmitter();
	~Transmitter();
	queue <Packet*> bufor_;
	int transmiter_id_;
	int packet_generation_number;			//liczba wygenerowanych pakietow przez  transmitery
	//int generation_time_;  // czas generacji pakietu ->zmienna losowa
	bool ack;

	void generate_packet_(Packet *ptr, double time);  // funkcja generujaca pakiety

	void negative_transmission_number_increment();
	double show_negative_transmission_number();
	void set_negative_transmission_number(double x);

	void positive_transmission_number_increment();
	double show_positive_transmission_number();
	void set_positive_transmission_number(double x);
	void set_packet_error_level(double x, double y);
	double show_packet_error_level();
};
#endif // SYMULACJA CYFROWA Transmitter H
