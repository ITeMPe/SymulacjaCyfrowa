#include <iostream>
#include <cstdlib>
#include <string>
#include "symulation.h"
using namespace std;

int main()
{
	//srand(time(nullptr));
	int work_step_by_step = 0;

	bool show_messages = false;

	double required_simulation_time=60000;			// czas trwania symulacji
	double begining_phase_length = 1200;			//Wartosc wyznaczona na podstawie wykresow fazy poczatkowej...
	int symulation_number = 0;
	cout << "SYMULACJA CYFROWA" << endl << "Marcin Przepiorkowski " << endl << "Elektronika i Telekomunikacja" << endl << endl;;
	
	cout << "Jesli chcesz wybrac prace krokowa wcisnij 1" << endl << endl;
	cin >> work_step_by_step;
	if (work_step_by_step == 1) { show_messages = 1; }
	cout << "Wpisz nr. symulacji do wykonania: [ od 0 do 9 ] " << endl;
	cin >> symulation_number;
//*************************************************************************************************
	Symulation symulation;

		//cout << "podaj wymagany czas symulacji: " << endl;
		//cin >> required_simulation_time;
		if (required_simulation_time < 0) required_simulation_time = 60000; // bezpiecznik 
		symulation.start_symulation(required_simulation_time, work_step_by_step, show_messages, begining_phase_length, symulation_number);
		cout << endl << "-------------KONIEC SYMULACJI------ " << symulation_number << " ----" << endl;
		cout << endl << endl;
		cout << endl << endl;
		system("pause");
	
	return 0;
}