#include <iostream>

using namespace std;

//Your code here

class Library {
protected:
    string name;
    string city;
    float base_price;
    bool weekend_working;

    
    
public:
    Library(){}
    Library(string name, string city, float base_price, bool weekend_working)
    {
        this->name=name;
        this->city=city;
        this->base_price=base_price;
        this->weekend_working=weekend_working;
    }

    bool isWeekendWorking() const {
        return weekend_working;
    }

    virtual void printDetail()=0;


    virtual double calculateMembershipCardCost()=0;



    ~Library(){}
};

class AcademicLibrary: public Library
{
private:
    bool open_cooperation;
    int specialized_articles;

public:
    AcademicLibrary(string name, string city, float base_price, bool weekend_working,
                    bool open_cooperation,int specialized_articles): Library(name,city,base_price,weekend_working)
    {
        this->open_cooperation=open_cooperation;
        this->specialized_articles=specialized_articles;
    }

    double calculateMembershipCardCost()
    {
        double cena = base_price;
        if(open_cooperation== true)
        {
            cena=cena+cena*24/100;

        }
        return cena+specialized_articles*6;

    }

    void printDetail()
    {
        cout<<name<<" - (Academic) "<<city<<" "<<specialized_articles<<" "<<calculateMembershipCardCost()<<endl;
    }



    ~AcademicLibrary(){}
};

class NationalLibrary: public Library
{
private:
    bool cultural_program;
    int national_articles;

public:
    NationalLibrary(string name, string city, float base_price, bool weekend_working,
                    bool cultural_program, int national_articles): Library(name,city,base_price,weekend_working)
    {
        this->cultural_program=cultural_program;
        this->national_articles=national_articles;
    }

    double calculateMembershipCardCost()
    {
       double cena = base_price;
       if(cultural_program==true)
       {
           cena = cena -cena *7/100;
       }
       return cena+national_articles*15;
    }

    void printDetail()
    {
        cout<<name<<" - (National) "<<city<<" "<<national_articles<<" "<<calculateMembershipCardCost()<<endl;
    }





    ~NationalLibrary(){}

};

int findMostExpensiveNationalLibrary(Library **l, int n)
{

    bool najde =false;
    int index=0;
    double max=l[0]->calculateMembershipCardCost();
    for(int i=0;i<n;i++)
    {
        Library *n = dynamic_cast<NationalLibrary*>(l[i]);
        if(n!=0)
        {
            if(max<=l[i]->calculateMembershipCardCost())
            {
                max = l[i]->calculateMembershipCardCost();
                index = i;
                if(l[i]->isWeekendWorking()== true)
                {
                    max = l[i]->calculateMembershipCardCost();
                    index = i;
                    
                }
                najde = true;
            }
        }
        
    }
    if(najde)
    {
        return index;
    }else{
        return -1;
    }


}

int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Library** m = new Library*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        bool weekend_working;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> weekend_working;
        cin.ignore();

        if (type == 1) {
            bool open_cooperation;
            int specialized_articles;

            cin >> open_cooperation >> specialized_articles;
            cin.ignore();

            m[i] = new AcademicLibrary(name, city, base_price, weekend_working, open_cooperation, specialized_articles);
        } else {
            bool cultural_program;
            int national_articles;

            cin >> cultural_program >> national_articles;
            cin.ignore();

            m[i] = new NationalLibrary(name, city, base_price, weekend_working, cultural_program, national_articles);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateMembershipCardCost() << endl;
        }
        cout << "calculateMembershipCardCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int most_expensive_nat_lib_index = findMostExpensiveNationalLibrary(m, n);
        if(most_expensive_nat_lib_index>=0){
            m[most_expensive_nat_lib_index]->printDetail();
        }else{
            cout << "National Library not found in the array!"<<endl;
        }
        cout << "findMostExpensiveNationalLibrary method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}
