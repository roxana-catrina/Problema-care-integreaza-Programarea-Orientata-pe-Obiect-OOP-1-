#include <iostream>
#include <list>
#include <string>
#include <fstream>
using namespace std;
class disciplina {
private:
	string denumire;
	float calificativ;
public:
	disciplina(string denumire, float calificativ) {
		this->calificativ = calificativ;
		this->denumire = denumire;
	}
	void afisare_disiciplina() {
		cout << "DENUMIRE: " << denumire << endl;
		cout << "CALIFICATIV: " << calificativ << endl;
	}
	void afisare_disiciplina_fisier(ofstream &fout) {
		fout << "DENUMIRE: " << denumire << endl;
		fout << "CALIFICATIV: " << calificativ << endl;
	}
	float get_calificativ() {
		return calificativ;
	}
	string get_denumire_disciplina() {
		return denumire;
	}
	void modificare_nota(float nota_noua) {
		calificativ = nota_noua;
	}
};
class profesor_coordonator {
	string nume;
	int varsta;
	string materie_predata;
public:
	profesor_coordonator(string nume, int varsta, string materie_predata) {
		this->nume = nume;
		this->varsta = varsta;
		this->materie_predata = materie_predata;
	}
	void afisare_profesor() {
		cout << "NUME PROFESOR: " << nume << endl;
		cout << "VARSTA PROFESOR: " << varsta << endl;
		cout << "MATERIA PREDATA: " << materie_predata << endl;
	}
	void afisare_profesor_fisier(ofstream &fout) {
		fout << "NUME PROFESOR: " << nume << endl;
		fout << "VARSTA PROFESOR: " << varsta << endl;
		fout << "MATERIA PREDATA: " << materie_predata << endl;
	}
	string get_nume_profesor() {
		return nume;
	}
};
class student {
private:
	int varsta,varsta_p;
	string nume,nume_p,materie_p;
	float medie;
	list <disciplina *> discipline;
	bool an_terminal;
	profesor_coordonator *p;
public:
	student(string nume,int varsta,list <disciplina*> disp, bool an_terminal,profesor_coordonator *pre) {
		this->nume = nume;
		this->varsta = varsta;
		discipline.assign(disp.begin(), disp.end());
		this->an_terminal = an_terminal;
			for (disciplina *x : discipline)
				medie = medie+ x->get_calificativ();
			medie = medie / discipline.size();
			if (an_terminal == 1) {
				
				medie = medie + varsta / 10;
				p = pre;
			}
	}
	void afisare_student() {
		cout << "NUME: " << nume << endl;
		cout << "VARSTA: " << varsta << endl;
		cout << "STUDENTUL ESTE AN TERMINAL: " << (an_terminal ? "DA" : "NU") << endl;;
		cout << "Materiile studiate de student: " << endl;
		for (disciplina *x : discipline)
			x->afisare_disiciplina();
		cout << "MEDIE: " << medie << endl;
		if (an_terminal == 1) {
			cout << "PROFESORUL COORDONATOR ESTE: " << endl;
			p->afisare_profesor();
		}
	}
	void afisare_student_fisier(ofstream &fout) {
		fout << "NUME: " << nume << endl;
		fout << "VARSTA: " << varsta << endl;
		fout << "STUDENTUL ESTE AN TERMINAL: " << (an_terminal ? "DA" : "NU") << endl;;
		fout << "Materiile studiate de student: " << endl;
		for (disciplina *x : discipline)
			x->afisare_disiciplina_fisier(fout);
		fout << "MEDIE: " << medie << endl;
		if (an_terminal == 1) {
			fout << "PROFESORUL COORDONATOR ESTE: " << endl;
			p->afisare_profesor_fisier(fout);
		}
	}
	int get_varsta() {
		return varsta;
	}
	string returnare_nume_profesor_coordonator() {
		return p->get_nume_profesor();
	}
	bool este_an_terminal() {
		return an_terminal;
	}
	void cautare_disciplina(string nume,float nota) {
		for (disciplina *x : discipline)
			if (x->get_denumire_disciplina() == nume)
			{
				x->modificare_nota(nota);
				medie = 0;
			}
		for (disciplina *x : discipline)
			medie = medie + x->get_calificativ();
		medie = medie / discipline.size();
		if (an_terminal == 1) {

			medie = medie + varsta / 10;
			
		}

	}
	string get_nume_student() {
		return nume;
	}
	float get_medie() {
		return medie;
	}
	student operator ++(int) {
		varsta = varsta + 1;
		return *this;
	}
	
	
	bool operator==(const student s)  {
		return this->medie == s.medie;
	}

};
void citire_globala_fisier(list <student *>& studenti,ifstream &in) {
	int varsta, varsta_p,nr_discipline;
	string nume, nume_p, materie_p;
	float medie;
	list <disciplina *> discipline;
	disciplina *d;
	string denumire;
	float calificativ;
	bool an_terminal;
	student *s;
	profesor_coordonator *p=nullptr;
	while (in >> nume >> varsta) {
		in >> nr_discipline;
		for (int i = 1; i <= nr_discipline; i++)
		{
			in >> denumire >> calificativ;
			d = new disciplina(denumire, calificativ);
			discipline.push_back(d);
		}
		in >> an_terminal;
		if (an_terminal == 1){
			in >> nume_p >> varsta_p >> materie_p;
			p = new profesor_coordonator(nume_p, varsta_p, materie_p);
}
		s = new student(nume, varsta, discipline, an_terminal, p);
		studenti.push_back(s);
		discipline.clear();
}

	  }
