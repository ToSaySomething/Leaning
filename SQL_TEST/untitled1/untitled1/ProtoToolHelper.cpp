#include "ProtoToolHelper.h"
#include <typeinfo>
#include <exception>
#include <string>
#include <QDebug>
#include "Poco/SharedPtr.h"
#include "Poco/JSON/Object.h"
#include "ProductObj.h"
#include "BaseObj.h"
#include "Tool.h"
#include "Serialization.pb.h"

using std::string;
using std::exception;
using tutorial::CmdData;
using tutorial::CmdData_ProductObj;
using Poco::SharedPtr;
using Poco::JSON::Object;

CmdData ProtoToolHelper::StringToCmdData(const string ciphertext){
    CmdData cd;
    cd.ParseFromString(ciphertext);
    return cd;
}

string ProtoToolHelper::CmdDataToString(CmdData cd){
    string str = "";
    cd.SerializeToString(&str);
    return str;
}

bool ProtoToolHelper::setCmdData(SharedPtr<table::BaseObj> obj, CmdData::CmdType type, CmdData &cd, string class_name){
    cd.set_type(type);
    if(class_name.compare("ProductObj")==0){
        cd.set_name(CmdData::ProductObj_Name);
        if(!setProductObj(obj.cast<table::ProductObj>(),cd))
            return false;
        else return true;
    }
    else return false;
}

bool ProtoToolHelper::setProductObj(SharedPtr<table::ProductObj> p_obj, CmdData &cd){
    try{
        SharedPtr<CmdData_ProductObj> cd_pobj = new CmdData_ProductObj;
        cd_pobj.get()->set_id(p_obj.get()->getId());
        cd_pobj.get()->set_name(p_obj.get()->getName());
        cd_pobj.get()->set_tablename(p_obj.get()->getTableName());
        cd_pobj.get()->set_value(p_obj.get()->getValue());
        cd.set_allocated_product(cd_pobj);
    }catch(exception e){
        Tool::showMsgOnMainWindow(e.what());
        return false;
    }
    return true;
}


table::BaseObj *ProtoToolHelper::getBaseObj(CmdData cd){
    if(cd.name()==CmdData::ProductObj_Name){
        table::ProductObj *p = new table::ProductObj();
        p->setId(cd.product().id());
        p->setName(cd.product().name());
        p->setValue(cd.product().value());
        table::BaseObj *p1 = dynamic_cast<table::BaseObj*>(p);
//        qDebug()<<"id:"<<p.get()->getId()<<"\tname:"<<QString::fromStdString(p.get()->getName())
//               <<"\tvalue:"<<p.get()->getValue()<<"\n";
//        SharedPtr<table::ProductObj> p2 = dynamic_cast<table::ProductObj*>(p1.get());
//        qDebug()<<"id:"<<p2.get()->getId()<<"\tname:"<<QString::fromStdString(p2.get()->getName())
//               <<"\tvalue:"<<p2.get()->getValue()<<"\n";
        return p1;
    }
    else return NULL;
}


CmdData ProtoToolHelper::jsonToCmdData(Object obj){
    CmdData cd;
    CmdData::ObjName obj_Name = static_cast<CmdData::ObjName>(obj.get("ObjName").convert<int>());
    cd.set_name(obj_Name);
    CmdData::CmdType cmd_type = static_cast<CmdData::CmdType>(obj.get("CmdType").convert<int>());
    cd.set_type(cmd_type);

    CmdData_ProductObj *cd_pobj = new CmdData_ProductObj;
    string table_name = obj.get("tablename").toString();
    cd_pobj->set_tablename(table_name);
    int id = obj.get("id").convert<int>();
    cd_pobj->set_id(id);
    string name = obj.get("name").toString();
    cd_pobj->set_name(name);
    int value = obj.get("value").convert<int>();
    cd_pobj->set_value(value);

    cd.set_allocated_product(cd_pobj);
    return cd;
}












