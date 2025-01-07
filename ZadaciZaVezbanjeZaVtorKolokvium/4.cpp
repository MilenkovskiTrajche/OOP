#include <cstring>
#include <iostream>
using namespace std;

enum Size{small,medium,family};

class Pizza{
protected:
    char name[20];
    char ingredients[100];
    float inPrice;
public:
    Pizza(){}
    Pizza(char *name,char *ingredients,float inPrice){
        strcpy(this->name,name);
        strcpy(this->ingredients,ingredients);
        this->inPrice=inPrice;
    }
    virtual bool operator<(Pizza &p){
        return this->price()<p.price();
    }
    virtual void print() = 0;
    virtual int price() = 0;
    friend ostream& operator<<(ostream &out,Pizza &p){
        p.print();
        return out;
    }
    virtual ~Pizza(){}
};
class FlatPizza : public Pizza{
    Size size;
public:
    FlatPizza():Pizza(){}
    FlatPizza(char *name,char *ingredients,float inPrice) : Pizza(name,ingredients,inPrice){}
    FlatPizza(char *name,char *ingredients,float inPrice,
              Size size) : Pizza(name,ingredients,inPrice){
        this->size = size;
    }
    string pizzaSizeToString(Size size) {
        switch (size) {
            case small:
                return "small";
            case medium:
                return "medium";
            case family:
                return "family";
            default:
                return "small";
        }
    }
    int price(){
        int osnovna = inPrice;
        if(size == small){
            return osnovna + osnovna*10/100;
        }
        else if(size ==medium ){
            return osnovna + osnovna*20/100;
        }
        else if(size == family){
            return osnovna + osnovna*30/100;
        }
        return osnovna+osnovna*10/100;
    }
    void print(){
        cout<<name<<": "<<ingredients<<", "<<pizzaSizeToString(size)<<" - "<<price()<<endl;
    }

    ~FlatPizza(){}
};

class FoldedPizza : public Pizza{
private:
    bool whiteFlour=true;
public:
    FoldedPizza():Pizza(){}
    FoldedPizza(char *name,char *ingredients,float inPrice) : Pizza(name,ingredients,inPrice){}

    void setWhiteFlour(bool whiteFl){
        this->whiteFlour = whiteFl;
    }
    bool getwhiteFlour(){
        return whiteFlour;
    }

    int price() {
        int osnovna = inPrice;
        if (getwhiteFlour()==true) {
            return osnovna + osnovna * 10 / 100;
        } else return osnovna + osnovna * 30 / 100;
    }
    void print(){
        cout<<name<<": "<<ingredients<<", ";
        if(getwhiteFlour()== true){
            cout<<"wf - "<<price()<<endl;
        }
        else cout << "nwf - " << price() << endl;

    }

    ~FoldedPizza(){}
};
void expensivePizza(Pizza **p,int n){
    int max = p[0]->price();
    int index=0;
    for(int i=0;i<n;i++){
        if(max<p[i]->price()){
            max = p[i]->price();
            index = i;
        }
    }
    p[index]->print();
}
int main() {
    int test_case;
    char name[20];
    char ingredients[100];
    float inPrice;
    Size size;
    bool whiteFlour;

    cin >> test_case;
    if (test_case == 1) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FlatPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 2) {
        // Test Case FlatPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        int s;
        cin>>s;
        FlatPizza fp(name, ingredients, inPrice, (Size)s);
        cout << fp;

    } else if (test_case == 3) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        cout << fp;
    } else if (test_case == 4) {
        // Test Case FoldedPizza - Constructor, operator <<, price
        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza fp(name, ingredients, inPrice);
        fp.setWhiteFlour(false);
        cout << fp;

    } else if (test_case == 5) {
        // Test Cast - operator <, price
        int s;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp1 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp1;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        cin>>s;
        FlatPizza *fp2 = new FlatPizza(name, ingredients, inPrice, (Size)s);
        cout << *fp2;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp3 = new FoldedPizza(name, ingredients, inPrice);
        cout << *fp3;

        cin.get();
        cin.getline(name,20);
        cin.getline(ingredients,100);
        cin >> inPrice;
        FoldedPizza *fp4 = new FoldedPizza(name, ingredients, inPrice);
        fp4->setWhiteFlour(false);
        cout << *fp4;

        cout<<"Lower price: "<<endl;
        if(*fp1<*fp2)
            cout<<fp1->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp1<*fp3)
            cout<<fp1->price()<<endl;
        else cout<<fp3->price()<<endl;

        if(*fp4<*fp2)
            cout<<fp4->price()<<endl;
        else cout<<fp2->price()<<endl;

        if(*fp3<*fp4)
            cout<<fp3->price()<<endl;
        else cout<<fp4->price()<<endl;

    } else if (test_case == 6) {
        // Test Cast - expensivePizza
        int num_p;
        int pizza_type;

        cin >> num_p;
        Pizza **pi = new Pizza *[num_p];
        for (int j = 0; j < num_p; ++j) {

            cin >> pizza_type;
            if (pizza_type == 1) {
                cin.get();
                cin.getline(name,20);

                cin.getline(ingredients,100);
                cin >> inPrice;
                int s;
                cin>>s;
                FlatPizza *fp = new FlatPizza(name, ingredients, inPrice, (Size)s);
                cout << (*fp);
                pi[j] = fp;
            }
            if (pizza_type == 2) {

                cin.get();
                cin.getline(name,20);
                cin.getline(ingredients,100);
                cin >> inPrice;
                FoldedPizza *fp =
                        new FoldedPizza (name, ingredients, inPrice);
                if(j%2)
                    (*fp).setWhiteFlour(false);
                cout << (*fp);
                pi[j] = fp;

            }
        }

        cout << endl;
        cout << "The most expensive pizza:\n";
        expensivePizza(pi,num_p);


    }
    return 0;
}