void cautare_varsta(int varsta, list <student *>studenti) {
	int k = 0;
 for(student *x: studenti)
	 if (varsta == x->get_varsta()) {
		 x->afisare_student();
		 cout << endl; 
		 k = 1;
	 }
 if (k == 0)
	 cout << "NU EXISTA STUDENTI!!!" << endl;
}
void cautare_profesor_coordonator(string nume,list <student *>studenti) {
	int k = 0;
	for(student *x:studenti )
		if(x->este_an_terminal()==1 && x->returnare_nume_profesor_coordonator()==nume)
		{
			k = 1;
			x->afisare_student();
			cout << endl;
		}
	if (k == 0)
		cout << "NU A FOST GASIT!"<<endl;
}
void schimbare_nota(string nume, string denumire, float nota, list <student *>studenti) {
	for (student *x : studenti)
		if (x->get_nume_student() == nume)
			x->cautare_disciplina(denumire, nota);
}
void modificare_varsta(string nume, list <student *>studenti) {
	for (student *x : studenti)
		if (x->get_nume_student() == nume)
			(*x)++;
}
student * student_medie_maxima(list <student *>studenti) {
	int  maxim = 0;
	student *max=nullptr;
	for (student *x : studenti)
		if (x->get_medie() > maxim){
			maxim = x->get_medie();
			max = x;
		}
	return max;


}
ifstream &operator>>(ifstream &in, list <student *>&studenti) {
	citire_globala_fisier(studenti, in);
	return in;
}
ostream &operator <<(ostream &cout, list <student *>studenti) {
	for (student *x : studenti)
	{
		x->afisare_student();
		cout << endl;
	}
	return cout;
}
ofstream &operator <<(ofstream &fout, list <student *>studenti) {
	for (student *x : studenti) {
		x->afisare_student_fisier(fout);
		fout << endl;
	}
	return fout;
}
int main() {
	list <student * > studenti;
	int opt;
	ifstream in;
	float nota;
	in.open("citire.txt");
	ofstream fout;
	fout.open("scriere.txt");
	int varsta_cautata;
	string nume,denumire;
	student *s, *primul;
	do {
		cout << "1) Inițializare listă studenți din fișier " << endl;
		cout << "2)Afișarea listei de studenți " << endl;
		cout << "3) Căutarea unui student după vârstă " << endl;
		cout << "4)Căutarea unui student an terminal după numele profesorului coordonator. " << endl;
		cout << "5) Modificați nota unui student(identificat după nume) pentru o anumită disciplină dată de la tastatură." << endl;
		cout << "6) Ștergerea unui student după nume " << endl;
		cout << " 7) Sortarea studenților după media finală în ordine descrescătoare" << endl;
		cout << "8)  Modificarea vârstei pentru un student dat de la tastatură, după nume, prin supraîncărcarea operatorului ++ " << endl;
		cout << " 9)  Verificarea dacă primul student din listă este același student cu studentul cu cea mai mare medie finală, prin supraîncărcarea operatorului ==" << endl;
		cout << " 10)  Salvarea listei de studenți în fișier." << endl;
		cout << " Alege o optiune: " << endl;
		cin >> opt;
		switch (opt)
		{
		case 1: in >> studenti;
			break;
		case 2:
			cout << studenti;
			break;
		case 3:
			cout << "INtroduceti varsta pe care doriti s o cautati: ";
			cin >> varsta_cautata;
			cautare_varsta(varsta_cautata, studenti);
			break;
		case 4: 
			cout << "Dati numele profesorului :";
			cin >> nume;
			cautare_profesor_coordonator(nume, studenti);
			break;
		case 5:
			cout << "Nume student: ";
			cin >> nume;
			cout << "Nume materie: ";
			cin >> denumire;
			cout << "Noua nota: ";
			cin >> nota;
			schimbare_nota(nume, denumire, nota, studenti);
			cout << studenti;
			break;
		case 6:
			cout << "Nume student: ";
			cin >> nume;
			studenti.remove_if([nume](student *s) {return s->get_nume_student() == nume; });
			cout << studenti;
			break;
		case 7:
			studenti.sort([](student *stanga, student *dreapta) {return stanga->get_medie() > dreapta->get_medie(); });
			cout << studenti;
			break;
		case 8:
			cout << "Nume student: ";
			cin >> nume;
			modificare_varsta(nume, studenti);
			cout << studenti;
			break;
		case 9:
			s = student_medie_maxima(studenti);
			primul = studenti.front();
			if (*s == *primul)
				cout << "DA"<<endl;
			else cout << "NU"<<endl;
			break;
		case 10:
			fout << studenti;
			break;
		default: cout << "Optiune invalida!";
			break;
		}
	} while (1);
	return 0;
}