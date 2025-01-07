#include<iostream>
#include<string.h>
using namespace std;

class Karticka{
   protected:
       char smetka[16];
       int pin;
       bool povekjePin;
       const static int P;
   public:
   Karticka(){}
    Karticka(char* smetka,int pin){
       strcpy(this->smetka,smetka);
       this->pin=pin;
       this->povekjePin=false;
     }
     
     virtual int tezinaProbivanje()
     {
         int brCifri=0;
         int temp= pin;
         while(temp!=0)
         {
             temp = temp/10;
             brCifri++;
         }
         return brCifri;
     }
     friend ostream &operator<<(ostream &out,Karticka &k){
         out<<k.smetka<<": "<<k.tezinaProbivanje()<<endl;
         return out;
     }
     bool getDopolnitelenPin()
     {
         return povekjePin;
     }
     char *getSmetka()
     {
         return smetka;
     }
     virtual ~Karticka(){}
   
};
const int Karticka::P = 4;

class SpecijalnaKarticka  : public Karticka
{
private:
    int n;//dopolnitelni pinovi
    int *pinovi;
public:
    SpecijalnaKarticka(): Karticka()
    {
        this->n=0;
        this->pinovi = new int[0];
        this->povekjePin = true;
    }
    SpecijalnaKarticka(char* smetka,int pin) : Karticka(smetka,pin)
    {
        this->n=0;
        this->pinovi = new int[0];
        this->povekjePin = true;
    }
    SpecijalnaKarticka(const SpecijalnaKarticka &sk) : Karticka(sk)
    {
        this->n=sk.n;
        this->pinovi = new int[sk.n];
        for(int i=0;i<n;i++)
        {
            this->pinovi[i] = sk.pinovi[i];
        }
    }
    
    
    //@Override
    int tezinaProbivanje()
    {
        int osnovnaTezina = Karticka::tezinaProbivanje();
        return osnovnaTezina + n;
    }
    
    SpecijalnaKarticka& operator+=(int novPin)
    {
        if(n==Karticka::P)
        {
            cout<<"Brojot na pinovi ne smee da go nadmine dozvolenoto!"<<endl;
        }
        else
        {
            int *temp = new int[n+1];
            for(int i=0;i<n;i++)
            {
                temp[i] = pinovi[i];
            }
            temp[n] = novPin;
            n++;
            delete []pinovi;
            pinovi = temp;
        }
        return *this;
    }
    ~SpecijalnaKarticka()
    {
        delete []pinovi;
    }
};



class Banka {
private:
    char naziv[30];
    Karticka *karticki[20];
    int broj;
    static int LIMIT;
public:
    Banka(char *naziv, Karticka** karticki,int broj ){
      strcpy(this->naziv,naziv);
      for (int i=0;i<broj;i++){
        //ako kartickata ima dopolnitelni pin kodovi
        if (karticki[i]->getDopolnitelenPin()){
            this->karticki[i]=new SpecijalnaKarticka(*dynamic_cast<SpecijalnaKarticka*>(karticki[i]));
        }
        else this->karticki[i]=new Karticka(*karticki[i]);
      }
      this->broj=broj;
    }
    
    void static setLIMIT(int l)
    {
        LIMIT = l;
    }
    
    void pecatiKarticki()
    {
        cout<<"Vo bankata "<<naziv <<" moze da se probijat kartickite:"<<endl;
        for(int i=0;i<broj;i++)
        {
            if(karticki[i]->tezinaProbivanje() <=LIMIT)
            {
                cout<<*karticki[i];
            }
        }
    }
    void dodadiDopolnitelenPin(char *smetka,int novPin)
    {
        for(int i=0;i<broj;i++)
        {
            if(strcmp(karticki[i]->getSmetka(),smetka)==0)
            {
                
                //*karticki[i] +=novPin; - ova ne e dozvoleno
                
                SpecijalnaKarticka *sp = dynamic_cast<SpecijalnaKarticka*>(karticki[i]);
                if(sp!=NULL)
                {
                    *sp+=novPin;
                }
                
                break;
            }
        }
    }
    
    ~Banka(){
    for (int i=0;i<broj;i++) delete karticki[i];
    }

    
    
};
int Banka::LIMIT  = 7;


int main(){

Karticka **niza;
int n,m,pin;
char smetka[16];
bool daliDopolnitelniPin;
cin>>n;
niza=new Karticka*[n];
for (int i=0;i<n;i++){
   cin>>smetka;
   cin>>pin;
   cin>>daliDopolnitelniPin;
   if (!daliDopolnitelniPin)
    niza[i]=new Karticka(smetka,pin);
   else
    niza[i]=new SpecijalnaKarticka(smetka,pin);
}

Banka komercijalna("Komercijalna",niza,n);
for (int i=0;i<n;i++) delete niza[i];
delete [] niza;
cin>>m;
for (int i=0;i<m;i++){
   cin>>smetka>>pin;
   
   komercijalna.dodadiDopolnitelenPin(smetka,pin);
   
}

Banka::setLIMIT(5);

komercijalna.pecatiKarticki();

}
