#define _CRT_SECURE_NO_WARNINGS

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
        x = p.x; y = p.y;
    };

    Punkt(float x = 0, float y = 0)
    {
        this->x = x; this->y = y;
    };

    void dodaj(Punkt& p);//dodaje do siebie współrzędne punktu p (dodawanie wektorów w przestrzeni 2d )
    void operator+= (Punkt& p);
    void drukuj();// drukuje swoje współrzędne
    //bool operator<<(Punkt& p);
    bool porownaj(Punkt& p);
    bool operator== (Punkt & p);
    //void operator= (Punkt& p);
    Punkt operator+ (Punkt& p);
    friend ostream& operator<< (ostream& strumien, const Punkt& p);
};

void Punkt::dodaj(Punkt& p)
{
    x += p.x;
    y += p.y;
}

void Punkt::operator+= (Punkt& p)
{
    this->dodaj(p);
}

void Punkt::drukuj()
{
    cout << "x=" << x << " y=" << y << endl;
}

ostream& operator<< (ostream& strumien, const Punkt& p)
{
    return strumien << "x=" << p.x << " y=" << p.y << endl;
}

bool Punkt::porownaj(Punkt& p)
{
    if (x == p.x && y == p.y)
        return true;
    return false;
}

bool Punkt::operator== (Punkt& p)
{
    return(this->porownaj(p));
}

/*void Punkt::operator= (Punkt& p)
{
    x = p.x;
    y = p.y;
}*/

Punkt Punkt::operator+ (Punkt& p)
{
    Punkt tmp;
    tmp.x = this->x + p.x;
    tmp.y = this->y + p.y;
    return tmp;
}

class Tablica
{
    Punkt* w;
    int dl; // dlugość Tablicy

public:
    Tablica(int dl_ = 0)
    {
        dl = dl_;
        w = new Punkt[dl];
        for (int i = 0; i < dl; i++)
        {
            w[i] = Punkt(0, 0);
        }
    }; // tworzy Tablice o zadanej długości i wypełnia punktami (0,0)

    Tablica(Tablica& tab)
    {
        dl = tab.dl;
        w = new Punkt[dl];
        for (int i = 0; i < dl; i++)
            w[i] = tab.w[i];
    }; //inicjalizacja za pomocą innej Tablicy

    Tablica(float* x, float* y, int dl_)
    {
        dl = dl_;
        w = new Punkt[dl];
        for (int i = 0; i < dl; i++)
        {
            w[i] = Punkt(x[i], y[i]);
        }
    }; // inicjalizacja tablicy punktów tablicami x -ów i y -ów

    ~Tablica()
    {
        delete[] w;
    };

    void dodaj(Tablica& tab);// dodaje do siebie Tablice
    void operator+=(Tablica& tab);
    bool porownaj(Tablica& tab);// porownaie z inna Tablica
    bool operator== (Tablica& tab);
    void drukuj();
    friend ostream& operator<< (ostream& strumien, const Tablica& tab);
    void operator= (Tablica& tab);
    Punkt& operator[](int n);
};

void Tablica::dodaj(Tablica& tab)
{
    if (dl < tab.dl)
    {
        Punkt* new_w = new Punkt[tab.dl];
        for (int i = 0; i < dl; i++)
            new_w[i] = w[i];
        for (int i = dl; i < tab.dl; i++)
            new_w[i] = Punkt(0, 0);
        delete[] w;
        w = new_w;
        new_w = nullptr;
        dl = tab.dl;
    }
    for (int i = 0; i < tab.dl; i++)
        w[i].dodaj(tab.w[i]);
}

void Tablica::operator+=(Tablica& tab)
{
    this->dodaj(tab);
}

bool Tablica::porownaj(Tablica& tab)
{
    if (dl != tab.dl)
        return false;
    for (int i = 0; i < dl; i++)
        if (w[i].porownaj(tab.w[i]) == false)
            return false;
    return true;
}

bool Tablica::operator== (Tablica& tab)
{
    return(this->porownaj(tab));
}

void Tablica::drukuj()
{
    for (int i = 0; i < dl; i++)
        w[i].drukuj();
}

ostream& operator<< (ostream& strumien, const Tablica& tab)
{
    for (int i = 0; i < tab.dl; i++)
        strumien << tab.w[i];
    return strumien;
}

void Tablica::operator= (Tablica& tab)
{
    delete[] w;
    dl = tab.dl;
    w = new Punkt[dl];
    for (int i = 0; i < dl; i++)
        w[i] = tab.w[i];
}

Punkt& Tablica::operator[](int n)
{
    return w[n];
}

class Wektor
{
    float x, y;
    
public:
    Wektor(const char* nazwa_pliku)
    {
        FILE* plik = fopen(nazwa_pliku, "r");
        if (plik)
        {
            float liczba;
            if (fscanf(plik, "%f", &liczba))
                x = liczba;
            else
                x = 0;
            if (fscanf(plik, "%f", &liczba))
                y = liczba;
            else
                y = 0;
            fclose(plik);
        }
        else
        {
            cerr << "Nie wczytano pliku!";
            x = 0;
            y = 0;
        }
    }

    void drukuj();
};

void Wektor::drukuj()
{
    cout << "Wektor: x=" << x << " y=" << y << endl;
}

int main()
{
    Punkt A(2, 3);
    Punkt B(3, 4);
    A += B;
    cout<<A;
    if (A == B)
        cout << "rowne";
    else
        cout << "nie rowne";
    cout << endl;
    A = B;
    if (A == B)
        cout << "rowne";
    else
        cout << "nie rowne";
    cout << endl;
    Punkt C(1, 1);
    C=A+B;
    cout<<C;

    int dl = 6;
    float* tab_x = new float[dl];
    for (int i = 0; i < dl; i++)
        tab_x[i] = i;
    float* tab_y = new float[dl];
    for (int i = 0; i < dl; i++)
        tab_y[i] = i / 2;
    Tablica tab0(tab_x, tab_y, dl);
    Tablica tab1(4);
    tab1 = tab0;
    cout << endl;
    cout << tab1;
    if (tab1 == tab0)
        cout << "rowne";
    else
        cout << "nie rowne";
    cout << endl;
    tab1 += tab1;
    cout << tab1;
    if (tab1 == tab0)
        cout << "rowne";
    else
        cout << "nie rowne";
    cout << endl;
    cout << tab1[1];

    Wektor wek("wektor.txt");
    wek.drukuj();

    return 0;
}