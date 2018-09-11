
#ifndef MYSQL_H
#define MYSQL_H

#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
using Poco::Data::Session;
using Poco::Data::Statement;

struct Person{
    std::string name;
    std::string tel;
    std::string age;
};

namespace xx {
class SQL;
}

class SQL{
public:
    SQL(){}
    ~SQL(){}
    void init();
    void exit();
    void create(Session session);
    void insert(Person person, Session session);
    void update(std::string TELP, std::string name, Session session);
    void select(Person person, Session session);
    void del(std::string name, Session session);
private:
};//class SQL

#endif // MYSQL_H


