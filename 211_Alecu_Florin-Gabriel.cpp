#include <iostream>
#include <string.h>
#include <windows.h>

using namespace std;

int echar(char *c1, char *c2){
    if(strlen(c1)!=strlen(c2) || c1==NULL || c2==NULL)
        return 0;
    else{
        for(int i=0; i < strlen(c1); i++){
            if(c1[i]!=c2[i])
                return 0;
        }
    }
    return 1;
}
///////////////////////////////////////////////////////student
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

student::student(char *num = NULL, int an_nastere = 0, int numar_credite = 0, double medie_generala = 0) { ///initializare
	if (num != NULL) {
		this->nume = new char[strlen(num)];
		strcpy(nume, num);
	}
	this->an_nastere = an_nastere;
	this->numar_credite = numar_credite;
	this->medie_generala = medie_generala;
}
student::student(student &s) {   ///copiere
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

void student::set(char *num, int an_nastere = 0, int numar_credite = 0, double medie_generala = 0) {
    if (num != NULL) {
		this->nume = new char[strlen(num)];
		strcpy(this->nume, num);
	}
	this->an_nastere = an_nastere;
	this->numar_credite = numar_credite;
	this->medie_generala = medie_generala;
}

void student::set(student &s) {
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
	num = new char[250];
	in >> num;
	nume = new char [strlen(num)];
    strcpy(nume,num);

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
		out << "Nume student: " << nume << "\nAnul nasterii: " << an_nastere << "\nNumar credite: " << numar_credite << "\nMedie generala: " << medie_generala << "\n";
}
ostream& operator<<(ostream& out, student& z) {
	z.afisare(out);
	return out;
}
char *student::getNume() {
	return this->nume;
}
////////////////////////////////////////////////////////////////////grupa
class grupa {
private:
	int nr_studenti;
	student *v;
	double medie_generala_grupa;

public:
	grupa();
	grupa(grupa&);				//constructor copiere
	~grupa();
	//eliminare student din grupa//
	void elimina(char*);
	//adaugare student in grupa//
	void adauga(student);
	//verificare daca exista student in grupa (dupa nume)//
	void verificare(char*);
	int returnNrStudenti();
	void afisareNumeStudenti();
	void afisare(ostream &out);
	friend ostream& operator<<(ostream &out, grupa& g); //supraincarcare <<
};
grupa::grupa() {
	this->nr_studenti = 0;
	this->medie_generala_grupa = 0;
	this->v = new student[10];
}	  //constructor

grupa::grupa(grupa& g){
	this->nr_studenti = g.nr_studenti;
	this->medie_generala_grupa = g.medie_generala_grupa;
	this->v = new student[nr_studenti];
	for(int i = 0; i < nr_studenti; i++)
		v[i].set(g.v[i]);
}

grupa::~grupa() {
	delete[] v;
	nr_studenti = 0;
	medie_generala_grupa = 0;
}   //destructor

void grupa::adauga(student s){
	student *temp;
	temp = new student[nr_studenti];

	for(int i = 0; i <= nr_studenti-1; i++)
		temp[i].set(v[i]);

	//for(int i =0; i<nr_studenti; i++)  //debug
	//	cout<<temp[i]<<" \n";

	delete[] v;
	this->nr_studenti = nr_studenti + 1;
	this->v = new student[nr_studenti];

	if(nr_studenti > 1)

		for(int i = 0; i<=nr_studenti-2; i++){
			v[i].set(temp[i]);
			//cout<<v[i]<<"\n"; //debug
		}
	//delete[] temp;
	v[nr_studenti-1].set(s);
	//cout<<v[nr_studenti-1]<<"\n"; //debug
}


void grupa::elimina(char *nume = NULL) {
		if(nr_studenti > 0){
			bool ok = 1;
			student *temp;
			temp = new student[nr_studenti - 1];

			for(int i = 0; i < nr_studenti - 1; i++){
				if(echar(nume, v[i].getNume()) != 0)
					ok = 0;
				if(ok)
					temp[i].set(v[i]);
				if(!ok)
					temp[i].set(v[i+1]);
			}
			if(echar(nume, v[nr_studenti-1].getNume())!=0)
				ok = 0;
			if(ok == 0){
				delete[] v;
				this->nr_studenti--;
				v = new student[nr_studenti];
				for(int i = 0; i < nr_studenti; i++)
					v[i].set(temp[i]);

				delete[] temp;
				cout << "Studentul a fost sters din grupa!\n";
			}
			else
				cout << "Studentul nu exista!\n";
		}
		else
			cout << "Nu exista studenti in grupa!!\n";
}
void grupa::verificare(char *nume) {
	bool ok = false;
	for (int i = 0; i < nr_studenti; i++) {
		if (echar(v[i].getNume(), nume) != 0) {
            //cout<<"\n"<<this->v[i].getNume()<<" == "<<nume;
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
	for (int i=0; i < nr_studenti; i++) {
		cout << v[i].getNume() << "\n";
	}
}
int grupa::returnNrStudenti() {
	return nr_studenti;
}
void grupa::afisare(ostream &out) {
	int i;
	if (this->nr_studenti == 0)
		out << "Nu exista studenti in aceasta grupa!";
	else
		for (i = 0; i < this->nr_studenti; i++) {
			out << this->v[i] << "\n\n";
		}
}
ostream &operator<<(ostream& out, grupa &g){
	g.afisare(out);
	return out;
}

void menu_output()
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
			cout << gr;
		}
		if (option == 3)
		{
			char *nume;
			if(gr.returnNrStudenti() > 0 ){
            cout << "Studentii din grupa: \n";
            gr.afisareNumeStudenti();	//Afisaza numele studentilor din grupa
            cout << "Introduceti numele studentului pe care vreti sa il eliminati din grupa: \n";
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
    menu();

	return 0;
}
