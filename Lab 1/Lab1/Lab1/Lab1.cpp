#include <iostream>

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
    void dodaj(Punkt* p);
    void drukuj();// drukuje swoje współrzędne
    bool porownaj(Punkt& p);
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

    bool porownaj(Tablica& tab);// porownaie z inna Tablica

    void drukuj();
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

bool Tablica::porownaj(Tablica& tab)
{
    if (dl != tab.dl)
        return false;
    for (int i = 0; i < dl; i++)
        if (w[i].porownaj(tab.w[i]) == false)
            return false;
    return true;
}

void Tablica::drukuj()
{
    for (int i = 0; i < dl; i++)
        w[i].drukuj();
}

int main()
{
    Punkt p1;
    Punkt p2(3, 4);
    Punkt p3(1, 1);
    Punkt p4(p3);
    p2.dodaj(p4);
    p2.dodaj(&p4);
    p2.drukuj();

    int dl = 6;
    float* tab_x = new float[dl];
    for (int i = 0; i < dl; i++)
        tab_x[i] = i;
    float* tab_y = new float[dl];
    for (int i = 0; i < dl; i++)
        tab_y[i] = i / 2;
    Tablica tab0(4);
    Tablica tab1(tab_x, tab_y, dl);
    Tablica tab2(tab1);
    cout << tab2.porownaj(tab1) << endl;
    tab2.dodaj(tab1);
    cout << tab2.porownaj(tab0) << endl;
    cout << tab2.porownaj(tab1) << endl;
    tab0.drukuj();
    cout << endl;
    tab1.drukuj();
    cout << endl;
    tab2.drukuj();
    delete[] tab_x;
    delete[] tab_y;
    tab_x = nullptr;
    tab_y = nullptr;
    return 0;
}