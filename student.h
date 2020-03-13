#include <iostream>
using namespace std;
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
	//this->nume = nume;
	if (num != NULL) {
		this->nume = new char[strlen(num)];
		strcpy(nume, num);
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

void student::set(char *num, int an_nastere = 0, int numar_credite = 0, double medie_generala = 0) {
	//this->nume = nume;
    if (num != NULL) {
		this->nume = new char[strlen(num)];
		strcpy(this->nume, num);
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
    //in.getline(num,250);
	num = new char[250];
	in >> num;
    //this->nume=new char[strlen(num)];
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
	//if(nume!=NULL && nume!="")
	//	out << "Nume student: " << nume << "\nAnul nasterii: " << an_nastere << "\nNumar credite: " << numar_credite << "\nMedie generala: " << medie_generala;
		out << "Nume student: " << nume << "\nAnul nasterii: " << an_nastere << "\nNumar credite: " << numar_credite << "\nMedie generala: " << medie_generala << "\n";
	//else
	//	out << "Nu a fost introdus acest student!\n";

}
ostream& operator<<(ostream& out, student& z) {
	z.afisare(out);
	return out;
}
char *student::getNume() {
	return this->nume;
}
