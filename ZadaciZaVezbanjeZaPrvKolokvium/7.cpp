//
// Created by milen on 24/03/2024.
//

#include<iostream>
#include <iomanip>
#include <limits.h>
using namespace std;


struct Vozenje{
    char ime[100];
    int min;
    float cena;
    bool popust;

    void print(){
        cout<<ime<<" "<<min<<" ";
        if (cena == static_cast<int>(cena)) { //cena-cena==0 primer 6-6 = 0// dodaj .00
            cout<<cena<<".00"<<endl;
        }
        else if(cena - static_cast<int>(cena) != 0.00){//primer 6.1//6.1 - 6 = 0.1 !=0
                cout<<cena<<"0"<<endl;
            }
        else
        cout<<setprecision(2)<<cena<<endl;
    }
};
struct ZabavenPark{
    char naziv[100];
    char lokacija[100];
    Vozenje v[100];
    int br;

    void print(){
        cout<<naziv<<" "<<lokacija<<endl;
        for(int i=0;i<br;i++){
            v[i].print();
        }
    }
};

void najdobar_park(ZabavenPark *zp,int n) {
    int vreme,brojac, brojacmax = 0;
    int maxvreme = 0, index = 0;
    for (int i = 0; i < n; i++){
        vreme = 0;// restartiraj na 0 za nareden park
        brojac = 0;
        for (int j = 0; j < zp[i].br; j++){
            if (zp[i].v[j].popust == 1) {
                brojac++;//broj na vozenja ako ima studentsku popust
            }
            vreme += zp[i].v[j].min;//sobiraj vremeto vo zabavniot park
        }//nadvor od for za vozenje
        if (brojac > brojacmax) {//vlezi vo for za zabaven park i smenigi
            brojacmax = brojac;//zacuvaj vo brojacmax -brojacot
            index = i;//zapamti i
            maxvreme = vreme;//zacuvaj vo max vreme -vremeto//zacuvajgi zosto ke se restartirat na 0
        }
        else if(brojac == brojacmax  && vreme > maxvreme)//ako se isti toj so pogolemo vreme ispecati
        {
            index = i;
            maxvreme = vreme;
        }

    }
    cout <<"Najdobar park: "<<zp[index].naziv<<" "<<zp[index].lokacija << endl;
}

int main(){
    int n;
    cin>>n;
    ZabavenPark zp[100];
    for(int i=0;i<n;i++){
        cin>>zp[i].naziv;
        cin>>zp[i].lokacija;
        cin>>zp[i].br;
        for(int j=0;j<zp[i].br;j++){
            cin>>zp[i].v[j].ime;
            cin>>zp[i].v[j].min;
            cin>>zp[i].v[j].cena;
            cin>>zp[i].v[j].popust;
        }
    }

    for(int i=0;i<n;i++){
        zp[i].print();
    }
    najdobar_park(zp,n);
    return 0;
}