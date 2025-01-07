#include <iostream>//istream =cin ostream cout
#include <cstring>

using namespace std;

class Vozac{
protected:
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
public:
    Vozac(){}
    Vozac(char *name,int age,int tr,bool veteran){
        strcpy(this->ime,name);
        this->vozrast = age;
        this->trki = tr;
        this->vet = veteran;
    }
    friend ostream& operator<<(ostream &out,Vozac &v){
        out<<v.ime<<endl;
        out<<v.vozrast<<endl;
        out<<v.trki<<endl;
        if(v.vet)
            out<<"VETERAN"<<endl;
        return out;
    }
    virtual float zarabotuvacka() = 0;
    virtual float danok() = 0;

//    bool operator==(Vozac *v){
//        return this->zarabotuvacka()==v->zarabotuvacka();
//    }
    virtual ~Vozac(){}

};

class Avtomobilist : public Vozac{
private:
    float cena_avto;
public:
    Avtomobilist() : Vozac(){}
    Avtomobilist(char *name,int age,int tr,bool veteran,
                 float price) : Vozac(name,age,tr,veteran){
        this->cena_avto = price;
    }
    float zarabotuvacka(){
        return cena_avto/5;
    }
    float danok(){
        float osnovna = zarabotuvacka();//11000
        if(trki>10){
            osnovna=osnovna*15/100;//11000+ 11000*15/100=
        }
        else{
            osnovna=osnovna*10/100;
        }
        return osnovna;
    }
    ~Avtomobilist(){}
};

class Motociklist : public Vozac{
private:
    int mokjnost;
public:
    Motociklist() : Vozac(){}
    Motociklist(char *name,int age,int tr,bool veteran,
                 int power) : Vozac(name,age,tr,veteran){
        this->mokjnost = power;
    }

    float zarabotuvacka(){
        return mokjnost*20;
    }
    float danok(){
        float osnovna = zarabotuvacka();
        if(vet){
            osnovna=osnovna*25/100;
        }
        else{
            osnovna=osnovna*20/100;
        }
        return osnovna;
    }
    ~Motociklist(){}
};

int soIstaZarabotuvachka(Vozac **v,int n,Vozac *vozac){
int br=0;
    for(int i=0;i<n;i++){
        Vozac *av = dynamic_cast<Avtomobilist*>(v[i]);
        Vozac *vz = dynamic_cast<Motociklist *>(v[i]);

        if(av!=0){
            if(v[i]->zarabotuvacka() == vozac->zarabotuvacka()){
                br++;
            }
        }
        if(vz!=0){
            if (v[i]->zarabotuvacka() == vozac->zarabotuvacka()) {
                br++;
            }
        }
    }
        return br;
}

int main() {
    int n, x;
    cin >> n >> x;
    Vozac **v = new Vozac*[n];
    char ime[100];
    int vozrast;
    int trki;
    bool vet;
    for(int i = 0; i < n; ++i) {
        cin >> ime >> vozrast >> trki >> vet;
        if(i < x) {
            float cena_avto;
            cin >> cena_avto;
            v[i] = new Avtomobilist(ime, vozrast, trki, vet, cena_avto);
        } else {
            int mokjnost;
            cin >> mokjnost;
            v[i] = new Motociklist(ime, vozrast, trki, vet, mokjnost);
        }
    }
    cout << "=== DANOK ===" << endl;
    for(int i = 0; i < n; ++i) {
        cout << *v[i];
        cout << v[i]->danok() << endl;
    }
    cin >> ime >> vozrast >> trki >> vet;
    int mokjnost;
    cin >> mokjnost;
    Vozac *vx = new Motociklist(ime, vozrast, trki, vet, mokjnost);
    cout << "=== VOZAC X ===" << endl;
    cout << *vx;
    cout << "=== SO ISTA ZARABOTUVACKA KAKO VOZAC X ===" << endl;
    cout << soIstaZarabotuvachka(v, n, vx);
    for(int i = 0; i < n; ++i) {
        delete v[i];
    }
    delete [] v;
    delete vx;
    return 0;
}