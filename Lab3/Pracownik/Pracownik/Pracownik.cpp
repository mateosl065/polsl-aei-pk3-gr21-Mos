﻿#include <iostream>
#include <string>

using namespace std;
 
enum DniTygodnia {pon,wt,sr,cz,pi};

class Pracownik
{
    static int id;
    int mid;
    string imie;
    string nazwisko;
    
protected:
    int zarobek;
    int wiek;

public:
    string nik()
    {
        return imie + nazwisko;
    }
    Pracownik(string imie, string nazwisko, int wiek)
    {
        this->imie = imie;
        this->nazwisko = nazwisko;
        this->wiek = wiek;
        zarobek = 0;
        mid = id;
    }
    void wynagrodzenie(int zarobek = 2500)
    {
        this->zarobek = zarobek;
    }
    friend int Kadrowa::ilelat(Pracownik p);
};

class Szef : public Pracownik
{
    int nr_pokoju;
    DniTygodnia data;

public:
    void zwolnij(Pracownik* p)
    {
        delete p;
    }
    Szef(string imie, string nazwisko, int wiek,  int nr_pokoju, DniTygodnia data) :Pracownik(imie,nazwisko,wiek)
    {
        this->data = data;
    }
    void wynagrodzenie(int zarobek = 2500)
    {
        this->zarobek = 10 * zarobek;
    }
};

class Kadrowa: public Pracownik
{
    int nr_pokoju;
    DniTygodnia data;

public:
    Kadrowa(string imie, string nazwisko, int wiek, int nr_pokoju, DniTygodnia data) :Pracownik(imie, nazwisko, wiek)
    {
        this->data = data;
    }
    void wynagrodzenie(int zarobek = 2500)
    {
        this->zarobek = 2 * zarobek;
    }
    int ilelat(Pracownik p)
    {
        return p.wiek;
    }
};

int main()
{
    Pracownik prac1("Jan", "Kowalski", 30);
    Szef szefu("Janusz", "Nowak", 45, 102, pi);
    Pracownik* pprac;
    pprac = new Pracownik("Jan", "Janowski", 25);
    pprac = &prac1;
    pprac = &szefu;
    Kadrowa kadrowa()
}