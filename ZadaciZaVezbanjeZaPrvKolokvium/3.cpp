//
// Created by milen on 05/04/2024.
//
#include<iostream>
#include<cstring>
using namespace std;

// vasiot kod za klasite ovde
class StockRecord {
private:
    char id[12];
    char naziv[50];
    double price;
    double newPrice;
    int shares;
public:
    StockRecord(){}
    StockRecord (char *id,char *company,double price,int shares) {
        strcpy(this->id,id);
        strcpy(this->naziv, company);
        this->price = price;
        this->shares = shares;

    }
    void setNewPrice(double cena){
        this->newPrice = cena;
    }
    double getNewPrice(){
        return newPrice;
    }
    double value(){
        return shares * newPrice;
    }
    double profit(){
        return shares * (newPrice - price);
    }
    friend ostream& operator<<(ostream &out,StockRecord &sr){
        out<<sr.naziv<<" "<<sr.shares<<" "<<sr.price<<" "<<sr.newPrice<<" "<<sr.profit()<<endl;
        return out;
    }
    int getShares(){
        return shares;
    }
    ~StockRecord(){}
};
class Client{
    char clientName[61];
    int clientID;
    StockRecord *sr;
    int n;
public:
    Client(){
        n = 0;
        sr = nullptr;
    }
    Client(char *clientName,int clientID){
        strcpy(this->clientName,clientName);
        this->clientID = clientID;
        n = 0;
        sr = nullptr;
    }
    double totalValue(){
        double sum=0;
        for(int i=0;i<n;i++){
            sum+=sr[i].value();
        }
        return sum;
    }
    Client& operator+=(const StockRecord &nov){
        StockRecord *temp = new StockRecord[n+1];
        for(int i=0;i<n;i++){
            temp[i] = sr[i];
        }
        temp[n] = nov;
        n++;
        delete [] sr;
        sr = temp;
        return *this;
    }
    friend ostream& operator<<(ostream &out,Client &c){
        out<<c.clientID<<" "<<c.totalValue()<<endl;
        for(int i=0;i<c.n;i++){
            cout<<c.sr[i];
        }
        return out;
    }
    ~Client(){
        delete []sr;
    }
};

// ne menuvaj vo main-ot
int main(){

    int test;
    cin >> test;

    if(test == 1){
        double price;
        cout << "=====TEST NA KLASATA StockRecord=====" << endl;
        StockRecord sr("1", "Microsoft", 60.0, 100);
        cout << "Konstruktor OK" << endl;
        cin >> price;
        sr.setNewPrice(price);
        cout << "SET metoda OK" << endl;
    }
    else if(test == 2){
        cout << "=====TEST NA METODITE I OPERATOR << OD KLASATA StockRecord=====" << endl;
        char id[12], company[50];
        double price, newPrice;
        int n, shares;
        cin >> n;
        for(int i = 0; i < n; ++i){
            cin >> id;
            cin >> company;
            cin >> price;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(id, company, price, shares);
            sr.setNewPrice(newPrice);
            cout << sr.value() << endl;
            cout << sr;
        }
    }
    else if(test == 3){
        cout << "=====TEST NA KLASATA Client=====" << endl;
        char companyID[12], companyName[50], clientName[50];
        int clientID, n, shares;
        double oldPrice, newPrice;
        bool flag = true;
        cin >> clientName;
        cin >> clientID;
        cin >> n;
        Client c(clientName, clientID);
        cout << "Konstruktor OK" << endl;
        for(int i = 0; i < n; ++i){
            cin >> companyID;
            cin >> companyName;
            cin >> oldPrice;
            cin >> newPrice;
            cin >> shares;
            StockRecord sr(companyID, companyName, oldPrice, shares);
            sr.setNewPrice(newPrice);
            c += sr;
            if(flag){
                cout << "Operator += OK" << endl;
                flag = false;
            }
        }
        cout << c;
        cout << "Operator << OK" << endl;
    }
    return 0;

}