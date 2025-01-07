#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

class Transport{
protected:
    char destinacija[20];
    int cena;
    int rastojanie;
public:
    Transport(){}
    Transport(char *destinacija,int cena,int rastojanie){
        strcpy(this->destinacija,destinacija);
        this->cena = cena;
        this->rastojanie = rastojanie;
    }
    bool operator<(const Transport &t){
        return rastojanie<t.rastojanie;
    }
    char* getDestinacija(){
        return destinacija;
    }
    int getRastojanie(){
        return rastojanie;
    }
    virtual void print(){
        cout<<destinacija<<" "<<rastojanie<<" "<<cenaTransport()<<endl;
    }
    virtual float cenaTransport() = 0;
    virtual ~Transport(){}
};

class AvtomobilTransport : public Transport{
private:
    bool shofer;
public:
    AvtomobilTransport() : Transport(){}
    AvtomobilTransport(char *destinacija,int cena,int rastojanie,bool shofer) : Transport(destinacija,cena,rastojanie){
        this-> shofer = shofer;
    }
    float cenaTransport(){
        if(shofer)
            return cena+cena*20/100;
        else
            return cena;
    }
    bool getShofer(){
        return shofer;
    }
    ~AvtomobilTransport(){}
};
class KombeTransport : public Transport{
private:
    int lugje;
public:
    KombeTransport() : Transport(){}
    KombeTransport(char *destinacija,int cena,int rastojanie,int lugje) : Transport(destinacija,cena,rastojanie){
        this-> lugje = lugje;
    }
    float cenaTransport(){
        return cena-lugje*200;
    }
    ~KombeTransport(){}
};

void pecatiPoloshiPonudi(Transport **ponudi, int n, Transport &T){
    Transport **poskapiPonudi = new Transport *[n];//nova niza
    int brojac=0;//brojac za novata niza

    for(int i=0;i<n;i++){//ako e poskapo go dodavame vo novata niza
        if(ponudi[i]->cenaTransport()>T.cenaTransport()){
            poskapiPonudi[brojac++] = ponudi[i];
        }
    }

    sort(poskapiPonudi, poskapiPonudi+brojac, [](Transport *a,Transport *b){
        return *a<*b;
    });

    for(int i=0;i<brojac;i++){//ja pecatime novata niza
        poskapiPonudi[i]->print();
    }
}

int main(){

    char destinacija[20];
    int tip,cena,rastojanie,lugje;
    bool shofer;
    int n;
    cin>>n;
    Transport  **ponudi;
    ponudi=new Transport *[n];

    for (int i=0;i<n;i++){

        cin>>tip>>destinacija>>cena>>rastojanie;
        if (tip==1) {
            cin>>shofer;
            ponudi[i]=new AvtomobilTransport(destinacija,cena,rastojanie,shofer);

        }
        else {
            cin>>lugje;
            ponudi[i]=new KombeTransport(destinacija,cena,rastojanie,lugje);
        }


    }

    AvtomobilTransport nov("Ohrid",2000,600,false);
    pecatiPoloshiPonudi(ponudi,n,nov);

    for (int i=0;i<n;i++) delete ponudi[i];
    delete [] ponudi;
    return 0;
}
