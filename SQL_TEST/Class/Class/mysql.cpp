#include "mysql.h"
#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/Data/RecordSet.h"
#include <vector>
#include <iostream>
#include <sstream>

using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Data::SQLite::Connector;


void MYSQL::init()
{
    Connector::registerConnector();
}

void MYSQL::exit()
{
     Connector::unregisterConnector();
}

void MYSQL::create()
{
    init();
    Session session = getsession();
    session << "DROP TABLE IF EXISTS Person", now;//-drop
    session << "CREATE TABLE Person (Name VARCHAR(20), ID VARCHAR(12), Email VARCHAR(12)) ", now;
    exit();
}
void MYSQL::insert(Person person)
{
    init();
    Session session = getsession();
    Statement insert(session);
    insert << "INSERT INTO Person VALUES('" + person.name + "' ,'" + person.id + "' ,'" +person.email + "')";
    insert.execute();
    exit();
}

void MYSQL::update(Person person)
{
    // name update id
    init();
    Session session = getsession();
    if(person.name!="" && person.id!="")
        session << "update Person set ID = ? WHERE Name= ?", use(person.id), use(person.name), now;
    if(person.name!="" && person.email!="")
        session << "update Person set Email = ? WHERE Name= ?", use(person.email), use(person.name), now;
    exit();
}

void MYSQL::select(Person person)
{
    init();
    Session session = getsession();
    Statement select(session);
    select << "SELECT Name, ID, Email FROM Person",
            into(person.name), into(person.id), into(person.email), range(0,1);
    while(!select.done())
    {
        select.execute();
    }
    exit();
}

void MYSQL::del(std::string name){
    init();
    Session session = getsession();
    Statement del(session);
    del << "DELETE FROM Person WHERE Name = ?", use(name), now;
    exit();
}

int MYSQL::display(struct Person person[])
{
    init();
    Session session = getsession();
    Statement select(session);

    typedef Poco::Tuple<std::string, std::string, std::string > _Person;
    typedef std::vector<_Person> People;
    People people;
    select << "SELECT Name, ID, Email FROM Person", into(people), now;

    int cnt = 0;
    for (People::const_iterator it = people.begin(); it != people.end(); ++it)
    {

        std::cout << "Name: " << it->get<0>() <<
            ", ID: " << it->get<1>() <<
            ", Email: " << it->get<2>() << std::endl;
        person[cnt].name = it->get<0>();
        person[cnt].id = it->get<1>();
        person[cnt++].email = it->get<2>();
    }
    exit();
    return cnt;
}
/*
    SessionPool pool("SQLite", "Sample.db");
    Session _session(pool.get());
*/
