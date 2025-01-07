//
// Created by milen on 27/03/2024.
//
#include <iostream>
using namespace std;

struct Skilift{
    char ime[15];
    int max;
    bool raboti;
};
struct SkiCenter{
    char naziv[20];
    char drzava[20];
    Skilift sl[20];
    int n;
};
void najgolemKapacitet(SkiCenter *sc,int n){
    int maxsum=0,maxskilift=0,indexsc=0;
    for(int i=0;i<n;i++){
        int sum=0,skilift=0;
        maxskilift=sc[i].n;
        for(int j=0;j<sc[i].n;j++) {
            if (sc[i].sl[j].raboti || sum==maxsum && skilift > maxskilift) {
                sum += sc[i].sl[j].max;
                skilift += sc[i].n;
                indexsc = i;
                maxsum = sum;
                maxskilift=skilift;
            }
        }
    }
    cout<<sc[indexsc].naziv<<"\n"<<sc[indexsc].drzava<<"\n"<<maxsum<<endl;
}
int main(){
    int n;
    cin>>n;
    SkiCenter sc[n];
    for(int i=0;i<n;i++){
        cin>>sc[i].naziv>>sc[i].drzava>>sc[i].n;
        for(int j=0;j<sc[i].n;j++){
            cin>>sc[i].sl[j].ime>>sc[i].sl[j].max>>sc[i].sl[j].raboti;
        }
    }
    najgolemKapacitet(sc,n);
}