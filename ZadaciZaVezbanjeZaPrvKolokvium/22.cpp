//
// Created by milen on 30/03/2024.
//
#include <iostream>
#include <cstring>
using namespace std;
struct Proizvod{
    char id[20];
    int cena;
    int brproizvodi;
};
struct Narachka{
    char naziv[15];
    Proizvod p[10];
    int brnaracki;
    int naracki[10];
};

void bubbleSort(Proizvod *p, int n) {//po azbucen redosled
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) { // Corrected loop condition
            if (strcmp(p[j].id, p[j + 1].id) > 0) {//ako e pogolem j ke javi deka e pogolemo od j+1
                Proizvod temp = p[j];//ke gi smenime
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
}
void pecatiFaktura(Narachka narachka) {
    int index = -1; 
    int vkupnaCena = 0;

    cout << "Faktura za " << narachka.naziv << endl;

    for (int i = 0; i < narachka.brnaracki; i++) {
        if (narachka.p[i].brproizvodi < narachka.naracki[i]) {
            index = i;
            break; }
    }

    if (index == -1) {
        bubbleSort(narachka.p, narachka.brnaracki);//brnaracki=n,naracka.p=Proizvod

        for (int i = 0; i < narachka.brnaracki; i++) {
            Proizvod& proizvod = narachka.p[i];
            int naracano = narachka.naracki[i];
            int cena = proizvod.cena;
            int vkupno = cena * naracano;

            cout << proizvod.id << " " << cena << " " << naracano << " " << vkupno << endl;

            proizvod.brproizvodi -= naracano;
            vkupnaCena += vkupno;
        }

        cout << "Vkupnata suma na fakturata e " << vkupnaCena << endl;
    } else {
        cout << "Fakturata ne moze da se izgotvi" << endl;
    }
}
int main(){
    Narachka narachka;
    cin>>narachka.naziv>>narachka.brnaracki;
    int i;
    for(i=0;i<narachka.brnaracki;i++){
        cin>>narachka.p[i].id>>narachka.p[i].cena>>narachka.p[i].brproizvodi;
    }
    int j;
    for(j=0;j<narachka.brnaracki;j++){
        cin>>narachka.naracki[j];
    }
    pecatiFaktura(narachka);
    return 0;
}