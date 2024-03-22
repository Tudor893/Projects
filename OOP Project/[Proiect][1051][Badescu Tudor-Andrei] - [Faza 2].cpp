#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>
#include <cstdlib>
#include <conio.h>
#include <vector>
#include <map>
#include <list>
#include <set>
#include <ctime>
using namespace std;

class StocIngredient {
	string denumire="N/A";
	float cantitateDisponibilaDinStoc = 0;
public:
	StocIngredient(){}
	StocIngredient(string denumire, float cantitateDisponibilaDinStoc) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		if (cantitateDisponibilaDinStoc > 0)
			this->cantitateDisponibilaDinStoc = cantitateDisponibilaDinStoc;
	}
	const string getDenumire() {
		return this->denumire;
	}
	const float getCantitateDisponibilaDinStoc() {
		return this->cantitateDisponibilaDinStoc;
	}
	void setDenumire(const string denumire) {
		if (denumire.length() > 3)
			this->denumire = denumire;
	}
	void setCantitateDisponibilaDinStoc(const float cantitateDisponibilaDinStoc) {
		if (cantitateDisponibilaDinStoc >= 0)
			this->cantitateDisponibilaDinStoc = cantitateDisponibilaDinStoc;
	}
	friend istream& operator>>(istream& in, StocIngredient& ingredient) {
		cout << "Denumire: ";
		getline(in, ingredient.denumire);
		cout << "\nCantitate disponibila din stoc: ";
		in >> ingredient.cantitateDisponibilaDinStoc;
		return in;
	}
	friend ifstream& operator>>(ifstream& in, StocIngredient& ingredient) {
		getline(in, ingredient.denumire);
		in >> ingredient.cantitateDisponibilaDinStoc;
		return in;
	}
	friend ostream& operator <<(ostream& out, const StocIngredient& ingredient) {
		if (ingredient.denumire.length() > 0)
			out << "\nDenumire: " << ingredient.denumire;
		else
			out << "\nDenumire: " << "-";
		if (ingredient.cantitateDisponibilaDinStoc > 0)
			out << "\nCantitate disponibila din stoc: " << ingredient.cantitateDisponibilaDinStoc;
		else
			out << "\nCantitate disponibila din stoc: " << 0;
		
		
		return out;
	}
};
class Ingredient {
	string denumire = "N/A";
	float cantitateNecesara = 0;
	float pret = 0;
public:
	Ingredient() {}
	Ingredient(string denumire, float cantitateNecesara, float pret) {
		if (denumire.length() > 0)
			this->denumire = denumire;
		if (cantitateNecesara > 0  && pret > 0) {
			this->cantitateNecesara = cantitateNecesara;
			this->pret = pret;
		}
	}
	Ingredient(const Ingredient& ingredient) {
		this->denumire = ingredient.denumire;
		this->cantitateNecesara = ingredient.cantitateNecesara;
		this->pret = ingredient.pret;
	}
	Ingredient& operator =(const Ingredient& ingredient) {
		if (this != &ingredient) {

			this->denumire = ingredient.denumire;
			this->cantitateNecesara = ingredient.cantitateNecesara;
			this->pret = ingredient.pret;
		}
		return *this;
	}
	void setDenumire(const string denumire) {
		if (denumire.length() > 3)
			this->denumire = denumire;
	}
	void setCantitateNecesara(const float cantitateNecesara) {
		if (cantitateNecesara > 0)
			this->cantitateNecesara = cantitateNecesara;
	}
	void setPret(const float pret) {
		if (pret > 0)
			this->pret = pret;
	}
	const string getDenumire() {
		return this->denumire;
	}
	const float getCantitateNecesara() {
		return this->cantitateNecesara;
	}
	const float getPret() {
		return this->pret;
	}
	friend istream& operator >>(istream& in, Ingredient& ingredient) {

		cout << "\nIntroduceti denumirea ingredientului: ";
		getline(in, ingredient.denumire);
		//in.ignore();
		cout << "Introduceti cantitatea necesara(kg): ";
		in >> ingredient.cantitateNecesara;
		cout << "Introduceti pretul per 100g: ";
		in >> ingredient.pret;
		in.ignore();
		return in;
	}
	friend ostream& operator <<(ostream& out, const Ingredient& ingredient) {
		if (ingredient.denumire.length() > 0)
			out << "\nDenumire: " << ingredient.denumire;
		else
			out << "\nDenumire: " << "-";

		if (ingredient.cantitateNecesara > 0)
			out << "\nCantitate necesara: " << ingredient.cantitateNecesara;
		else
			out << "\nCantitate necesara: " << 0;

		if (ingredient.pret > 0)
			out << "\nPret: " << ingredient.pret;
		else
			out << "\nPret: invalid";
		return out;
	}
	Ingredient operator +(float cantitateNecesara) {
		if (cantitateNecesara > 0) {
			Ingredient aux = *this;
			aux.cantitateNecesara += cantitateNecesara;
			return aux;
		}
	}
	operator double() {
		return this->pret;
	}
	Ingredient operator ++() {
		this->pret++;
		return *this;
	}
	Ingredient operator ++(int) {
		Ingredient copie(*this);
		this->pret++;
		return copie;
	}
	void modificarePret(float procent) {
		this->pret += this->pret * procent;
	}
};
class Reteta {
	string numeReteta = "N/A";
	int nrIngrediente = 0;
	Ingredient** listaIngrediente = nullptr;
public:
	Reteta() {}
	Reteta(string numeReteta) {
		if (numeReteta.length() > 3)
			this->numeReteta = numeReteta;
	}
	Reteta(string numeReteta, int nrIngrediente, Ingredient** listaIngrediente) {
		if (numeReteta.length() > 3)
			this->numeReteta = numeReteta;
		if (nrIngrediente > 0 && listaIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->listaIngrediente[i] = new Ingredient(*listaIngrediente[i]);
		}
	}
	Reteta(const Reteta& reteta) {
		this->numeReteta = reteta.numeReteta;
		if (reteta.nrIngrediente > 0 && reteta.listaIngrediente != nullptr) {
			this->nrIngrediente = reteta.nrIngrediente;
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->listaIngrediente[i] = new Ingredient(*reteta.listaIngrediente[i]);
		}
	}
	Reteta& operator =(const Reteta& reteta) {
		if (this != &reteta) {
			for (int i = 0;i < this->nrIngrediente;i++) {
				delete this->listaIngrediente[i];
				this->listaIngrediente[i] = nullptr;
			}
			delete[] this->listaIngrediente;
			this->listaIngrediente = nullptr;

			this->numeReteta = reteta.numeReteta;
			if (reteta.nrIngrediente > 0 && reteta.listaIngrediente != nullptr) {
				this->nrIngrediente = reteta.nrIngrediente;
				this->listaIngrediente = new Ingredient * [this->nrIngrediente];
				for (int i = 0;i < this->nrIngrediente;i++)
					this->listaIngrediente[i] = new Ingredient(*reteta.listaIngrediente[i]);
			}
		}
		return *this;
	}
	void setNumeReteta(const string numeReteta) {
		if (numeReteta.length() > 3)
			this->numeReteta = numeReteta;
	}
	void setNrIngrediente(const int nrIngrediente) {
		if (nrIngrediente > 0)
			this->nrIngrediente = nrIngrediente;
	}
	void setListaIngrediente(int nrIngrediente, Ingredient** listaIngrediente) {
		if (nrIngrediente > 0 && listaIngrediente != nullptr) {
			this->nrIngrediente = nrIngrediente;
			this->listaIngrediente = new Ingredient * [this->nrIngrediente];
			for (int i = 0;i < this->nrIngrediente;i++)
				this->listaIngrediente[i] = new Ingredient(*listaIngrediente[i]);
		}
	}
	const string getNumeReteta() {
		return this->numeReteta;
	}
	const int getNrIngrediente() {
		return this->nrIngrediente;
	}
	Ingredient** getListaIngrediente() {
		return this->listaIngrediente;
	}
	friend istream& operator >>(istream& in, Reteta& reteta) {
		for (int i = 0;i < reteta.nrIngrediente;i++) {
			delete  reteta.listaIngrediente[i];
			reteta.listaIngrediente[i] = nullptr;
		}
		delete[] reteta.listaIngrediente;
		reteta.listaIngrediente = nullptr;

		cout << "\nDenumire reteta: ";
		getline(in, reteta.numeReteta);
		cout << "Numar de ingrediente: ";
		in >> reteta.nrIngrediente;
		in.ignore();
		cout << "-----------Lista de ingrediente--------------";
		reteta.listaIngrediente = new Ingredient * [reteta.nrIngrediente];
		for (int i = 0;i < reteta.nrIngrediente;i++) {
			reteta.listaIngrediente[i] = new Ingredient();
			in >> *reteta.listaIngrediente[i];
		}


		return in;
	}
	friend ostream& operator <<(ostream& out, const Reteta& reteta) {
		out << "\nNume reteta: " << reteta.numeReteta;
		out << "\nNumar de ingrediente: " << reteta.nrIngrediente;
		out << "\nLista ingredientelor retetei: ";
		if (reteta.listaIngrediente != nullptr)
			for (int i = 0;i < reteta.nrIngrediente;i++)
				out << *reteta.listaIngrediente[i];
		else
			out << "-";
		return out;
	}
	Ingredient* operator [](int pozitie) {
		if (pozitie >= 0 && pozitie < this->nrIngrediente)
			return this->listaIngrediente[pozitie];
	}
	void adaugaIngredientLaReteta(const Ingredient& ingredient) {
		if (&ingredient != nullptr) {
			Ingredient** listaTemporara = new Ingredient * [this->getNrIngrediente() + 1];
			for (int i = 0; i < this->getNrIngrediente(); i++) {
				listaTemporara[i] = new Ingredient(*this->listaIngrediente[i]);
			}
			listaTemporara[this->getNrIngrediente()] = new Ingredient(ingredient);
			for (int i = 0; i < this->getNrIngrediente(); i++) {
				delete this->listaIngrediente[i];
			}
			delete[] this->listaIngrediente;
			this->listaIngrediente = listaTemporara;
			this->setNrIngrediente(this->getNrIngrediente() + 1);
		}
	}
	void afisareIngredientDinReteta(const string denumire) {
		for (int i = 0;i < this->nrIngrediente;i++)
			if (this->listaIngrediente[i]->getDenumire() == denumire)
				cout << *this->listaIngrediente[i];
	}
	~Reteta() {
		for (int i = 0;i < this->nrIngrediente;i++) {
			delete this->listaIngrediente[i];
			this->listaIngrediente[i] = nullptr;
		}
		delete[] this->listaIngrediente;
		this->listaIngrediente = nullptr;
	}
};
class Preparat{
	float gramaj = 0;
	int calorii = 0;
	bool esteVegan = false;
	Reteta* reteta = nullptr;
public:
	Preparat() {}
	Preparat(bool esteVegan) :esteVegan(esteVegan) {}
	Preparat(float gramaj, int calorii) {
		if (gramaj != 0 && calorii != 0) {
			this->gramaj = gramaj;
			this->calorii = calorii;
		}
	}
	Preparat(float gramaj, int calorii, bool esteVegan, Reteta* reteta) {
		if (gramaj != 0)
			this->gramaj = gramaj;
		if (calorii != 0)
			this->calorii = calorii;
		this->esteVegan = esteVegan;
		if (reteta != nullptr)
			this->reteta = new Reteta(*reteta);
	}
	Preparat(const Preparat& preparat) {
		this->gramaj = preparat.gramaj;
		this->calorii = preparat.calorii;
		this->esteVegan = preparat.esteVegan;
		this->reteta = new Reteta(*preparat.reteta);
	}
	Preparat& operator =(const Preparat& preparat) {
		if (this != &preparat) {
			delete this->reteta;
			this->reteta = nullptr;

			this->gramaj = preparat.gramaj;
			this->calorii = preparat.calorii;
			this->esteVegan = preparat.esteVegan;
			this->reteta = new Reteta(*preparat.reteta);
		}
		return *this;
	}
	void setGramaj(const float gramaj) {
		if (gramaj > 0)
			this->gramaj = gramaj;
	}
	void setCalorii(const int calorii) {
		if (calorii > 100)
			this->calorii = calorii;
	}
	void setEsteVegan(const bool esteVegan) {
		if (esteVegan == true || esteVegan == false)
			this->esteVegan = esteVegan;
	}
	void setReteta(Reteta* reteta) {
		if (reteta != nullptr) {
			this->reteta = new Reteta(*reteta);
		}
	}
	const float getGramaj() {
		return this->gramaj;
	}
	const int getCalorii() {
		return this->calorii;
	}
	const bool getEsteVegan() {
		return this->esteVegan;
	}
	Reteta* getReteta() {
		return this->reteta;
	}
	friend istream& operator >>(istream& in, Preparat& preparat) {

		cout << "\nIntroducere specificatii despre preparatul: " << preparat.afisareNumePreparat();
		cout << "\nGramaj preparat: ";
		in >> preparat.gramaj;
		cout << "\nCalorii preparat: ";
		in >> preparat.calorii;
		cout << "\nEste produsul vegan(1/0): ";
		in >> preparat.esteVegan;
		in.ignore();
		cout << "\nReteta preparatului: ";
		preparat.reteta = new Reteta;
		in >> *preparat.reteta;
		return in;
	}
	friend ostream& operator <<(ostream& out, const Preparat& preparat) {
		out << "Numele preparatului: " << preparat.reteta->getNumeReteta();
		out << "\nGramaj preparat: " << preparat.gramaj;
		out << "\nCalorii preparat: " << preparat.calorii;
		if (preparat.esteVegan != 0)
			out << "\nPreparatul este vegan";
		else
			out << "\nPreparatul nu este vegan";
		out << "\n----------Reteta preparatului------------";
		out << *preparat.reteta;
		return out;
	}
	string afisareNumePreparat() {
		return this->reteta->getNumeReteta();
	}
	void analizaCalorii() {
		if (this->calorii > 650)
			cout << "Acesta este un preparat bogat caloric.";
		else
			cout << "Preparatul se incadreaza in limite calorice normale.";
	}
	bool operator !() {
		return !this->esteVegan;
	}
	~Preparat() {
		delete this->reteta;
		this->reteta = nullptr;
	}
};
class Meniu {
	const float ratingMeniu;
	string limbaMeniu = "N/A";
	int nrPreferinte = 0;
	string* preferinteClienti = nullptr;
	set<string> preferinteAnterioare;
	list<string> angajatiiLunii;
public:
	Meniu(float ratingMeniu) :ratingMeniu(ratingMeniu) {}
	Meniu(float ratingMeniu, set<string> preferintiAnterioare, list<string> angajatiiLunii) : ratingMeniu(ratingMeniu) {
		this->preferinteAnterioare = preferinteAnterioare;
		this->angajatiiLunii = angajatiiLunii;
	}
	Meniu(float ratingMeniu, string limbaMeniu, int nrPreferinte, string* preferinteClienti) :ratingMeniu(ratingMeniu) {
		if (limbaMeniu.length() > 3)
			this->limbaMeniu = limbaMeniu;
		if (nrPreferinte != 0 && preferinteClienti != nullptr) {
			this->nrPreferinte = nrPreferinte;
			this->preferinteClienti = new string[this->nrPreferinte];
			for (int i = 0;i < this->nrPreferinte;i++)
				this->preferinteClienti[i] = preferinteClienti[i];
		}
	}
	Meniu(const Meniu& meniu) :ratingMeniu(meniu.ratingMeniu) {
		this->limbaMeniu = meniu.limbaMeniu;
		this->nrPreferinte = meniu.nrPreferinte;
		this->preferinteClienti = new string[this->nrPreferinte];
		for (int i = 0;i < this->nrPreferinte;i++)
			this->preferinteClienti[i] = meniu.preferinteClienti[i];
	}
	Meniu& operator =(const Meniu& meniu) {
		if (this != &meniu) {
			delete[] this->preferinteClienti;
			this->preferinteClienti = nullptr;

			this->limbaMeniu = meniu.limbaMeniu;
			this->nrPreferinte = meniu.nrPreferinte;
			this->preferinteClienti = new string[this->nrPreferinte];
			for (int i = 0;i < this->nrPreferinte;i++)
				this->preferinteClienti[i] = meniu.preferinteClienti[i];
		}
		return *this;
	}
	void setLimbaMeniu(const string limbaMeniu) {
		if (limbaMeniu.length() > 3)
			this->limbaMeniu = limbaMeniu;
	}
	void setNrPreferinte(const int nrPreferinte) {
		if (nrPreferinte > 0)
			this->nrPreferinte = nrPreferinte;
	}
	void setPreferinteClienti(int nrPreferinte, string* preferinteClienti) {
		if (nrPreferinte > 0 && preferinteClienti != nullptr)
		{
			this->nrPreferinte = nrPreferinte;
			this->preferinteClienti = new string[this->nrPreferinte];
			for (int i = 0;i < this->nrPreferinte;i++)
				this->preferinteClienti[i] = preferinteClienti[i];
		}
	}
	const float getRatingMeniu() {
		return this->ratingMeniu;
	}
	const string getLimbaMeniu() {
		return this->limbaMeniu;
	}
	const int getNrPreferinte() {
		return this->nrPreferinte;
	}
	const string* getPreferinteClienti() {
		return this->preferinteClienti;
	}
	friend istream& operator >>(istream& in, Meniu& meniu) {
		delete[] meniu.preferinteClienti;
		meniu.preferinteClienti = nullptr;
		in.ignore();
		cout << "Setati limba in care a fost realizat meniul: ";
		getline(in, meniu.limbaMeniu);
		cout << "Setati numarul de preparate preferate de clienti: ";
		in >> meniu.nrPreferinte;
		cout << "Preferintele clientilor: ";
		meniu.preferinteClienti = new string[meniu.nrPreferinte];
		in.ignore();
		for (int i = 0;i < meniu.nrPreferinte;i++) {
			cout << "\nPreferinta " << i + 1 << " este ";
			getline(in, meniu.preferinteClienti[i]);
		}
		return in;
	}
	friend ostream& operator <<(ostream& out, const Meniu& meniu) {
		out << "Rating-ul meniului este de " << meniu.ratingMeniu << " stele";
		out << "\nMeniul a fost realizat in limba " << meniu.limbaMeniu;
		//out << "\nNumarul de preparate preferate ale clientilor: " << meniu.nrPreferinte;
		out << "\nPreferintele clientilor: ";
		for (int i = 0;i < meniu.nrPreferinte;i++)
			out << "'" << meniu.preferinteClienti[i] << "' ";
		out << endl;
		return out;
	}
	bool operator ==(const Meniu& meniu) {
		if (this->ratingMeniu != meniu.ratingMeniu
			|| this->limbaMeniu != meniu.limbaMeniu
			|| this->nrPreferinte != meniu.nrPreferinte)
			return false;
		for (int i = 0;i < this->nrPreferinte;i++)
			if (this->preferinteClienti[i] != meniu.preferinteClienti[i])
				return false;
		return true;
	}
	friend bool operator >=(float rating, const Meniu& meniu) {
		return rating >= meniu.ratingMeniu;
	}
	void afisareTipMeniu() {
		if (this->ratingMeniu > 4.6)
			cout << "\nMeniul este foarte apreciat";
	}
	void sortarePreferinte() {
		string aux;
		for (int i = 0;i < this->nrPreferinte - 1;i++)
			for (int j = i + 1;j < this->nrPreferinte;j++)
				if (this->preferinteClienti[i][0] > this->preferinteClienti[j][0]) {
					aux = this->preferinteClienti[i];
					this->preferinteClienti[i] = this->preferinteClienti[j];
					this->preferinteClienti[j] = aux;
				}
		for (int i = 0;i < this->nrPreferinte;i++)
			cout << this->preferinteClienti[i] << " ";
	}
	~Meniu() {
		delete[] this->preferinteClienti;
		this->preferinteClienti = nullptr;
	}
};
class ComandaClient {
	const int idComanda;
	static float TVA;
	float cuponReducere = 0;
	Meniu* meniu = nullptr;
	Reteta* generareListaRetete = nullptr;
	StocIngredient* generareStocIngrediente = nullptr;
	vector<vector<string>> feedbackClienti;
	int nrPreparateComandate = 0;
	string* listaPreparateComandate = nullptr;
	static vector<int> alegeriUtilizatori;
	static int greseliUtilizator;
	static time_t sfarsit;
public:
	ComandaClient(int idComanda, Reteta* generareListaRetete, StocIngredient* generareStocIngrediente, vector<vector<string>> feedbackClienti) :idComanda(idComanda) {
		this->generareListaRetete = new Reteta[6];
		for (int i = 0; i < 6; i++)
			this->generareListaRetete[i] = generareListaRetete[i];
		this->generareStocIngrediente = new StocIngredient[16];
		for (int i = 0; i < 16; i++)
			this->generareStocIngrediente[i] = generareStocIngrediente[i];
		this->feedbackClienti = feedbackClienti;
	}
	ComandaClient(int idComanda, float cuponReducere) :idComanda(idComanda) {
		if (cuponReducere != 0)
			this->cuponReducere = cuponReducere;
	}
	ComandaClient(int idComanda, Meniu* meniu, int nrPreparateComandate, string* listaPreparateComandate) :idComanda(idComanda) {
		if (meniu != nullptr)
			this->meniu = new Meniu(*meniu);
		if (nrPreparateComandate > 0 && listaPreparateComandate != nullptr) {
			this->nrPreparateComandate = nrPreparateComandate;
			this->listaPreparateComandate = new string[this->nrPreparateComandate];
			for (int i = 0;i < this->nrPreparateComandate;i++)
				this->listaPreparateComandate[i] = listaPreparateComandate[i];
		}

	}
	ComandaClient(const ComandaClient& comanda) :idComanda(comanda.idComanda) {
		this->cuponReducere = comanda.cuponReducere;
		this->meniu = new Meniu(*comanda.meniu);
		if (comanda.nrPreparateComandate != 0 && comanda.listaPreparateComandate != nullptr) {
			this->nrPreparateComandate = comanda.nrPreparateComandate;
			this->listaPreparateComandate = new string[this->nrPreparateComandate];
			for (int i = 0;i < this->nrPreparateComandate;i++)
				this->listaPreparateComandate[i] = comanda.listaPreparateComandate[i];
		}
	}
	ComandaClient& operator =(const ComandaClient& comanda) {
		if (this != &comanda) {
			delete[] this->listaPreparateComandate;
			this->listaPreparateComandate = nullptr;

			this->cuponReducere = comanda.cuponReducere;
			this->meniu = new Meniu(*comanda.meniu);
			if (comanda.nrPreparateComandate != 0 && comanda.listaPreparateComandate != nullptr) {
				this->nrPreparateComandate = comanda.nrPreparateComandate;
				this->listaPreparateComandate = new string[this->nrPreparateComandate];
				for (int i = 0;i < this->nrPreparateComandate;i++)
					this->listaPreparateComandate[i] = comanda.listaPreparateComandate[i];
			}
		}return *this;
	}
	const int getIdComanda() {
		return this->idComanda;
	}
	static float getTVA() {
		return ComandaClient::TVA;
	}
	static vector<int> getAlegeriUtilizator() {
		return ComandaClient::alegeriUtilizatori;
	}
	static int getGreseliUtilizator() {
		return ComandaClient::greseliUtilizator;
	}
	static time_t getTimpSfarsit() {
		return ComandaClient::sfarsit;
	}
	const float getCuponReducere() {
		return this->cuponReducere;
	}
	const Meniu* getMeniu() {
		return this->meniu;
	}
	const int getNrPreparateComandate() {
		return nrPreparateComandate;
	}
	const string* getListaPreparateComandate() {
		return listaPreparateComandate;
	}
	void setCuponReducere(const float cuponReducere) {
		if (cuponReducere > 0)
			this->cuponReducere = cuponReducere;
	}
	static void setTVA(float TVA) {
		if (TVA > 0)
			ComandaClient::TVA = TVA;
	}
	void setMeniu(Meniu* meniu) {
		if (meniu != nullptr)
			this->meniu = meniu;
	}
	void setNrPreparateComandate(const int nrPreparateComandate) {
		if (nrPreparateComandate > 0)
			this->nrPreparateComandate = nrPreparateComandate;
	}
	void setListaPreparateComandate(string* listaPreparateComandate, int nrPreparateComandate) {
		if (listaPreparateComandate != nullptr && nrPreparateComandate > 0) {
			this->nrPreparateComandate = nrPreparateComandate;
			this->listaPreparateComandate = new string[this->nrPreparateComandate];
			for (int i = 0;i < this->nrPreparateComandate;i++)
				this->listaPreparateComandate[i] = listaPreparateComandate[i];
		}
	}
	friend istream& operator >>(istream& in, ComandaClient& comanda) {
		cout << "\n------------------------------Legenda-------------------------------";
		cout << "\nPentru a afisa meniul scrieti 'meniu' sau 'Meniu'\nPentru a introduce comanda scrieti 'cmd' sau 'Cmd'\nPentru a afisa caracteristicile meniului scrieti 'caracteristici' sau 'Caracteristici'\nPentru a reveni la legenda scrieti 'back' sau 'Back'\nPentru a vizualiza feedback-ul clientilor scrieti 'feedback' sau 'Feedback'";
		cout << "\nIntroduceti ce doriti: ";
		string input;
		in >> input;
		in.ignore();
		if (input == "meniu" || input == "Meniu") {
			comanda.alegeriUtilizatori[0]++;
			system("cls"); //clear screen 
			Reteta* listaRetete = new Reteta[6];
			listaRetete = comanda.generareListaRetete;
			comanda.afisareMeniu(listaRetete);
			in >> comanda;
			return in;
		}
		else
			if (input == "cmd" || input == "Cmd") {
				comanda.alegeriUtilizatori[1]++;
				system("cls"); //clear screen 
				Reteta* listaRetete = new Reteta[6];
				listaRetete = comanda.generareListaRetete;
				comanda.afisareMeniu(listaRetete);

				cout << "\n\nIntroduceti comanda (ex: ''2 Pizza, 3 Paste Carbonara''): ";
				int cantitate = 0;
				char* sir;
				char buffer[250];
				comanda.listaPreparateComandate = new string[100];
				int pozitie = 0;
				int check = 1;
				string* aux = nullptr;
				in.getline(buffer, 250);
				sir = new char[strlen(buffer) + 1];
				strcpy(sir, buffer);
				char* pch;
				pch = strtok(sir, ",");
				while (pch != NULL) {
					char sirNumere[5];
					int j = 0;
					int p = 0;
					for (int i = 0;i < strlen(pch);i++)
						if (j > 3)
						{
							break;
						}
						else
							if (pch[i] >= '0' && pch[i] <= '9')
							{
								sirNumere[j] = pch[i];
								j++;
							}
							else
								if (pch[i] == ' ' && pch[i - 1] >= '0' && pch[i - 1] <= '9' && pch[i + 1] >= '0' && pch[i + 1] <= '9')
									check = 0;
								else
									if (pch[i] == ' ' && (pch[i - 1] >= '0' && pch[i - 1] <= '9' || pch[i + 1] >= '0' && pch[i + 1] <= '9'))
										p++;

					sirNumere[j] = '\0';
					int numarPreparate = atoi(sirNumere);
					if (numarPreparate == 0 || sirNumere[0] == '\0' || numarPreparate > 50 || check == 0)
					{
						cout << "Comanda a fost introdusa gresit.\nApasati orice tasta pentru a reveni la introducerea comenzii:";
						comanda.greseliUtilizator++;
						(void)_getch(); //ignora return value
						system("cls"); //clear screen 
						Reteta* listaRetete = new Reteta[6];
						listaRetete = comanda.generareListaRetete;
						comanda.afisareMeniu(listaRetete);
						in >> comanda;
						return in;
					}
					//cout << "\nNR PREPARATE: "<<numarPreparate;
					char sirPreparat[20];
					int k = 0;
					if (strlen(pch) - j - p > 20 || pch[p + j - 1] != ' ')
					{
						cout << "Comanda a fost introdusa gresit.\nApasati orice tasta pentru a reveni la introducerea comenzii:";
						comanda.greseliUtilizator++;
						(void)_getch(); //ignora return value
						system("cls"); //clear screen 
						Reteta* listaRetete = new Reteta[6];
						listaRetete = comanda.generareListaRetete;
						comanda.afisareMeniu(listaRetete);
						in >> comanda;
						return in;
					}
					for (int i = j + p;i < strlen(pch);i++)
					{
						sirPreparat[k] = pch[i];
						k++;
					}

					sirPreparat[k] = '\0';
					//cout << endl << sirPreparate;
					aux = new string[numarPreparate];
					for (int i = 0;i < numarPreparate;i++)
						aux[i] = sirPreparat;
					int n = 0;
					for (int i = pozitie;i < numarPreparate + pozitie;i++) {
						comanda.listaPreparateComandate[i] = aux[n];
						n++;
					}
					pozitie += numarPreparate;
					pch = strtok(NULL, ",");
				}
				aux = new string[pozitie];
				aux = comanda.listaPreparateComandate;
				comanda.listaPreparateComandate = aux;
				comanda.nrPreparateComandate = pozitie;

			}
			else
				if (input == "Caracteristici" || input == "caracteristici")
				{
					comanda.alegeriUtilizatori[2]++;
					system("cls"); //clear screen 
					cout << "\nSpecificatiile meniului sunt:" << endl;
					cout << *comanda.meniu;
					cout << "\nApasati orice tasta pentru a reveni la inceput: ";
					(void)_getch(); //ignora return value
					system("cls"); //clear screen 
					in >> comanda;
					return in;
				}
				else
				{
					system("cls"); //clear screen 
					if (input == "back" || input == "Back") {
						comanda.alegeriUtilizatori[3]++;
						cout << "Ati ales sa reveniti la inceput. Reintroduceti din nou, tinand cont de legenda prezentata." << endl;
					}
					else
						if (input == "feedback" || input == "Feedback") {
							comanda.alegeriUtilizatori[4]++;
							system("cls");
							for (int i = 0;i < comanda.feedbackClienti.size();i++) {
								cout << endl;
								for (int j = 0;j < comanda.feedbackClienti[i].size();j++)
									cout << comanda.feedbackClienti[i][j] << endl;
							}
							in >> comanda;
							return in;
						}
						else
						cout << "Ati introdus gresit. Reintroduceti din nou, tinand cont de legenda prezentata." << endl;
					in >> comanda;
					return in;
				}
				comanda.sfarsit = time(0);
		cout << comanda;
		return in;
	}
	friend ostream& operator <<(ostream& out, ComandaClient& comanda) {
		string optiune;
		Reteta* listaRetete = new Reteta[6];
		listaRetete = comanda.generareListaRetete;
		StocIngredient* ingredient = new StocIngredient[16];
		ingredient = comanda.generareStocIngrediente;
		int nrCelMaiComandatPreparat = 0;
		float costPreparatScumpCarePredomina=0;
		string numePreparatScumpCarePredomina;
		vector<string> numeCeleMaiComandatePreparate;
		map<string, int> celMaiFolositTopping;
		for (int i = 0;i < 16;i++)
			celMaiFolositTopping[ingredient[i].getDenumire()] = 0;
		int numarRetete = 6;
		int inc = 0;
		if (comanda.nrPreparateComandate > 0) {
			int i = 0;
			while (i < comanda.nrPreparateComandate) {
				for (int j = 0;j < numarRetete; j++)
					if (comanda.listaPreparateComandate[i] == listaRetete[j].getNumeReteta())
						inc++;
				i++;
			}
			if (inc != comanda.nrPreparateComandate)
			{
				out << "Comanda a fost introdusa gresit.\nApasati orice tasta pentru a reveni la introducerea comenzii: ";
				comanda.greseliUtilizator++;
				(void)_getch(); //ignora return value
				system("cls"); //clear screen 
				//comanda.afisareMeniu(listaRetete);
				cin >> comanda;
				return out;
			}
		}
		int l = 0;
		int ct = 0;
		if (comanda.nrPreparateComandate > 0)
		{
			int i = 0;
			while (i < comanda.nrPreparateComandate)
			{
				int k = i;
				while (i + 1 < comanda.nrPreparateComandate && comanda.listaPreparateComandate[i] == comanda.listaPreparateComandate[i + 1])
					i++;
				float suma = 0;
				float marjaProfit = 0.4f;
				int nr = i - k + 1;
				for (int j = 0;j < numarRetete; j++)
					if (comanda.listaPreparateComandate[i] == listaRetete[j].getNumeReteta())
						for (int k = 0;k < listaRetete[j].getNrIngrediente();k++)
							for (int f = 0;f < 16;f++)
								if (ingredient[f].getDenumire() == listaRetete[j].getListaIngrediente()[k]->getDenumire())
									if (nr * listaRetete[j].getListaIngrediente()[k]->getCantitateNecesara() <= ingredient[f].getCantitateDisponibilaDinStoc())
									{
										suma += (listaRetete[j].getListaIngrediente()[k]->getCantitateNecesara() / 0.1f * listaRetete[j].getListaIngrediente()[k]->getPret());
										for (int i = 0;i < 16;i++)
											if (listaRetete[j].getListaIngrediente()[k]->getDenumire() == ingredient[i].getDenumire())
											{
												ingredient[i].setCantitateDisponibilaDinStoc(ingredient[i].getCantitateDisponibilaDinStoc() - nr * listaRetete[j].getListaIngrediente()[k]->getCantitateNecesara());
												celMaiFolositTopping[ingredient[i].getDenumire()]+=1*nr;
												break;
											}
									}
									else
									{
										out << "\nPreparatul " << listaRetete[j].getNumeReteta() << " nu poate fi realizat deoarece stocul ingredientului " << listaRetete[j].getListaIngrediente()[k]->getDenumire() << " nu poate face fata comenzii";
										out << "\nApasati orice tasta pentru a reveni la introducerea comenzii: ";
										(void)_getch(); //ignora return value
										system("cls"); //clear screen 
										comanda.afisareMeniu(listaRetete);
										cin >> comanda;
										return out;
									}

				if (l == 0) {
					out << "\nID comanda: " << comanda.idComanda;
					out << "\nAti comandat: ";
					l++;
				}
				suma = nr * suma;
				if (nr > nrCelMaiComandatPreparat)
				{
					numeCeleMaiComandatePreparate.clear();
					nrCelMaiComandatPreparat = nr;
					numeCeleMaiComandatePreparate.push_back(comanda.listaPreparateComandate[i]);
				}
				else
					if (nr == nrCelMaiComandatPreparat)
					{
						numeCeleMaiComandatePreparate.push_back(comanda.listaPreparateComandate[i]);
					}
				out << endl << nr << " X " << comanda.listaPreparateComandate[i] << "  " << fixed << setprecision(2) << (suma * marjaProfit + suma) * (1 + ComandaClient::TVA);
				if (costPreparatScumpCarePredomina < (suma * marjaProfit + suma) * (1 + ComandaClient::TVA))
				{
					costPreparatScumpCarePredomina = (suma * marjaProfit + suma) * (1 + ComandaClient::TVA);
					numePreparatScumpCarePredomina = comanda.listaPreparateComandate[i];
				}
				i++;
			}
		}
		float marjaProfit = 0.4f;
		if (comanda.nrPreparateComandate != 0) {
			if (comanda.cuponReducere > 0)
				out << "\nCupon de reducere: " << comanda.cuponReducere;
			else
				out << "\nCupon de reducere: - ";
			out << "\nTotal de plata: " << fixed << setprecision(2) << comanda.calculSumaDePlatit(listaRetete, marjaProfit);
			if (comanda.cuponReducere > 0)
				out << "\nTotal de plata dupa aplicarea reducerii: " << fixed << setprecision(2) << comanda.calculSumaDePlatit(listaRetete, marjaProfit) - comanda.calculSumaDePlatit(listaRetete, marjaProfit) * comanda.cuponReducere;
			out << "\nComanda a fost inregistrata cu succes!";
		}

		ofstream g("RaportStocRamas.txt");
		time_t oraExacta = time(0);
		char* dt = ctime(&oraExacta);
		g << dt;
		map<string, float> mapIngredient;
		for (int i = 0;i < 16;i++)
			mapIngredient[ingredient[i].getDenumire()] = ingredient[i].getCantitateDisponibilaDinStoc();
		map<string, float>::iterator itMap;
		for (itMap = mapIngredient.begin();itMap != mapIngredient.end();itMap++)
		{
			g << itMap->first << "-" << itMap->second << " kg" << endl;
		}

		ofstream g1("RaportCelMaiComandatPreparat.txt");
		g1 << "Comanda a fost:";
		for (int i = 0;i < comanda.nrPreparateComandate;i++)
			if (comanda.listaPreparateComandate[i] != comanda.listaPreparateComandate[i + 1])
				g1 << endl << "-" << comanda.listaPreparateComandate[i];
		if (numeCeleMaiComandatePreparate.size() == 1)
			g1 << "\nCel mai comandat preparat a fost " << numeCeleMaiComandatePreparate[0] << " in numar de " << nrCelMaiComandatPreparat << " unitati.";
		else{
			g1 << "\nCele mai comandate preparate au fost in numar de " << nrCelMaiComandatPreparat << " unitati si se regasesc in lista urmatoare:";
			for (int i = 0;i < numeCeleMaiComandatePreparate.size();i++)
				g1 << endl << numeCeleMaiComandatePreparate[i];

		}

		ofstream g2("RaportPreparatPredominantScump.txt");
		g2 << "Comanda a fost:";
		for (int i = 0;i < comanda.nrPreparateComandate;i++)
			if (comanda.listaPreparateComandate[i] != comanda.listaPreparateComandate[i + 1])
				g2 << endl << "-" << comanda.listaPreparateComandate[i];
		g2 << "\nAvand pretul cel mai mare, preparatul " << numePreparatScumpCarePredomina << " predomina in proportie de " << fixed << setprecision(2) << ((costPreparatScumpCarePredomina - costPreparatScumpCarePredomina * comanda.cuponReducere) / (comanda.calculSumaDePlatit(listaRetete, marjaProfit) - comanda.calculSumaDePlatit(listaRetete, marjaProfit) * comanda.cuponReducere)) * 100 << "% din totalul dumneavoastra de plata.";
		
		ofstream g3("RaportCeleMaiFolositeIngrediente.txt");
		g3 << "Comanda a fost:";
		for(int i=0;i<comanda.nrPreparateComandate;i++)
			if(comanda.listaPreparateComandate[i]!=comanda.listaPreparateComandate[i+1])
				g3 << endl << "-"<<comanda.listaPreparateComandate[i];
		map<string, int>::iterator iterMap;
		int max = 0;
		for (iterMap = celMaiFolositTopping.begin();iterMap != celMaiFolositTopping.end();iterMap++)
			if (iterMap->second > 0 && iterMap->second > max && iterMap->first != "Faina" && iterMap->first != "Sos de rosii" && iterMap->first != "Ulei de masline")
				max = iterMap->second;
		g3 << "\nCele mai folosite ingrediente sunt in numar de " << max << " si se gasesc in lista urmatoare:";
		for (iterMap = celMaiFolositTopping.begin();iterMap != celMaiFolositTopping.end();iterMap++)
			if (iterMap->second == max && iterMap->first != "Faina" && iterMap->first != "Sos de rosii" && iterMap->first != "Ulei de masline")
				g3 << endl << iterMap->first;

		int iesi=0;
		out << "\nPuteti vizualiza cele 3 rapoarte create. Scrieti 'Raport (indexul dorit)' pentru a vedea un raport sau 'Exit' pentru a iesi";
		out << "\nExemplu: 'Raport 1'";
		while (iesi == 0) {
			out << endl << "Introduceti optiunea dorita: ";
			getline(cin, optiune);
			if (optiune == "Raport 1")
			{
				comanda.alegeriUtilizatori[5]++;
				out << dt;
				for (itMap = mapIngredient.begin();itMap != mapIngredient.end();itMap++)
					out << itMap->first << "-" << itMap->second << " kg" << endl;
			}
			else
				if (optiune == "Raport 2")
				{
					comanda.alegeriUtilizatori[5]++;
					if (numeCeleMaiComandatePreparate.size() == 1)
						out << "Cel mai comandat preparat a fost " << numeCeleMaiComandatePreparate[0] << " in numar de " << nrCelMaiComandatPreparat << " unitati.";
					else
					{
						out << "Cele mai comandate preparate au fost in numar de " << nrCelMaiComandatPreparat << " unitati si se regasesc in lista urmatoare:";
						for (int i = 0;i < numeCeleMaiComandatePreparate.size();i++)
							out << endl << numeCeleMaiComandatePreparate[i];
					}
					out << endl;
				}
				else
					if (optiune == "Raport 3") {
						comanda.alegeriUtilizatori[5]++;
						out << "Avand pretul cel mai mare, preparatul " << numePreparatScumpCarePredomina << " predomina in proportie de " << fixed << setprecision(2) << ((costPreparatScumpCarePredomina - costPreparatScumpCarePredomina * comanda.cuponReducere) / (comanda.calculSumaDePlatit(listaRetete, marjaProfit) - comanda.calculSumaDePlatit(listaRetete, marjaProfit) * comanda.cuponReducere)) * 100 << "% din totalul dumneavoastra de plata.";
						out << endl;
					}
					else
						if (optiune == "Raport 4"){
							comanda.alegeriUtilizatori[5]++;
							out << "Cele mai folosite ingrediente sunt in numar de " << max << " si se gasesc in lista urmatoare:";
							for (iterMap = celMaiFolositTopping.begin();iterMap != celMaiFolositTopping.end();iterMap++)
								if (iterMap->second == max && iterMap->first != "Faina" && iterMap->first != "Sos de rosii" && iterMap->first != "Ulei de masline")
									out << endl << iterMap->first;
							out << endl;
						}
						else
						if (optiune == "Exit") {
							iesi++;
						}
						else
							out << "Ati introdus gresit. Introduceti din nou tinand cont de legenda precizata.";
		}
		return out;
	}
	float calculSumaDePlatit(Reteta reteta[], float marjaProfit) {
		float suma = 0;
		for (int i = 0;i < this->nrPreparateComandate;i++)
			for (int j = 0;j < 6; j++)
				if (this->listaPreparateComandate[i] == reteta[j].getNumeReteta())
					for (int k = 0; k < reteta[j].getNrIngrediente(); k++)
						suma += (reteta[j].getListaIngrediente()[k]->getCantitateNecesara() / 0.1f * reteta[j].getListaIngrediente()[k]->getPret());

		return (suma * marjaProfit + suma) * (1 + ComandaClient::TVA);
	}
	void afisareMeniu(Reteta reteta[]) {
		float suma = 0;
		float marjaProfit = 0.4f;
		float* vectorPreturi = new float[6];
		for (int j = 0;j < 6;j++) {
			suma = 0;
			for (int k = 0;k < reteta[j].getNrIngrediente();k++)
				suma += (reteta[j].getListaIngrediente()[k]->getCantitateNecesara() / 0.1f * reteta[j].getListaIngrediente()[k]->getPret());

			vectorPreturi[j] = (suma * marjaProfit + suma) * (1 + ComandaClient::TVA);
		}

		cout << "======================== Meniu Restaurant ==========================\n";
		cout << "\n   Pizza";		         cout<<"                Pret";
		cout << endl << reteta[0].getNumeReteta() << "          " << fixed << setprecision(2) << vectorPreturi[0] << " lei";	       
		cout << endl << reteta[1].getNumeReteta() << "       " << fixed << setprecision(2) << vectorPreturi[1] << " lei";			 
		cout << endl << reteta[2].getNumeReteta() << "           " << fixed << setprecision(2) << vectorPreturi[2] << " lei";
		cout << endl << reteta[3].getNumeReteta() << "     " << fixed << setprecision(2) << vectorPreturi[3] << " lei";
		cout << endl << reteta[4].getNumeReteta() << "        " << fixed << setprecision(2) << vectorPreturi[4] << " lei";
		cout << endl << reteta[5].getNumeReteta() << "        " << fixed << setprecision(2) << vectorPreturi[5] << " lei";
		
		delete[] vectorPreturi;
	}
	~ComandaClient() {
		delete[] this->listaPreparateComandate;
		this->listaPreparateComandate = nullptr;
	}
};
float ComandaClient::TVA = 0.19f;
vector<int> ComandaClient::alegeriUtilizatori(6, 0);
int ComandaClient::greseliUtilizator = 0;
time_t ComandaClient::sfarsit = 0;

