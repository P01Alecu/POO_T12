#include <iostream>
#include <string.h>
#include "grupa.h"
#include <windows.h>

using namespace std;

void menu_output1()
{
	cout << "\n Alecu Florin Gabriel - Grupa 211 - 12 - Nume proiect: \n";
	cout << "\n\t MENIU:";
	cout << "\n===========================================\n";
	cout << "\n";
	cout << "1. Adauga un student in grupa.\n";
	cout << "2. Afisaza studentii din grupa.\n";
	cout << "3. Elimina un student in grupa.\n";
	cout << "4. Verifica dupa nume daca un student se afla in grupa.\n";
	cout << "0. Iesire.\n";
}
void menu_output2()
{
	cout << "\n Alecu Florin Gabriel - Grupa 211 - 12 - Nume proiect: \n";
	cout << "\n\t MENIUL GRUPEI " << " :";
	cout << "\n===========================================\n";
	cout << "\n";
	cout << "1. Creaza o grupa.\n";
	cout << "2. Sterge o grupa.\n";
	cout << "3. Intra in grupa pentru modificari.\n";
	cout << "0. Iesire.\n";
	cout << "\n Grupe existente: ";
}
void menu()
{
	int option;///optiunea aleasa din meniu
	option = 0;

	grupa gr;
	do
	{
		menu_output1();

		cout << "\nIntroduceti numarul actiunii: ";
		cin >> option;

		if (option == 1)
		{
			//student q("Alecu", 1, 1, 1);
			student q;
			cin >> q;
			cout << q;
			gr.adauga(q);
		}
		if (option == 2) {
			//Afisare
			cout << gr;
		}
		if (option == 3)
		{
			char *nume;
			if (gr.returnNrStudenti() == 0)
				cout << "Nu exista studenti in grupa!!";
			else {
				cout << "Studentii din grupa: \n";
				gr.afisareNumeStudenti();	//Afisaza numele studentilor din grupa
				cout << "Introduceti numele studentului pe care vreti sa il eliminati din grupa: \n";
				//cin >> nume;
                    //cin.getline(nume,256);
                nume = new char[256];
                cin >> nume;
            }
				gr.elimina(nume);
			}

		if (option == 4)
		{
			char *nume;
			if (gr.returnNrStudenti() == 0)
				cout << "Nu exista studenti in grupa!!";
			else {
				cout << "Introduceti numele studentului din grupa: ";
				//cin >> nume;
                    //cin.getline(nume,256);
                nume = new char[256];
                cin >> nume;
				gr.verificare(nume);
			}
		}
		if (option == 0)
		{
			cout << "\nEXIT!\n";
		}
		if (option < 0 || option>4)
		{
			cout << "\nSelectie invalida\n";
		}
		cout << "\n";
		system("pause"); ///Pauza - Press any key to continue...
		system("cls");   ///Sterge continutul curent al consolei
	} while (option != 0);
}

int main() {
    //menu();

    grupa *a = new grupa[5];
    student s("Alecu", 1, 2, 3);
    a[0].adauga(s);

    //grupa b(a[0]);
    grupa b;
    b = a[0];
    cout<<b;


	return 0;
}
