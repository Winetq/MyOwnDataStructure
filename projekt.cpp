#include <iostream>
#include <cctype>
#include <cstdlib>

using std::cout;
using std::cin;
using std::endl;

class BigNumber
{
private:
    char * number;
    int n;
public:
    static int LICZBA;
    bool czy_minus;
    BigNumber();
    BigNumber(const BigNumber & bg);
    ~BigNumber();
    void get_number();
    void show_number();
    int how_many_digit() { return n; }
    char & operator[](int z);
    const char & operator[](int z) const;
    BigNumber operator+(BigNumber & bg);
    BigNumber operator-(BigNumber & bg);
    BigNumber & operator=(const BigNumber & bg);
    char zwracanie_cyferki(int nr) { return (*this)[nr]; }
    friend char * update_array(char * arr, int & arr_size, char sign);
};

class MyOwnDataStructure
{
private:
    BigNumber ** liczby;
public:
    MyOwnDataStructure();
    ~MyOwnDataStructure();
    void setter(BigNumber arr[], int x);
    void show();
    void minimum();
    void maximum();
};

int main()
{
    int ile_liczb;
    cin >> ile_liczb;
    while (cin.get() != '\n')
        continue; //pobranie znaku enter

    BigNumber * obiekty_liczb = new BigNumber[ile_liczb];

    for (int i = 0; i < ile_liczb; i++)
        obiekty_liczb[i].get_number();

    MyOwnDataStructure struktura1;
    struktura1.setter(obiekty_liczb, ile_liczb);

    char ch;
    char operacja[15];
    int licznik = 0;
    bool jaki_znak;
    cin.get(ch);
    while (ch != 'q')
    {
        if (ch == '\n')
        {
            if (isalpha(operacja[0]))
            {
                if (operacja[1] == 'a')
                    struktura1.maximum();
                else
                    struktura1.minimum();
            }
            else if (operacja[0] == '?')
                struktura1.show();
            else
            {
                char liczba1[5];
                char liczba2[5];
                char liczba3[5];
                int licz = 0;
                int cyferki = 0;
                for (int i = 0; i < 5; i++)
                    liczba1[i] = '-';
                for (int i = 0; i < 5; i++)
                    liczba2[i] = '-';
                for (int i = 0; i < 5; i++)
                    liczba3[i] = '-';
                while (isdigit(operacja[licz]))
                {
                    liczba1[cyferki] = operacja[licz];
                    licz++;
                    cyferki++;
                }
                licz++;
                licz++;
                licz++;
                cyferki = 0;
                while (isdigit(operacja[licz]))
                {
                    liczba2[cyferki] = operacja[licz];
                    licz++;
                    cyferki++;
                }
                licz++;
                if (operacja[licz] == '+')
                    jaki_znak = false;
                else
                    jaki_znak = true;
                licz++;
                licz++;
                cyferki = 0;
                while (isdigit(operacja[licz]))
                {
                    liczba3[cyferki] = operacja[licz];
                    licz++;
                    cyferki++;
                }

                for (int i = 0; i < 5; i++)
                {
                    if (liczba1[i] == '-')
                        liczba1[i] = '\0';
                }
                for (int i = 0; i < 5; i++)
                {
                    if (liczba2[i] == '-')
                        liczba2[i] = '\0';
                }
                for (int i = 0; i < 5; i++)
                {
                    if (liczba3[i] == '-')
                        liczba3[i] = '\0';
                }

                int ile_cyfr = 0;
                for (int i = 0; i < 5; i++)
                {
                    if (isdigit(liczba1[i]))
                        ile_cyfr++;
                }
                int a;
                if (ile_cyfr == 1)
                    a = (int)liczba1[0] - 48;
                else
                    a = atoi(liczba1);

                ile_cyfr = 0;
                for (int i = 0; i < 5; i++)
                {
                    if (isdigit(liczba2[i]))
                        ile_cyfr++;
                }
                int b;
                if (ile_cyfr == 1)
                    b = (int)liczba2[0] - 48;
                else
                    b = atoi(liczba2);

                ile_cyfr = 0;
                for (int i = 0; i < 5; i++)
                {
                    if (isdigit(liczba3[i]))
                        ile_cyfr++;
                }
                int c;
                if (ile_cyfr == 1)
                    c = (int)liczba3[0] - 48;
                else
                    c = atoi(liczba3);

                if (jaki_znak == false)
                    obiekty_liczb[a] = obiekty_liczb[b] + obiekty_liczb[c];
                else
                    obiekty_liczb[a] = obiekty_liczb[b] - obiekty_liczb[c];
            }
            for (int i = 0; i < 15; i++)
                operacja[i] = '\0'; //zerujemy tablice
            licznik = 0;
        }
        else
        {
            operacja[licznik] = ch;
            licznik++;
        }
        cin.get(ch);
    }

    delete [] obiekty_liczb;

    return 0;
}

//definicje klasy BigNumber

int BigNumber::LICZBA = 0;

BigNumber::BigNumber()
{
    n = 0;
    number = NULL;
    czy_minus = false;
    LICZBA++;
}

BigNumber::~BigNumber()
{
    --LICZBA;
    delete [] number;
}

char * update_array(char * arr, int & arr_size, char sign) //przed BigNumber::get_number()
{
    char * nowa_tablica = new char[arr_size + 4];

    for (int i = 0; i < arr_size; i++)
        nowa_tablica[i] = arr[i];

    nowa_tablica[arr_size - 1] = sign;

    delete [] arr;

    return nowa_tablica;
}

