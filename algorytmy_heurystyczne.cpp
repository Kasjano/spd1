#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Zadanie{
public:
    int nr;  //nr zadania
    int pj;  // czas wykonywania
    int rj;  // czas dostępu
    int qj;  // czas stygnięcia
    int rozpoczecie;  //czas rozpoczecia zadania
    Zadanie(){
        pj=0;
        rj=0;
        qj=0;
    }
    Zadanie(int Nr, int Pj, int Rj, int Qj) : nr(Nr), pj(Pj), rj(Rj), qj(Qj){}

    bool operator<(const Zadanie& other) const {
        return nr < other.nr;
    }
};

class Problem{
public:
    int n; //liczba zadań
    vector<Zadanie> Zadania;

    //funkcja dodania zadania do listy
    void dodajZadanie(int Nr,int Pj, int Rj, int Qj) {
        Zadanie zadanie(Nr,Pj,Rj,Qj);
        Zadania.push_back(zadanie);
    }

    //posortowanie według czasu dostępu - od najmniejszego czasu dostępu
    void sortowanie(){
        sort(Zadania.begin(), Zadania.end(),[](const Zadanie& a, const Zadanie& b) {return a.rj < b.rj;});
    }

    //sortowanie według czasu stygnięcia - od największego czasu stygnięcia
    void sortowanie2(){
        sort(Zadania.begin(), Zadania.end(),[](const Zadanie& a, const Zadanie& b) {return a.qj > b.qj;});
    }

    void sortowanie3(){
        sort(Zadania.begin(), Zadania.end(),[](const Zadanie& a, const Zadanie& b) {return a.pj > b.pj;});
    }

    void WypiszUszeregowanie(){
        for (const auto& obiekt : Zadania) {
            cout<< obiekt.nr << " ";
        }
        cout << endl;
    }
    
    void ZliczenieCzasuWykonania(){
        int czas_wykonania=0;
        for(int i=0;i<n;i++){
            if(Zadania[i].rj>czas_wykonania){
                czas_wykonania=Zadania[i].rj;
            }
            Zadania[i].rozpoczecie=czas_wykonania;
            czas_wykonania=czas_wykonania+Zadania[i].pj;
        }
        czas_wykonania=czas_wykonania+Zadania[n-1].qj;
        for(int i=0;i<n;i++){
            //cout << "czas rozpoczecia nr " << i << " " << Zadania[i].rozpoczecie << endl;
            if(Zadania[i].rozpoczecie+Zadania[i].pj+Zadania[i].qj>czas_wykonania)
            czas_wykonania=Zadania[i].rozpoczecie+Zadania[i].pj+Zadania[i].qj;
        }
        cout << "Czas wykonania " << czas_wykonania <<endl;
    }

    // Wyświetlanie elementów wektora
    void wypiszWektor() {
        //cout << "Elementy wektora:" << endl;
        for (const auto& obiekt : Zadania) {
            cout << "nr" << obiekt.nr << " pj:" << obiekt.pj << " rj:" << obiekt.rj << " qj:" << obiekt.qj <<endl;
        }
    }
};

class Rozwiazanie{
public:
    int kryterium;
    vector<int> uszeregowanie;
};

int main(int argc, char *argv[]) {
    Problem problem;
    Zadanie zadanie;
    int Rozpoczecie=0;
    char linia[200];
    char *nazwa=argv[1];
    int nr=1;

    FILE *dane = fopen(nazwa, "r");
    if (!dane) {
        printf("Nie udalo sie otworzyc pliku");
        return 1;
    }

    while (fgets(linia,200,dane)!=NULL){
        sscanf(linia,"%d", &problem.n);
        while(fgets(linia, 200, dane) != NULL && sscanf(linia,"%d %d %d",&zadanie.rj,&zadanie.pj,&zadanie.qj)==3){
            //cout << zadanie.rj <<zadanie.pj << zadanie.qj << endl;
            problem.dodajZadanie(nr,zadanie.pj,zadanie.rj,zadanie.qj);
            nr++;
        }   
    }

    cout << "Oto wczytany wektor zadan" << endl;
    problem.wypiszWektor();
    problem.sortowanie();
    cout << endl << "Uszeregowanie wedlug rj: ";
    problem.WypiszUszeregowanie();
    problem.ZliczenieCzasuWykonania();
    problem.sortowanie2();
    cout << endl << "Uszeregowanie wedlug qj: ";
    problem.WypiszUszeregowanie();
    problem.ZliczenieCzasuWykonania();
    problem.sortowanie3();
    cout << endl << "Uszeregowanie dla algorytmu konstrukcyjnego: ";
    problem.WypiszUszeregowanie();
    problem.ZliczenieCzasuWykonania();
    return 0;
}
