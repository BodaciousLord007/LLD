#include<iostream>
using namespace std;

class User{
private:
    string name;
    string email;
    string phone;
public:
    User(const string &name, const string &email, const string &phone): name(name), email(email), phone(phone){}
    void print() const{
        cout << "Name:" << this->name << "\n";
        cout << "Email:" << this->email << "\n";
        cout << "Phone:" << this->phone << "\n";
    }
    class userBuilder
    {
    private:
        string name;
        string email;
        string phone;

    public:
        userBuilder &withName(const string &name)
        {
            this->name = name;
            return *this;
        }
        userBuilder &withEmail(const string &email)
        {
            this->email = email;
            return *this;
        }
        userBuilder &withPhone(const string &phone)
        {
            this->phone = phone;
            return *this;
        }
        User build(){
            return User(name, email, phone);
        }
    };
};
int main(){
    User u = User::userBuilder()
                 .withName("Anurag")
                 .withEmail("abc&email.com")
                 .withPhone("123")
                 .build();
    u.print();
    return 0;
}