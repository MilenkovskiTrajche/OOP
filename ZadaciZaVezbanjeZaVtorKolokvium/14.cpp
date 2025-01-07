#include <iostream>
#include <cstring>
#include <string>
#include <cctype>

using namespace std;


class SMS
{
protected:
    char tel[20];
    float cena;
public:
    SMS(){}
    SMS(char *tel,float cena)
    {
        strcpy(this->tel,tel);
        this->cena = cena;
    }
    virtual float SMS_cena() = 0;
    friend ostream& operator<<(ostream& out,SMS &s)
    {
        out<<"Tel: "<<s.tel<<" - cena: "<<s.SMS_cena()<<"den."<<endl;
        return out;
    }
    virtual ~SMS(){}
};
class RegularSMS : public SMS
{
private:
    char msg[1000];
    bool roam;
    static int rProcent;
public:
    RegularSMS(): SMS(){}
    RegularSMS(char *tel,float cena,char *msg,bool roam) : SMS(tel,cena)
    {
        strcpy(this->msg, msg);
        this->roam = roam;
    }
    static void set_rProcent(int r)
    {
        rProcent = r;
    }
    float SMS_cena()
    {
        int brPoraki = strlen(msg)/160 + 1;
        if(strlen(msg)%160==0)
            brPoraki--;
        int cenaRoam=0;
        if(roam)
        {
            cenaRoam = cena * rProcent /100;
        }
        
        return brPoraki *(cena + cenaRoam + cena*18/100);
    }
    ~RegularSMS(){}
};
int RegularSMS::rProcent = 300;

class SpecialSMS : public SMS
{
private:
    static int sProcent;
    bool hum;
public:
    SpecialSMS(): SMS(){}
    SpecialSMS(char *tel,float cena,bool hum) : SMS(tel,cena)
    {
        this->hum = hum;
    }
    static void set_sProcent(int s)
    {
        sProcent = s;
    }
    float SMS_cena()
    {
        int humCena=0;
        int ddv=0;
        if(!hum)
        {
            humCena = cena * sProcent/100;
            ddv = cena * 18/100;
        }
        return cena + humCena + ddv;
    }
    ~SpecialSMS(){}
};
int SpecialSMS::sProcent = 150;

void vkupno_SMS(SMS **poraki, int n)
{
    int r=0,s=0;
    float rVkupno=0;
    float sVkupno=0;
    for(int i=0;i<n;i++)
    {
        RegularSMS *rs = dynamic_cast<RegularSMS*>(poraki[i]);
        if(rs!=0)
        {
            rVkupno +=rs->SMS_cena();
            r++;
        }
        else
        {
            SpecialSMS *ss = dynamic_cast<SpecialSMS*>(poraki[i]);
            sVkupno+=ss->SMS_cena();
            s++;
        }
    }
    cout<<"Vkupno ima "<<r<<" regularni SMS poraki i nivnata cena e: "<<rVkupno<<endl;
    cout<<"Vkupno ima "<<s<<" specijalni SMS poraki i nivnata cena e: "<<sVkupno<<endl;
}
int main(){

    char tel[20], msg[1000];
    float cena;
    float price;
    int p;
    bool roam, hum;
    SMS  **sms;
    int n;
    int tip;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing RegularSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new RegularSMS(tel, cena, msg, roam);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 2){
        cout << "====== Testing SpecialSMS class ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i < n; i++){
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cout << "CONSTRUCTOR" << endl;
            sms[i] = new SpecialSMS(tel, cena, hum);
            cout << "OPERATOR <<" << endl;
            cout << *sms[i];
        }
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 3){
        cout << "====== Testing method vkupno_SMS() ======" << endl;
        cin >> n;
        sms = new SMS *[n];

        for (int i = 0; i<n; i++){

            cin >> tip;
            cin >> tel;
            cin >> cena;
            if (tip == 1) {

                cin.get();
                cin.getline(msg, 1000);
                cin >> roam;
                
                sms[i] = new RegularSMS(tel, cena, msg, roam);

            }
            else {
                cin >> hum;

                sms[i] = new SpecialSMS(tel, cena, hum);
            }
        }

        vkupno_SMS(sms, n);
        for (int i = 0; i<n; i++) delete sms[i];
        delete[] sms;
    }
    if (testCase == 4){
        cout << "====== Testing RegularSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            sms1 = new RegularSMS(tel, cena, msg, roam);
            cout << *sms1;
        
            cin >> tel;
            cin >> cena;
            cin.get();
            cin.getline(msg, 1000);
            cin >> roam;
            cin >> p;
            RegularSMS::set_rProcent(p);
            sms2 = new RegularSMS(tel, cena, msg, roam);
            cout << *sms2;
        
        delete sms1, sms2;
    }
    if (testCase == 5){
        cout << "====== Testing SpecialSMS class with a changed percentage======" << endl;
        SMS *sms1, *sms2;
            cin >> tel;
            cin >> cena;
            cin >> hum;
            sms1 = new SpecialSMS(tel, cena, hum);
            cout << *sms1;
        
            cin >> tel;
            cin >> cena;
            cin >> hum;
            cin >> p;
            SpecialSMS::set_sProcent(p);
            sms2 = new SpecialSMS(tel, cena, hum);
            cout << *sms2;
        
        delete sms1, sms2;
    }
    
    return 0;
}

