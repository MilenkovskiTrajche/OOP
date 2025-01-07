#include <iostream>
#include <cstring>
#include <string>

using namespace std;

class ExistingGame
{
private:
    char *msg;
public:
    ExistingGame()
    {
        this->msg = new char[0];
    }
    ExistingGame(char *msg)
    {
        this->msg = new char[strlen(msg)+1];
        strcpy(this->msg,msg);
    }
    void message()
    {
        cout<<msg<<endl;
    }
    ~ExistingGame()
    {
        delete []msg;
    }
};

class Game
{
protected:
    char game_name[100];
    float game_price;
    bool game_on_sale;
public:
    Game(){}
    Game(char *game_name,float game_price,bool game_on_sale)
    {
        strcpy(this->game_name,game_name);
        this->game_price = game_price;
        this->game_on_sale = game_on_sale;
    }
    
    bool operator==(const Game &g)
    {
        return strcmp(this->game_name,g.game_name)==0;
    }
    bool getOnSale()
    {
        return game_on_sale;
    }
    virtual void print()
    {
        cout<<"Game: "<<game_name<<", regular price: $"<<game_price;
        if(game_on_sale)
            cout<<", bought on sale";
    }
    char* getGameName()
    {
        return game_name;
    }
    
    float getPrice()
    {
        return game_price;
    }
    friend  ostream& operator<<(ostream &out, Game &g)
    {
        g.print();
        return out;
    }
    
    
    
    virtual void read()
    {
        getchar();
        cin.getline(game_name,100);
        cin>>game_price>>game_on_sale;
    }
    friend istream& operator>>(istream &in,Game &g)
    {
        g.read();
        return in;
    }
    virtual ~Game(){}
};

class SubscriptionGame : public Game
{
private:
    float sub_game_monthly_fee;
    int sub_game_month;
    int sub_game_year;
public:
    SubscriptionGame (): Game(){}
    
    SubscriptionGame(char *game_name,float game_price,bool game_on_sale,
                     float sub_game_monthly_fee, int sub_game_month, int sub_game_year) : Game(game_name,game_price,game_on_sale)
    {
        this->sub_game_monthly_fee = sub_game_monthly_fee;
        this->sub_game_month = sub_game_month;
        this->sub_game_year = sub_game_year;
    }
    float getFee()
    {
        return sub_game_monthly_fee;
    }
    int getYear()
    {
        return sub_game_year;
    }
    int getMonth()
    {
        return sub_game_month;
    }
    void print()
    {
        Game::print();
        cout<<", monthly fee: $"<<sub_game_monthly_fee<<", purchased: "<<sub_game_month<<"-"<<sub_game_year<<endl;
    }
//    friend ostream& operator<<(ostream &out, SubscriptionGame &sg)
//    {
//        sg.print();
//        return out;
//    }
    
    void read()
    {
        Game::read();
        cin>>sub_game_monthly_fee>>sub_game_month>>sub_game_year;
    }
//    friend istream& operator>>(istream &in,SubscriptionGame &sg)
//    {
//        sg.read();
//        return in;
//    }
    ~SubscriptionGame(){}
};


class User
{
private:
    char username[100];
    Game **g;
    int n;
public:
    User()
    {
        this->n=0;
        g = new Game*[0];
    }
    User(char *username)
    {
        strcpy(this->username,username);
        this->n = 0;
        this->g = new Game*[0];
    }
    User (const User &u)
    {
        strcpy(this->username,u.username);
        this->n = u.n;
        this->g = new Game*[n];
        for(int i=0;i<n;i++)
        {
            this->g[i] = u.g[i];
        }
    }
    User& operator= (const User &u)
    {
        if(this!=&u)
        {
            delete []g;
            strcpy(this->username,u.username);
            this->n = u.n;
            this->g = new Game*[n];
            for(int i=0;i<n;i++)
            {
                this->g[i] = u.g[i];
            }
        }
        
        return *this;
    }
    
    User& operator+=(Game &nova)
    {
        for(int i=0;i<n;i++)
        {
            if(strcmp(g[i]->getGameName(),nova.getGameName())==0)
            {
                throw ExistingGame("The game is already in the collection");
            }
        }
        
        Game **temp = new Game*[n+1];
        for(int i=0;i<n;i++)
        {
            temp[i] = g[i];
        }
        temp[n] = &nova;
        n++;
        delete []g;
        g = temp;
        return *this;
    }
    friend ostream& operator<<(ostream &out,const User &u)
    {
        out<<"User: "<<u.username<<endl;
        for(int i=0;i<u.n;i++)
        {
            cout<<*u.g[i];
        }
        return out;
    }
   
