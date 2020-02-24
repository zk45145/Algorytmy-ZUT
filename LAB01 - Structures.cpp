// ALGO2 IN1 20B LAB01
// KRZYSZTOF ZAWADZKI
// zk45145@zut.edu.pl

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>

struct Struktura
{
    int a;
    char b;
    float c;
};

bool czyBylaWylosowana(int i, Struktura **tab)
{
    for (int j=0; j<i; j++)
    {
        if (tab[j]->a==tab[i]->a) return 1;
    }
    return 0;
}

Struktura** losowanie (int n)
{
    const char Zakres[]="BCDEFGHIJKLMNOPQRS";
    Struktura **tab = (Struktura**)malloc(sizeof(Struktura*)*n);
    for (int i=0; i<n; i++)
    {
        tab[i]=(Struktura*) malloc(sizeof(Struktura));
        do
        {
            tab[i]->a=rand() % 10000 - 1000;
        }
        while (czyBylaWylosowana(i, tab));
        tab[i]->b=Zakres[rand()%(sizeof(Zakres)-1)];
        tab[i]->c=1000+i+1;
    }
    return tab;
}

void kasowanie (Struktura **tab, int n)
{
    for (int i=0; i<n; i++)
    {
        free(tab[i]);
    }
    free (tab);
    tab = NULL;
}

Struktura** sortowanie (Struktura **tab, int n)
{
    bool flag;                  // flaga pomocniczna
    Struktura *temp;            //zmienna pomocnicza do zamiany liczb w sortowaniu babelkowym
    for (int i=0; i<n-1; i++)
    {
        flag=0;
        for (int j=0; j<n-i-1; j++)
        {
            if (tab[j]->a>tab[j+1]->a)
            {
                temp=tab[j];
                tab[j]=tab[j+1];
                tab[j+1]=temp;
                flag=1;
            }
        }
        if (flag==0)
            return tab;
    }
    return tab;
}

int zliczanie_znakow (Struktura **tab, int n, char c)
{
    int licznik=0;
    for (int i=0; i<n; i++)
    {
        if (tab[i]->b==c) licznik++;
    }
    return licznik;
}


int main()
{
    clock_t begin, end;
    double time_spent;
    begin = clock();
    srand(time(NULL));

    int n;
    char znak;
    std::ifstream plik;
    plik.open("inlab01.txt");
        if(!plik)
        {
                std::cout << "Blad odczytu pliku! " << std::endl;
                return false;
        }
        plik >> n;
        plik >> znak;

    plik.close();

    Struktura **tab = losowanie (n);
    sortowanie (tab, n);

    for (int i=0; i<20; i++)
    {
        std::cout << tab[i]->a << "   " << tab[i]->b << "   " << tab[i]->c << std::endl;
    }
    std::cout << std::endl << zliczanie_znakow(tab, n, znak) << " - liczba wystapien znaku " << znak << std::endl;

    kasowanie(tab, n);

    end = clock();
    time_spent = (double)(end - begin);
    if (time_spent<1000) std::cout << "0.";
    std::cout << time_spent << " s - czas wykonania programu" << std::endl;

    return 0;
}
