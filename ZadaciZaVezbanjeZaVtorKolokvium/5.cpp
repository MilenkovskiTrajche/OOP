#include <iostream>
#include <cstring>

using namespace std;

#define MAX 100


class UserExistsException{
    string msg;
public:
    UserExistsException(string msg){
        this->msg = msg;
    }
    void print(){
        cout<<msg<<endl;
    }
};

enum typeC{standard,loyal,vip};

class Customer{
private:
    char name[50];
    char email[50];
    typeC tip;
    int dicount;
    int bdiscount;
    int numProducts;
public:
    Customer(){
        this->dicount = 10;
        this->bdiscount=20;
        this->tip = standard;
    }
    Customer(char *name,char *email,typeC tip,int numProducts){
        strcpy(this->name,name);
        strcpy(this->email,email);
        this->tip = tip;
        this->numProducts = numProducts;
        this->dicount = 10;
        this->bdiscount=20;
    }
    void setDiscount1(int n){
        this->dicount = n;
    }
    int getNumProducts(){
        return numProducts;
    }
    char* getIme(){
        return name;
    }
    char* getMail(){
        return email;
    }
    typeC getTip(){
        return (typeC)tip;
    }
    void setTip(typeC q){
        this->tip = q;
    }
    friend ostream& operator<<(ostream &out,const Customer &c){
        out<<c.name<<endl;
        out<<c.email<<endl;
        out<<c.numProducts<<endl;
        if(c.tip==standard){
            out<<"standard "<<0<<endl;
        }
        if(c.tip==loyal){
            out<<"loyal "<<c.dicount<<endl;
        }
        if(c.tip==vip){
            out<<"vip "<<(c.dicount+c.bdiscount)<<endl;
        }
        return out;
    }


    ~Customer(){}
};

class FINKI_bookstore{
private:
    int brCustomer;
    Customer *c;
public:
    FINKI_bookstore(){
        this->brCustomer = 0;
        this->c = new Customer[brCustomer];
    }
    FINKI_bookstore(Customer *c,int brCustomer){
        this->brCustomer = brCustomer;
        this->c = new Customer[brCustomer];
        for(int i=0;i<brCustomer;i++){
            this->c[i] = c[i];
        }
    }
    FINKI_bookstore(const FINKI_bookstore &fb){
        this->brCustomer = fb.brCustomer;
        this->c = new Customer[fb.brCustomer];
        for(int i=0;i<fb.brCustomer;i++){
            this->c[i] = fb.c[i];
        }
    }
    FINKI_bookstore& operator=(const FINKI_bookstore &fb){
        if(this!=&fb) {
            delete []c;
            this->brCustomer = fb.brCustomer;
            this->c = new Customer[fb.brCustomer];
            for (int i = 0; i < fb.brCustomer; i++) {
                this->c[i] = fb.c[i];
            }
        }
        return *this;
    }
    FINKI_bookstore& setCustomers(Customer *cm,int n){
        delete []c;
        this->brCustomer = n;
        this->c = new Customer[n];
        for(int i = 0;i<brCustomer;i++){
            this->c[i] = cm[i];
        }
        return *this;
    }
    FINKI_bookstore& operator+=( Customer &nov){
        for(int i=0;i<brCustomer;i++){
            if(strcmp(c[i].getMail(),nov.getMail())==0){
                throw UserExistsException("The user already exists in the list!");
            }
        }

        Customer *temp = new Customer[brCustomer+1];
        for(int i=0;i<brCustomer;i++){
            temp[i] = c[i];
        }
        temp[brCustomer]=nov;
        delete []c;
        c=temp;
        brCustomer++;
        return *this;

    }


    FINKI_bookstore& update(){
        for(int i=0;i<brCustomer;i++){
            if(c[i].getTip()==standard && c[i].getNumProducts() > 5) {
                c[i].setTip(loyal);
            }
            else if(c[i].getTip()==loyal && c[i].getNumProducts() > 10) {
                c[i].setTip(vip);

            }
        }
        return *this;
    }

    friend ostream& operator<<(ostream &out, FINKI_bookstore &fc){
        for(int i=0;i<fc.brCustomer;i++){
            cout<<fc.c[i];
        }
        return out;
    }

    ~FINKI_bookstore(){
        delete []c;
    }
};

int main(){
    int testCase;
    cin >> testCase;

    char name[MAX];
    char email[MAX];
    int tC;
    int discount;
    int numProducts;


    if (testCase == 1){
        cout << "===== Test Case - Customer Class ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

    }

    if (testCase == 2){
        cout << "===== Test Case - Static Members ======" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        cout << "===== CONSTRUCTOR ======" << endl;
        Customer c(name, email, (typeC) tC, numProducts);
        cout << c;

        c.setDiscount1(5);

        cout << c;
    }

    if (testCase == 3){
        cout << "===== Test Case - FINKI-bookstore ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << fc <<endl;
    }

    if (testCase == 4){
        cout << "===== Test Case - operator+= ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        Customer c(name, email, (typeC) tC, numProducts);

        try {
            fc += c;
        }catch (UserExistsException &ic){
            ic.print();
        }

        cout << fc;
    }

    if (testCase == 5){
        cout << "===== Test Case - operator+= (exception) ======" << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);
        cout << "OPERATOR +=" << endl;
        cin.get();
        cin.getline(name,MAX);
        cin.getline(email,MAX);
        cin >> tC;
        cin >> numProducts;
        
        //dodadeno e Customer bidekji nefakja c
        Customer c(name, email, (typeC) tC, numProducts);

        try {
            fc += c;
        }catch (UserExistsException &ic){
            ic.print();
        }

        cout << fc;
    }

    if (testCase == 6){
        cout << "===== Test Case - update method  ======" << endl << endl;
        FINKI_bookstore fc;
        int n;
        cin >> n;
        Customer customers[MAX];
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,MAX);
            cin.getline(email,MAX);
            cin >> tC;
            cin >> numProducts;
            Customer c(name, email, (typeC) tC, numProducts);
            customers[i] = c;
        }

        fc.setCustomers(customers, n);

        cout << "Update:" << endl;
        fc.update();
        cout << fc;
    }
    return 0;

}
