#include "SqlOper.h"

#include "Poco/Data/SQLite/Connector.h"
#include "Poco/SharedPtr.h"
#include <vector>
#include <iostream>
#include <sstream>
#include <vector>

#include "BaseObj.h"

using std::string;
using std::stringstream;

using Poco::Data::SQLite::Connector;
using Poco::Data::Session;
using Poco::Data::SessionPool;
using Poco::SharedPtr;
using namespace Poco::Data::Keywords;

void Db::SqlOper::init(){
    Connector::registerConnector();
}

void Db::SqlOper::shutDown(){
    Connector::unregisterConnector();
}

Session Db::SqlOper::getSession(){
    return Session(Connector::KEY,"new.db");
}

string Db::SqlOper::intToString(int a){
    stringstream ss;
    ss<<a;
    string result = ss.str();
    return result;
}

string Db::SqlOper::createTable(table::BaseObj *base_ptr){
    init();
    Session ses = getSession();
    string result("");
    result = base_ptr->dropTableCmd(ses);
    result += base_ptr->createTableCmd(ses);
    shutDown();
    return result;
}

string Db::SqlOper::selectData(table::BaseObj *base_ptr){

    init();
    Session ses = getSession();
    string result("");
    result = base_ptr->selectCmd(ses);
    shutDown();
    return result;
}

string Db::SqlOper::insertData(table::BaseObj *base_ptr){
    init();
    Session ses = getSession();
    string result("");
    result = base_ptr->insertCmd(ses);
    shutDown();
    return result;
}

string Db::SqlOper::deleteData(table::BaseObj *base_ptr){
    init();
    Session ses = getSession();
    string result("");
    result = base_ptr->deleteCmd(ses);
    shutDown();
    return result;
}

string Db::SqlOper::updateData(table::BaseObj *base_ptr){
    init();
    Session ses = getSession();
    string result("");
    result = base_ptr->updateCmd(ses);
    shutDown();
    return result;
}






