//RESENIE
#include <iostream>
#include <cstring>
using namespace std;

class IceCream {
private:
    char *name;
    char ingredients[100];
    float price;
    int discount;
    void copy(const IceCream &ic) {
        name = new char[strlen(ic.name) + 1];
        strcpy(name, ic.name);
        strncpy(ingredients, ic.ingredients, 99);
        ingredients[99] = '\0';
        price = ic.price;
        discount = ic.discount;
    }
public:
    IceCream(const char *nm = "", const char *ingr = "", float p = 0) {
        name = new char[strlen(nm) + 1];
        strcpy(name, nm);
        strncpy(ingredients, ingr, 99);
        ingredients[99] = '\0';
        price = p;
        discount = 0;
    }

    IceCream(const IceCream &ic) {
        copy(ic);
    }

    IceCream& operator=(const IceCream &ic) {
        if (this == &ic) return *this;
        delete [] name;
        copy(ic);
        return *this;
    }

    friend ostream& operator<<(ostream &out, const IceCream &ic) {
        out << ic.name << ": ";
        out << ic.ingredients << " ";
        out << ic.price << " ";
        if (ic.discount > 0) {
            out << "(" << ic.price * (100 - ic.discount) / 100 << ")";
        }
        return out;
    }
    void setName(char *n) {
        delete [] name;
        name = new char[strlen(n) + 1];
        strcpy(name, n);
    }

    IceCream& operator++() {
        discount += 5;
        return *this;
    }

    IceCream operator+(const char* extra) {
        
        char* newName = new char[strlen(name) + strlen(extra) + 4];
        strcat(newName, name);
        strcat(newName, " + ");
        strcat(newName, extra);
        
        IceCream res(newName, ingredients, price + 10);
        res.setDiscount(discount);
        return res;
    }
    
    void setName(const char* n) {
        delete [] name;
    	name = new char[strlen(n) + 1];
        strcpy(name, n);
    }
    
    void setDiscount(int d) {
    	
        if(d>=0&&d<=100)
            discount = d;
    }

    ~IceCream() {
        delete [] name;
    }
};

class IceCreamShop {
private:
    char name[50];
    IceCream *icecreams;
    int n;
    void copy(const IceCreamShop &ics) {
        strcpy(name, ics.name);
        n = ics.n;
        icecreams = new IceCream[n];
        for (int i = 0; i < n; ++i) {
            icecreams[i] = ics.icecreams[i];
        }
    }
public:
    IceCreamShop(char* nm) {
        strcpy(name, nm);
        icecreams = NULL;
        n = 0;
    }
    IceCreamShop(const IceCreamShop &ics) {
        copy(ics);
    }
    IceCreamShop& operator=(const IceCreamShop &ics) {
        if (this == &ics) return *this;
        delete [] icecreams;
        copy(ics);
        return *this;
    }
    ~IceCreamShop() {
        delete [] icecreams;
    }

    IceCreamShop& operator+= (IceCream &ic) {
        IceCream *tmp = icecreams;
        icecreams = new IceCream[n + 1];
        for (int i = 0; i < n; ++i) {
            icecreams[i] = tmp[i];
        }
        icecreams[n] = ic;
        ++n;
        delete [] tmp;
        return *this;
    }

    friend ostream& operator<<(ostream &out, const IceCreamShop &ics) {
        cout << ics.name << endl;
        for (int i = 0; i < ics.n; ++i) {
            out << ics.icecreams[i] << endl;
        }
        return out;
    }

};

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        //cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        
        cin >> discount;
        ic1.setDiscount(discount);
 

    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}

//STARTER
/*#include <iostream>
#include <cstring>
using namespace std;


// vashiot kod ovde

// zabraneto e menuvanje na main funkcijata

int main() {
    char name[100];
    char ingr[100];
    float price;
    int discount;

    int testCase;

    cin >> testCase;
	cin.get();
    if(testCase == 1) {
        cout << "====== TESTING IceCream CLASS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        ic1.setDiscount(discount);
        cin.get();
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cin >> discount;
        IceCream ic2(name, ingr, price);
        ic2.setDiscount(discount);
        cout << "OPERATOR <<" << endl;
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR ++" << endl;
        ++ic1;
        cout << ic1 << endl;
        cout << "OPERATOR +" << endl;
        IceCream ic3 = ic2 + "chocolate";
        cout << ic3 << endl;
    } else if(testCase == 2) {
        cout << "====== TESTING IceCream CONSTRUCTORS ======" << endl;
        cin.getline(name,100);
        cin.getline(ingr,100);
        cin >> price;
        cout << "CONSTRUCTOR" << endl;
        IceCream ic1(name, ingr, price);
        cout << ic1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        IceCream ic2(ic1);
        cin.get();
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        cout << "OPERATOR =" << endl;
        ic1 = ic2;
        cin.getline(name,100);
        ic2.setName(name);
        cout << ic1 << endl;
        cout << ic2 << endl;
        
        cin >> discount;
        ic1.setDiscount(discount);
 

    } else if(testCase == 3) {
        cout << "====== TESTING IceCreamShop ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        cout << "CONSTRUCTOR" << endl;
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        cout << "OPERATOR +=" << endl;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        cout << ics;
    } else if(testCase == 4) {
        cout << "====== TESTING IceCreamShop CONSTRUCTORS ======" << endl;
        char icsName[50];
        cin.getline(icsName,100);
        IceCreamShop ics(icsName);
        int n;
        cin >> n;
        for(int i = 0; i < n; ++i) {
            cin.get();
            cin.getline(name,100);
        	cin.getline(ingr,100);
            cin >> price;
            IceCream ic(name, ingr, price);
            ics += ic;
        }
        IceCream x("FINKI fruits", "strawberry ice cream, raspberry ice cream, blueberry ice cream", 60);
        IceCreamShop icp = ics;
        ics+=x;
        cout << ics << endl;
        cout << icp << endl;
    }


    return 0;
}
*/
