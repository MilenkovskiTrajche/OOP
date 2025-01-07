//
// Created by milen on 26/03/2024.
//
#include <iostream>
#include <limits.h>
using namespace std;

struct Laptop{
    char firma[100];
    float golemina;
    bool touch;
    int cena;

    void print(){
        cout<<firma<<" "<<golemina<<" "<<cena<<endl;
    }
};
struct ITStore{
    char naziv[100];
    char lokacija[100];
    Laptop l[100];
    int n;

    void print(){
        cout<<naziv<<" "<<lokacija<<endl;
        for(int i=0;i<n;i++){
            l[i].print();
        }
    }
};

void najeftina_ponuda(ITStore *s,int n){
    int min = INT_MAX;
    int indexs,indexl;
    for(int i=0;i<n;i++){
        for(int j=0;j<s[i].n;j++){
            if(min>s[i].l[j].cena && s[i].l[j].touch){
                min = s[i].l[j].cena;
                indexl=j;
                indexs=i;
            }
        }
    }
    cout<<"Najeftina ponuda ima prodavnicata:\n"<<s[indexs].naziv<<" "<<s[indexs].lokacija<<endl;
    cout<<"Najniskata cena iznesuva: "<<s[indexs].l[indexl].cena<<endl;
}

int main() {
    ITStore s[100];
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
        cin>>s[i].naziv>>s[i].lokacija>>s[i].n;
        for(int j=0;j<s[i].n;j++){
            cin>>s[i].l[j].firma>>s[i].l[j].golemina>>s[i].l[j].touch>>s[i].l[j].cena;
        }
    }
    for(int i=0;i<n;i++){
        s[i].print();
    }
    najeftina_ponuda(s, n);

    return 0;
}