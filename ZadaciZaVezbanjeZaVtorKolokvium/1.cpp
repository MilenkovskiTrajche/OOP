#include <iostream>
#include <cstring>
#include <string>
using namespace std;

class Book{
protected:
    char isbn[20];
    char title[50];
    char author[30];
    float price;
public:
    Book(){}
    Book(char *isbn,char *title,char *author,float price){
        strcpy(this->isbn,isbn);
        strcpy(this->title,title);
        strcpy(this->author,author);
        this->price = price;
    }

    virtual float bookPrice()=0;

    virtual char* setISBN(char *i){
        strcpy(this->isbn,i);
        return this->isbn;
    };
    bool operator>(Book &b){
        return this->bookPrice()>b.bookPrice();
    }
    virtual void print(){
        cout<<isbn<<": "<<title<<", "<<author<<" "<<bookPrice()<<endl;
    }
    friend ostream& operator<<(ostream &out,Book &b){
        b.print();
        return out;
    }
    virtual ~Book(){}
};


class OnlineBook : public Book{
private:
    char *url;
    int size;
public:
    OnlineBook():Book(){
        this->url = new char[0];
        this->url[0] = '\0';
    }
    OnlineBook(char *isbn,char *title,char *author,float price,char *url,int size):Book(isbn,title,author,price){
        this->size = size;
        this->url = new char[strlen(url)+1];
        strcpy(this->url,url);
    }
    OnlineBook(const OnlineBook &ob):Book(ob){
        this->size = ob.size;
        this->url = new char[strlen(ob.url)+1];
        strcpy(this->url,ob.url);
    }
    OnlineBook& operator=(const OnlineBook &ob) {
        if (this != &ob) {
            Book::operator=(ob);
            delete []url;
            this->size = ob.size;
            this->url = new char[strlen(ob.url) + 1];
            strcpy(this->url, ob.url);
        }
        return *this;
    }

    float bookPrice(){
        float osnovna=price;
        if(size>20){
            return osnovna+osnovna*20/100;
        }
        return osnovna;
    }

    ~OnlineBook(){
        delete []url;
    }
};
class PrintBook:public Book{
private:
    bool inStock;
    float weight;
public:
    PrintBook():Book(){}
    PrintBook(char *isbn,char *title,char *author,float price,float weight,bool inStock):Book(isbn,title,author,price){
        this->weight = weight;
        this->inStock = inStock;
    }
    float bookPrice(){
        float osnovna=price;
        if(weight>0.7){
            return osnovna+osnovna*15/100;
        }
        return osnovna;
    }
    ~PrintBook(){}
};

void mostExpensiveBook(Book** books, int n) {
    int index = 0;
    float maxPrice = books[0]->bookPrice();
    int onlineBookCount = 0;
    int printBookCount = 0;

    for (int i = 0; i < n; ++i) {
        if (books[i]->bookPrice() > maxPrice) {
            maxPrice = books[i]->bookPrice();
            index = i;
        }
        if (dynamic_cast<OnlineBook*>(books[i])) {
            ++onlineBookCount;
        }
        else if (dynamic_cast<PrintBook*>(books[i])) {
            ++printBookCount;
        }
    }

    cout << "FINKI-Education" << endl;
    cout << "Total number of online books: " << onlineBookCount << endl;
    cout << "Total number of print books: " << printBookCount << endl;
    cout << "The most expensive book is:" << endl;
    cout << *books[index];
}
int main(){

    char isbn[20], title[50], author[30], url[100];
    int size, tip;
    float price, weight;
    bool inStock;
    Book  **books;
    int n;

    int testCase;
    cin >> testCase;

    if (testCase == 1){
        cout << "====== Testing OnlineBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> url;
            cin >> size;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new OnlineBook(isbn, title, author, price, url, size);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 2){
        cout << "====== Testing OnlineBook CONSTRUCTORS ======" << endl;
        cin >> isbn;
        cin.get();
        cin.getline(title, 50);
        cin.getline(author, 30);
        cin >> price;
        cin >> url;
        cin >> size;
        cout << "CONSTRUCTOR" << endl;
        OnlineBook ob1(isbn, title, author, price, url, size);
        cout << ob1 << endl;
        cout << "COPY CONSTRUCTOR" << endl;
        OnlineBook ob2(ob1);
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
        cout << "OPERATOR =" << endl;
        ob1 = ob2;
        cin >> isbn;
        ob2.setISBN(isbn);
        cout << ob1 << endl;
        cout << ob2 << endl;
    }
    if (testCase == 3){
        cout << "====== Testing PrintBook class ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i < n; i++){
            cin >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            cin >> weight;
            cin >> inStock;
            cout << "CONSTRUCTOR" << endl;
            books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            cout << "OPERATOR <<" << endl;
            cout << *books[i];
        }
        cout << "OPERATOR >" << endl;
        cout << "Rezultat od sporedbata e: " << endl;
        if (*books[0] > *books[1])
            cout << *books[0];
        else
            cout << *books[1];
    }
    if (testCase == 4){
        cout << "====== Testing method mostExpensiveBook() ======" << endl;
        cin >> n;
        books = new Book *[n];

        for (int i = 0; i<n; i++){

            cin >> tip >> isbn;
            cin.get();
            cin.getline(title, 50);
            cin.getline(author, 30);
            cin >> price;
            if (tip == 1) {

                cin >> url;
                cin >> size;

                books[i] = new OnlineBook(isbn, title, author, price, url, size);

            }
            else {
                cin >> weight;
                cin >> inStock;

                books[i] = new PrintBook(isbn, title, author, price, weight, inStock);
            }
        }

        mostExpensiveBook(books, n);
    }

    for (int i = 0; i<n; i++) delete books[i];
    delete[] books;
    return 0;
}
