#include <iostream>
#include <math.h>

using namespace std;

class Punkt
{
    float x;
    float y;
public:
    Punkt(Punkt& p)
    {
        x = p.x;
        y = p.y;
    };

    Punkt(float x = 0, float y = 0)
    {
        this->x = x;
        this->y = y;
    };

    void dodaj(Punkt& p);//dodaje do siebie współrzędne punktu p (dodawanie wektorów w przestrzeni 2d )
    void dodaj(Punkt* p);
    void drukuj();// drukuje swoje współrzędne
    bool porownaj(Punkt& p);
    bool operator==(Punkt& p);

    friend class Wektor;
};

void Punkt::dodaj(Punkt& p)
{
    x += p.x;
    y += p.y;
}

void Punkt::dodaj(Punkt* p)
{
    x += p->x;
    y += p->y;
}

void Punkt::drukuj()
{
    cout << "x=" << x << " y=" << y << endl;
}

bool Punkt::porownaj(Punkt& p)
{
    if (x == p.x && y == p.y)
        return true;
    return false;
}

bool Punkt::operator==(Punkt& p)
{
    return this->porownaj(p);
}


class Wektor :public Punkt
{
    float dlugosc;
    float kierunek;

public:
    Wektor(float x = 0, float y = 0) : Punkt(x, y)
    {
        dlugosc = sqrt(x * x + y * y);
        kierunek = atan(y / x);
    };

    Wektor(Punkt& p) :Punkt(p)
    {
        dlugosc = sqrt(x * x + y * y);
        kierunek = atan(y / x);
    };

    void dodaj(Wektor& w);
    void dodaj(Wektor* w);
    void drukuj();
    bool porownaj(Wektor& w);
    bool operator==(Wektor& w);

    friend class TablicaWektorowSort;
};

void Wektor::dodaj(Wektor& w)
{
    x += w.x;
    y += w.y;
    dlugosc = sqrt(x * x + y * y);
    kierunek = atan(y / x);
}

void Wektor::dodaj(Wektor* w)
{
    x += w->x;
    y += w->y;
    dlugosc = sqrt(x * x + y * y);
    kierunek = atan(y / x);
}

void Wektor::drukuj()
{
    Punkt::drukuj();
    cout << "dlugosc=" << dlugosc << endl << "kierunek=" << kierunek << endl << endl;
}

bool Wektor::porownaj(Wektor& w)
{
    if (x == w.x && y == w.y)
        return true;
    return false;
}

bool Wektor::operator==(Wektor& w)
{
    return this->porownaj(w);
}


class TablicaWektorow
{
    Wektor* wsk;
    int dl; // dlugość Tablicy

public:
    TablicaWektorow()
    {
        dl = 0;
        wsk = nullptr;
    };

    ~TablicaWektorow()
    {
        if (wsk)
        {
            delete[] wsk;
            wsk = nullptr;
        }
    };

    void wstaw(Wektor&w);
    void drukuj();

    friend class TablicaWektorowSort;
};

void TablicaWektorow::wstaw(Wektor& w)
{
    dl++;
    if (!wsk)
    {
        wsk=new Wektor[dl];
        wsk[0] = w;
    }
    else
    {
        Wektor*new_wsk = new Wektor[dl];
        for (int i = 0; i < dl-1; i++)
        {
            new_wsk[i] = wsk[i];
        }
        new_wsk[dl - 1] = w;
        delete[] wsk;
        wsk = new_wsk;
        new_wsk = nullptr;
    }
}

void TablicaWektorow::drukuj()
{
    for (int i = 0; i < dl; i++)
        wsk[i].drukuj();
}


class TablicaWektorowSort :public TablicaWektorow
{
public:

    TablicaWektorowSort()
    {
        dl = 0;
        wsk = nullptr;
    };

    ~TablicaWektorowSort()
    {
        if (wsk)
        {
            delete[] wsk;
            wsk = nullptr;
        }
    };

    void wstaw(Wektor& w);
    void operator=(Wektor& w);
};

void TablicaWektorowSort::wstaw(Wektor& w)
{
    dl++;
    if (!wsk)
    {
        wsk = new Wektor[dl];
        wsk[0] = w;
    }
    else
    {
        bool po_wstawieniu = false;
        Wektor* new_wsk = new Wektor[dl];
        for (int i = 0; i < dl-1; i++)
        {
            if (!po_wstawieniu && w.dlugosc <= wsk[i].dlugosc)
            {
                new_wsk[i] = w;
                po_wstawieniu = true;
            }
            else
                new_wsk[i] = wsk[i-po_wstawieniu];
        }
        if (!po_wstawieniu)
            new_wsk[dl - 1] = w;
        else
            new_wsk[dl - 1] = wsk[dl - 2];
        delete[] wsk;
        wsk = new_wsk;
        new_wsk = nullptr;
    }
}

void TablicaWektorowSort::operator=(Wektor& w)
{
    this->wstaw(w);
}


int main()
{
    Punkt p(3, 4);
    Wektor w0(p);
    Wektor w1(1, 1);
    w1.dodaj(w1);
    Wektor* wsk = &w0;
    w1.dodaj(wsk);
    w0.drukuj();
    w1.drukuj();
    if (w1 == w0)
        cout << "rowne";
    else
        cout << "nie rowne";
    cout << endl;
    Wektor w2(3, 4);
    if (w2 == w0)
        cout << "rowne";
    else
        cout << "nie rowne";
    cout << endl<<endl<<endl;

    Wektor w3(10, 99);
    TablicaWektorow nieuporzadkowana;
    nieuporzadkowana.wstaw(w3);
    nieuporzadkowana.wstaw(w2);
    nieuporzadkowana.wstaw(w1);
    nieuporzadkowana.wstaw(w0);
    nieuporzadkowana.drukuj();
    cout << endl;
    TablicaWektorowSort uporzadkowana;
    uporzadkowana = w3;
    uporzadkowana = w2;
    uporzadkowana = w1;
    uporzadkowana = w0;
    uporzadkowana.drukuj();
}