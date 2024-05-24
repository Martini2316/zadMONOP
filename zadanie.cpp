#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Pole {
public:
    string nazwa;
    Pole(string n) : nazwa(n) {}
    virtual void informacje() {
        cout << "Pole: " << nazwa << endl;
    }
    void virtual akcja(class Gracz* gracz) = 0;
};

class Nieruchomosc : public Pole {
public:
    int kosztZakupu;
    int oplata;
    int kosztDomu;
    int kosztHotelu;
    Nieruchomosc(string n, int k, int o, int kd, int kh) : Pole(n), kosztZakupu(k), oplata(o), kosztDomu(kd), kosztHotelu(kh) {}
    void informacje() {
        cout << "Nieruchomosc: " << nazwa << ", Koszt zakupu: " << kosztZakupu << ", Koszt domu: " << kosztDomu << ", Koszt hotelu: " << kosztHotelu << ", Oplata: " << oplata << endl;
    }
    void akcja(class Gracz* gracz);
};

class Szansa : public Pole {
public:
    Szansa(string n) : Pole(n) {}
    void informacje() {
        cout << "Szansa: " << nazwa << endl;
    }
    void akcja(class Gracz* gracz);
};

class Ryzyko : public Pole {
public:
    Ryzyko(string n) : Pole(n) {}
    void informacje() {
        cout << "Ryzyko: " << nazwa << endl;
    }
    void akcja(class Gracz* gracz);
};

class Bankier {
public:
    void pobierzOplate(Nieruchomosc* nieruchomosc, int kwota) {
        cout << "Pobieram oplate " << kwota << " za postoj na nieruchomosci: " << nieruchomosc->nazwa << endl;
    }
};

class Gracz {
public:
    string nazwa;
    int pieniadze;
    vector<Pole*> nieruchomosci;

    Gracz(string n, int p) : nazwa(n), pieniadze(p) {}

    void kupNieruchomosc(Nieruchomosc* nieruchomosc) {
        if (pieniadze >= nieruchomosc->kosztZakupu) {
            nieruchomosci.push_back(nieruchomosc);
            pieniadze -= nieruchomosc->kosztZakupu;
            cout << "Gracz " << nazwa << " kupil nieruchomosc: " << nieruchomosc->nazwa << endl;
        } else {
            cout << "Gracz " << nazwa << " nie ma wystarczajaco pieniedzy na zakup nieruchomosci: " << nieruchomosc->nazwa << endl;
        }
    }

    void pokazNieruchomosci() {
        cout << "Nieruchomosci gracza " << nazwa << ":" << endl;
        for (int i = 0; i < nieruchomosci.size(); i++) {
            nieruchomosci[i]->informacje();
        }
    }

    void trafNaPole(Pole* pole) {
        cout << "Gracz " << nazwa << " trafia na pole: " << pole->nazwa << endl;
        pole->akcja(this);
    }
};

void Nieruchomosc::akcja(Gracz* gracz) {
    cout << "Gracz " << gracz->nazwa << " stoi na nieruchomosci: " << nazwa << " i placi oplata: " << oplata << endl;
    gracz->pieniadze -= oplata;
}

void Szansa::akcja(Gracz* gracz) {
    int kwota = rand() % 200 + 1;
    gracz->pieniadze += kwota;
    cout << "Gracz " << gracz->nazwa << " otrzymuje " << kwota << " na polu Szansa!" << endl;
}

void Ryzyko::akcja(Gracz* gracz) {
    int kwota = rand() % 200 + 1;
    gracz->pieniadze -= kwota;
    cout << "Gracz " << gracz->nazwa << " traci " << kwota << " na polu Ryzyko!" << endl;
}

int main() {
    srand(time(0));

    Nieruchomosc n1("Kamienica", 500, 50, 100, 500);

    Nieruchomosc n2("Willa", 400, 40, 80, 400);

    Nieruchomosc n3("SUPER DROGA NIERUCHOMOSC", 1500, 40, 80, 400);

    Nieruchomosc n4("SUPER Tania NIERUCHOMOSC", 200, 40, 80, 400);


    Szansa s1("Szansa");
    Ryzyko r1("Ryzyko");

    Gracz gracz1("Jan", 1500);
    Gracz gracz2("Anna", 1000);

    cout << "Stan konta gracza " << gracz1.nazwa << ": " << gracz1.pieniadze << " zl" << endl;
    cout << "Stan konta gracza " << gracz2.nazwa << ": " << gracz2.pieniadze << " zl" << endl;

    cout << "\n";
    gracz1.kupNieruchomosc(&n1);
    cout << "\n";
    gracz1.pokazNieruchomosci();
    cout << "\n";

    gracz2.kupNieruchomosc(&n2);
    cout << "\n";
    gracz2.kupNieruchomosc(&n3);
    cout << "\n";
    gracz2.kupNieruchomosc(&n4);
    cout << "\n";
    gracz2.pokazNieruchomosci();
    cout << "\n";

    Bankier bankier;
    bankier.pobierzOplate(&n1, 50);
    cout << "\n";

    gracz1.trafNaPole(&r1);
    cout << "\n";

    gracz2.trafNaPole(&s1);

    cout << "\n";
    cout << "Stan konta gracza " << gracz1.nazwa << ": " << gracz1.pieniadze << " zl" << endl;
    cout << "\n";
    cout << "Stan konta gracza " << gracz2.nazwa << ": " << gracz2.pieniadze << " zl" << endl;

    return 0;
}
