#include "packet.h"
#include <iostream>
#include <windows.h>
#include "medium.h"
#include "process.h"
#include "transmitter.h"
#include "source.h"
#include "generator.h"
using namespace std;

Packet::Packet(Transmitter *ptr, Symulation *sym_ptr,Source *source_ptr, double time)
{
	retransmission_number_ = 0;   // LR
	ack_transmission_time_ = 1;	  // CTIZ
	packet_transmission_time_ = time;
	packet_id = 0;
	double current_difs = 0.0;
	transmiter_ptr = ptr;
	symulation_ptr = sym_ptr;
	src_ptr_ = source_ptr;
	sym_ptr->all_packets_increment();
	delivery_time_packet_ = 0.0;
	delay_packet_timie_ = 0.0;
	arrival_packet_time = sym_ptr->clock;
	leave_bufor_packet_time = 0.0;
	waiting_packet_time = 0.0;
	time_in_medium = 0.0;
}


Packet::~Packet()
{
}
void Packet::set_ptt(int cgp)
{
	packet_transmission_time_ = cgp;
}

void Packet::inc_ret_number()
{
	++retransmission_number_;
}
void Packet::set_packet_id(int transmit, int numb)
{
	packet_id = numb*10+transmit;  // zakodowany id pakietu = nr. wygenerowanego pakietu prze i'ty transmiter*10 + id transmitera
}
int Packet::show_packet_id()
{
	return packet_id;
}

void Packet::set_arrival_packet_time(double time)
{
	
	arrival_packet_time = time;
}
double Packet::show_arrival_packet_time()
{
	return arrival_packet_time;
}

void Packet::set_leave_bufor_packet_time(double time)
{
	
	leave_bufor_packet_time = time;
}
double Packet::show_leave_bufor_packet_time()
{
	return leave_bufor_packet_time;
}

void Packet::set_delay_packet_time(double time)
{
	
	delay_packet_timie_ = time;
}

void Packet::set_waiting_packet_time(double time)
{
	
	waiting_packet_time = time;
}
void Packet::set_delivery_packet_time(double time)
{
	
	delivery_time_packet_ = time;
}




