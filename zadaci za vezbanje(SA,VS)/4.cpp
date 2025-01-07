#include <iostream>
#include <cstring>

using namespace std;

class Museum{
protected:
    string name;
    string city;
    float base_price;
    int working_hours;
public:
    Museum(){};
    Museum(string name,string city,float base_price,int working_hour){
        this->name = name;
        this->city=city;
        this->base_price = base_price;
        this->working_hours=working_hour;
    }
    int getWH(){
        return working_hours;
    }
    virtual void printDetail(){}
    virtual double calculateTicketCost(){
        return base_price;
    }
    virtual ~Museum(){}
};

class ScientificMuseum : public Museum{
private:
    bool interactive_shows;
    int multimedia_pres;
public:
    ScientificMuseum():Museum(){}
    ScientificMuseum(string name,string city,float base_price,int working_hour,
                     bool interactive_shows,int multimedia_pres):Museum(name,city,base_price,working_hour){
        this->interactive_shows=interactive_shows;
        this->multimedia_pres=multimedia_pres;
    }
    double calculateTicketCost(){
        double osnovna=base_price;
        if(interactive_shows){
            osnovna=osnovna+osnovna*12/100;
        }
        return osnovna+(multimedia_pres*6);
    }
    void printDetail(){
        cout<<name<<" - (Scientific) "<<city<<" "<<multimedia_pres<<" "<<calculateTicketCost()<<endl;
    }
    ~ScientificMuseum(){}
};
class ArtMuseum : public Museum{
private:
    bool amateur_shows;
    int original_artwork;
public:
    ArtMuseum():Museum(){}
    ArtMuseum(string name,string city,float base_price,int working_hour,
                     bool amateur_shows,int original_artwork):Museum(name,city,base_price,working_hour){
        this->amateur_shows=amateur_shows;
        this->original_artwork=original_artwork;
    }
    double calculateTicketCost(){
        double osnovna=base_price;
        if(amateur_shows){
            osnovna=osnovna-osnovna*18/100;
        }
        return osnovna+(original_artwork*3);
    }
    void printDetail(){
        cout<<name<<" - (Art) "<<city<<" "<<amateur_shows<<" "<<calculateTicketCost()<<endl;
    }
    ~ArtMuseum(){}
};
int findCheapestScientificMuseum(Museum **m, int n){
    double minP=m[0]->calculateTicketCost();
    int maxC=m[0]->getWH();
    int index=0;
    bool najde=false;

    for(int i=0;i<n;i++){
        Museum *sc = dynamic_cast<ScientificMuseum*>(m[i]);
        if(sc!=0){
            if(minP>m[i]->calculateTicketCost()){
                minP=m[i]->calculateTicketCost();
                index=i;
            }
            if(minP==m[i]->calculateTicketCost()){
                if(maxC<m[i]->getWH()){
                    minP=m[i]->calculateTicketCost();
                    maxC=m[i]->getWH();
                    index=i;
                }
            }
            najde=true;
        }

    }
    if(najde) {
        return index;
    }else{
        return -1;
    }

}
int main() {
    int n, testCase, type;
    cin >> testCase >> n;
    cin.ignore();

    Museum** m = new Museum*[n];

    for (int i = 0; i < n; ++i) {
        string name;
        string city;
        float base_price;
        int working_hours;

        cin >> type;
        cin.ignore();
        getline(cin, name);
        getline(cin, city);
        cin >> base_price;
        cin.ignore();
        cin >> working_hours;
        cin.ignore();

        if (type == 1) {
            bool interactive_shows;
            int multimedia_pres;

            cin >> interactive_shows >> multimedia_pres;
            cin.ignore();

            m[i] = new ScientificMuseum(name, city, base_price, working_hours, interactive_shows, multimedia_pres);
        } else {
            bool amateur_shows;
            int original_artwork;

            cin >> amateur_shows >> original_artwork;
            cin.ignore();

            m[i] = new ArtMuseum(name, city, base_price, working_hours, amateur_shows, original_artwork);
        }
    }

    if(testCase == 1){
        cout << "Abstract and child classes OK" << endl;
    }
    else if(testCase == 2){
        for(int i = 0; i < n; i++){
            cout << m[i]->calculateTicketCost() << endl;
        }
        cout << "calculateTicketCost method OK" << endl;
    }
    else if(testCase == 3){
        for(int i = 0; i < n; i++){
            m[i]->printDetail();
        }
        cout << "printDetail method OK" << endl;
    }
    else if(testCase == 4){
        int cheapest_sci_museum_index = findCheapestScientificMuseum(m, n);
        if(cheapest_sci_museum_index>=0){
            m[cheapest_sci_museum_index]->printDetail();
        }else{
            cout << "Scientific Museum not found in the array!"<<endl;
        }
        cout << "findCheapestOnlineOrder method OK" << endl;
    }


    for (int i = 0; i < n; ++i) {
        delete m[i];
    }

    delete[] m;

    return 0;
}