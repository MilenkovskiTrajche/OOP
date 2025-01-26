#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;
class StudentFailedException {
private:
    string id;
public:
    StudentFailedException(string id) {
        this->id = id;
    }
    void print() {
        cout<<"Student with id "<<id <<" failed the course"<<endl;
    }
};
class Student {
private:
    string index;
    string name;
    string surname;
    int poeni;
public:
    Student() {}
    Student(string index, string name, string surname, int poeni) {
        this->index = index;
        this->name = name;
        this->surname = surname;
        this->poeni = poeni;
    }
    int grade() const{
        int grade=0;
        if (poeni>=0 && poeni<50) {
            grade=5;
        }
        if (poeni>=50 && poeni<60) {
            grade=6;
        }
        if (poeni>=60 && poeni<70) {
            grade=7;
        }
        if (poeni>=70 && poeni<80) {
            grade=8;
        }
        if (poeni>=80 && poeni<90) {
            grade=9;
        }
        if (poeni>=90 && poeni<=100) {
            grade=10;
        }
        return grade;

    }
    string getIndex() {
        return index;
    }
    friend ostream& operator<<(ostream& os, Student& student) {
        os << student.index<<" "<<student.name<<" "<<student.surname<<" "<<student.poeni;
        os<<" Grade: "<<student.grade();
    }
    string getName() {
        return name;
    }
    string getSurname() {
        return surname;
    }
    int getPoeni() {
        return poeni;
    }
    ~Student() {}
};

class Results {
private:
    Student *s;
    int n;
public:
    Results() {
        this->n=0;
        this->s = new Student[n];
    }
    Results(Student *s, int n) {
        this->n = n;
        this->s = new Student[n];
        for (int i = 0; i < n; i++) {
            this->s[i] = s[i];
        }
    }
    Results& operator +=(Student &nov) {
        if (nov.getPoeni()<50) {
            throw StudentFailedException(nov.getIndex());
        }
        Student *temp = new Student[n+1];
        for (int i = 0; i < n; i++) {
            temp[i] = s[i];
        }
        temp[n] = nov;
        delete []s;
        s = temp;
        this->n++;
        return *this;
    }
    friend ostream& operator<<(ostream& os, Results& results) {
        for (int i = 0; i < results.n; i++) {
            os<<results.s[i]<<endl;
        }
        return os;
    }
    Results withGrade(int grade) {
        Results vrakja;
        for (int i = 0; i < n; i++) {
            if (s[i].grade()==grade) {
                vrakja+=s[i];
            }

        }
        return vrakja;
    }
    void zapishi() {
        ofstream out1("output1.txt",ios::out);
        if (!out1.is_open()) {
            cout<<"Can't open output file"<<endl;
            return;
        }
        for (int i = 0; i < n; i++) {
            out1<<s[i]<<endl;
        }
        out1.close();
    }
    int getN() {
        return n;
    }
    Student* getStudent() {
        return s;
    }
    ~Results() {
        delete []s;
    }
};

void wtf() {
    ofstream fout("input.txt");
    string line;
    while (getline(std::cin, line)) {
        if (line == "----"){
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

    Results results;
    //TODO your code here
    //TODO Read the students from the file and add them in `results`
    ifstream fin("input.txt");
    if (!fin.is_open()) {
        cout<<"File not found"<<endl;
        return 1;
    }
    string index,ime,prezime;
    int poeni;
    while (fin>>index>>ime>>prezime>>poeni) {
        fin.ignore();
        Student s(index,ime,prezime,poeni);
        try {
            results += s;
        }catch (StudentFailedException &e) {
            e.print();
        }
    }
    fin.close();

    results.zapishi();

    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE NEXT COMMENT
    int grade;
    cin >> grade;
    //DO NOT MODIFY THE CODE BETWEEN THIS AND THE PREVIOUS COMMENT

    //TODO Save the results in the files output1.txt and output2.txt after this line

    Results nov = results.withGrade(grade);
    ofstream fout("output2.txt",ios::out);
    for (int i=0;i<nov.getN();i++) {
        fout<<nov.getStudent()[i].getIndex()<<" "<<nov.getStudent()[i].getName()<<" "
        <<nov.getStudent()[i].getSurname()<<" "<<nov.getStudent()[i].getPoeni()
        <<" Grade: "<<nov.getStudent()[i].grade()<<endl;
    }
    if (nov.getN()==0) {
        fout<<"None"<<endl;
    }


    results.zapishi();

    //DO NOT MODIFY THE CODE BELLOW

    cout << "All students:" << endl;
    rff("output1.txt");
    cout << "Grade report for grade " << grade << ": " << endl;
    rff("output2.txt");


    return 0;
}