void BigNumber::get_number()
{
    char ch;
    int rozmiar = 0;
    number = new char[rozmiar + 4];
    cin.get(ch);
    if (ch == '-')
        czy_minus = true;
    while (ch != '\n')
    {
        rozmiar++;
        if (rozmiar % 4 == 0)
            number = update_array(number, rozmiar, ch);
        else
            number[rozmiar - 1] = ch;
        cin.get(ch);
    }
    n = rozmiar;
}

void BigNumber::show_number()
{
    for (int i = 0; i < n; i++)
        cout << number[i];
    cout << endl;
}

char & BigNumber::operator[](int z)
{
    return number[z];
}

const char & BigNumber::operator[](int z) const
{
    return number[z];
}

BigNumber BigNumber::operator+(BigNumber & bg)
{
    BigNumber sum;
    if (czy_minus == false && bg.czy_minus == false) //dwa plusy
    {
        if (n < bg.how_many_digit())
        {
            sum.number = new char[bg.how_many_digit() + 2];
            for (int i = 0; i <= bg.how_many_digit(); i++)
                sum.number[i] = '0';
            sum.number[bg.how_many_digit() + 1] = '\0';
            int regulator = n - 1;
            int rozmiar = bg.how_many_digit() - 1;
            int jedynka = 0;
            while (rozmiar != -1)
            {
                if (regulator >= 0)
                {
                    int a1 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + jedynka;
                    int b1 = (int)zwracanie_cyferki(regulator) - 48;
                    int a1b1 = a1 + b1;
                    if (a1b1 >= 10)
                    {
                        jedynka = 1;
                        int znak = a1b1 - 10;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a1b1;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                else
                {
                    int a1 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + jedynka;
                    if (a1 >= 10)
                    {
                        jedynka = 1;
                        int znak = a1 - 10;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                        if (rozmiar == 0)
                            sum.number[rozmiar] = (char)jedynka + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a1;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                regulator--;
                rozmiar--;
            }
            if (sum.number[0] == '0')
            {
                for (int i = 0; i < bg.how_many_digit(); i++)
                {
                    sum.number[i] = sum.number[i + 1];
                    if (i == (bg.how_many_digit() - 1))
                        sum.number[i + 1] = '\0';
                }
            }
        }
        else if (n == bg.how_many_digit())
        {
            sum.number = new char[n + 2];
            for (int i = 0; i <= n; i++)
                sum.number[i] = '0';
            sum.number[n + 1] = '\0';
            int rozmiar = n - 1;
            int jedynka = 0;
            while (rozmiar != -1)
            {
                int a1 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + jedynka;
                int b1 = (int)zwracanie_cyferki(rozmiar) - 48;
                int a1b1 = a1 + b1;
                if (a1b1 >= 10)
                {
                    jedynka = 1;
                    int znak = a1b1 - 10;
                    sum.number[rozmiar + 1] = (char)znak + '0';
                    if (rozmiar == 0)
                        sum.number[rozmiar] = (char)jedynka + '0';
                }
                else
                {
                    jedynka = 0;
                    int znak = a1b1;
                    sum.number[rozmiar + 1] = (char)znak + '0';
                }
                rozmiar--;
            }
            if (sum.number[0] == '0')
            {
                for (int i = 0; i < bg.how_many_digit(); i++)
                {
                    sum.number[i] = sum.number[i + 1];
                    if (i == (bg.how_many_digit() - 1))
                        sum.number[i + 1] = '\0';
                }
            }
        }
        else //n > bg.how_many_digit()
        {
            sum.number = new char[n + 2];
            for (int i = 0; i <= n; i++)
                sum.number[i] = '0';
            sum.number[n + 1] = '\0';
            int regulator = bg.how_many_digit() - 1;
            int rozmiar = n - 1;
            int jedynka = 0;
            while (rozmiar != -1)
            {
                if (regulator >= 0)
                {
                    int a1 = (int)zwracanie_cyferki(rozmiar) - 48 + jedynka;
                    int b1 = (int)bg.zwracanie_cyferki(regulator) - 48;
                    int a1b1 = a1 + b1;
                    if (a1b1 >= 10)
                    {
                        jedynka = 1;
                        int znak = a1b1 - 10;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a1b1;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                else
                {
                    int a1 = (int)zwracanie_cyferki(rozmiar) - 48 + jedynka;
                    if (a1 >= 10)
                    {
                        jedynka = 1;
                        int znak = a1 - 10;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                        if (rozmiar == 0)
                            sum.number[rozmiar] = (char)jedynka + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a1;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                regulator--;
                rozmiar--;
            }
            if (sum.number[0] == '0')
            {
                for (int i = 0; i < n; i++)
                {
                    sum.number[i] = sum.number[i + 1];
                    if (i == (n - 1))
                        sum.number[i + 1] = '\0';
                }
            }
        }
        sum.czy_minus = false;
    }
    else if (czy_minus == true && bg.czy_minus == true) //dwa minusy
    {
        if (n < bg.how_many_digit())
        {
            sum.number = new char[bg.how_many_digit() + 2];
            for (int i = 0; i <= bg.how_many_digit(); i++)
                sum.number[i] = '0';
            sum.number[bg.how_many_digit() + 1] = '\0';
            int regulator = n - 1;
            int rozmiar = bg.how_many_digit() - 1;
            int jedynka = 0;
            while (rozmiar != 0)
            {
                if (regulator >= 1)
                {
                    int a1 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + jedynka;
                    int b1 = (int)zwracanie_cyferki(regulator) - 48;
                    int a1b1 = a1 + b1;
                    if (a1b1 >= 10)
                    {
                        jedynka = 1;
                        int znak = a1b1 - 10;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a1b1;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                else
                {
                    int a1 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + jedynka;
                    if (a1 >= 10)
                    {
                        jedynka = 1;
                        int znak = a1 - 10;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                        if (rozmiar == 1)
                            sum.number[rozmiar] = (char)jedynka + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a1;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                regulator--;
                rozmiar--;
            }
            if (sum.number[1] == '0')
                sum.number[1] = '-';
            else
                sum.number[0] = '-';
            if (sum.number[0] == '0')
            {
                for (int i = 0; i < bg.how_many_digit(); i++)
                {
                    sum.number[i] = sum.number[i + 1];
                    if (i == (bg.how_many_digit() - 1))
                        sum.number[i + 1] = '\0';
                }
            }
        }
        else if (n == bg.how_many_digit())
        {
            sum.number = new char[n + 2];
            for (int i = 0; i <= bg.how_many_digit(); i++)
                sum.number[i] = '0';
            sum.number[n + 1] = '\0';
            int rozmiar = n - 1;
            int jedynka = 0;
            while (rozmiar != 0)
            {
                int a1 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + jedynka;
                int b1 = (int)zwracanie_cyferki(rozmiar) - 48;
                int a1b1 = a1 + b1;
                if (a1b1 >= 10)
                {
                    jedynka = 1;
                    int znak = a1b1 - 10;
                    sum.number[rozmiar + 1] = (char)znak + '0';
                    if (rozmiar == 1)
                            sum.number[rozmiar] = (char)jedynka + '0';
                }
                else
                {
                    jedynka = 0;
                    int znak = a1b1;
                    sum.number[rozmiar + 1] = (char)znak + '0';
                }
                rozmiar--;
            }
            if (sum.number[1] == '0')
                sum.number[1] = '-';
            else
                sum.number[0] = '-';
            if (sum.number[0] == '0')
            {
                for (int i = 0; i < bg.how_many_digit(); i++)
                {
                    sum.number[i] = sum.number[i + 1];
                    if (i == (bg.how_many_digit() - 1))
                        sum.number[i + 1] = '\0';
                }
            }
        }
        else //n > bg.how_many_digit()
        {
            sum.number = new char[n + 2];
            for (int i = 0; i <= n; i++)
                sum.number[i] = '0';
            sum.number[n + 1] = '\0';
            int regulator = bg.how_many_digit() - 1;
            int rozmiar = n - 1;
            int jedynka = 0;
            while (rozmiar != 0)
            {
                if (regulator >= 1)
                {
                    int a1 = (int)zwracanie_cyferki(rozmiar) - 48 + jedynka;
                    int b1 = (int)bg.zwracanie_cyferki(regulator) - 48;
                    int a1b1 = a1 + b1;
                    if (a1b1 >= 10)
                    {
                        jedynka = 1;
                        int znak = a1b1 - 10;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a1b1;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                else
                {
                    int a1 = (int)zwracanie_cyferki(rozmiar) - 48 + jedynka;
                    if (a1 >= 10)
                    {
                        jedynka = 1;
                        int znak = a1 - 10;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                        if (rozmiar == 1)
                            sum.number[rozmiar] = (char)jedynka + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a1;
                        sum.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                regulator--;
                rozmiar--;
            }
            if (sum.number[1] == '0')
                sum.number[1] = '-';
            else
                sum.number[0] = '-';
            if (sum.number[0] == '0')
            {
                for (int i = 0; i < n; i++)
                {
                    sum.number[i] = sum.number[i + 1];
                    if (i == (n - 1))
                        sum.number[i + 1] = '\0';
                }
            }
        }
        sum.czy_minus = false;
    }
    else if (czy_minus == false && bg.czy_minus == true)
    {
        BigNumber sum1;
        sum1.number = new char[n + 2];
        sum1.czy_minus = true;
        for (int i = 0; i <= n; i++)
            sum1.number[i] = '0';
        sum1.number[n + 1] = '\0';
        sum1.number[0] = '-';
        for (int i = 0; i < n; i++)
            sum1.number[i + 1] = number[i];
        int rozmiar_sum1 = 0;
        for (int ile = 0; sum1.number[ile] != '\0'; ile++)
            rozmiar_sum1++;
        sum1.n = rozmiar_sum1;
        sum = sum1 - bg; //SUPER

        if (sum.czy_minus == false)
        {
            BigNumber minusik;
            minusik.number = new char[sum.how_many_digit() + 2];
            minusik.czy_minus = true;
            for (int i = 0; i <= sum.how_many_digit(); i++)
                minusik.number[i] = '0';
            minusik.number[sum.how_many_digit() + 1] = '\0';
            minusik.number[0] = '-';
            for (int i = 0; i < sum.how_many_digit(); i++)
                minusik.number[i + 1] = sum.number[i];
            int rozmiar_minusik = 0;
            for (int ile = 0; minusik.number[ile] != '\0'; ile++)
                rozmiar_minusik++;
            minusik.n = rozmiar_minusik;
            sum = minusik;
        }
        else
        {
            BigNumber plusik;
            plusik.number = new char[sum.how_many_digit()];
            plusik.czy_minus = false;
            for (int i = 0; i < (sum.how_many_digit() - 1); i++)
                plusik.number[i] = '0';
            plusik.number[sum.how_many_digit() - 1] = '\0';
            for (int i = 0; i < (sum.how_many_digit() - 1); i++)
                plusik.number[i] = sum.number[i + 1];
            int rozmiar_plusik = 0;
            for (int ile = 0; plusik.number[ile] != '\0'; ile++)
                rozmiar_plusik++;
            plusik.n = rozmiar_plusik;
            sum = plusik;
        }
    }
    else if (czy_minus == true && bg.czy_minus == false)
    {
        BigNumber sum1;
        sum1.number = new char[bg.how_many_digit() + 2];
        sum1.czy_minus = true;
        for (int i = 0; i <= bg.how_many_digit(); i++)
            sum1.number[i] = '0';
        sum1.number[bg.how_many_digit() + 1] = '\0';
        sum1.number[0] = '-';
        for (int i = 0; i < bg.how_many_digit(); i++)
            sum1.number[i + 1] = bg.number[i];
        int rozmiar_sum1 = 0;
        for (int ile = 0; sum1.number[ile] != '\0'; ile++)
            rozmiar_sum1++;
        sum1.n = rozmiar_sum1;
        sum = *this - sum1; //SUPER
    }
    int rozmiar_sum = 0;
    for (int ile = 0; sum.number[ile] != '\0'; ile++)
        rozmiar_sum++;
    sum.n = rozmiar_sum;
    return sum;
}

BigNumber BigNumber::operator-(BigNumber & bg)
{
    BigNumber diff;
    if (czy_minus == false && bg.czy_minus == false) //dwa plusy
    {
        if (n < bg.how_many_digit()) //wynikiem jest liczba ujemna
        {
            diff.number = new char[bg.how_many_digit() + 2];
            for (int i = 0; i <= bg.how_many_digit(); i++)
                diff.number[i] = '0';
            diff.number[bg.how_many_digit() + 1] = '\0';
            int regulator = n - 1;
            int rozmiar = bg.how_many_digit() - 1;
            int a1 = (int)bg.zwracanie_cyferki(0) - 48 - 1;
            int jedynka = 0;
            while (rozmiar != 0)
            {
                if (regulator == (n - 1))
                {
                    int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 10;
                    int b2 = (int)zwracanie_cyferki(regulator) - 48;
                    int a2b2 = a2 - b2;
                    if (a2b2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2b2 - 10;
                        diff.number[rozmiar + 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2b2;
                        diff.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                else if(regulator < (n - 1) && regulator >= 0)
                {
                    int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                    int b2 = (int)zwracanie_cyferki(regulator) - 48;
                    int a2b2 = a2 - b2;
                    if (a2b2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2b2 - 10;
                        diff.number[rozmiar + 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2b2;
                        diff.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                else
                {
                    int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                    if (a2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2 - 10;
                        diff.number[rozmiar + 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2;
                        diff.number[rozmiar + 1] = (char)znak + '0';
                    }
                }
                regulator--;
                rozmiar--;
            }
            int ostatni = a1 + jedynka;
            diff.number[rozmiar + 1] = (char)ostatni + '0';
            diff.number[0] = '-';
            diff.czy_minus = true;
        }
        else if (n == bg.how_many_digit())
        {
            bool ktora_wieksza; //gdy n to ktora_wieksza = 0, gdy bg to ktora_wieksza = 1
            if ((int)bg.zwracanie_cyferki(0) < (int)zwracanie_cyferki(0))
                ktora_wieksza = 0;
            else if ((int)bg.zwracanie_cyferki(0) > (int)zwracanie_cyferki(0))
                ktora_wieksza = 1;
            else
            {
                int r = 0;
                while (r != n)
                {
                    r++;
                    if ((int)bg.zwracanie_cyferki(r) < (int)zwracanie_cyferki(r))
                    {
                        ktora_wieksza = 0;
                        break;
                    }
                    if ((int)bg.zwracanie_cyferki(r) > (int)zwracanie_cyferki(r))
                    {
                        ktora_wieksza = 1;
                        break;
                    }
                }
            }

            if (ktora_wieksza == 0) //wynikiem liczba dodatnia
            {
                diff.number = new char[n + 1];
                for (int i = 0; i < n; i++)
                    diff.number[i] = '0';
                diff.number[n] = '\0';
                int rozmiar = n - 1;
                int a1 = (int)zwracanie_cyferki(0) - 48 - 1;
                int jedynka = 0;
                while (rozmiar != 0)
                {
                    if (rozmiar == (n - 1))
                    {
                        int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 10;
                        int b2 = (int)bg.zwracanie_cyferki(rozmiar) - 48;
                        int a2b2 = a2 - b2;
                        if (a2b2 >= 10)
                        {
                            jedynka = 1;
                            int znak = a2b2 - 10;
                            diff.number[rozmiar] = (char)znak + '0';
                        }
                        else
                        {
                            jedynka = 0;
                            int znak = a2b2;
                            diff.number[rozmiar] = (char)znak + '0';
                        }
                    }
                    else
                    {
                        int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                        int b2 = (int)bg.zwracanie_cyferki(rozmiar) - 48;
                        int a2b2 = a2 - b2;
                        if (a2b2 >= 10)
                        {
                            jedynka = 1;
                            int znak = a2b2 - 10;
                            diff.number[rozmiar] = (char)znak + '0';
                        }
                        else
                        {
                            jedynka = 0;
                            int znak = a2b2;
                            diff.number[rozmiar] = (char)znak + '0';
                        }
                    }
                    rozmiar--;
                }
                int ostatni1 = a1 + jedynka;
                int ostatni2 = (int)bg.zwracanie_cyferki(rozmiar) - 48;
                int ostatni12 = ostatni1 - ostatni2;
                diff.number[rozmiar] = (char)ostatni12 + '0';
                if (diff.number[0] == '0')
                {
                    for (int i = 0; i < (bg.how_many_digit() - 1); i++)
                    {
                        diff.number[i] = diff.number[i + 1];
                        if (i == (bg.how_many_digit() - 2))
                            diff.number[i + 1] = '\0';
                    }
                }
                diff.czy_minus = false;
            }
            else //wynikiem liczba ujemna
            {
                diff.number = new char[n + 2];
                for (int i = 0; i <= n; i++)
                    diff.number[i] = '0';
                diff.number[n + 1] = '\0';
                int rozmiar = n - 1;
                int a1 = (int)bg.zwracanie_cyferki(0) - 48 - 1;
                int jedynka = 0;
                while (rozmiar != 0)
                {
                    if (rozmiar == (n-1))
                    {
                        int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 10;
                        int b2 = (int)zwracanie_cyferki(rozmiar) - 48;
                        int a2b2 = a2 - b2;
                        if (a2b2 >= 10)
                        {
                            jedynka = 1;
                            int znak = a2b2 - 10;
                            diff.number[rozmiar + 1] = (char)znak + '0';
                        }
                        else
                        {
                            jedynka = 0;
                            int znak = a2b2;
                            diff.number[rozmiar + 1] = (char)znak + '0';
                        }
                    }
                    else
                    {
                        int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                        int b2 = (int)zwracanie_cyferki(rozmiar) - 48;
                        int a2b2 = a2 - b2;
                        if (a2b2 >= 10)
                        {
                            jedynka = 1;
                            int znak = a2b2 - 10;
                            diff.number[rozmiar + 1] = (char)znak + '0';
                        }
                        else
                        {
                            jedynka = 0;
                            int znak = a2b2;
                            diff.number[rozmiar + 1] = (char)znak + '0';
                        }
                    }
                    rozmiar--;
                }
                int ostatni1 = a1 + jedynka;
                int ostatni2 = (int)zwracanie_cyferki(rozmiar) - 48;
                int ostatni12 = ostatni1 - ostatni2;
                diff.number[rozmiar + 1] = (char)ostatni12 + '0';
                if (diff.number[1] == '0')
                    diff.number[1] = '-';
                else
                    diff.number[0] = '-';
                if (diff.number[0] == '0')
                {
                    for (int i = 0; i < bg.how_many_digit(); i++)
                    {
                        diff.number[i] = diff.number[i + 1];
                        if (i == (bg.how_many_digit() - 1))
                            diff.number[i + 1] = '\0';
                    }
                }
                diff.czy_minus = true;
            }
        }
        else //n > bg.how_many_digit()
        {
            diff.number = new char[n + 1];
            for (int i = 0; i < n; i++)
                diff.number[i] = '0';
            diff.number[n] = '\0';
            int regulator = bg.how_many_digit() - 1;
            int rozmiar = n - 1;
            int a1 = (int)zwracanie_cyferki(0) - 48 - 1;
            int jedynka = 0;
            while (rozmiar != 0)
            {
                if (regulator == (bg.how_many_digit() - 1))
                {
                    int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 10;
                    int b2 = (int)bg.zwracanie_cyferki(regulator) - 48;
                    int a2b2 = a2 - b2;
                    if (a2b2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2b2 - 10;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2b2;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                }
                else if(regulator < (n - 1) && regulator >= 0)
                {
                    int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                    int b2 = (int)bg.zwracanie_cyferki(regulator) - 48;
                    int a2b2 = a2 - b2;
                    if (a2b2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2b2 - 10;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2b2;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                }
                else
                {
                    int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                    if (a2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2 - 10;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                }
                regulator--;
                rozmiar--;
            }
            int ostatni = a1 + jedynka;
            diff.number[rozmiar] = (char)ostatni + '0';
            diff.czy_minus = false;
        }
    }
    else if (czy_minus == true && bg.czy_minus == true) //dwa minusy
    {
        if (n < bg.how_many_digit())
        {
            diff.number = new char[bg.how_many_digit()];
            for (int i = 0; i < (bg.how_many_digit() - 1); i++)
                diff.number[i] = '0';
            diff.number[bg.how_many_digit() - 1] = '\0';
            int regulator = n - 1;
            int rozmiar = bg.how_many_digit() - 1;
            int a1 = (int)bg.zwracanie_cyferki(1) - 48 - 1;
            int jedynka = 0;
            while (rozmiar != 1)
            {
                if (regulator == (n - 1))
                {
                    int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 10;
                    int b2 = (int)zwracanie_cyferki(regulator) - 48;
                    int a2b2 = a2 - b2;
                    if (a2b2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2b2 - 10;
                        diff.number[rozmiar - 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2b2;
                        diff.number[rozmiar - 1] = (char)znak + '0';
                    }
                }
                else if(regulator < (n - 1) && regulator >= 1)
                {
                    int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                    int b2 = (int)zwracanie_cyferki(regulator) - 48;
                    int a2b2 = a2 - b2;
                    if (a2b2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2b2 - 10;
                        diff.number[rozmiar - 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2b2;
                        diff.number[rozmiar - 1] = (char)znak + '0';
                    }
                }
                else
                {
                    int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                    if (a2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2 - 10;
                        diff.number[rozmiar - 1] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2;
                        diff.number[rozmiar - 1] = (char)znak + '0';
                    }
                }
                regulator--;
                rozmiar--;
            }
            int ostatni = a1 + jedynka;
            diff.number[rozmiar - 1] = (char)ostatni + '0';
            diff.czy_minus = false;
        }
        else if (n == bg.how_many_digit())
        {
            bool ktora_wieksza; //gdy n to ktora_wieksza = 0, gdy bg to ktora_wieksza = 1
            if ((int)bg.zwracanie_cyferki(1) < (int)zwracanie_cyferki(1))
                ktora_wieksza = 0;
            else if ((int)bg.zwracanie_cyferki(1) > (int)zwracanie_cyferki(1))
                ktora_wieksza = 1;
            else
            {
                int r = 1;
                while (r != n)
                {
                    r++;
                    if ((int)bg.zwracanie_cyferki(r) < (int)zwracanie_cyferki(r))
                    {
                        ktora_wieksza = 0;
                        break;
                    }
                    if ((int)bg.zwracanie_cyferki(r) > (int)zwracanie_cyferki(r))
                    {
                        ktora_wieksza = 1;
                        break;
                    }
                }
            }

            if (ktora_wieksza == 0)
            {
                diff.number = new char[n + 1];
                for (int i = 0; i < n; i++)
                    diff.number[i] = '0';
                diff.number[n] = '\0';
                int rozmiar = n - 1;
                int a1 = (int)zwracanie_cyferki(1) - 48 - 1;
                int jedynka = 0;
                while (rozmiar != 1)
                {
                    if (rozmiar == (n - 1))
                    {
                        int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 10;
                        int b2 = (int)bg.zwracanie_cyferki(rozmiar) - 48;
                        int a2b2 = a2 - b2;
                        if (a2b2 >= 10)
                        {
                            jedynka = 1;
                            int znak = a2b2 - 10;
                            diff.number[rozmiar] = (char)znak + '0';
                        }
                        else
                        {
                            jedynka = 0;
                            int znak = a2b2;
                            diff.number[rozmiar] = (char)znak + '0';
                        }
                    }
                    else
                    {
                        int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                        int b2 = (int)bg.zwracanie_cyferki(rozmiar) - 48;
                        int a2b2 = a2 - b2;
                        if (a2b2 >= 10)
                        {
                            jedynka = 1;
                            int znak = a2b2 - 10;
                            diff.number[rozmiar] = (char)znak + '0';
                        }
                        else
                        {
                            jedynka = 0;
                            int znak = a2b2;
                            diff.number[rozmiar] = (char)znak + '0';
                        }
                    }
                    rozmiar--;
                }
                int ostatni1 = a1 + jedynka;
                int ostatni2 = (int)bg.zwracanie_cyferki(rozmiar) - 48;
                int ostatni12 = ostatni1 - ostatni2;
                diff.number[rozmiar] = (char)ostatni12 + '0';
                if (diff.number[1] == '0')
                    diff.number[1] = '-';
                else
                    diff.number[0] = '-';
                if (diff.number[0] == '0')
                {
                    for (int i = 0; i < n; i++)
                    {
                        diff.number[i] = diff.number[i + 1];
                        if (i == (n - 1))
                            diff.number[i + 1] = '\0';
                    }
                }
                diff.czy_minus = true;
            }
            else
            {
                diff.number = new char[n];
                for (int i = 0; i < (n - 1); i++)
                    diff.number[i] = '0';
                diff.number[n - 1] = '\0';
                int rozmiar = n - 1;
                int a1 = (int)bg.zwracanie_cyferki(1) - 48 - 1;
                int jedynka = 0;
                while (rozmiar != 1)
                {
                    if (rozmiar == (n - 1))
                    {
                        int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 10;
                        int b2 = (int)zwracanie_cyferki(rozmiar) - 48;
                        int a2b2 = a2 - b2;
                        if (a2b2 >= 10)
                        {
                            jedynka = 1;
                            int znak = a2b2 - 10;
                            diff.number[rozmiar - 1] = (char)znak + '0';
                        }
                        else
                        {
                            jedynka = 0;
                            int znak = a2b2;
                            diff.number[rozmiar - 1] = (char)znak + '0';
                        }
                    }
                    else
                    {
                        int a2 = (int)bg.zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                        int b2 = (int)zwracanie_cyferki(rozmiar) - 48;
                        int a2b2 = a2 - b2;
                        if (a2b2 >= 10)
                        {
                            jedynka = 1;
                            int znak = a2b2 - 10;
                            diff.number[rozmiar - 1] = (char)znak + '0';
                        }
                        else
                        {
                            jedynka = 0;
                            int znak = a2b2;
                            diff.number[rozmiar - 1] = (char)znak + '0';
                        }
                    }
                    rozmiar--;
                }
                int ostatni1 = a1 + jedynka;
                int ostatni2 = (int)zwracanie_cyferki(rozmiar) - 48;
                int ostatni12 = ostatni1 - ostatni2;
                diff.number[rozmiar - 1] = (char)ostatni12 + '0';
                if (diff.number[0] == '0')
                {
                    for (int i = 0; i < (bg.how_many_digit() - 1); i++)
                    {
                        diff.number[i] = diff.number[i + 1];
                        if (i == (bg.how_many_digit() - 2))
                            diff.number[i + 1] = '\0';
                    }
                }
                diff.czy_minus = false;
            }
        }
        else //n > bg.how_many_digit()
        {
            diff.number = new char[n + 1];
            for (int i = 0; i < n; i++)
                diff.number[i] = '0';
            diff.number[n] = '\0';
            int regulator = bg.how_many_digit() - 1;
            int rozmiar = n - 1;
            int a1 = (int)zwracanie_cyferki(1) - 48 - 1;
            int jedynka = 0;
            while (rozmiar != 1)
            {
                if (rozmiar == (n - 1))
                {
                    int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 10;
                    int b2 = (int)bg.zwracanie_cyferki(regulator) - 48;
                    int a2b2 = a2 - b2;
                    if (a2b2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2b2 - 10;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2b2;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                }
                else if(regulator < (n - 1) && regulator >= 1)
                {
                    int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                    int b2 = (int)bg.zwracanie_cyferki(regulator) - 48;
                    int a2b2 = a2 - b2;
                    if (a2b2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2b2 - 10;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2b2;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                }
                else
                {
                    int a2 = (int)zwracanie_cyferki(rozmiar) - 48 + 9 + jedynka;
                    if (a2 >= 10)
                    {
                        jedynka = 1;
                        int znak = a2 - 10;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                    else
                    {
                        jedynka = 0;
                        int znak = a2;
                        diff.number[rozmiar] = (char)znak + '0';
                    }
                }
                regulator--;
                rozmiar--;
            }
            int ostatni = a1 + jedynka;
            diff.number[rozmiar] = (char)ostatni + '0';
            diff.czy_minus = true;
            diff.number[0] = '-';
        }
    }
    else if (czy_minus == false && bg.czy_minus == true)
    {
        BigNumber diff1;
        diff1.number = new char[bg.how_many_digit()];
        diff1.czy_minus = false;
        for (int i = 0; i < (bg.how_many_digit() - 1); i++)
            diff1.number[i] = '0';
        diff1.number[bg.how_many_digit() - 1] = '\0';
        for (int i = 0; i < (bg.how_many_digit() - 1); i++)
            diff1.number[i] = bg.number[i + 1];
        int rozmiar_diff1 = 0;
        for (int ile = 0; diff1.number[ile] != '\0'; ile++)
            rozmiar_diff1++;
        diff1.n = rozmiar_diff1;
        diff = *this + diff1; //SUPER
    }
    else if (czy_minus == true && bg.czy_minus == false)
    {
        BigNumber diff1;
        diff1.number = new char[bg.how_many_digit() + 2];
        diff1.czy_minus = true;
        for (int i = 0; i <= bg.how_many_digit(); i++)
            diff1.number[i] = '0';
        diff1.number[bg.how_many_digit() + 1] = '\0';
        diff1.number[0] = '-';
        for (int i = 0; i < bg.how_many_digit(); i++)
            diff1.number[i + 1] = bg.number[i];
        int rozmiar_diff1 = 0;
        for (int ile = 0; diff1.number[ile] != '\0'; ile++)
            rozmiar_diff1++;
        diff1.n = rozmiar_diff1;
        diff = *this + diff1; //SUPER
    }
    int rozmiar_diff = 0;
    for (int ile = 0; diff.number[ile] != '\0'; ile++)
        rozmiar_diff++;
    diff.n = rozmiar_diff;
    return diff;
}

BigNumber & BigNumber::operator=(const BigNumber & bg)
{
    delete [] number;
    n = bg.n;
    czy_minus = bg.czy_minus;
    number = new char[n + 1];
    for (int i = 0; i < n; i++)
        number[i] = bg.number[i];
    number[n] = '\0';
    return *this;
}

BigNumber::BigNumber(const BigNumber & bg)
{
    LICZBA++;
    n = bg.n;
    czy_minus = bg.czy_minus;
    number = new char[n + 1];
    for (int i = 0; i < n; i++)
        number[i] = bg.number[i];
    number[n] = '\0';
}

//definicje klasy MyOwnDataStructure

MyOwnDataStructure::MyOwnDataStructure()
{
    liczby = new BigNumber * [BigNumber::LICZBA];
}

MyOwnDataStructure::~MyOwnDataStructure()
{
    for (int i = 0; i < BigNumber::LICZBA; i++)
        delete [] liczby[i];
    delete [] liczby;
}

void MyOwnDataStructure::setter(BigNumber arr[], int x)
{
    for (int i = 0; i < x; i++)
    {
        if (i == 0)
            liczby[i] = arr;
        else
            liczby[i] = &arr[i];
    }
}

void MyOwnDataStructure::show()
{
    for (int i = 0; i < BigNumber::LICZBA; i++)
        liczby[i]->show_number();
}

void MyOwnDataStructure::minimum()
{
    int licznik = 0;
    for (int i = 0; i < BigNumber::LICZBA; i++)
    {
        if (liczby[i]->czy_minus == false)
            licznik++;
    }
    if (licznik == BigNumber::LICZBA)
    {
        int potencjalne_minimum = liczby[0]->how_many_digit();
        for (int i = 1; i < BigNumber::LICZBA; i++)
        {
            if (potencjalne_minimum > liczby[i]->how_many_digit())
                potencjalne_minimum = liczby[i]->how_many_digit();
        }
        int finalne_minimum;
        int regulator = 0;
        for (int i = 0; i < BigNumber::LICZBA; i++)
        {
            if (liczby[i]->how_many_digit() == potencjalne_minimum)
            {
                if (regulator == 0)
                {
                    finalne_minimum = i;
                    regulator++;
                }
                else
                {
                    int r = 0;
                    if ((int)liczby[finalne_minimum]->zwracanie_cyferki(r) > (int)liczby[i]->zwracanie_cyferki(r))
                            finalne_minimum = i;
                    else if ((int)liczby[finalne_minimum]->zwracanie_cyferki(r) == (int)liczby[i]->zwracanie_cyferki(r))
                    {
                        while (r != potencjalne_minimum)
                        {
                            r++;
                            if ((int)liczby[finalne_minimum]->zwracanie_cyferki(r) > (int)liczby[i]->zwracanie_cyferki(r))
                            {
                                finalne_minimum = i;
                                break;
                            }
                            else if ((int)liczby[finalne_minimum]->zwracanie_cyferki(r) < (int)liczby[i]->zwracanie_cyferki(r))
                                break;
                        }
                    }
                }
            }
        }
        liczby[finalne_minimum]->show_number();
    }
    else
    {
        if (licznik == (BigNumber::LICZBA - 1))
        {
            for (int i = 0; i < BigNumber::LICZBA; i++)
            {
                if (liczby[i]->czy_minus == true)
                    liczby[i]->show_number();
            }
        }
        else
        {
            int potencjalne_minimum;
            int finalne_minimum;
            int regulator = 0;
            for (int i = 0; i < BigNumber::LICZBA; i++)
            {
                if (liczby[i]->czy_minus == true)
                {
                    if (regulator == 0)
                    {
                        potencjalne_minimum = liczby[i]->how_many_digit();
                        finalne_minimum = i;
                        regulator++;
                    }
                    else
                    {
                        if (potencjalne_minimum < liczby[i]->how_many_digit())
                        {
                            potencjalne_minimum = liczby[i]->how_many_digit();
                            finalne_minimum = i;
                        }
                        else if (potencjalne_minimum == liczby[i]->how_many_digit())
                        {
                            int r = 1;
                            if ((int)liczby[finalne_minimum]->zwracanie_cyferki(r) < (int)liczby[i]->zwracanie_cyferki(r))
                                finalne_minimum = i;
                            else if ((int)liczby[finalne_minimum]->zwracanie_cyferki(r) == (int)liczby[i]->zwracanie_cyferki(r))
                            {
                                while (r != potencjalne_minimum)
                                {
                                    r++;
                                    if ((int)liczby[finalne_minimum]->zwracanie_cyferki(r) < (int)liczby[i]->zwracanie_cyferki(r))
                                    {
                                        finalne_minimum = i;
                                        break;
                                    }
                                    else if ((int)liczby[finalne_minimum]->zwracanie_cyferki(r) > (int)liczby[i]->zwracanie_cyferki(r))
                                        break;
                                }
                            }
                        }
                    }
                }
            }
            liczby[finalne_minimum]->show_number();
        }
    }
}

void MyOwnDataStructure::maximum()
{
    int licznik = 0;
    for (int i = 0; i < BigNumber::LICZBA; i++)
    {
        if (liczby[i]->czy_minus == true)
            licznik++;
    }
    if (licznik == BigNumber::LICZBA)
    {
        int potencjalne_maximum = liczby[0]->how_many_digit();
        for (int i = 1; i < BigNumber::LICZBA; i++)
        {
            if (potencjalne_maximum > liczby[i]->how_many_digit())
                potencjalne_maximum = liczby[i]->how_many_digit();
        }
        int finalne_maximum;
        int regulator = 0;
        for (int i = 0; i < BigNumber::LICZBA; i++)
        {
            if (liczby[i]->how_many_digit() == potencjalne_maximum)
            {
                if (regulator == 0)
                {
                    finalne_maximum = i;
                    regulator++;
                }
                else
                {
                    int r = 1;
                    if ((int)liczby[finalne_maximum]->zwracanie_cyferki(r) > (int)liczby[i]->zwracanie_cyferki(r))
                            finalne_maximum = i;
                    else if ((int)liczby[finalne_maximum]->zwracanie_cyferki(r) == (int)liczby[i]->zwracanie_cyferki(r))
                    {
                        while (r != potencjalne_maximum)
                        {
                            r++;
                            if ((int)liczby[finalne_maximum]->zwracanie_cyferki(r) > (int)liczby[i]->zwracanie_cyferki(r))
                            {
                                finalne_maximum = i;
                                break;
                            }
                            else if ((int)liczby[finalne_maximum]->zwracanie_cyferki(r) < (int)liczby[i]->zwracanie_cyferki(r))
                                break;
                        }
                    }
                }
            }
        }
        liczby[finalne_maximum]->show_number();
    }
    else
    {
        if (licznik == (BigNumber::LICZBA - 1))
        {
            for (int i = 0; i < BigNumber::LICZBA; i++)
            {
                if (liczby[i]->czy_minus == false)
                    liczby[i]->show_number();
            }
        }
        else
        {
            int potencjalne_maximum;
            int finalne_maximum;
            int regulator = 0;
            for (int i = 0; i < BigNumber::LICZBA; i++)
            {
                if (liczby[i]->czy_minus == false)
                {
                    if (regulator == 0)
                    {
                        potencjalne_maximum = liczby[i]->how_many_digit();
                        finalne_maximum = i;
                        regulator++;
                    }
                    else
                    {
                        if (potencjalne_maximum < liczby[i]->how_many_digit())
                        {
                            potencjalne_maximum = liczby[i]->how_many_digit();
                            finalne_maximum = i;
                        }
                        else if (potencjalne_maximum == liczby[i]->how_many_digit())
                        {
                            int r = 0;
                            if ((int)liczby[finalne_maximum]->zwracanie_cyferki(r) < (int)liczby[i]->zwracanie_cyferki(r))
                                finalne_maximum = i;
                            else if ((int)liczby[finalne_maximum]->zwracanie_cyferki(r) == (int)liczby[i]->zwracanie_cyferki(r))
                            {
                                while (r != potencjalne_maximum)
                                {
                                    r++;
                                    if ((int)liczby[finalne_maximum]->zwracanie_cyferki(r) < (int)liczby[i]->zwracanie_cyferki(r))
                                    {
                                        finalne_maximum = i;
                                        break;
                                    }
                                    else if ((int)liczby[finalne_maximum]->zwracanie_cyferki(r) > (int)liczby[i]->zwracanie_cyferki(r))
                                        break;
                                }
                            }
                        }
                    }
                }
            }
            liczby[finalne_maximum]->show_number();
        }
    }
}