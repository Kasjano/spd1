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

    void sprawdz_permutacje(){
        vector<Zadanie> kopia = Zadania;
        vector<int> uszeregowanie;
        for(int i=0;i<n;i++){
            uszeregowanie.push_back(kopia[i].nr);
        }

        sort(kopia.begin(), kopia.end(), [](const Zadanie& a, const Zadanie& b) { return a.nr < b.nr; });
        int najkrotszy_czas_wykonania=1000000;
        int nr=1;

        do {
            int czas_wykonania=0;
            for(int i=0;i<n;i++){
                if(kopia[i].rj>czas_wykonania){
                    czas_wykonania=kopia[i].rj;
                }
                kopia[i].rozpoczecie=czas_wykonania;
                czas_wykonania=czas_wykonania+kopia[i].pj;
            }
            czas_wykonania=czas_wykonania+kopia[n-1].qj;
            for(int i=0;i<n;i++){
                //cout << "czas rozpoczecia nr " << i << " " << Zadania[i].rozpoczecie << endl;
                if(kopia[i].rozpoczecie+kopia[i].pj+kopia[i].qj>czas_wykonania)
                czas_wykonania=kopia[i].rozpoczecie+kopia[i].pj+kopia[i].qj;
            }
            if(czas_wykonania<najkrotszy_czas_wykonania){
                najkrotszy_czas_wykonania=czas_wykonania;
                for(int i=0;i<n;i++){
                    uszeregowanie[i]=kopia[i].nr;
                }
            }

            //cout << "Permutacja nr" << nr << ": ";
            //for (int i = 0; i < n; i++) {
            //    cout << kopia[i].nr << " ";
            //}
        //cout << endl << czas_wykonania;
        nr++;
        } while (next_permutation(kopia.begin(), kopia.end()));
        cout << endl;
        cout << "Przeglad zupelny:" << endl; 
        cout << "Najkrotszy czas wykonania dla przegladu zupelnego: " << najkrotszy_czas_wykonania <<endl;
        cout << "Dla wektora zadan: ";
        for (int element : uszeregowanie) {
            cout<< element << " ";
        }
        cout << endl;
    }

    void wypiszWektor() {
        //cout << "Elementy wektora:" << endl;
        for (const auto& obiekt : Zadania) {
            cout << "nr" << obiekt.nr << " pj:" << obiekt.pj << " rj:" << obiekt.rj << " qj:" << obiekt.qj <<endl;
        }
    }
   
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
    problem.sprawdz_permutacje();
    return 0;
}
