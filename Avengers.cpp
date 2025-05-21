#include<bits/stdc++.h>

using namespace std;

class QNS{
    private:
        //variables
        int P;//powerLevel
        int D;//Durability
        int E;//energyStorage
        int H;//heatLevel

    public:
        //Constructors
        //1.parametrized constructor
        QNS(int P,int D,int E,int H){
            this->P = min(P,5000);
            this->D = D;
            this->E = E;
            this->H = max(H,0);
        }
        
        //2.Copy constructor
        QNS(const QNS& qns){
            P = min(qns.P,5000);
            D = qns.D;
            E = qns.E;
            H = max(qns.H,0);
        }
        //3.default constructor
        QNS(){
            //default values
            P = 1000;
            D = 500;
            E = 300;
            H = 0;
        }
        //4

        //Operator Overloading
        //1.Addition
        QNS operator+(const QNS& qns){
            QNS temp = *this;
            temp.P += qns.E;
            temp.D += qns.D;
            temp.E += qns.P;
            if (temp.P > 5000) {
                temp.P = 5000;
            }
            return temp;
        }
        
        //2.Suntraction
        QNS operator-(int X){
            QNS temp = *this;
            temp.D -= X;
            temp.E += X;
            temp.H += X;
            return temp;
        }
        
        //3.Multiplication
        QNS operator*(int X){
            QNS temp = *this;  // Copy current object
            temp.P = temp.P + ((temp.P * X) / 100);
            temp.E = temp.E + (5 * X);
            temp.H = temp.H + X;
            if (temp.P > 5000) {
                temp.P = 5000;
            }
            return temp;
        }
        
        //4.Division
        QNS operator/(int X){
            //According to formula
            QNS temp = *this;
            temp.D += X;
            temp.E = E;
            temp.H -= X;
            if(temp.H < 0){temp.H = 0;}
            return temp;
        }

        //Function Overloading
        QNS& boostPower(int factor){
            *this = *this * factor;
            return *this;
        }
        
        QNS& boostPower(QNS& otherSuit){
            //using + operator qns = otherSuit
            *this = *this + otherSuit;
            if(P > 5000){
                setP(5000);
            }
            return *this;
        }

        //Comparision Overloading
        bool operator ==(QNS& qns){
            //whether suit are eaqual or not
            if(P == qns.P && D == qns.D){
                return true;
            }
            return false;
        }
        bool operator <(QNS& qns){
            //compares suits effectiveness
            if((P + D) < (qns.P + qns.D)){
                return true;
            }
            return false;
        }
        //Other functions
        bool isOverheated(){ 
            return H > 500; 
        }
        bool isDestroyed(){
            return D <= 0; 
        }
        //getters
        int getP(){
            return P;//get P
        }
        int getD(){
            return D;//get D
        }
        int getE(){
            return E;//get E
        }
        int getH(){
            return H;//get H
        }
        //setters
        void setP(int X){
            P = X;
        }
        void setD(int X){
            D = X;
        }
        void setE(int X){
            E = X;
        }
        void setH(int X){
            H = X;
        }
        

};

class Avenger{
    private:
        string name;//Avenger name
        QNS suit;//his suit
        int AS;//attackStrength
    public:
        Avenger(string avName, QNS& avSuit, int strength){
            name = avName;
            suit = avSuit;
            AS = strength;
        }
        QNS& attack(Avenger& enemy){
            //using - operator in QNS class
            if(!suit.isOverheated() && !suit.isDestroyed()){
                if(!enemy.suit.isDestroyed())
                    enemy.suit=enemy.suit - AS;
            }
            return enemy.suit;
        }
        QNS& upgradeSuit(QNS& qns){
            //using + operation in QNS system
            suit = suit + qns;
            return suit;
        }
        QNS& repair(int x){
            //using / operator in QNS sys
            suit = suit / x;
            return suit;
        }
        void printStatus(){
            cout << name << " " << suit.getP() << " " << suit.getD() << " " << suit.getE() << " " << suit.getH() << endl; 
        }
        QNS& getSuit(){
            return suit;
        }
        string getName(){
            return name;
        }
        QNS& boostPower(int X){
            return suit.boostPower(X);
        }
        QNS& boostPower(QNS &otherSuit){
            return suit.boostPower(otherSuit);
        }
        int score(){
            /*if(suit.isOverheated()){
                return 0;
            }
            if(suit.isDestroyed()){
                return suit.getP();
            }
            return suit.getP()+suit.getD();*/
            return suit.getP()+suit.getD();
        }
};

