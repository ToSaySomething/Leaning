#include "ProductObj.h"

#include <Poco/Data/SQLite/Connector.h>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "BaseObj.h"

using std::string;
using Poco::Data::SQLite::Connector;
using Poco::Data::Session;
using namespace Poco::Data::Keywords;

table::ProductObj::ProductObj(){
    this->table_name = "ProductObj";
}

table::ProductObj::ProductObj(int m_id,string m_name, int m_value){
    this->table_name = "ProductObj";
    this->id = m_id;
    this->name = m_name;
    this->value = m_value;
}

void table::ProductObj::setId(int m_id){
    this->id = m_id;
}

void table::ProductObj::setName(string m_name){
    this->name = m_name;
}

void table::ProductObj::setValue(int m_value){
    this->value = m_value;
}

int table::ProductObj::getId(){
    return this->id;
}

string table::ProductObj::getName(){
    return this->name;
}

int table::ProductObj::getValue(){
    return this->value;
}

string table::ProductObj::getTableName(){
    return this->table_name;
}

string table::ProductObj::selectCmd(Session ss){
    string result("");
    //define DataAll
    typedef Poco::Tuple<int,string,int>Data;
    typedef std::vector<Data> DataAll;
    DataAll buff;
    //execute this command
    ss<<"SELECT id, name, value FROM "+ this->table_name, into(buff), now;
    result+=printType();
    for(DataAll::const_iterator it = buff.begin();it!=buff.end();it++){

        result += (intToString(it->get<0>())+"\t"+
                   it->get<1>()+"\t"+
                   intToString(it->get<2>())+"\n"
                   );
    }
    return result;
}

string table::ProductObj::updateCmd(Session ss){
    string result("");
    ss<<"UPDATE " + this->table_name + " SET name = '" + this->name + "', value = '" + intToString(this->value) + "' WHERE id = '" + intToString(this->id) + "'", into(result), now;
    return result;
}

string table::ProductObj::deleteCmd(Session ss){
    string result("");
    ss<< "DELETE FROM " + this->table_name + " WHERE id = '" + intToString(this->id) + "'",  into(result), now;
    return result;
}

string table::ProductObj::insertCmd(Session ss){
    string result("");
    ss<<"INSERT INTO " + this->table_name + " VALUES('" + intToString(this->id) + "','" + this->name + "','" + intToString(this->value) + "')", into(result), now;
    return result;
}

string table::ProductObj::createTableCmd(Session ss){
    string result("");
    ss<<"CREATE TABLE " + this->table_name + "(id int(10), name char(20), value int(5));", into(result), now;
    return result;
}

string table::ProductObj::dropTableCmd(Session ss){
    string result("");
    ss<< "DROP TABLE IF EXISTS " + this->table_name,into(result),now;
    return result;
}

string table::ProductObj::printType(){
    return "ID\tNAME\tVALUE\n";
}
