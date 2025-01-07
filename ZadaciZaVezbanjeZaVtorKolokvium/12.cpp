#include <iostream>
#include <cstring>
using namespace std;


class InvalidProductionDate{
public:
    void print() {
        cout << "Невалидна година на производство"<<endl;
    }
};


enum tip{Mobilen,Laptop};
class Device{
private:
    char ime[100];
    tip vrsta;
    int godina;
    static int PocetniCasovi;
public:
    Device(){}
    Device(char *ime,tip tip,int godina){
        strcpy(this->ime,ime);
        this->vrsta = tip;
        this->godina = godina;
    }
    static void setPocetniCasovi(int max){
        PocetniCasovi = max;
    }
    int proverka(){
        double servis=0;
        if(godina>2015){
            servis+=1.5;
        }
        if(tip(vrsta)==1){
            servis+2;
        }

        return (int)servis+PocetniCasovi;
    }
    void print(){
        cout<<ime<<endl;
        if(vrsta==0){
            cout<<"Mobilen ";
            if(godina>2015){
                cout<<PocetniCasovi+2<<endl;
            }
            else{
                cout<<PocetniCasovi<<endl;
            }
        }
        else if(vrsta == 1) {
            cout << "Laptop ";
            if(godina>2015){
                cout<<PocetniCasovi+2+2<<endl;
            }
            else{
                cout<<PocetniCasovi+2<<endl;
            }
        }
    }
    friend ostream& operator<<(ostream &out,Device &d){
        d.print();
        return out;
    }
    int getGodina(){
        return godina;
    }

    ~Device(){}
};
int Device::PocetniCasovi = 1;

class MobileServis : public Device{
private:
    char naziv[50];
    Device *devices;
    int n;
public:
    MobileServis(): Device(){
        this->n=0;
        this->devices = new Device[n];
    }
    MobileServis(char *naziv):Device(){
        strcpy(this->naziv,naziv);
        this->n=0;
        this->devices = new Device[n];
    }
    MobileServis(const MobileServis &ms):Device(ms){
        strcpy(this->naziv,ms.naziv);
        this->n=ms.n;
        this->devices = new Device[ms.n];
        for(int i=0;i<ms.n;i++){
            this->devices[i] = ms.devices[i];
        }
    }
    MobileServis& operator=(const MobileServis &ms){
        if(this!=&ms){
            delete []devices;
            strcpy(this->naziv, ms.naziv);
            this->n = ms.n;
            this->devices = new Device[ms.n];
            for (int i = 0; i < ms.n; i++) {
                this->devices[i] = ms.devices[i];
            }
        }
        return *this;
    }

    MobileServis& operator+=(Device &nov){
        if(nov.getGodina()<=2019 && nov.getGodina()>=2000){
            Device *temp = new Device[n+1];
            for(int i=0;i<n;i++){
                temp[i] = devices[i];
            }
            temp[n] = nov;
            delete []devices;
            n++;
            devices = temp;
        }
        else{
            InvalidProductionDate(s);
            s.print();
        }
        return *this;
    }
    void pecatiCasovi(){
        cout<<"Ime: "<<naziv<<endl;
        for(int i=0;i<n;i++){
            devices[i].print();
        }
    }
    ~MobileServis(){
        delete []devices;
    }
};

int main()
{
    int testCase;
    cin >> testCase;
    char ime[100];
    int tipDevice;
    int godina;
    int n;
    Device devices[50];
    if (testCase == 1){
        cout << "===== Testiranje na klasite ======" << endl;
        cin >> ime;
        cin >> tipDevice;
        cin >> godina;
        Device ig(ime,(tip)tipDevice,godina);
        cin>>ime;
        MobileServis t(ime);
        cout<<ig;
    }
    if (testCase == 2){
        cout << "===== Testiranje na operatorot += ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 3){
        cout << "===== Testiranje na isklucoci ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        t.pecatiCasovi();
    }
    if (testCase == 4){
        cout <<"===== Testiranje na konstruktori ======"<<endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }
    if (testCase == 5){
        cout << "===== Testiranje na static clenovi ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);

            t+=tmp;
        }
        t.pecatiCasovi();
        cout << "===== Promena na static clenovi ======" << endl;
        Device::setPocetniCasovi(2);
        t.pecatiCasovi();
    }

    if (testCase == 6){
        cout << "===== Testiranje na kompletna funkcionalnost ======" << endl;
        cin>>ime;
        cin >> n;
        MobileServis t(ime);
        for(int i=0;i<n;i++)
        {
            cin >> ime;
            cin >> tipDevice;
            cin >> godina;
            Device tmp(ime,(tip)tipDevice,godina);
            t+=tmp;
        }
        Device::setPocetniCasovi(3);
        MobileServis t2 = t;
        t2.pecatiCasovi();
    }

    return 0;

}