#include "student.h"

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

class grupa {
private:
	char *nume_grupa;
	int nr_studenti;
	int nr_max_studenti;
	student *v = new student[30];	// vector de studenti alocat dinamic?---------------------------------------------------------
	double medie_generala_grupa;

public:
	grupa();
	//grupa(int, student);         /////////////////////////////////////////
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
	void copie(grupa&);
};
grupa::grupa() {
	this->nr_studenti = 0;
	this->medie_generala_grupa = 0;
}	  //constructor

grupa::grupa(grupa& g){
	this->nr_studenti = g.nr_studenti;
	this->nr_max_studenti = g.nr_max_studenti;
	this->medie_generala_grupa = g.medie_generala_grupa;
	nume_grupa = g.nume_grupa;
	for(int i = 0; i < nr_studenti; i++)
		v[i].set(g.v[i]);
}

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
	for (int i=0; i < this->nr_studenti; i++) {
		cout << this->v[i].getNume() << "\n";
	}
}
int grupa::returnNrStudenti() {
	return this->nr_studenti;
}
void grupa::afisare(ostream &out) {
	int i;
	for (i = 0; i < this->nr_studenti; i++) {
		out << this->v[i] << "\n\n";
	}
	if (i == 0)
		out << "Nu exista studenti in aceasta grupa!";
}
ostream &operator<<(ostream& out, grupa &g){
	g.afisare(out);
	return out;
}