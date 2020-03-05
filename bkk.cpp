#include "pch.h"
#include <iostream>
#include <string.h>

using namespace std;

int echar(char *c1, char *c2){
    if(strlen(c1)!=strlen(c2))
        return 0;
    else{
        for(int i=0; i < strlen(c1); i++){
            if(c1[i]!=c2[i])
                return 0;
        }
    }
    return 1;
}

class student {
private:
	char *nume;
	int an_nastere;
	int numar_credite;
	double medie_generala;
public:
	student(char*, int, int, double);                     ///constructor initializare
	student(student&);                     ///constructor copiere
	~student();                            ///destructor

	void set(char*, int, int, double); //set
	void set(student&); //set copy

	void afisare(ostream &out);
	void citire(istream &in);
	friend istream& operator>>(istream &in, student& z);  ///supraincarcare pe >>
	friend ostream& operator<<(ostream &out, student& z); ///supraincarcare pe <<

	char *getNume();
};

student::student(char *nume = NULL, int an_nastere = 0, int numar_credite = 0, double medie_generala = 0) { ///initializare
	//this->nume = nume;
	if (nume != NULL) {
		this->nume = new char[strlen(nume)];
		strcpy(this->nume, nume);
	}
	this->an_nastere = an_nastere;
	this->numar_credite = numar_credite;
	this->medie_generala = medie_generala;
}
student::student(student &s) {   ///copiere
	//this->nume = s.nume;
	if (s.nume != NULL) {
		this->nume = new char[strlen(s.nume)];
		strcpy(this->nume, s.nume);
	}
	this->an_nastere = s.an_nastere;
	this->numar_credite = s.numar_credite;
	this->medie_generala = s.medie_generala;
}
student::~student() {    ///destructorul
	this->nume = NULL;
	this->an_nastere = 0;
	this->numar_credite = 0;
	this->medie_generala = 0;
}

void student::set(char *nume, int an_nastere = 0, int numar_credite = 0, double medie_generala = 0) {
	//this->nume = nume;
    if (nume != NULL) {
		this->nume = new char[strlen(nume)];
		strcpy(this->nume, nume);
	}
	this->an_nastere = an_nastere;
	this->numar_credite = numar_credite;
	this->medie_generala = medie_generala;
}

void student::set(student &s) {
	//this->nume = s.nume;
    if (s.nume != NULL) {
		this->nume = new char[strlen(s.nume)];
		strcpy(this->nume, s.nume);
	}
	this->an_nastere = s.an_nastere;
	this->numar_credite = s.numar_credite;
	this->medie_generala = s.medie_generala;
}


void student::citire(istream &in) {
	cout << "Cititi numele studentului: ";
	char *num;
    in.getline(num,250);
    this->nume=new char[strlen(num)];
    strcpy(this->nume,num);

	cout << "Cititi anul nasterii al studentului: ";
	in >> an_nastere;
	cout << "Cititi numarul de credite ale studentului: ";
	in >> numar_credite;
	cout << "Cititi media generala a studentului: ";
	in >> medie_generala;
}
istream& operator>>(istream& in, student& z) {
	z.citire(in);
	return in;
}

void student::afisare(ostream &out) {
	out << "Nume student: " << nume << "\nAnul nasterii: " << an_nastere << "\nNumar credite: " << numar_credite << "\nMedie generala: " << medie_generala;
}
ostream& operator<<(ostream& out, student& z) {
	z.afisare(out);
	return out;
}
char *student::getNume() {
	return this->nume;
}

class grupa {
private:
	int nr_studenti;
	int nr_max_studenti;
	student *v = new student[30];	// vector de studenti alocat dinamic?---------------------------------------------------------
	double medie_generala_grupa;

public:
	//constructor de initializare, destructor care dezaloca toti studentii pointati in componenetele vectorului//
	//grupa(int , student*, double);
	grupa();
	grupa(int, student);         /////////////////////////////////////////
	grupa(grupa&);				/////////////////////////////////////////
	~grupa();
	//eliminare student din grupa//
	void elimina(char*);
	//adaugare student in grupa//
	void adauga(student);
	//verificare daca exista student in grupa (dupa nume)//
	void verificare(char*);
	int returnNrStudenti();
	void afisareNumeStudenti();
	void afisare();
};
grupa::grupa() {
	this->nr_studenti = 0;
	this->medie_generala_grupa = 0;
}	  //constructor

grupa::~grupa() {
	delete[] v;
}   //destructor

void grupa::adauga(student s) {
	this->nr_studenti++;
	this->v[(this->nr_studenti) - 1].set(s);
}

void grupa::elimina(char *nume) {
		bool ok = 1;
		for (int i = 0; i < (this->nr_studenti) - 1; i++) {
			if (echar(nume, this->v[i].getNume())!=0)
				ok = 0;
			if (!ok) {
				//continue;
				this->v[i].set(this->v[i + 1]);
			}
		}
		if (ok && echar(this->v[this->nr_studenti - 1].getNume(), nume)!=0) {
			this->v[this->nr_studenti - 1].set(NULL, 0, 0, 0);
			ok = 0;
		}
		if (ok == 0) {
			this->nr_studenti--;
			cout << "Student sters din grupa!\n";
		}
		else
			cout << "Studentul nu exista!";
}
void grupa::verificare(char *nume) {
	bool ok = false;
	for (int i = 0; i < nr_studenti; i++) {
		if (echar(this->v[i].getNume(), nume) != 0) {
            cout<<"\n"<<this->v[i].getNume()<<" == "<<nume;
			ok = true;
			break;
		}
	}
	if (ok)
		cout << "Elevul se afla in aceasta grupa.\n";
	else
		cout << "Elevul NU se afla in grupa\n";
}
void grupa::afisareNumeStudenti() {
	for (int i=0; i < this->nr_studenti; i++) {
		cout << this->v[i].getNume() << "\n";
	}
}
int grupa::returnNrStudenti() {
	return this->nr_studenti;
}
void grupa::afisare() {
	int i;
	for (i = 0; i < this->nr_studenti; i++) {
		cout << this->v[i] << "\n\n";
	}
	if (i == 0)
		cout << "Nu exista studenti in aceasta grupa!";
}

void menu_output()
{
	cout << "\n Alecu Florin Gabriel - Grupa 211 - 12 - Nume proiect: \n";
	cout << "\n\t MENIU:";
	cout << "\n===========================================\n";
	cout << "\n";
	cout << "1. Adauga un student in grupa.\n";
	cout << "2. Afisaza studentii din grupa grupa.\n";
	cout << "3. Elimina un student in grupa.\n";
	cout << "4. Verifica dupa nume daca un student se afla in grupa.\n";
	cout << "0. Iesire.\n";
}
void menu()
{
	int option;///optiunea aleasa din meniu
	option = 0;

	grupa gr;
	do
	{
		menu_output();

		cout << "\nIntroduceti numarul actiunii: ";
		cin >> option;

		if (option == 1)
		{
			student q;
			cin >> q;
			cout << q;
			gr.adauga(q);
		}
		if (option == 2) {
			//Afisare
			gr.afisare();
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
                cin.getline(nume,256);
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
                cin.getline(nume,256);
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
		//system("pause"); ///Pauza - Press any key to continue...
		//system("cls");   ///Sterge continutul curent al consolei
	} while (option != 0);
}

int main() {
	menu();
	student a;
	cin >> a;
	cout<<a;
	return 0;
}
