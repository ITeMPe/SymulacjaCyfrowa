#include "symulation.h"
#include "event_list.h"
#include "process.h"
#include "event.h"
#include <ctime>
#include "transmitter.h"
#include <iostream>
#include <windows.h>
#include "medium.h"
#include <ostream>
#include "source.h"
#include <string>
#include <fstream>
#include "generator.h"
using namespace std;

Symulation::Symulation()
{
	agenda = new Event_list();
	all_packets_ = 0;
	all_positive_transmission_ = 0;
	all_negative_transmission_ = 0;
	all_retransmissions_ = 0;
	symul_ptr = this;
	all_delay_packet_time_ = 0.0;
	all_waiting_packet_time = 0.0;
	average_delay_packet_time_ = 0.0;
	average_waiting_packet_time = 0.0;
	all_positive_delivery_retransmition_ = 0.0;
	average_packet_error_level = 0.0;
	Generator ** generators = nullptr;
}

Symulation::~Symulation()
{
}

void Symulation::start_symulation(double requied_simulation_time, int work_step_by_step,  bool show_messages, double begin_phase_length, int sym_numb)
{
	
	generators = new Generator*[400];
	fstream file;
	file.open("ziarna123.txt", ios::in);
	if (file.good() == false)
	{
		cout << "Plik nie istnieje";
		exit(0);
	}
	string line;
	int licznik = 0;
	while (getline(file, line))
	{
		generators[licznik] = new Generator(atoi(line.c_str()));
		licznik++;
	}
	file.close();


	HANDLE hOut;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
//-------------------------------------------------------------------------
	double clock = 0.0;
	Medium *medium=new Medium();
	Transmitter transmitter[10];			// stworzenie 10 transmiterow (nadajnikow)
	Transmitter *tran_tab_ptr = transmitter;
											// ZMIANA LICZBY TRANSMITEROW.......********************************************************************** z 4 na 10
	for (int i = 0; i < 10;++i)
	{
		transmitter[i].transmiter_id_=i;
		transmitter[i].packet_generation_number = 0;
	}
	 
	Transmitter *transmitter_ptr = nullptr;
	double max_packet_error_level;

	transmitter_ptr = &transmitter[0];
Source *source0 = new Source(transmitter_ptr,symul_ptr,sym_numb*30+0);
source0->start_source(agenda, clock);

	transmitter_ptr = &transmitter[1];
Source *source1 = new Source(transmitter_ptr, symul_ptr, sym_numb * 30 + 3);
source1->start_source(agenda, clock);

	transmitter_ptr = &transmitter[2];
Source *source2 = new Source(transmitter_ptr, symul_ptr, sym_numb * 30 + 6);
source2->start_source(agenda, clock);

	transmitter_ptr = &transmitter[3];
Source *source3 = new Source(transmitter_ptr, symul_ptr, sym_numb * 30 + 9);
source3->start_source(agenda, clock);
//**************************************************************************************************************************
transmitter_ptr = &transmitter[4];
Source *source4 = new Source(transmitter_ptr, symul_ptr, sym_numb * 30 + 12);
source4->start_source(agenda, clock);

transmitter_ptr = &transmitter[5];
Source *source5 = new Source(transmitter_ptr, symul_ptr, sym_numb * 30 + 15);
source5->start_source(agenda, clock);

transmitter_ptr = &transmitter[6];
Source *source6 = new Source(transmitter_ptr, symul_ptr, sym_numb * 30 + 18);
source6->start_source(agenda, clock);

transmitter_ptr = &transmitter[7];
Source *source7 = new Source(transmitter_ptr, symul_ptr, sym_numb * 30 + 21);
source7->start_source(agenda, clock);
//**************************************************************************************************************************
transmitter_ptr = &transmitter[8];
Source *source8 = new Source(transmitter_ptr, symul_ptr, sym_numb * 30 + 24);
source8->start_source(agenda, clock);

transmitter_ptr = &transmitter[9];
Source *source9 = new Source(transmitter_ptr, symul_ptr, sym_numb * 30 + 27);
source9->start_source(agenda, clock);



//**************************************************************************************************************************



	while(clock < requied_simulation_time)
	{
		
		//---------------------------------------------------------//
		SetConsoleTextAttribute(hOut, FOREGROUND_RED);
if(show_messages) cout << endl << "\t AGENDA" << endl;
if (show_messages)agenda->show_agenda();						//to dla mnie info o agendzie
		current = agenda->first()->proc_;	
		clock = agenda->first()->event_time_;
		
		agenda->remove_first(show_messages);			
		current->execute(agenda, clock,medium, tran_tab_ptr, symul_ptr,begin_phase_length);		// wykonywanie pierwszego pakietu z agendy
		
		SetConsoleTextAttribute(hOut, FOREGROUND_INTENSITY);
if (show_messages)	cout << "Wykonywanie procesu: " << current <<"\t faza procesu: "<<current->phase<< "\t id_pakietu (procesu): "<< "POMYSLE POZNIEJ"<<endl;
		
		SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
if (show_messages)	cout <<"clock: "<< clock <<"\t requied_simulation_time: "<<requied_simulation_time<<endl<<endl;

		for (int i = 0; i < 10; i++)
		{
if (show_messages)	cout << "Bufor nr: " << i << "  ilosc pakietow w buforze: " << transmitter[i].bufor_.size() << endl;
		}
if (show_messages)	cout << endl <<endl << endl;
		if(work_step_by_step == 1)
		{
			system("pause");
		}

		if(begin_phase_length>clock)
		{
			set_all_packets(0);
			set_all_retransmission(0);
			set_all_positive_transmission(0);
			set_all_negative_transmission(0);
			set_all_delay_packet_time(0);
			set_all_waiting_packet_time(0);
			set_average_waiting_packet_time(0, 1);
			set_averag_delay_time(0,1);
			average_packet_error_level = 0.0;
			all_positive_delivery_retransmition_ = 0.0;
		}

			if (show_messages)
			{
			cout << endl << "Liczba wygenerowanych pakietow: " << symul_ptr->all_packets_ << endl;
			cout << "Liczba pozytywnych transmisji:  " << symul_ptr->all_positive_transmission_ << endl;
			cout << "Liczba negatywnych transmisji:  " << symul_ptr->all_negative_transmission_ << endl;
			cout << "Liczba retransmisji:  " << symul_ptr->all_retransmissions_ << endl << endl;
			}

	}//---------------------------------------------- END WHILE
	




	
	
	
cout << endl << endl <<" S T A T Y S T Y K I  DLA SYMULACJI nr. " <<sym_numb<< endl << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << "Bufor nr: " << i << "  ilosc pakietow w buforze: " << transmitter[i].bufor_.size() <<endl<< endl;
	}


	cout << "Liczba wygenerowanych pakietow: " << symul_ptr->all_packets_ << endl;
	cout << "Liczba pozytywnych transmisji:  " << symul_ptr->all_positive_transmission_ << endl;
	cout << "Liczba negatywnych transmisji:  " << symul_ptr->all_negative_transmission_ << endl;
	cout << "Liczba retransmisji:  " << symul_ptr->all_retransmissions_ << endl << endl;
	
	
		for (int i = 0; i < 10;i++)  //to dla mnie zeby wiedziec czy statystyki nei klamia :D
		{
			if(transmitter[i].show_positive_transmission_number() !=0)   // zabezpieczenie --> czasem transmiter nie wyslal jeszcze nic i byloby dzielenie przez 0 !!!
			{
				transmitter[i].set_packet_error_level(transmitter[i].show_negative_transmission_number(), transmitter[i].show_positive_transmission_number());
			}
			else { transmitter[i].set_packet_error_level(0, 1); }
			SetConsoleTextAttribute(hOut, FOREGROUND_RED);
			cout << "\t Pakietowa Stopa bledow transmitera " << transmitter[i].transmiter_id_ << "\t" <<transmitter[i].show_packet_error_level() <<" %"<< endl;SetConsoleTextAttribute(hOut, FOREGROUND_GREEN);
			cout << "\t Liczba wygenerowanych pakietow przez transmiter: " << transmitter[i].packet_generation_number << endl;
			cout << "\t Liczba dostarczonych pakietow przez transmiter: " << transmitter[i].show_positive_transmission_number() << endl<<endl;
		}cout << endl << endl; 
		for (int i = 0; i < 10;i++)
		{
			average_packet_error_level += transmitter[i].show_packet_error_level();
		}
		average_packet_error_level = average_packet_error_level / 10.0;
		cout << "Srednia pakietowa stopa bledow: " << symul_ptr->average_packet_error_level <<" %"<< endl;
		

		max_packet_error_level = transmitter[0].show_packet_error_level();
		for (int i = 1; i < 10; i++)
		{
			if (transmitter[i].show_packet_error_level() > max_packet_error_level)
			{
				max_packet_error_level = transmitter[i].show_packet_error_level();
			}
		}

		cout <<endl<<endl<< "Maksymalna pakietowa stopa bledow: " <<max_packet_error_level<<" %"<<endl<< endl;
		
		cout << "Srednia liczba retransmisji pakietow: " << symul_ptr->all_positive_delivery_retransmition_ / symul_ptr->show_all_positive_transmissions() << endl << endl;
		
		cout << "Przeplywnosc systemu: " << symul_ptr->all_positive_transmission_ / requied_simulation_time *1000 <<" [pakiet/sek]" <<endl<< endl;
	
		symul_ptr->set_averag_delay_time(symul_ptr->show_all_delay_packet_time(), symul_ptr->show_all_positive_transmissions());
		cout << "Srednie opoznienie pakietu w buforze: " <<  symul_ptr->show_average_delay_time()<< " ms" << "\t\t";
				cout << " all delay packet time: " << symul_ptr->show_all_delay_packet_time() << "\t\t all positive transmission: " << symul_ptr->show_all_positive_transmissions() <<endl<< endl;
			
		symul_ptr->set_average_waiting_packet_time(symul_ptr->show_all_waiting_time(), symul_ptr->show_all_positive_transmissions());
		cout << "Sredni czas oczekiwania: " << symul_ptr->show_average_waiting_packet_time() << " ms" << "\t\t";
				cout << " waiting time: " << symul_ptr->show_all_waiting_time() << "\t\t all positive transmission: " << symul_ptr->show_all_positive_transmissions() <<endl<< endl;

	cout << endl;
	cout << endl << "ZEGAR --> " << clock << endl;




}

