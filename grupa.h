#include "student.h"

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

class grupa {
private:
	char *nume_grupa;
	int nr_studenti;
	//int nr_max_studenti;
	student *v;	// vector de studenti alocat dinamic?---------------------------------------------------------
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
};
grupa::grupa() {
	this->nr_studenti = 0;
	this->medie_generala_grupa = 0;
	this->v = new student[10];
}	  //constructor


grupa::grupa(grupa& g){
	this->nr_studenti = g.nr_studenti;
	//this->nr_max_studenti = g.nr_max_studenti;
	this->medie_generala_grupa = g.medie_generala_grupa;
	nume_grupa = g.nume_grupa;
	this->v = new student[nr_studenti];
	for(int i = 0; i < nr_studenti; i++)
		v[i].set(g.v[i]);
}

grupa::~grupa() {
	delete[] v;
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
