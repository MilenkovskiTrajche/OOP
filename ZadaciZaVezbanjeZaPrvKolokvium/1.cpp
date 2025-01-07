#include <iostream>
#include <cstring>
using namespace std;
enum tip{POP,ROCK,RAP};

class Pesna{
    char *ime;
    int min;
    tip kojtip;
public:
    Pesna(){
        this->ime = new char[0];
    }
    Pesna(char *ime,int min,tip kojtip){
        this->ime = new char[strlen(ime)+1];
        strcpy(this->ime,ime);
        this->min = min;
        this->kojtip = kojtip;
    }
    Pesna(const Pesna &p){
        this->ime = new char[strlen(p.ime)+1];
        strcpy(this->ime,p.ime);
        this->min = p.min;
        this->kojtip = p.kojtip;
    }
    Pesna& operator=(const Pesna &p) {
        if (this != &p) {
            delete []ime;
            this->ime = new char[strlen(p.ime) + 1];
            strcpy(this->ime, p.ime);
            this->min = p.min;
            this->kojtip = p.kojtip;
        }
        return *this;
    }
    void pecati(){
        cout<<"\""<<ime<<"\""<<"-"<<min<<"min"<<endl;
    }
    tip getTip(){
        return kojtip;
    }
    int getMin(){
        return min;
    }
    ~Pesna(){
        delete []ime;
    }
};
class CD{
    Pesna p[10];
    int brpesni;
    int maxmin;
public:
    CD(){}
    CD(int maxmin){
        this->maxmin = maxmin;
        this->brpesni = 0;
    }
    CD(const CD &cd){
        this->maxmin = cd.maxmin;
        this->brpesni = 0;

    }
    CD& operator=(const CD &cd){
        if(this!=&cd) {
            this->maxmin = cd.maxmin;
            this->brpesni = 0;
        }
        return *this;
    }
    int novaVreme(int index){
        p[index].getMin();
    }
    int MAXvreme(){
        int sum=0;
        for(int i=0;i<brpesni;i++){
            sum += p[i].getMin();
        }
        return sum;
    }
    void dodadiPesna(Pesna &nova){
        if (brpesni < 10 && nova.getMin()+MAXvreme()<maxmin) {
            p[brpesni++] = nova;
        }
    }
    void pecatiPesniPoTip(tip kojtip){
        for(int i=0;i<brpesni;i++){
            if(p[i].getTip() == kojtip){
                p[i].pecati();
            }
        }
    }
    int getBroj(){
        return brpesni;
    }
    Pesna& getPesna(int index){
        return p[index];
    }

    ~CD(){}
};

int main() {
    // se testira zadacata modularno
    int testCase;
    cin >> testCase;

    int n, minuti, kojtip;
    char ime[50];

    if(testCase == 1) {
        cout << "===== Testiranje na klasata Pesna ======" << endl;
        cin >> ime;
        cin >> minuti;
        cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
        Pesna p(ime,minuti,(tip)kojtip);
        p.pecati();
    } else if(testCase == 2) {
        cout << "===== Testiranje na klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<n; i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 3) {
        cout << "===== Testiranje na metodot dodadiPesna() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        for (int i=0; i<omileno.getBroj(); i++)
            (omileno.getPesna(i)).pecati();
    }
    else if(testCase == 4) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }
    else if(testCase == 5) {
        cout << "===== Testiranje na metodot pecatiPesniPoTip() od klasata CD ======" << endl;
        CD omileno(20);
        cin>>n;
        for (int i=0;i<n;i++){
            cin >> ime;
            cin >> minuti;
            cin >> kojtip; //se vnesuva 0 za POP,1 za RAP i 2 za ROK
            Pesna p(ime,minuti,(tip)kojtip);
            omileno.dodadiPesna(p);
        }
        cin>>kojtip;
        omileno.pecatiPesniPoTip((tip)kojtip);

    }

    return 0;
}