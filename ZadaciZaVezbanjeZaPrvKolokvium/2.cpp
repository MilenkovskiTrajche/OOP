//
// Created by milen on 03/04/2024.
//

#include <iostream>
using namespace std;

class List{
    int n;
    int *niza;
public:
    List(){
        this->n = 0;
        this->niza = new int[n];
    }
    List(int *niza,int n){
        this->n = n;
        this->niza = new int[n];
        for(int i=0;i<n;i++){
            this->niza[i] = niza[i];
        }
    }
    List(const List &l){
        this->n = l.n;
        this->niza = new int[l.n];
        for(int i=0;i<l.n;i++){
            this->niza[i] = l.niza[i];
        }
    }
    List& operator=(const List &l){
        if(this!=&l) {
            delete []niza;
            this->n = l.n;
            this->niza = new int[l.n];
            for (int i = 0; i < l.n; i++) {
                this->niza[i] = l.niza[i];
            }
        }
        return *this;
    }
    int sumL(){
        int sum=0;
        for(int i=0;i<n;i++){
            sum += niza[i];
        }
        return sum;
    }
    double average(){
        double sum=0;
        for(int i=0;i<n;i++){
            sum += niza[i];
        }
        return sum/n;
    }
    void pecati(){
        for(int i=0;i<n;i++){
            cout<<niza[i]<<" ";
        }
        cout<<"sum: "<<sumL()<<" average: "<<average()<<endl;
    }
    int getinfo(){
        return n;
    }
    ~List(){
        delete []niza;
    }
};

class ListContainer{
    List *l;
    int brList;
    int brojac;
    int fbrojac;
public:
    ListContainer(){
        this->brList = 0;
        this->l = new List[brList];
        this->brojac = 0;
        this->fbrojac =0;
    }
    ListContainer(const ListContainer &lc){
        this->brList = lc.brList;
        this->brojac=0;
        this->fbrojac =0;
        this->l = new List[lc.brList];
        for(int i=0;i<lc.brList;i++){
            this->l[i] = lc.l[i];
        }
    }
    ListContainer& operator=(const ListContainer &lc){
        if(this!=&lc){
            delete []l;
            this->brList = lc.brList;
            this->l = new List[lc.brList];
            for(int i=0;i<lc.brList;i++){
                this->l[i] = lc.l[i];
            }
        }
        return *this;
    }
    int sum(){
        int sum=0;
        for(int i=0;i<brList;i++){
            sum += l[i].sumL();
        }
        return sum;
    }
    double average(){
        int sum=0;
        double a=0;
        for(int i=0;i<brList;i++){
            sum+=l[i].sumL();
            a+=l[i].getinfo();
        }
        return sum/a;
    }
//    void addNewList(List &l)
//    {
//        List *tmp = new List[brList+1];
//        for(int i=0; i<brList; i++){
//            if(l.sumL() == this->l[i].sumL()){
//                brojac++;
//                return;
//            }
//            else{
//                tmp[i] = this->l[i];
//                brojac++;
//
//            }
//        }
//        tmp[brList++] = l;
//        delete [] this->l;
//        this->l = tmp;
//    }

 void addNewList(List nova) {
     bool shouldAdd = true;
     int novaSuma = nova.sumL();

     for (int i = 0; i < brList; ++i) {
         if (l[i].sumL() == novaSuma) {
             shouldAdd = false;
             break;
         }
     }

     if (shouldAdd) {
         List *temp = new List[brList + 1];
         for (int i = 0; i < brList; ++i) {
             temp[i] = l[i];
         }
         temp[brList++] = nova;
         delete[] l;
         l = temp;
         brojac++;
     } else {
         fbrojac++;
     }
 }

    void print() {
        if (brList == 0) {
            cout << "The list is empty" << endl;
            return;
        }

        else {
            for (int i = 0; i < brList; i++) {
                cout << "List number: " << i + 1 << " List info: " << l[i].getinfo() << ": ";
                l[i].pecati();
            }

            cout << "Sum: " << sum() << " Average: " << average() << endl;
        }
        cout << "Successful attempts: " <<this->brList<<" Failed attempts: "<<fbrojac<<endl;

    }
    ~ListContainer(){
        delete []l;
    }
};
int main() {

    ListContainer lc;
    int N;
    cin>>N;

    for (int i=0;i<N;i++) {
        int n;
        int niza[100];

        cin>>n;

        for (int j=0;j<n;j++){
            cin>>niza[j];

        }

        List l=List(niza,n);

        lc.addNewList(l);
    }


    int testCase;
    cin>>testCase;

    if (testCase==1) {
        cout<<"Test case for operator ="<<endl;
        ListContainer lc1;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1=lc;
        lc1.print();
        cout<<lc1.sum()<<" "<<lc.sum()<<endl;
        lc1.sum();
        lc1.average();

    }
    else {
        lc.print();
    }

}

// void addNewList(List nova) {
//     bool shouldAdd = true;
//     int novaSuma = nova.sumL();

//     for (int i = 0; i < brList; ++i) {
//         if (l[i].sumL() == novaSuma) {
//             shouldAdd = false;
//             break;
//         }
//     }

//     if (shouldAdd) {
//         List* temp = new List[brList + 1];
//         for (int i = 0; i < brList; ++i) {
//             temp[i] = l[i];
//         }
//         temp[brList++] = nova;
//         delete[] l;
//         l = temp;
//         brojac++;
//     }
//     else{
//         fbrojac++;
//     }
    