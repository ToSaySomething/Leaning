#include "mainwindow.h"
#include <QApplication>

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
    std::string age;
};

class SQL{
  public:
    SQL(){}
    ~SQL(){}
    void init(){
        Connector::registerConnector();
    }

    void exit(){
         Connector::unregisterConnector();
    }

    void create(Session session){
        init();
//        Session session("SQLite", "Sample.db");
        session << "DROP TABLE IF EXISTS Person", now;//-drop
        session << "CREATE TABLE Person (Name VARCHAR(20), TEL VARCHAR(12), Age VARCHAR(12)) ", now;
        exit();
    }

    void insert(Person person, Session session){
        init();
        Statement insert(session);
        insert << "INSERT INTO Person VALUES('" + person.name + "' ,'" + person.tel + "' ,'" +person.age + "')";
        insert.execute();
        exit();
    }

    void update(std::string TELP, std::string name, Session session){
        //update
        //std::string TELP = "110";
        //std::string name = "Li";
        init();
        session << "update Person set TEL = ? WHERE Name= ?", use(TELP), use(name), now;
        exit();
    }

    void select(Person person, Session session){
        init();
        Statement select(session);
        select << "SELECT Name, TEL, Age FROM Person",
                into(person.name), into(person.tel), into(person.age), range(0,1);
        while(!select.done()){
            select.execute();
        }
        exit();
    }

    void del(std::string name, Session session){
        init();
        Statement del(session);
        del << "DELETE FROM Person WHERE Name = ?", use(name), now;
        exit();
    }
  private:


};


int main(int argc, char *argv[]){

    SQL sql1;
    sql1.init();
    Session session("SQLite", "Sample.db");

    Person person = {"An","xx","111"};

    sql1.create(session);

    sql1.insert(person, session);

    sql1.select(person, session);

    std::string TELP = "110";
    std::string name = "An";
    sql1.update(TELP, name, session);


    person.name = "Li";
    person.tel = "232";
    person.age = "101";
    sql1.insert(person, session);

    std::string name1 = "Li";
    sql1.del(name1, session);

    sql1.exit();

    return 0;
}