void Packet::execute(Event_list *list, double clock, Medium *med, Transmitter *ptr, Symulation *sym_ptr, double begin_phase_lengt)
{

 bool show_messages = false;  //*************************** 		to zmienna do doatkowa potrzeba do debugowania

	if (show_messages)
	{
		system("cls");
		cout << "Symulacja w trakcjie... Porosze czekac :) " << endl;
		cout << "clock: " << clock << "\t\t liczba retransmisji aktualnie wykonujacego sie pakietu: " << this->retransmission_number_;
	}


	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
	//*****************************************************************************************************************
	if (show_messages) {
		cout << "Witaj w funkcji execute klasy Packet, zaczynmy zabawe :D " << endl;
		cout << "czas zajetosci medium: " << med->show_medium_time_busy() << "\t clock: " << clock << endl;
		cout << "dostep do lacza: " << med->show_medium_access() << endl;
		cout << "Pakiet wygenerowany z Transmitera nr. " << this->transmiter_ptr->transmiter_id_ << "\t ID pakietu:" << this->packet_id << "\t Liczba retransmisji pakietu: " << this->retransmission_number_ << endl;
	}
	bool active = true;
	while (active)
	{
		switch (phase)
		{
		case 0:
			if (show_messages)	cout << "switch 0" << endl;
			current_difs = 0.0;
			if (!this->transmiter_ptr->bufor_.empty())
			{
				if (transmiter_ptr->bufor_.front()->packet_id == this->packet_id)		//sprawdzenie czy pakiet jest pierwszy w kolejce do wysylania w buforze
				{
					this->set_leave_bufor_packet_time(clock); // ustawienie czasu opuszczenia pakietu z bufora
					phase = 1;			 // jesli tak to idz do kolejej fazy
				}
				else
				{
					active = false; break;		//uspij sie
				}
			}
		case 1:			// nasluchiwanie kanalu --> if DIFS >2ms  && medium jest wolne  -->faza 2
			if (show_messages)	cout << "switch 1" << endl;
			if (clock >= med->show_medium_time_busy())		//czy medium powinno byc juz wolne?
			{
				med->set_medium_access(true);
				if (show_messages)	cout << "NASLUCHIWANIE WOLNEGO LACZA...." << "DIFS = " << current_difs << endl;
				if (current_difs > 2)	
				{
					this->time_in_medium = clock;
					if (show_messages)		cout << "Mozna nadawac.. !!! --> DIFS = " << current_difs << endl;
					med->tab_transmitted_packets[med->iterator] = this;
					med->iterator = (med->iterator + 1) % 10;		// bylo mod 4
					if (show_messages)		cout << "adres pakietu: " << this << endl;   //*********
					phase = 2;
					this->activate(0.0, list, clock); active = false;
					break;
				}
				current_difs += 0.5;
				this->activate(0.5, list, clock);
				active = false; break;
			}
			this->activate(0.5, list, clock);
			current_difs = 0.0;
			active = false;
			break;
		case 2:
			if (med->iterator >1) //jesli iterator >2 --> sa co najmniej 2 pakiety w medium.. jest wiecej niz 1 pakiet --> trzeba sprawdzic czy czasy sa takie same czy nie
			{
				for (int i = 0; i < 10; i++)
				{
					if (med->tab_transmitted_packets[i % 20] != nullptr && med->tab_transmitted_packets[(i + 1) % 10] != nullptr) // zabezpieczenie przed przekroczeniem tablicy
					{
						if (med->tab_transmitted_packets[i % 10]->time_in_medium == med->tab_transmitted_packets[(i + 1) % 10]->time_in_medium) // czy czasy te same
						{
							med->collision = true;
						}
					}
				}
				if (med->collision)		// KOLIZJA WYKRYTA --> Retransmisja !!
				{
					for (int i = 0; i < 10; i++)
					{
						if (med->tab_transmitted_packets[i % 10] != nullptr)
						{
							if (med->tab_transmitted_packets[i % 10]->retransmission_number_>=5)
							{
								med->tab_transmitted_packets[i % 10]->phase = 4;
								active = false; break;
							}
							med->iterator = 0; //wyzerowanie iteratora
							med->tab_transmitted_packets[i]->phase = 1;
							med->tab_transmitted_packets[i]->retransmission_number_++;
							sym_ptr->all_retrensmissions_increment();
							int max_range = static_cast<int>(pow(2.0, this->retransmission_number_)-1);			// losowanie czasu ponownej retransisji
							double R = symulation_ptr->generators[src_ptr_->index_ + 2]->generator_rownomierny() * 100;
							int	temp_R = static_cast<int> (R);
							R = temp_R *max_range;
							R = R / 10.0;
							med->tab_transmitted_packets[i]->activate(med->tab_transmitted_packets[i]->packet_transmission_time_*R, list, clock); //RETRANSMISJA
							med->tab_transmitted_packets[i] = nullptr; 				
						}
					}
					active = false;
					break;
				}
			}
			else // tylko jeden pakiet w medium --> wysylaj
			{
				med->iterator = 0; //wyzerowanie iteratora
				this->activate(this->packet_transmission_time_, list, clock);
				med->set_medium_access(false);
				med->set_medium_time_busy(this->packet_transmission_time_ + this->ack_transmission_time_, clock);
				this->phase = 3;
				active = false;
				break;
			}
		case 3:		//  Koniec transmisji 
															if (show_messages)		cout << "switch 3" << endl;
															if (show_messages)		cout << "Koniec transmisji pakietu ..." << endl;
			if (retransmission_number_ < 5)				 // ZMIANA LICZBY MOZLIWYCH RETRANSMISJI DO 5 Z 15 !!!!!!!!!!!!!!!!!!!
			{											
					phase = 4;
					transmiter_ptr->ack = true;		// ustaienie potwierdzenia transmisji ACK 
			}
			else
			{
				transmiter_ptr->ack = false; 
				terminated = true;
				phase = 4;
			}
		case 4:		// koniec transmisji...
			if (show_messages)	cout << "switch 4" << endl;
			if (show_messages)	cout << "KONIEC TRANSMISJI !!!!" << endl;
			med->tab_transmitted_packets[0] = nullptr; med->iterator = 0;
								for (int i = 0; i < 10; i++)
								{
									if (show_messages)		cout << med->tab_transmitted_packets[i] << endl;
								}
			if (transmiter_ptr->ack)  // jesli odebrano ACK --> sukces
			{
				SetConsoleTextAttribute(hOut, FOREGROUND_RED);
				if (show_messages)	cout << "TRANSMISJA ZAKONCZONA SUKCESEM !!!" << endl;
				this->transmiter_ptr->positive_transmission_number_increment();
				
				sym_ptr->all_positive_transmission_increment();
				if (this->retransmission_number_ > 1) sym_ptr->all_positive_delivery_retransmition_++;
				
				this->set_delivery_packet_time(clock);
				if(begin_phase_lengt<clock)	this->set_delay_packet_time(delivery_time_packet_ - arrival_packet_time);
				this->set_waiting_packet_time(leave_bufor_packet_time - arrival_packet_time);
				sym_ptr->set_all_delay_packet_time(delay_packet_timie_);
				sym_ptr->set_all_waiting_packet_time(waiting_packet_time);
				if (!this->transmiter_ptr->bufor_.empty())
				{
					this->transmiter_ptr->bufor_.pop();		//  zdejmowanie dostarczonego pakietu z bufora
					if (!this->transmiter_ptr->bufor_.empty())
					{
						this->transmiter_ptr->bufor_.front()->activate(0.0, list, clock);		// obudenie kolejnego pakietu w buforze
					}
				}
				SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
				active = false; terminated = true;
				break;
			}
			SetConsoleTextAttribute(hOut, FOREGROUND_BLUE);
			if (show_messages)	cout << "TRANSMISJA ZAKONCZONA NIEPOWODZENIEM ...." << endl;
			this->transmiter_ptr->negative_transmission_number_increment(); 	// inkrementacja odrzuconych pakietow przez transmiter
			sym_ptr->all_negative_transmission_increment();
			if (show_messages)	cout << this->retransmission_number_ << endl;
			SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
			if (!this->transmiter_ptr->bufor_.empty())
			{
				this->transmiter_ptr->bufor_.pop();	//  zdejmowanie utraconego pakietu z bufora
				if (!this->transmiter_ptr->bufor_.empty())
				{
					this->transmiter_ptr->bufor_.front()->activate(0.0, list, clock);   // obudenie kolejnego pakietu w buforze
				}
			} 
			terminated = true;
			active = false;
			break;
			} //end switch 

		}
			if(begin_phase_lengt>clock)
			 {
				 set_arrival_packet_time(0);
				 set_leave_bufor_packet_time(0);
				 set_delivery_packet_time(0);
				 set_delay_packet_time(0);
				 set_waiting_packet_time(0);
				 this->transmiter_ptr->set_negative_transmission_number(0);
				 this->transmiter_ptr->set_positive_transmission_number(0);
				 this->symulation_ptr->all_positive_delivery_retransmition_ = 0;
			 }
	}

