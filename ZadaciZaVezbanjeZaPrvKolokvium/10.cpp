//
// Created by milen on 27/03/2024.
//

#include <iostream>
using namespace std;
struct Igrac{
    char ime[15];
    int lvl;
    int poeni;
};
struct KompjuterskaIgra{
    char naziv[20];
    Igrac i[30];
    int n;
};

void najdobarIgrac(KompjuterskaIgra *ki, int n) {
    int popular = 0, maxpoeni = 0, maxlvl = 0, index = 0, indexI = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < ki[i].n; j++) {
            int poeni = ki[i].i[j].poeni; //gi sobirame poenite
            int lvl = ki[i].i[j].lvl; //gi sobirame lvl
            if (poeni > maxpoeni || (poeni == maxpoeni && lvl > maxlvl)) {
                popular = ki[i].n;
                maxpoeni = poeni;
                maxlvl = lvl;
                index = i;
                indexI = j;
            }
        }
    }

    cout << "Najdobar igrac e igracot so korisnicko ime " << ki[index].i[indexI].ime
         << " koj ja igra igrata " << ki[index].naziv << endl;
}

int main(){
    KompjuterskaIgra ki[50];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>ki[i].naziv>>ki[i].n;
        for(int j=0;j<ki[i].n;j++){
            cin>>ki[i].i[j].ime>>ki[i].i[j].lvl>>ki[i].i[j].poeni;
        }
    }
    najdobarIgrac(ki,n);
}