#ifndef PROTOTOOLHELPER_H
#define PROTOTOOLHELPER_H
#include "Serialization.pb.h"
#include "ProductObj.h"
#include "BaseObj.h"
#include "Poco/SharedPtr.h"
#include "Poco/JSON/Object.h"

using std::string;
using tutorial::CmdData;
using Poco::SharedPtr;
using Poco::JSON::Object;

class ProtoToolHelper{
public:
    static CmdData StringToCmdData(const string);
    static string CmdDataToString(CmdData);
    static bool setCmdData(SharedPtr<table::BaseObj>, CmdData::CmdType,CmdData&,string);
    static bool setProductObj(SharedPtr<table::ProductObj>, CmdData&);
    static table::BaseObj *getBaseObj(CmdData);
    static CmdData jsonToCmdData(Object);
};

#endif // PROTOTOOLHELPER_H
