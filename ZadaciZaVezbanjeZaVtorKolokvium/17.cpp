#include <iostream>
#include <cstring>
using namespace std;

class FudbalskaEkipa{
protected:
    char coach[100];
    int goals[10];
public:
    FudbalskaEkipa(){}
    FudbalskaEkipa(char *coach, int* goals){
        strcpy(this->coach,coach);
        for(int i=0;i<10;i++){
            this->goals[i] = goals[i];
        }
    }

    FudbalskaEkipa& operator+=(int p){
        for(int i=1;i<10;i++){//nizata 10(0-9) i=1 za da odi pomalce 1pat
            goals[i-1] = goals [i]; //0 go zemi 1,1 ke go zemi 2 itn. i posledniot(9) ke bidi prazen
        }
        goals[9] = p;//vo posledniot go dodavame p,noviot broj
        return *this;
    }

    virtual int uspeh()=0;
    virtual void print()=0;


    friend ostream& operator<<(ostream &out,FudbalskaEkipa &fe){
        fe.print();
        return out;
    }
    ~FudbalskaEkipa(){}
};

class Klub : public FudbalskaEkipa{
protected:
    char x[100];//ime
    int tg; //broj tituli
public:
    Klub():FudbalskaEkipa(){}
    Klub(char *coach, int* goals,
         char *x,int tg):FudbalskaEkipa(coach,goals){
        strcpy(this->x,x);
        this->tg = tg;
    }
    int uspeh(){
        int sumaG=0;
        for(int i=0;i<10;i++){
            sumaG+=goals[i];
        }
        return (sumaG*3) + (tg*1000);
    }
    void print(){
        cout<<x<<"\n"<<coach<<"\n"<<uspeh()<<endl;
    }
    ~Klub(){}
};

class Reprezentacija : public FudbalskaEkipa{
private:
    char drzava[100];
    int nastapi;
public:
    Reprezentacija():FudbalskaEkipa(){}
    Reprezentacija(char *coach, int* goals,
         char *x,int tg):FudbalskaEkipa(coach,goals){
        strcpy(this->drzava,x);
        this->nastapi = tg;
    }

    int uspeh(){
        int sumaG=0;
        for(int i=0;i<10;i++){
            sumaG+=goals[i];
        }
        return (sumaG*3) + (nastapi*50);
    }

    void print(){
        cout<<drzava<<"\n"<<coach<<"\n"<<uspeh()<<endl;
    }
    ~Reprezentacija(){}
};

void najdobarTrener(FudbalskaEkipa **f,int n){
    int max = f[0]->uspeh();
    int index=0;
    for(int i=0;i<n;i++){
        if(max<f[i]->uspeh()){
            max = f[i]->uspeh();
            index=i;
        }
    }
    cout<<*f[index];
};
int main() {
    int n;
    cin >> n;
    FudbalskaEkipa **ekipi = new FudbalskaEkipa*[n];
    char coach[100];
    int goals[10];
    char x[100];
    int tg;
    for (int i = 0; i < n; ++i) {
        int type;
        cin >> type;
        cin.getline(coach, 100);
        cin.getline(coach, 100);
        for (int j = 0; j < 10; ++j) {
            cin >> goals[j];
        }
        cin.getline(x, 100);
        cin.getline(x, 100);
        cin >> tg;
        if (type == 0) {
            ekipi[i] = new Klub(coach, goals, x, tg);
        } else if (type == 1) {
            ekipi[i] = new Reprezentacija(coach, goals, x, tg);
        }
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== DODADI GOLOVI =====" << endl;
    for (int i = 0; i < n; ++i) {
        int p;
        cin >> p;
        cout << "dodavam golovi: " << p << endl;
        *ekipi[i] += p;
    }
    cout << "===== SITE EKIPI =====" << endl;
    for (int i = 0; i < n; ++i) {
        cout << *ekipi[i];
    }
    cout << "===== NAJDOBAR TRENER =====" << endl;
    najdobarTrener(ekipi, n);
    for (int i = 0; i < n; ++i) {
        delete ekipi[i];
    }
    delete [] ekipi;
    return 0;
}