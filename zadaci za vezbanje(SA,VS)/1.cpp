#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;

class NoProductFoundException {
private:
    string category;
    public:
    NoProductFoundException( string category) {
        this->category = category;
    }
    void print() {
        cout << "No products from category "<<category<<" were found in the store" << endl;

    }
};
class Product {
protected:
    string name;
    string kategorija;
    int price;
    int kolicina;
public:
    Product(){}
    Product(string name, string kategorija, int price,int kolicina) {
        this->name = name;
        this->kategorija = kategorija;
        this->price = price;
        this->kolicina = kolicina;
    }
    int totalPrice() const{
        return price*kolicina;
    }

    string getKategorija() const{
        return kategorija;
    }
    string getName() const {
        return name;
    }
    int getPrice() {
        return price;
    }
    int getKolicina() {
        return kolicina;
    }
    friend ostream& operator<<(ostream &os, const Product &product) {
        os << product.name << " (" << product.kategorija << ") "
           << product.kolicina << " x " << product.price << " = "
           << product.totalPrice();
        return os;
    }


    ~Product(){}
};

class Store {
protected:
    Product *p;
    int n;
public:
    Store() {
        this->n=0;
        this->p = new Product[n];
    }
    Store(Product *p,int n) {
        this->n = n;
        this->p = new Product[n];
        for(int i=0;i<n;i++) {
            this->p[i] = p[i];
        }
    }
    Store(const Store &s) {
        this->n = s.n;
        this->p = new Product[n];
        for(int i=0;i<n;i++) {
            this->p[i] = s.p[i];
        }
    }
    Store& operator=(const Store &s) {
        if(this!=&s) {
            delete []p;
            this->n = s.n;
            this->p = new Product[n];
            for(int i=0;i<n;i++) {
                this->p[i] = s.p[i];
            }
        }
        return *this;
    }
    Store& operator+=(Product &nov) {
        Product *temp = new Product[n+1];
        for(int i=0;i<n;i++) {
            temp[i] = p[i];
        }
        temp[n] = nov;
        delete []p;
        this->p = temp;
        n++;
        return *this;
    }
    Store fromCategory(string &category) {
        Store result;
        for (int i = 0; i < n; i++) {
            if (p[i].getKategorija() == category) {
                result += p[i];
            }
        }
        if (result.n == 0) {
            throw NoProductFoundException(category);
        }
        return result;
    }

    void zapishi() {
        ofstream myfile("output1.txt", ios::out);
        if (!myfile.is_open()) {
            cout << "NE postoi datoteka" << endl;
            return;
        }
        for (int i = 0; i < n; i++) {
            myfile << p[i] << endl;
        }
        myfile.close();
    }

    int getN() {
        return n;
    }
    Product* getProduct() {
        return p;
    }

    ~Store() {
        delete []p;
    }
};
void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----") {
            break;
        }
        fout << line << endl;
    }
}

void rff(string path) {
    ifstream fin(path);
    string line;
    while (getline(fin, line)) {
        cout << line << endl;
    }
}


int main() {

    wtf();


    Store s;

    //TODO your code starts here
    //TODO Read the products from the file and add them in the store `s`

    // Читање од датотеката input.txt
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cout << "NE postoi datotekata input.txt" << endl;
        return 1;
    }
    string name,cat;
    int price, quantity;
    while (getline(fin, name) && getline(fin, cat) && fin >> price >> quantity) {
        fin.ignore(); // За прескокнување на нов ред
        Product p(name, cat, price, quantity);
        s += p;
    }
    fin.close();

    // Запишување во output1.txt
    s.zapishi();


    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT

    string category;
    cin >> category;

    // Запишување во output2.txt
    try {
        Store filtered = s.fromCategory(category);
        ofstream myfile("output2.txt", ios::out);
        for (int i = 0; i < filtered.getN(); i++) {
            myfile << filtered.getProduct()[i].getName() << " (" << filtered.getProduct()[i].getKategorija() << ") "
                   << filtered.getProduct()[i].getKolicina() << " x " << filtered.getProduct()[i].getPrice() << " = "
                   << filtered.getProduct()[i].totalPrice() << endl;
        }
        myfile.close();
    } catch (NoProductFoundException &e) {
        ofstream myfile("output2.txt", ios::out);
        //myfile << "No products from category " << category << " were found in the store" << endl;
        myfile.close();
        e.print();
    }
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line
    s.zapishi();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All products:" << endl;
    rff("output1.txt");
    cout << "Products from category " << category << ": " << endl;
    rff("output2.txt");


    return 0;
}