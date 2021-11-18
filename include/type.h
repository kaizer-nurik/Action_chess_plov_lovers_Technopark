#ifndef TYPE_H
#define TYPE_H


class Type
{
private:
    int style;
public:
    Type(/* args */);
    ~Type();
    bool getType();
    bool setType();
};

Type::Type(/* args */)
{
    getType();
    setType();
}

Type::~Type()
{
}

#endif // !TYPE_H