class Battle{
    private:
        vector<Avenger>heroes;
        vector<Avenger>enemies;
        vector<string>battleLog;
    public:
        void add_hero(Avenger& h){
            heroes.push_back(h);
        }
        void add_enemy(Avenger& e){
            enemies.push_back(e);
        }
        void repair(string name,int X){
            for(Avenger &hero : heroes){
                if(hero.getName() == name){
                    hero.repair(X);
                    battleLog.push_back(name+" repaired");
                    return;
                }
            }
        }
        void attack(string name1,string name2){
            for(Avenger& h: heroes){
                if(h.getName() == name1){
                    for(Avenger& e: enemies){
                        if(e.getName() == name2){
                            h.attack(e);
                            battleLog.push_back(name1+" attacks "+name2);
                            if(e.getSuit().isDestroyed()){
                                battleLog.push_back(name2+" suit destroyed");
                                return;
                            }
                            if(e.getSuit().isOverheated()){
                                battleLog.push_back(name2+" suit overheated");
                            }
                            return;
                        }
                    }
                }
            }
            for(Avenger& e: enemies){
                if(e.getName() == name1){
                    for(Avenger& h: heroes){
                        if(h.getName() == name2){
                            e.attack(h);
                            battleLog.push_back(name1+" attacks "+name2);
                            if(h.getSuit().isDestroyed()){
                                battleLog.push_back(name2+" suit destroyed");
                                return;
                            }
                            if(h.getSuit().isOverheated()){
                                battleLog.push_back(name2+" suit overheated");
                            }
                            return;
                        }
                    }
                }
            }
            for(Avenger& h: heroes){
                if(h.getName() == name1){
                    for(Avenger& e: heroes){
                        if(e.getName() == name2){
                            h.attack(e);
                            battleLog.push_back(name1+" attacks "+name2);
                            if(e.getSuit().isDestroyed()){
                                battleLog.push_back(name2+" suit destroyed");
                                return;
                            }
                            if(e.getSuit().isOverheated()){
                                battleLog.push_back(name2+" suit overheated");
                            }
                            return;
                        }
                    }
                }
            }
            for(Avenger& e: enemies){
                if(e.getName() == name1){
                    for(Avenger& h: enemies){
                        if(h.getName() == name2){
                            e.attack(h);
                            battleLog.push_back(name1+" attacks "+name2);
                            if(h.getSuit().isDestroyed()){
                                battleLog.push_back(name2+" suit destroyed");
                                return;
                            }
                            if(h.getSuit().isOverheated()){
                                battleLog.push_back(name2+" suit overheated");
                            }
                            return;
                        }
                    }
                }
            }
        }
        void boostpowerbyfactor(string name,int y){
            for(Avenger& h: heroes){
                if(h.getName() == name){
                    h.boostPower(y);
                    battleLog.push_back(name+" boosted");
                    if(h.getSuit().isOverheated()){
                        battleLog.push_back(name+" suit overheated");
                    }
                    return;
                }
            }
            for(Avenger& e: enemies){
                if(e.getName() == name){
                    e.boostPower(y);
                    battleLog.push_back(name+" boosted");
                    if(e.getSuit().isOverheated()){
                        battleLog.push_back(name+" suit overheated");
                    }
                    return;
                }
            }
        }
        void boostpower(string name,QNS& otherSuit){
            for(Avenger& h: heroes){
                if(h.getName() == name){
                    h.boostPower(otherSuit);
                    battleLog.push_back(name+" boosted");
                    if(h.getSuit().isOverheated()){
                        battleLog.push_back(name+" suit overheated");
                    }
                    return;
                }
            }
            for(Avenger& e: enemies){
                if(e.getName() == name){
                    e.boostPower(otherSuit);
                    battleLog.push_back(name+" boosted");
                    if(e.getSuit().isOverheated()){
                        battleLog.push_back(name+" suit overheated");
                    }
                    return;
                }
            }
        }
        void printStatus(string name){
            for(Avenger& h: heroes){
                if(h.getName() == name){
                    h.printStatus();
                    return;
                }
            }
            for(Avenger& e: enemies){
                if(e.getName() == name){
                    e.printStatus();
                    return;
                }
            }
        }
        void upgardesuit(string name,QNS& q){
            for(Avenger& h: heroes){
                if(h.getName() == name){
                    h.upgradeSuit(q);
                    battleLog.push_back(name+" upgraded");
                    return;
                }
            }
            for(Avenger& e: enemies){
                if(e.getName() == name){
                    e.upgradeSuit(q);
                    battleLog.push_back(name+" upgraded");
                    return;
                }
            }
        }
        void startBattle(vector<QNS>&suits,int k,int n,int m){
            int noA = n+m;
            //starts the battle(takes input)
            string command;
            while(cin >> command && command != "End"){
                if(command == "Attack"){
                    string name1,name2;
                    cin >> name1 >> name2;
                    attack(name1,name2);
                }else if(command == "Repair"){
                    string name;
                    int X;
                    cin >> name >> X;
                    repair(name,X);
                }else if(command == "BoostPowerByFactor"){
                    string name;
                    int y;
                    cin >> name >> y;
                    boostpowerbyfactor(name,y);
                }else if(command == "BoostPower"){
                    string name;
                    int P,D,E,H;
                    cin >> name >> P >> D >> E >> H;
                    QNS otherSuit(P,D,E,H);
                    boostpower(name,otherSuit);
                }else if(command == "AvengerStatus"){
                    string name;
                    cin >> name;
                    printStatus(name);
                }else if(command == "Upgrade"){
                    string name;
                    cin >> name;
                    
                    if(noA < k){
                        upgardesuit(name,suits[noA]);
                        noA++;
                    }else battleLog.push_back(name+" upgrade Fail");
                }else if(command == "PrintBattleLog"){
                    printBattleLog();
                }else if(command == "BattleStatus"){
                    if(Result() == 1){
                        cout << "heroes are winning" << endl;
                    }else if(Result() == -1){
                        cout << "enemies are winning" << endl;
                    }else{
                        cout << "tie" << endl;
                    }
                }
            }
        }
        void printBattleLog(){
            //prints battleLog \n
            for(string& s: battleLog){
                cout << s << endl;
            }
        }
        int Result(){
            //if res = 1 win
            //if res = 0 tie
            //if res = -1 loose
            int hs = 0;
            int es = 0;
            for(Avenger& A: heroes){
                if(!A.getSuit().isDestroyed()){
                    hs += A.score();
                }
            }
            for(Avenger& A: enemies){
                if(!A.getSuit().isDestroyed()){
                    es += A.score();
                }
            }
            if(hs > es){return 1;}
            else if(hs < es){return -1;}
            else return 0;
        }
        
};

int main(){
    int k,n,m;
    cin >> k >> n >> m;
    vector<QNS>suits;
    int P,D,E,H;
    for(int i=0;i<k;i++){
        cin >> P >> D >> E >> H;
        P = min(5000,P);
        QNS suit(P,D,E,H);
        suits.push_back(suit);
    }

    Battle battle;
    string name;
    int as;
    for(int i=0;i<n+m;i++){
        cin >> name >> as;
        if(i<n){
            Avenger A(name,suits[i],as);
            battle.add_hero(A);
        }else if(i<k){
            Avenger A(name,suits[i],as);
            battle.add_enemy(A);
        }else{
            cout << name << " is out of fight" << endl;
        }
    }
    string s;
    cin >> s;
    if(s == "BattleBegin"){
        battle.startBattle(suits,k,n,m);
    }


    return 0;
}
