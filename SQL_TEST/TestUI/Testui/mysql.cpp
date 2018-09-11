#include "mysql.h"
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


void SQL::init(){
    Connector::registerConnector();
}

void SQL::exit(){
     Connector::unregisterConnector();
}

void SQL::create(Session session){
    init();
    session << "DROP TABLE IF EXISTS Person", now;//-drop
    session << "CREATE TABLE Person (Name VARCHAR(20), TEL VARCHAR(12), Age VARCHAR(12)) ", now;
    exit();
}

void SQL::insert(Person person, Session session){
    init();
    Statement insert(session);
    insert << "INSERT INTO Person VALUES('" + person.name + "' ,'" + person.tel + "' ,'" +person.age + "')";
    insert.execute();
    exit();
}

void SQL::update(std::string TELP, std::string name, Session session){
    // name update TEL
    init();
    session << "update Person set TEL = ? WHERE Name= ?", use(TELP), use(name), now;
    exit();
}

void SQL::select(Person person, Session session){
    init();
    Statement select(session);
    select << "SELECT Name, TEL, Age FROM Person",
            into(person.name), into(person.tel), into(person.age), range(0,1);
    while(!select.done()){
        select.execute();
    }
    exit();
}

void SQL::del(std::string name, Session session){
    init();
    Statement del(session);
    del << "DELETE FROM Person WHERE Name = ?", use(name), now;
    exit();
}
