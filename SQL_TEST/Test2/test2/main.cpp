#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Data::SQLite::Connector;


struct Person{
    std::string name;
    std::string tel;
    std::string  age;
};

void init(){
    Connector::registerConnector();
}

void del(){
    Connector::unregisterConnector();
}

int main(int argc, char *argv[]){


    init();
    //-create
    Session session("SQLite", "Sample.db");

    //-drop
    session << "DROP TABLE IF EXISTS Person", now;
    session << "CREATE TABLE Person (Name VARCHAR(20), TEL VARCHAR(12), Age VARCHAR(12)) ", now;

    //-insert
    Person person ={"Li", "13500001111", "12"};
    Statement insert(session);

    insert << "INSERT INTO Person VALUES('" + person.name + "' ,'" + person.tel + "' ,'" +person.age + "')";
    insert.execute();

    //-select
    Statement select(session);
    select << "SELECT Name, TEL, Age FROM Person",
            into(person.name),
            into(person.tel),
            into(person.age),
            range(0,1);
    while(!select.done()){
        select.execute();
    }

    //update
    std::string TELP = "110";
    std::string name = "Li";
    session << "update Person set TEL = ? WHERE Name= ?", use(TELP),use(name),now;

    del();

    return 0;
}
