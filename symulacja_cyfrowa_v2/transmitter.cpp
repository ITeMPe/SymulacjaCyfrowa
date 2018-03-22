#include "transmitter.h"
#include  "packet.h"
#include <iostream>

using namespace std;

Transmitter::Transmitter()
{
	//generation_time_ = 10; // tymczasowo
	negative_transmission_number_ = 0.0;
	positive_transmission_number_ = 0.0;
	packet_error_level_ = 0.0;
}


Transmitter::~Transmitter()
{
}

void Transmitter::generate_packet_(Packet *packet, double time) //funkcja generujaca pakiet
{
	++packet_generation_number;
	packet->set_packet_id(this->transmiter_id_, this->packet_generation_number);
	packet->set_arrival_packet_time(time);
	bufor_.push(packet);

}


void Transmitter::negative_transmission_number_increment()
{
	negative_transmission_number_++;
}

double Transmitter::show_negative_transmission_number()
{
	return negative_transmission_number_;
}

void Transmitter::positive_transmission_number_increment()
{
	positive_transmission_number_++;
}

double Transmitter::show_positive_transmission_number()
{
	return positive_transmission_number_;
}

void Transmitter::set_negative_transmission_number(double x)
{
	negative_transmission_number_ = x;
}

void Transmitter::set_positive_transmission_number(double x)
{
	positive_transmission_number_ = x;
}

void Transmitter::set_packet_error_level(double x, double y)
{
	packet_error_level_ = (x / (x + y)) *100;
}

double Transmitter::show_packet_error_level()
{
	return packet_error_level_;
}