class IFile {
public:
	virtual void citireDinFisier(fstream& fisier) = 0;
	virtual void scriereInFisier(fstream& fisier) = 0;
};

class Locuinta {
	string adresa = "N/A";
	int codPostal = 0;
public:
	Locuinta() {}
	Locuinta(string adresa, int codPostal):adresa(adresa), codPostal(codPostal) {}
	friend ostream& operator <<(ostream& out, const Locuinta locuinta) {
		out << "Adresa este: " << locuinta.adresa;
		out << "\nCodul postal: " << locuinta.codPostal;
		return out;
	}
};

class Angajat :public IFile {
	string nume = "N/A";
	float salariu = 0;
	Locuinta* locuinta = nullptr;
public:
	Angajat(){}
	Angajat(string nume, float salariu, Locuinta* locuinta) {
		this->nume = nume;
		this->salariu = salariu;
		this->locuinta = new Locuinta(*locuinta);
	}
	void scriereInFisier(fstream& fisier) {
		int lg;
		lg = this->nume.length() + 1;
		fisier.write((char*)&lg, sizeof(int));
		fisier.write(this->nume.data(), lg);
		fisier.write((char*)&this->salariu, sizeof(float));
		fisier.write((char*)&locuinta, sizeof(Locuinta));
	}
	void citireDinFisier(fstream& fisier) {
		int lg = 0;
		fisier.read((char*)&lg, sizeof(int));
		char* buffer = new char[lg];
		fisier.read(buffer, lg);
		this->nume = buffer;
		delete[] buffer;
		fisier.read((char*)&this->salariu, sizeof(float));
		fisier.read((char*)&this->locuinta, sizeof(Locuinta));
	}
	friend ostream& operator <<(ostream& out, const Angajat angajat) {
		out << "\nNumele angajatului: " << angajat.nume;
		out << "\nSalariul angajatului: " << angajat.salariu;
		out << endl <<*angajat.locuinta;
		return out;
	}
};

