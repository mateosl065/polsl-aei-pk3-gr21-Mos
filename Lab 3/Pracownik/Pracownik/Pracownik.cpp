#include <iostream>
#include <string>

using namespace std;
 
enum DniTygodnia {pon,wt,sr,cz,pi};

class Kadrowa;

class Pracownik
{
    friend class Kadrowa;

    string imie;
    string nazwisko;
    int wiek;

protected:
    int zarobek;

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
    }
    void wynagrodzenie(int zarobek = 2500)
    {
        this->zarobek = zarobek;
    }
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
    Kadrowa kadrowa("Karyna","Nowak",32,101,cz);
    int wiek=kadrowa.ilelat(*pprac);
    cout << wiek;
}