    float total_spent()
    {
        float sum =0;
        for(int i=0;i<n;i++)
        {
            if(g[i]->getOnSale())
            {
                sum+=g[i]->getPrice() - g[i]->getPrice()*30/100;
            }
            
            else {
                sum+=g[i]->getPrice();
            }
            SubscriptionGame *sg = dynamic_cast<SubscriptionGame*>(g[i]);
            if(sg!=0)
            {
                int god =2018 -  sg->getYear();
                int month = 4 - sg->getMonth();
                sum+= (god * 12 + month) * sg->getFee();
            }
        }
        return sum;
    }
    ~User()
    {
        delete []g;
    }
};

int main() {
  int test_case_num;

  cin>>test_case_num;

  // for Game
  char game_name[100];
  float game_price;
  bool game_on_sale;

  // for SubscritionGame
  float sub_game_monthly_fee;
  int sub_game_month, sub_game_year;

  // for User
  char username[100];
  int num_user_games;

  if (test_case_num == 1){
    cout<<"Testing class Game and operator<< for Game"<<std::endl;
    cin.get();
    cin.getline(game_name,100);
    //cin.get();
    cin>>game_price>>game_on_sale;

    Game g(game_name, game_price, game_on_sale);

    cout<<g;
  }
  else if (test_case_num == 2){
    cout<<"Testing class SubscriptionGame and operator<< for SubscritionGame"<<std::endl;
    cin.get();
    cin.getline(game_name, 100);

    cin>>game_price>>game_on_sale;

    cin>>sub_game_monthly_fee;
    cin>>sub_game_month>>sub_game_year;

    SubscriptionGame sg(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
    cout<<sg;
  }
  else if (test_case_num == 3){
    cout<<"Testing operator>> for Game"<<std::endl;
    Game g;

    cin>>g;

    cout<<g;
  }
  else if (test_case_num == 4){
    cout<<"Testing operator>> for SubscriptionGame"<<std::endl;
    SubscriptionGame sg;

    cin>>sg;

    cout<<sg;
  }
  else if (test_case_num == 5){
    cout<<"Testing class User and operator+= for User"<<std::endl;
    cin.get();
    cin.getline(username,100);
    User u(username);

    int num_user_games;
    int game_type;
    cin >>num_user_games;

    try {

      for (int i=0; i<num_user_games; ++i){

        cin >> game_type;

        Game *g;
        // 1 - Game, 2 - SubscriptionGame
        if (game_type == 1){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;
          g = new Game(game_name, game_price, game_on_sale);
        }
        else if (game_type == 2){
          cin.get();
          cin.getline(game_name, 100);

          cin>>game_price>>game_on_sale;

          cin>>sub_game_monthly_fee;
          cin>>sub_game_month>>sub_game_year;
          g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
        }

        //cout<<(*g);

          try {
              u+=(*g);
          } catch (ExistingGame &eg) {
              eg.message();
          }
        
      }
    }catch(ExistingGame &ex){
      ex.message();
    }

    cout<<u;

//    cout<<"\nUser: "<<u.get_username()<<"\n";

//    for (int i=0; i < u.get_games_number(); ++i){
//        Game * g;
//        SubscriptionGame * sg;
//        g = &(u.get_game(i));

//        sg = dynamic_cast<SubscriptionGame *> (g);

//        if (sg){
//          cout<<"- "<<(*sg);
//        }
//        else {
//          cout<<"- "<<(*g);
//        }
//        cout<<"\n";
//    }

  }
  else if (test_case_num == 6){
      cout<<"Testing exception ExistingGame for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);

          try {
            u+=(*g);
          }
          catch(ExistingGame &ex){
            ex.message();
          }
        }

      cout<<u;

//      for (int i=0; i < u.get_games_number(); ++i){
//          Game * g;
//          SubscriptionGame * sg;
//          g = &(u.get_game(i));

//          sg = dynamic_cast<SubscriptionGame *> (g);

//          if (sg){
//            cout<<"- "<<(*sg);
//          }
//          else {
//            cout<<"- "<<(*g);
//          }
//          cout<<"\n";
//      }
  }
  else if (test_case_num == 7){
      cout<<"Testing total_spent method() for User"<<std::endl;
      cin.get();
      cin.getline(username,100);
      User u(username);

      int num_user_games;
      int game_type;
      cin >>num_user_games;

      for (int i=0; i<num_user_games; ++i){

          cin >> game_type;

          Game *g;
          // 1 - Game, 2 - SubscriptionGame
          if (game_type == 1){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;
            g = new Game(game_name, game_price, game_on_sale);
          }
          else if (game_type == 2){
            cin.get();
            cin.getline(game_name, 100);

            cin>>game_price>>game_on_sale;

            cin>>sub_game_monthly_fee;
            cin>>sub_game_month>>sub_game_year;
            g = new SubscriptionGame(game_name, game_price, game_on_sale, sub_game_monthly_fee, sub_game_month, sub_game_year);
          }

          //cout<<(*g);


          try {
              u+=(*g);
          } catch (ExistingGame &eg) {
              eg.message();
          }
        }

      cout<<u;

      cout<<"Total money spent: $"<<u.total_spent()<<endl;
  }
}


