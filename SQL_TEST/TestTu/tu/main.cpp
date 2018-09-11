#include "Poco/Data/Session.h"
#include "Poco/Data/SQLite/Connector.h"
#include <vector>
#include <iostream>
#include <sstream>
using namespace Poco::Data::Keywords;
using Poco::Data::Session;
using Poco::Data::Statement;
using Poco::Data::SQLite::Connector;

int main(int argc, char *argv[]){

    typedef Poco::Tuple<std::string, std::string, std::string> Person;
    typedef std::vector<Person> People;

    People people;
    people.push_back(Person("li", "zhen", "12"));
    people.push_back(Person("qi", "zhan", "16"));
    people.push_back(Person("xu", "zhong", "22"));

    Connector::registerConnector();
    Session ses("SQLite", "mysql.db");
    ses << "CREATE TABLE Person( Name char(20), Address char(20), age char(5) ) ", now;

    Statement ins(ses);
    ins << "INSERT INTO Person VALUES(?,?,?)", use(people), now;

    Statement sel(ses);
    sel << "SELECT Name, Address, Age FROM Person" ,into(people), now;
    for(People::const_iterator it = people.begin(); it!=people.end(); it++){
        std::cout << "Name: " << it->get<0>() <<
                     ", Address: " << it->get<1>() <<
                     ", Age: " << it->get<2>() <<std::endl;
    }

    return 0;
}
