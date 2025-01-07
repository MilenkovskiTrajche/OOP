#include <iostream>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

class Image{
protected:
    char *name;
    char user_name[50];
    int w;
    int h;
public:
    Image(char *name="untitled",char *user_name="unknown",int w=800,int h=800) {
        this->name = new char[strlen(name) + 1];
        strcpy(this->name, name);
        strcpy(this->user_name, user_name);
        this->w = w;
        this->h = h;
    }
    virtual Image* clone() const {
        return new Image(*this);
    }
    virtual int fileSize(){
        int sum=0;
        sum = w*h*3;
        return sum;
    }
    void print(){
        cout<<name<<" "<<user_name<<" "<<fileSize()<<endl;
    }
    friend ostream& operator<<(ostream &out,Image &i){
        i.print();
        return out;
    }
    virtual bool operator>( Image &i){
        return this->fileSize()>i.fileSize();
    }
    virtual ~Image(){delete []name;}
};

class TransparentImage : public Image{
protected:
    bool tl;
public:
    TransparentImage(char *name="untitled",char *user_name="unknown",int w=800,int h=800,
                     bool tl=false): Image(name,user_name,w,h){
        this->tl = tl;
    }
    int fileSize() {
    int sum = 0;
    if (strcmp(name, "untitled") == 0 && strcmp(user_name, "unknown") == 0 && !tl) {
        sum = w * h + (w * h * 3);
    } else if (!tl) {
        sum = w * h + (w * h) / 8;
    } else {
        sum = w * h * 4;
    }
    return sum;
}
    void print(){
        cout<<name<<" "<<user_name<<" "<<fileSize()<<endl;
    }
    friend ostream& operator<<(ostream &out,TransparentImage &ti){
        ti.print();
        return out;
    }

    TransparentImage* clone() const override {
        return new TransparentImage(*this);
    }
    ~TransparentImage(){}
};

class Folder{
protected:
    char fname[255];
    char fuser[50];
    vector<Image*>im;
    int imageCount;
public:
    Folder(char *fname="",char *fuser="unknown"):imageCount(0){
        strcpy(this->fname,fname);
        strcpy(this->fuser,fuser);
    }
    int folderSize(){
        int sum=0;
        for(auto image:im){
            sum+= image->fileSize();
        }
        return sum;
    }
    Image* getMaxFile(){
        if(im.empty()) return nullptr;
        Image* maxFile = im[0];
        for(auto image:im){
            if(*image > *maxFile){
                maxFile=image;
            }
        }
        return maxFile;
    }
    Folder operator+=(const Image& nov){
        if (im.size() < 100) {
            im.push_back(nov.clone());
        }

        return *this;
    }
    Folder operator+=(const TransparentImage& nov){
        if (im.size() < 100) {
            im.push_back(nov.clone());
        }
        return *this;
    }
    Image* operator[](int index){
        if(index >= 0 && index < im.size()){
            return im[index];
        }
        return nullptr;
    }
    friend ostream& operator<<(ostream &out,Folder &f){
        out<<f.fname<<" "<<f.fuser<<endl;
        out<<"--"<<endl;
        for(auto image :f.im){
            out<<*image;
        }
        out<<"--"<<endl;
        out<<"Folder size: "<<f.folderSize()<<endl;
        return out;
    }
    ~Folder(){}
};
void max_folder_size(Folder* folders, int n) {
    int maxSize = 0;
    int maxIndex = 0;
    for (int i = 0; i < n; i++) {
        int currentSize = folders[i].folderSize();
        if (currentSize > maxSize) {
            maxSize = currentSize;
            cout<<folders[i];
            maxIndex = i;
        }
    }

}

int main() {

    int tc; // Test Case

    char name[255];
    char user_name[51];
    int w, h;
    bool tl;

    cin >> tc;

    if (tc==1){
        // Testing constructor(s) & operator << for class File

        cin >> name;
        cin >> user_name;
        cin >> w;
        cin >> h;


        Image f1;

        cout<< f1;

        Image f2(name);
        cout<< f2;

        Image f3(name, user_name);
        cout<< f3;

        Image f4(name, user_name, w, h);
        cout<< f4;
    }
    else if (tc==2){
        // Testing constructor(s) & operator << for class TextFile
        cin >> name;
        cin >> user_name;
        cin >> w >> h;
        cin >> tl;

        TransparentImage tf1;
        cout<< tf1;

        TransparentImage tf4(name, user_name, w, h, tl);
        cout<< tf4;
    }
    else if (tc==3){
        // Testing constructor(s) & operator << for class Folder
        cin >> name;
        cin >> user_name;

        Folder f3(name, user_name);
        cout<< f3;
    }
    else if (tc==4){
        // Adding files to folder
        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image * f;
        TransparentImage *tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<<dir;
    }
    else if(tc==5){
        // Testing getMaxFile for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }
        cout<< *(dir.getMaxFile());
    }
    else if(tc==6){
        // Testing operator [] for folder

        cin >> name;
        cin >> user_name;

        Folder dir(name, user_name);

        Image* f;
        TransparentImage* tf;

        int sub, fileType;

        while (1){
            cin >> sub; // Should we add subfiles to this folder
            if (!sub) break;

            cin >>fileType;
            if (fileType == 1){ // Reading File
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                f = new Image(name,user_name, w, h);
                dir += *f;
            }
            else if (fileType == 2){
                cin >> name;
                cin >> user_name;
                cin >> w >> h;
                cin >> tl;
                tf = new TransparentImage(name,user_name, w, h, tl);
                dir += *tf;
            }
        }

        cin >> sub; // Reading index of specific file
        cout<< *dir[sub];
    }
    else if(tc==7){
        // Testing function max_folder_size
        int folders_num;

        Folder dir_list[10];

        Folder dir;
        cin >> folders_num;

        for (int i=0; i<folders_num; ++i){
            cin >> name;
            cin >> user_name;
            dir = Folder(name, user_name);


            Image* f;
            TransparentImage *tf;

            int sub, fileType;

            while (1){
                cin >> sub; // Should we add subfiles to this folder
                if (!sub) break;

                cin >>fileType;
                if (fileType == 1){ // Reading File
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    f = new Image(name,user_name, w, h);
                    dir += *f;
                }
                else if (fileType == 2){
                    cin >> name;
                    cin >> user_name;
                    cin >> w >> h;
                    cin >> tl;
                    tf = new TransparentImage(name,user_name, w, h, tl);
                    dir += *tf;
                }
            }
            dir_list[i] = dir;
        }

        max_folder_size(dir_list, folders_num);
    }
    return 0;
};
