#ifndef USER_H
#define USER_H

class User
{
private:
    int id;
    std::string name;
    unsigned int windCount;
    unsigned int defeatsCount;
public:
    User(/* args */);
    ~User();
    std::string getName();
    int getId();
    unsigned getWinsCount();
    unsigned getDefeatsCount();
};

User::User(/* args */)
{
}

User::~User()
{
}

#endif  // USER_H