int main() {
	ifstream f("StocDisponibil.txt");
	int i = 0;
	string denumire;
	int nrLinii = 0;
	float cantitateDisponibilaStoc = 0;
	while (getline(f, denumire)) { nrLinii++; }
	f.close();
	ifstream f1("StocDisponibil.txt");
	StocIngredient* stocIngredient = new StocIngredient[nrLinii/2];
	while (getline(f1, denumire) && f1 >> cantitateDisponibilaStoc && i!=nrLinii/2) {
		f1.ignore();
		stocIngredient[i] = StocIngredient(denumire, cantitateDisponibilaStoc);
		i++;
	}
	f1.close();

	ifstream f2("ListaRetete.txt");
	Reteta* listaRetete = new Reteta[6];
	string numeReteta;
	int nrIngrediente = 0;
	float cantitateNecesara = 0;
	float pret = 0;
	i = 0;
	while (i!=6) {
		getline(f2, numeReteta);
		f2 >> nrIngrediente;
		f2.ignore();
		Ingredient** ingredienteReteta = new Ingredient * [nrIngrediente];
		for (int k = 0; k < nrIngrediente; k++) {
			getline(f2, denumire);
			f2 >> cantitateNecesara;
			f2 >> pret;
			for (int j = 0;j < nrLinii / 2;j++)
				if (stocIngredient[j].getDenumire() == denumire)
				{
					ingredienteReteta[k] = new Ingredient(denumire, cantitateNecesara,  pret);
					break;
				}
			f2.ignore();
		}

		listaRetete[i] = Reteta(numeReteta, nrIngrediente, ingredienteReteta);
		i++;
		for (int k = 0; k < nrIngrediente; k++) 
			delete ingredienteReteta[k];
		delete[] ingredienteReteta;
	}
	f2.close();

	string salvareDate;
	int check = 0;
	while (check == 0) {
		cout << "Doriti sa salvati datele aplicatiei in fisiere binare?(Da/da sau Nu/nu): ";
		cin >> salvareDate;
		if (salvareDate == "Da" || salvareDate == "da") {
			fstream file("RetinereDateStocDisponibil.bin", ios::out | ios::binary);
			file.write((char*)stocIngredient, sizeof(StocIngredient) * (nrLinii / 2));
			file.close();
			/*file.open("RetinereDateStocDisponibil.bin", ios::in | ios::binary);
			StocIngredient* stocIngredient1 = new StocIngredient[nrLinii / 2];
			file.read((char*)stocIngredient1, sizeof(StocIngredient) * (nrLinii / 2));
			for (int i = 0;i < nrLinii / 2;i++)
				cout << stocIngredient1[i] << " ";*/

			fstream file1("RetinereListeRetete.bin", ios::out | ios::binary);
			file1.write((char*)listaRetete, sizeof(Reteta) * 6);
			file1.close();
			/*file1.open("RetinereListeRetete.bin", ios::in | ios::binary);
			Reteta* listaRetete1 = new Reteta[6];
			file1.read((char*)listaRetete1, sizeof(Reteta) * 6);
			for (int i = 0;i < 6;i++)
				cout << listaRetete1[i] << " ";*/
			check = 1;
		}
		else
			if (salvareDate == "Nu" || salvareDate == "nu")
				check = 1;
	}

	ifstream csv("FeedbackClienti.csv");
	vector<vector<string>> feedbackClienti;
	string linie;
	while (getline(csv, linie)) {
		size_t pos = 0;
		string valoare;
		vector<string> subsir;
		while ((pos = linie.find(',')) < linie.length()) {
			valoare = linie.substr(0, pos);
			subsir.push_back(valoare);
			linie.erase(0, pos + 1);
		}
		subsir.push_back(linie);
		feedbackClienti.push_back(subsir);
	}


	ComandaClient comanda1(1, listaRetete, stocIngredient, feedbackClienti);
	/*Locuinta locuinta("Strada Victoriei",100200);
	Angajat angajat("Popescu Laur", 4500, &locuinta);*/

	Angajat angajat1 = Angajat("Popescu Laur", 4500, new Locuinta("Strada Victoriei", 100200));
	Angajat angajat2 = Angajat("Tara Laura", 5000, new Locuinta("Strada Lacatului", 100234));
	

	fstream fisierScriere("Angajati.bin", ios::out | ios::binary);
	angajat1.scriereInFisier(fisierScriere);
	angajat2.scriereInFisier(fisierScriere);
	fisierScriere.close();

	fstream fisierCitire("Angajati.bin", ios::in | ios::binary);
	
	angajat1.citireDinFisier(fisierCitire);
	angajat2.citireDinFisier(fisierCitire);
	cout << angajat1;
	cout << angajat2;
	fisierCitire.close();
	cout << endl;
	
	ifstream f3("Preferinte.csv");
	string preferinte[] = {"Pizza Taraneasca","Pizza Casei"};
	Meniu meniu(4.8f, "romana", 2, preferinte);
	comanda1.setMeniu(&meniu);
	comanda1.setCuponReducere(0.1f);
	time_t start = time(0);
	cin >> comanda1;

	ofstream dataMining1("RaportAlegeriUtilizator.txt");
	dataMining1 << "-Raport Alegeri Utilizator-";
	dataMining1 << "\nUtilizatorul a ales sa vizualizeze meniul de " << comanda1.getAlegeriUtilizator()[0] << " ori.";
	dataMining1 << "\nUtilizatorul a ales sa introduca comanda de " << comanda1.getAlegeriUtilizator()[1] << " ori.";
	dataMining1 << "\nUtilizatorul a ales sa vizualizeze caracteristicile de " << comanda1.getAlegeriUtilizator()[2] << " ori.";
	dataMining1 << "\nUtilizatorul a ales comanda back de " << comanda1.getAlegeriUtilizator()[3] << " ori.";
	dataMining1 << "\nUtilizatorul a ales sa vizualizeze feedback-ul altor clienti de " << comanda1.getAlegeriUtilizator()[4] << " ori.";
	dataMining1 << "\nIn total, utilizatorul a ales sa vizualizeze rapoartele in numar de " << comanda1.getAlegeriUtilizator()[5] << " ori.";
	
	ofstream dataMining2("RaportGreseliUtilizator.txt");
	dataMining2 << "-Raport Introduceri Incorecte Ale Comenzii De Catre Utilizator-";
	dataMining2 << "\nUtilizatorul a introdus incorect comanda in numar de " << comanda1.getGreseliUtilizator() << " ori";
	
	ofstream dataMining3("RaportTimpPlasareComanda.txt");
	dataMining3 << "-Raport Timp Petrecut De Utilizator Pentru A Plasa Comanda-";
	dataMining3 << "\nUtilizatorul a petrecut " << (comanda1.getTimpSfarsit() - start) / 60 << " minute " << (comanda1.getTimpSfarsit() - start) % 60 << " secunde pentru a plasa comanda";
	return 0;
}