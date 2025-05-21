#include<iostream>
#include<map>
#include<vector>

using namespace std;

class Book{
    private:
        string isbn;
        int copAva;
        int totCop;
    public:
        string title;
        string author;
        Book(string title,string author,string isbn,int copava,int totCop){
            this->title = title;
            this->author = author;
            this->isbn = isbn;
            this->copAva = copava;
            this->totCop = totCop;
        }
        Book(){
            title = "UnknownTitle";
            author = "UnknownAuthor";
            isbn = "ISBN";
            copAva = 0;
            totCop = 5;
        }
        Book(Book& secbook,string newisbn){
            title = secbook.title;
            author = secbook.author;
            isbn = newisbn;
            copAva = secbook.copAva;
            totCop = secbook.totCop;
        }
        string getisbn(){
            return isbn;
        }
        int getcopAva(){
            return copAva;
        }
        int gettotCop(){
            return totCop;
        }
        void updateCopies(int count){
            if((count+copAva < 0) || (count+totCop < 0)){
                cout << "Invalid request! Count becomes negative" << endl;
                return;
            }
            copAva+=count;
            totCop+=count;
        }
        bool borrowBook(){
            if(copAva > 0){
                copAva--;
                return true;
            }
            cout << "Invalid request! Copy of book not available" << endl;
            return false; 
        }
        bool returnBook(){
            if(copAva >= totCop){
                cout << "Invalid request! Copy of book exceeds total copies" << endl;
                return false;
            }
            copAva++;
            return true;
        }
        void printDetails(){
            cout << title << " " << author<<" " << endl;
        }
    friend class Library;

};

class Member{
    private:
        string memID;
        map<string,int> borbooks;
        int borlim;
    public:
        string name;
        Member(string memID,string name){
            this->memID = memID;
            this->name = name;
            this->borlim = 3;
        }
        Member(string memID,string name,int borlim){
            this->memID = memID;
            this->name = name;
            this->borlim = borlim;
        }
        string getmemid(){
            return memID;
        }
        bool borrowBook(string isbn){
            int totbor = 0;
            for(auto & borbook : borbooks){
                totbor += borbook.second;
            }
            if(totbor < borlim){
                borbooks[isbn]++;
                return true;
            }
            cout << "Invalid request! Borrow limit exceeded" << endl;
            return false;   
        }
        bool returnBook(string isbn){
            if((borbooks.find(isbn) != borbooks.end()) && (borbooks[isbn] > 0)){
                borbooks[isbn]--;
                return true;
            }
            cout << "Invalid request! Book not borrowed" << endl;
            return false;
        }
        void printDetails(){
            for(auto & borbook : borbooks){
                if(borbook.second > 0){
                    cout << memID << " " << name <<" "<< borbook.first<<" "<<borbook.second<<endl; 
                }
            }
        }
    friend class Library;

};

class Library{
    private:
        vector<Book>books;
        vector<Member>members;
    public:
        bool addBook(Book& newbook){
            for(auto & book : books){
                if(book.getisbn() == newbook.getisbn()){
                    cout << "Invalid request! Book with same isbn already exists" << endl;
                    return false;
                }
            }
            books.push_back(newbook);
            return true;
        }
        vector<Book>& getvecbook(){
            return books;
        }
        bool registerMember(Member& mem){
            for(auto & member : members){
                if(member.memID == mem.memID){
                    cout << "Invalid request! Member with same id already exists" << endl;
                    return false;
                }
            }
            members.push_back(mem);
            return true;    
        }
        vector<Member>& getvecmem(){
            return members;
        }
        bool borrowBook(string memberID, string isbn){
            for(auto & book : books){
                if(book.getisbn()==isbn){
                    if(!book.borrowBook()){return false;}
                    for(auto & member : members){
                        if(member.memID == memberID){
                            if(!member.borrowBook(isbn)){
                                book.returnBook();
                                return false;
                            }
                            else{
                                return true;
                            }
                        }
                    }
                }
            }
            return false;
        }
        bool returnBook(string memberID, string isbn){
            for (auto & book : books){
                if (book.getisbn() == isbn) {
                    if(!book.returnBook()){return false;}
                    for (auto & member : members) {
                        if (member.memID == memberID) {
                            if (!member.returnBook(isbn)){
                                book.borrowBook();
                                return false;

                            }
                            return true;
                        }
                    }
                }
            }
            return false;
        }
        void printLibraryDetails(){
            for (auto & book : books) {
                cout << book.title << " " << book.author << " " << book.getcopAva() << endl;
            }
            for (auto & member : members) {
                cout << member.memID << " " << member.name << endl;
            }
        }
};

int main(){
    Library lib;
    string entity;
    while(cin>>entity && entity!= "Done"){
        if(entity == "Book"){
            string b;
            cin >> b;
            if((b != "None") && (b != "ExistingBook")){
                string author,isbn;
                int copAva,totCop;
                cin >> author >> isbn >> copAva >> totCop;
                Book b1(b,author,isbn,copAva,totCop);
                lib.addBook(b1);
            }else if(b == "ExistingBook"){
                string oldisbn,newisbn;
                cin >> oldisbn >> newisbn;
                vector<Book>& vecbook = lib.getvecbook();
                Book b1;
                for(auto & book : vecbook){
                    if(book.getisbn() == oldisbn){
                        Book b1(book,newisbn);
                        lib.addBook(b1);
                    }
                }
            }else if(b == "None"){
                Book b1;
                lib.addBook(b1);
            }

        }
        if(entity == "Member"){
            string m;
            cin >> m;
            if(m != "NoBorrowLimit"){
                string name;
                int blim;
                cin >> name >> blim; 
                Member m1(m,name,blim);
                lib.registerMember(m1);
            }else{
                string mid,name;
                cin >> mid >> name;
                Member m1(mid,name);
                lib.registerMember(m1);
            }
        }
        if(entity == "UpdateCopiesCount"){
            string isbn;
            int newCount;
            cin >> isbn >> newCount;
            vector<Book>& vecbook = lib.getvecbook();
            for(auto & book : vecbook){
                if(book.getisbn() == isbn){
                    book.updateCopies(newCount);
                }
            }
        }
        if(entity == "Borrow"){
            string memid,isbn;
            cin >> memid >> isbn;
            lib.borrowBook(memid,isbn);
        }
        if(entity == "Return"){
            string memid,isbn;
            cin >> memid >> isbn;
            lib.returnBook(memid,isbn);
        }
        if(entity == "PrintBook"){
            string isbn;
            cin >> isbn;
            vector<Book>& vecbook = lib.getvecbook();
            for(auto & book : vecbook){
                if(book.getisbn() == isbn){
                    book.printDetails();
                }
            }
        }
        if(entity == "PrintMember"){
            string memid;
            cin >> memid;
            vector<Member>& vecmem= lib.getvecmem();
            vecmem = lib.getvecmem();
            for(auto & member : vecmem){
                if(memid == member.getmemid()){
                    member.printDetails();
                }
            }
        }
        if(entity == "PrintLibrary"){
            lib.printLibraryDetails();
        }
    }
}