void Symulation::set_all_packets(int x)
{
	all_packets_ = x;
}

void Symulation::set_all_retransmission(int x)
{
	all_retransmissions_ = x;
}

void Symulation::set_all_positive_transmission(int x)
{
	all_positive_transmission_ = x;
}

void Symulation::set_all_negative_transmission(int x)
{
	all_negative_transmission_ = x;
}



void Symulation::all_packets_increment()
{
	++all_packets_;
}

void Symulation::all_retrensmissions_increment()
{
	++all_retransmissions_;
}

void Symulation::all_positive_transmission_increment()
{
	++all_positive_transmission_;
}

void Symulation::all_negative_transmission_increment()
{
	++all_negative_transmission_;
}

void Symulation::set_all_delay_packet_time(double time)
{

	all_delay_packet_time_ += time;
}

double Symulation::show_all_delay_packet_time()
{
	return all_delay_packet_time_;
}

int Symulation::show_all_positive_transmissions()
{
	return all_positive_transmission_;
}

void Symulation::set_averag_delay_time(double time1, int deliver_packets)
{
	 average_delay_packet_time_ =  time1 / static_cast<double>(deliver_packets);
}

double Symulation::show_average_delay_time()
{
	return average_delay_packet_time_;
}
void Symulation::set_average_waiting_packet_time(double time1, int deliver_packets)
{
	average_waiting_packet_time = time1 / static_cast<double>(deliver_packets);
}

double Symulation::show_average_waiting_packet_time()
{
	return average_waiting_packet_time;
}

void Symulation::set_all_waiting_packet_time(double time)
{
	
	all_waiting_packet_time += time;
}

double Symulation::show_all_waiting_time()
{
	return all_waiting_packet_time;
}
