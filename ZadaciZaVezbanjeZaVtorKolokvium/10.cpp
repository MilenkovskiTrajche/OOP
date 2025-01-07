#include <iostream>
#include <cstring>
#include <cstdlib>
using namespace std;

class NegativnaVrednost{

public:
    void print(){
        cout<<"Oglasot ima nevalidna vrednost za cenata i nema da bide evidentiran!"<<endl;
    }
};
class Oglas{
private:
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
public:
    Oglas(){}
    Oglas(char *naslov,char *kategorija,char *opis,float cena){
        strcpy(this->naslov,naslov);
        strcpy(this->kategorija,kategorija);
        strcpy(this->opis,opis);
        this->cena =cena;
    }
    bool operator>(const Oglas &o){
        return this->cena>o.cena;
    }
    friend ostream& operator<<(ostream &out,Oglas &o){
        out<<o.naslov<<endl;
        out<<o.opis<<endl;
        out<<o.cena<<" evra"<<endl;
        return out;
    }
    float getCena(){
        return cena;
    }
    char* getKategorija(){
        return kategorija;
    }
    ~Oglas(){}
};
class Oglasnik : public Oglas{
private:
    char naziv[50];
    Oglas *oglasi;
    int n;
public:
    Oglasnik():Oglas(){
        this->n=0;
        this->oglasi = new Oglas[n];
    }
    Oglasnik(char *naziv):Oglas(){
        strcpy(this->naziv,naziv);
        this->n=0;
        this->oglasi = new Oglas[n];
    }
    Oglasnik& operator+=( Oglas &nov){
        if(nov.getCena()<0){
            NegativnaVrednost(ng);
            ng.print();
        }
        else {
            Oglas *temp = new Oglas[n + 1];
            for (int i = 0; i < n; i++) {
                temp[i] = oglasi[i];
            }
            temp[n] = nov;
            n++;
            delete[]oglasi;
            oglasi = temp;
        }
        return *this;
    }
    friend ostream& operator<<(ostream &out,Oglasnik &ogl){
        out<<ogl.naziv<<endl;
        for(int i=0;i<ogl.n;i++){
            out<<ogl.oglasi[i]<<endl;
        }
        return out;
    }
    void oglasiOdKategorija(const char *k){
        for(int i=0;i<n;i++){
            if(strcmp(oglasi[i].getKategorija(),k)==0){
                cout<<oglasi[i]<<endl;
            }
        }
    }
    void najniskaCena(){
        float min = oglasi[0].getCena();
        int index=0;
        for(int i=0;i<n;i++){
            if(min>oglasi[i].getCena()){
                min = oglasi[i].getCena();
                index = i;
            }
        }
        cout<<oglasi[index]<<endl;
    }
    ~Oglasnik(){}

};


int main(){
    char naslov[50];
    char kategorija[30];
    char opis[100];
    float cena;
    char naziv[50];
    char k[30];
    int n;

    int tip;
    cin>>tip;

    if (tip==1){
        cout<<"-----Test Oglas & operator <<-----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o(naslov, kategorija, opis, cena);
        cout<<o;
    }
    else if (tip==2){
        cout<<"-----Test Oglas & operator > -----" <<endl;
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o1(naslov, kategorija, opis, cena);
        cin.get();
        cin.getline(naslov,49);
        cin.getline(kategorija,29);
        cin.getline(opis,99);
        cin>>cena;
        Oglas o2(naslov, kategorija, opis, cena);
        if (o1>o2) cout<<"Prviot oglas e poskap."<<endl;
        else cout<<"Prviot oglas ne e poskap."<<endl;
    }
    else if (tip==3){
        cout<<"-----Test Oglasnik, operator +=, operator << -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;
    }
    else if (tip==4){
        cout<<"-----Test oglasOdKategorija -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

    }
    else if (tip==5){
        cout<<"-----Test Exception -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

    }
    else if (tip==6){
        cout<<"-----Test najniskaCena -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }
    else if (tip==7){
        cout<<"-----Test All -----" <<endl ;
        cin.get();
        cin.getline(naziv,49);
        cin>>n;
        Oglasnik ogl(naziv);
        for (int i = 0; i < n; i++){
            cin.get();
            cin.getline(naslov,49);
            cin.getline(kategorija,29);
            cin.getline(opis,99);
            cin>>cena;
            Oglas o(naslov, kategorija, opis, cena);
            ogl+=o;
        }
        cout<<ogl;

        cin.get();
        cin.get();
        cin.getline(k,29);
        cout<<"Oglasi od kategorijata: " <<k<<endl;
        ogl.oglasiOdKategorija(k);

        cout<<"Oglas so najniska cena:"<<endl;
        ogl.najniskaCena();

    }

    return 0;
}
