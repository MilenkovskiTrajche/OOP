#include <iostream>
#include <cstring>

using namespace std;

class Koncert{
private:
    char naziv[20], lokacija[20];
    float cenaBilet;
    float popust;
public:
    Koncert(){
        this->popust=0.2;
    }
    Koncert(char *naziv,char *lokacija,float cenaBilet){
        strcpy(this->naziv,naziv);
        strcpy(this->lokacija,lokacija);
        this->cenaBilet = cenaBilet;
        this->popust = 0.2;
    }
    virtual void setSezonskiPopust(float n){
        this->popust = n;
    }
    float getSezonskiPopust() const{
        return this->popust;
    }
    virtual float cena(){
        return cenaBilet -= cenaBilet*popust;
    }
    float getCenaBilet(){
        return cenaBilet;
    }
    char* getNaziv(){
        return this->naziv;
    }
    virtual ~Koncert(){}
};

class ElektronskiKoncert:public Koncert{
private:
    char *imeDJ;
    float casovi;
    bool dnevna;
public:
    ElektronskiKoncert():Koncert(){
        this->imeDJ = new char[strlen(0)];
        this->dnevna = false;
    }
    ElektronskiKoncert(char *naziv,char *lokacija,float cenaBilet,
                       char *imeDJ,float casovi,bool dnevna):Koncert(naziv,lokacija,cenaBilet){
        this->imeDJ = new char[strlen(imeDJ)+1];
        strcpy(this->imeDJ,imeDJ);
        this->casovi = casovi;
        this->dnevna = dnevna;
    }
    ElektronskiKoncert(const ElektronskiKoncert &ek):Koncert(ek){
        this->imeDJ = new char[strlen(ek.imeDJ)+1];
        strcpy(this->imeDJ,ek.imeDJ);
        this->casovi = ek.casovi;
        this->dnevna = ek.dnevna;
    }
    ElektronskiKoncert& operator=(const ElektronskiKoncert &ek) {
        if (this != &ek) {
            delete []imeDJ;
            this->imeDJ = new char[strlen(ek.imeDJ) + 1];
            strcpy(this->imeDJ, ek.imeDJ);
            this->casovi = ek.casovi;
            this->dnevna = ek.dnevna;
        }
        return *this;
    }

    float cena(){
        float osnovna=getCenaBilet();//9100
        osnovna-=osnovna*getSezonskiPopust();//9100 -= 9100- 9100*0.2 //7280

        if(casovi>5 && casovi<7){
            osnovna+=150;
        }
        if(casovi>7){
            osnovna+=360;
        }
        if(dnevna){
            osnovna-=50;
        }
        else {
            osnovna += 100;
        }
        return osnovna;
    }

    ~ElektronskiKoncert(){
        delete []imeDJ;
    }

};

void najskapKoncert(Koncert **koncerti,int n) {
    int najskap = koncerti[0]->cena();
    int index=0,br=0;

    for (int i = 0; i < n; i++) {
        if(najskap < koncerti[i]->cena()){
            najskap = koncerti[i]->cena();
            index = i;
        }
        Koncert *k = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
        if(k!=0){
            br++;
        }
    }
    cout<<"Najskap koncert: "<<koncerti[index]->getNaziv()<<" "<<koncerti[index]->cena()<<endl;
    cout<<"Elektronski koncerti: "<<br<<" od vkupno "<<n<<endl;
}

bool prebarajKoncert(Koncert **koncerti,int n,char *ime,bool elektronski){

    for(int i=0;i<n;i++){

        if(elektronski) {
            Koncert *k = dynamic_cast<ElektronskiKoncert *>(koncerti[i]);
            if (k != 0) {
                if (strcmp(koncerti[i]->getNaziv(), ime) == 0) {
                    cout << koncerti[i]->getNaziv() << " " << koncerti[i]->cena() << endl;
                    return true;
                }
                else
                    return false;
            }
        }
        else if(!elektronski){
            if(strcmp(koncerti[i]->getNaziv(),ime)==0){
                cout<<koncerti[i]->getNaziv()<<" "<<koncerti[i]->cena()<<endl;
                return true;
            }
            else
                return false;
        }
    }
}
int main(){

    int tip,n,novaCena;
    char naziv[100], lokacija[100], imeDJ[40];
    bool dnevna;
    float cenaBilet, novPopust;
    float casovi;

    cin>>tip;
    if (tip==1){//Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Kreiran e koncert so naziv: "<<k1.getNaziv()<<endl;
    }
    else if (tip==2){//cena - Koncert
        cin>>naziv>>lokacija>>cenaBilet;
        Koncert k1(naziv,lokacija,cenaBilet);
        cout<<"Osnovna cena na koncertot so naziv "<<k1.getNaziv()<< " e: " <<k1.cena()<<endl;
    }
    else if (tip==3){//ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Kreiran e elektronski koncert so naziv "<<s.getNaziv()<<" i sezonskiPopust "<<s.getSezonskiPopust()<<endl;
    }
    else if (tip==4){//cena - ElektronskiKoncert
        cin>>naziv>>lokacija>>cenaBilet>>imeDJ>>casovi>>dnevna;
        ElektronskiKoncert s(naziv,lokacija,cenaBilet,imeDJ,casovi,dnevna);
        cout<<"Cenata na elektronskiot koncert so naziv "<<s.getNaziv()<<" e: "<<s.cena()<<endl;
    }
    else if (tip==5) {//najskapKoncert

    }
    else if (tip==6) {//prebarajKoncert
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        najskapKoncert(koncerti,5);
    }
    else if (tip==7){//prebaraj
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[4] = new ElektronskiKoncert("CavoParadiso","Mykonos",8800,"Guetta",3,true);
        char naziv[100];
        bool elektronski;
        cin>>elektronski;
        if(prebarajKoncert(koncerti,5, "Area",elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

        if(prebarajKoncert(koncerti,5, "Area",!elektronski))
            cout<<"Pronajden"<<endl;
        else cout<<"Ne e pronajden"<<endl;

    }
    else if (tip==8){//smeni cena
        Koncert ** koncerti = new Koncert *[5];
        int n;
        koncerti[0] = new Koncert("Area","BorisTrajkovski",350);
        koncerti[1] = new ElektronskiKoncert("TomorrowLand","Belgium",8000,"Afrojack",7.5,false);
        koncerti[2] = new ElektronskiKoncert("SeaDance","Budva",9100,"Tiesto",5,true);
        koncerti[3] = new Koncert("Superhiks","PlatoUkim",100);
        koncerti[2] -> setSezonskiPopust(0.9);
        //dodadeni dolu set metodite
        koncerti[1] -> setSezonskiPopust(0.9);
        koncerti[0] -> setSezonskiPopust(0.9);
        koncerti[3] -> setSezonskiPopust(0.9);
        najskapKoncert(koncerti,4);
    }

    return 0;
}
