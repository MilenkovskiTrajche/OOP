#include<iostream>
#include<cstring>
using namespace std;

class Patnik{

private:
    char ime[100];
    int klasa;
    bool velosiped;
public:
    Patnik(){};
    Patnik(char *ime,int klasa,bool velosiped){
        strcpy(this->ime,ime);
        this->klasa = klasa;
        this->velosiped = velosiped;
    }
    friend ostream& operator<<(ostream &out,Patnik &p){
        out<<p.ime<<endl;
        out<<p.klasa<<endl;
        if(p.velosiped){
            out<<"1"<<endl;
        }else{
            out<<"0"<<endl;
        }
        return out;
    }

    int getKlasa() const {
        return klasa;
    }

    bool isVelosiped() const {
        return velosiped;
    }
};

class Voz{

private:
    char destinacija[100];
    Patnik *p;
    int n;
    int maxV;
    int brV;
public:
    Voz(){
        this->n=0;
        this->p = new Patnik[n];
        this->brV=0;
    }
    Voz(char* destinacija,int maxV){
        strcpy(this->destinacija,destinacija);
        this->maxV = maxV;
        this->n = 0;
        this->p = new Patnik[n];
        this->brV=0;
    }

    Voz& operator+=(Patnik &nov) {
        if (nov.isVelosiped()) {
            if (brV + 1 > maxV) {
                return *this;
            }
            brV++;
        }
        Patnik *temp = new Patnik[n + 1];
        for (int i = 0; i < n; i++) {
            temp[i] = p[i];
        }
        temp[n] = nov;
        delete[] p;
        p = temp;
        n++;

        return *this;
    }

    friend ostream& operator<<(ostream &out,Voz &v){
        out<<v.destinacija<<endl;
        for(int i=0;i<v.n;i++){
            out<<v.p[i]<<endl;
        }
        return out;
    }

    void patniciNemaMesto(){
        int prvaKlasa=0,vtoraKlasa=0;
        for(int i=0;i<n;i++){
            if(n<=maxV){
                break;
            }
            if(p[i].getKlasa() == 1 && p[i].isVelosiped()){
                if(brV+1> maxV){
                    return;
                }else{
                    prvaKlasa++;
                }
            }
            if(p[i].getKlasa() == 2 && p[i].isVelosiped()){
                if(brV+1 > maxV){
                    return;
                }else{
                    vtoraKlasa++;
                }
            }
        }

        cout<<"Brojot na patnici od 1-va klasa koi ostanale bez mesto e: "<<prvaKlasa<<endl;
        cout<<"Brojot na patnici od 2-ra klasa koi ostanale bez mesto e: "<<vtoraKlasa<<endl;

    }

};


int main()
{
    Patnik p;
    char ime[100], destinacija[100];
    int n;
    bool velosiped;
    int klasa;
    int maxv;
    cin >> destinacija >> maxv;
    cin >> n;
    Voz v(destinacija, maxv);
    //cout<<v<<endl;
    for (int i = 0; i < n; i++){
        cin >> ime >> klasa >> velosiped;
        Patnik p1(ime, klasa, velosiped);
        //cout<<p<<endl;
        v += p1;
    }
    cout << v;
    v.patniciNemaMesto();

    return 0;
}
